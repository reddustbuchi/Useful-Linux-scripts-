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

import sys
import os
import re


class Options:
	def __init__(self, need_args, help_text, version_text):
		for name in need_args:
			if not re.fullmatch('(-[^-]|--[^=]+)', name):
				raise Exception('invalid option name "%s"' % name)

		self.excstk = False
		self.need_args = need_args
		self.help_text = help_text
		self.version_text = version_text


	def posixly_correct(self):  # pylint: disable=no-self-use
		return 'POSIXLY_CORRECT' in os.environ


	def needs_arg(self, name):
		return name in self.need_args


	def parse(self, name, _optarg):
		if name == '--excstk':
			self.excstk = True
		elif name == '--help' and self.help_text is not None:
			sys.stdout.write(self.help_text)
			sys.exit(0)
		elif name == '--version' and self.version_text is not None:
			sys.stdout.write(self.version_text)
			sys.exit(0)
		else:
			suffix = ' (taking an argument?)' if self.needs_arg(name) else ''
			suffix += ', try --help' if self.help_text is not None else ''
			raise Exception('unknown option "%s"%s' % (name, suffix))


def start(program_name, options, main_program):
	posixly_correct = 'POSIXLY_CORRECT' in os.environ

	try:
		if sys.hexversion < 0x3050000:
			raise Exception('python 3.5.0 or later required')

		nonopt = []
		optind = 1

		while optind < len(sys.argv):
			arg = sys.argv[optind]

			if posixly_correct and not arg.startswith('-'):
				break
			elif arg == '-' or not arg.startswith('-'):
				nonopt.append(arg)
			elif arg == '--':
				optind += 1
				break
			else:
				if not arg.startswith('--'):
					while True:
						name = arg[:2]
						optarg = arg[2:] if name != arg else None

						if options.needs_arg(name) or optarg is None:
							break

						options.parse(name, None)
						arg = '-' + optarg
				elif '=' in arg and arg.index('=') >= 3:
					name = arg.split('=', 1)[0]
					if not options.needs_arg(name):
						raise Exception('option "%s" does not take an argument' % name)
					optarg = arg[len(name) + 1:]
				else:
					name = arg
					optarg = None

				if optarg is None and int(options.needs_arg(name)) > 0:
					optind += 1
					if optind == len(sys.argv):
						raise Exception('option "%s" requires an argument' % name)
					optarg = sys.argv[optind]

				options.parse(name, optarg)

			optind += 1

		return main_program(nonopt + sys.argv[optind:], options)

	except Exception as ex:
		if options.excstk:
			raise
		else:
			sys.stderr.write('%s: %s\n' % (sys.argv[0] if sys.argv[0] else program_name, str(ex)))
			sys.exit(1)
