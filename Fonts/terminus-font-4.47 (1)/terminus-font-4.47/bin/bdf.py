#
# Copyright (c) 2018 Dimitar Toshkov Zhekov <dimitar.zhekov@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

import re
import codecs
from collections import OrderedDict
from enum import IntEnum, unique

import fnutil

# -- Width --
WIDTH_MAX = 127
HEIGHT_MAX = 255
SWIDTH_MAX = 32000

class Width:
	def __init__(self, x, y):
		self.x = x
		self.y = y


	@staticmethod
	def _parse(name, value, limit_x, limit_y):
		words = fnutil.split_words(name, value, 2)
		return Width(fnutil.parse_dec('width x', words[0], -limit_x, limit_x),
			fnutil.parse_dec('width y', words[1], -limit_y, limit_y))


	@staticmethod
	def parse_s(value):
		return Width._parse('SWIDTH', value, SWIDTH_MAX, SWIDTH_MAX)


	@staticmethod
	def parse_d(value):
		return Width._parse('DWIDTH', value, WIDTH_MAX, HEIGHT_MAX)


# -- BBX --
OFFSET_MIN = -128
OFFSET_MAX = 127

class BBX:
	def __init__(self, width, height, xoff, yoff):
		self.width = width
		self.height = height
		self.xoff = xoff
		self.yoff = yoff


	@staticmethod
	def parse(name, value):
		words = fnutil.split_words(name, value, 4)
		return BBX(fnutil.parse_dec('width', words[0], 1, WIDTH_MAX),
			fnutil.parse_dec('height', words[1], 1, HEIGHT_MAX),
			fnutil.parse_dec('bbxoff', words[2], -WIDTH_MAX, WIDTH_MAX),
			fnutil.parse_dec('bbyoff', words[3], -WIDTH_MAX, WIDTH_MAX))


	def row_size(self):
		return (self.width + 7) >> 3


	def __str__(self):
		return '%d %d %d %d' % (self.width, self.height, self.xoff, self.yoff)


# -- Base --
class _Base:
	def __init__(self):
		self.props = OrderedDict()
		self.bbx = None


	def set_prop(self, line, name, callback=None):
		if not line or not line.startswith(bytes(name, 'ascii')):
			raise Exception(name + ' expected')

		value = line[len(name):].lstrip()
		self.props[name] = value
		return value if callback is None else callback(name, value)


	@staticmethod
	def skip_comments(line):
		return None if not line or line[:7] == b'COMMENT' else line


# -- Char --
class Char(_Base):
	def __init__(self):
		_Base.__init__(self)
		self.code = -1
		self.swidth = None
		self.dwidth = None
		self.data = None


	@staticmethod
	def bitmap(data, row_size):
		bitmap = ''

		for index in range(0, len(data), row_size):
			bitmap += data[index:index + row_size].hex() + '\n'

		return bytes(bitmap, 'ascii').upper()


	def _read(self, input):
		# HEADER
		read_next = lambda: input.read_lines(_Base.skip_comments)

		self.set_prop(read_next(), 'STARTCHAR')
		self.code = self.set_prop(read_next(), 'ENCODING', fnutil.parse_dec)
		self.swidth = self.set_prop(read_next(), 'SWIDTH', lambda _, value: Width.parse_s(value))
		self.dwidth = self.set_prop(read_next(), 'DWIDTH', lambda _, value: Width.parse_d(value))
		self.bbx = self.set_prop(read_next(), 'BBX', BBX.parse)
		line = read_next()

		if line and line.startswith(b'ATTRIBUTES'):
			self.set_prop(line, 'ATTRIBUTES')
			line = read_next()

		# BITMAP
		if self.set_prop(line, 'BITMAP') != b'':
			raise Exception('BITMAP expected')

		row_len = self.bbx.row_size() * 2
		bitmap = b''

		for _ in range(0, self.bbx.height):
			line = read_next()

			if not line:
				raise Exception('bitmap data expected')

			if len(line) == row_len:
				bitmap += line
			else:
				raise Exception('invalid bitmap length')

		# FINAL
		if read_next() != b'ENDCHAR':
			raise Exception('ENDCHAR expected')

		self.data = codecs.decode(bitmap, 'hex')  # no spaces allowed
		return self


	@staticmethod
	def read(input):
		return Char()._read(input)  # pylint: disable=protected-access


	def write(self, ofs):
		for name, value in self.props.items():
			ofs.write_line((bytes(name, 'ascii') + b' ' + value).rstrip())

		ofs.write_line(Char.bitmap(self.data, self.bbx.row_size()) + b'ENDCHAR')


# -- XLFD --
@unique
class XLFD(IntEnum):
	FOUNDRY = 1
	FAMILY_NAME = 2
	WEIGHT_NAME = 3
	SLANT = 4
	SETWIDTH_NAME = 5
	ADD_STYLE_NAME = 6
	PIXEL_SIZE = 7
	POINT_SIZE = 8
	RESOLUTION_X = 9
	RESOLUTION_Y = 10
	SPACING = 11
	AVERAGE_WIDTH = 12
	CHARSET_REGISTRY = 13
	CHARSET_ENCODING = 14


# -- Font --
CHARS_MAX = 65535

class Font(_Base):
	def __init__(self):
		_Base.__init__(self)
		self.xlfd = []
		self.chars = []
		self.default_code = -1


	def check_bold(self, prefix, verb='will'):
		weight = str(self.xlfd[XLFD.WEIGHT_NAME], 'ascii')
		compare = weight.lower()
		consider = ['Normal', 'Bold'][self.get_bold()]

		if compare == 'medium':
			compare = 'normal'

		if compare != consider.lower():
			fnutil.warning(prefix, 'weight "%s" %s be considered %s' % (weight, verb, consider))


	def check_italic(self, prefix, verb='will'):
		slant = str(self.xlfd[XLFD.SLANT], 'ascii')
		consider = ['Regular', 'Italic'][self.get_italic()]

		if slant[:1].upper() != consider[:1].upper():
			fnutil.warning(prefix, 'slant "%s" %s be considered %s' % (slant, verb, consider))


	def get_ascent(self):
		try:
			return fnutil.parse_dec('FONT_ASCENT', self.props['FONT_ASCENT'], -HEIGHT_MAX, HEIGHT_MAX)
		except KeyError:
			return self.bbx.height + self.bbx.yoff


	def get_bold(self):
		return b'bold' in self.xlfd[XLFD.WEIGHT_NAME].lower()


	def get_italic(self):
		return int(re.search(b'[IO]', self.xlfd[XLFD.SLANT], re.IGNORECASE) is not None)


	def _read(self, input):
		# HEADER
		line = input.read_line()
		read_next = lambda: input.read_lines(_Base.skip_comments)

		if self.set_prop(line, 'STARTFONT') != b'2.1':
			raise Exception('STARTFONT 2.1 expected')

		self.xlfd = self.set_prop(read_next(), 'FONT', lambda name, value: value.split(b'-', 15))

		if len(self.xlfd) != 15 or self.xlfd[0] != b'':
			raise Exception('non-XLFD font names are not supported')

		self.set_prop(read_next(), 'SIZE')
		self.bbx = self.set_prop(read_next(), 'FONTBOUNDINGBOX', lambda name, value: BBX.parse(name, value))
		line = read_next()

		if line and line.startswith(b'STARTPROPERTIES'):
			num_props = self.set_prop(line, 'STARTPROPERTIES', lambda name, value: fnutil.parse_dec(name, value))
			start_index = len(self.props)

			for _ in range(0, num_props):
				line = read_next()

				if not line:
					raise Exception('property expected')

				match = re.fullmatch(br'(\w+)\s+([\d"].*)', line)

				if not match:
					raise Exception('invalid property format')

				name = str(match.group(1), 'ascii')
				value = match.group(2)

				if name == 'DEFAULT_CHAR':
					self.default_code = fnutil.parse_dec(name, value)

				self.props[name] = value

			if self.set_prop(read_next(), 'ENDPROPERTIES') != b'':
				raise Exception('ENDPROPERTIES expected')

			if len(self.props) != start_index + num_props + 1:
				fnutil.warning(input.location(), 'duplicate properties')
				self.props['STARTPROPERTIES'] = bytes(str(len(self.props)), 'ascii')

			line = read_next()

		# GLYPHS
		num_chars = self.set_prop(line, 'CHARS', lambda name, value: fnutil.parse_dec(name, value, 1, CHARS_MAX))

		for _ in range(0, num_chars):
			self.chars.append(Char.read(input))

		if next((char.code for char in self.chars if char.code == self.default_code), -1) != self.default_code:
			raise Exception('invalid DEFAULT_CHAR')

		# ENDING
		if read_next() != b'ENDFONT':
			raise Exception('ENDFONT expected')

		if read_next():
			raise Exception('garbage after ENDFONT')

		return self


	@staticmethod
	def read(input):
		return Font()._read(input)  # pylint: disable=protected-access


	def write(self, ofs):
		for name, value in self.props.items():
			ofs.write_line((bytes(name, 'ascii') + b' ' + value).rstrip())

		for char in self.chars:
			char.write(ofs)

		ofs.write_line(b'ENDFONT')
