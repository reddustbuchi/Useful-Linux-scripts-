//
// Copyright (c) 2018 Dimitar Toshkov Zhekov <dimitar.zhekov@gmail.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

'use strict';

const fnutil = require('./fnutil.js');

// -- Width --
const WIDTH_MAX = 127;
const HEIGHT_MAX = 255;
const SWIDTH_MAX = 32000;

class Width {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}

	static _parse(name, value,  limitX, limitY) {
		const words = fnutil.splitWords(name, value, 2);

		return new Width(fnutil.parseDec(name + ' X', words[0], -limitX, limitX),
			fnutil.parseDec(name + ' Y', words[1], -limitY, limitY));
	}

	static parseS(value) {
		return Width._parse('SWIDTH', value, SWIDTH_MAX, SWIDTH_MAX);
	}

	static parseD(value) {
		return Width._parse('DWIDTH', value, WIDTH_MAX, HEIGHT_MAX);
	}
}

// -- BBX --
class BBX {
	constructor(width, height, xoff, yoff) {
		this.width = width;
		this.height = height;
		this.xoff = xoff;
		this.yoff = yoff;
	}

	static parse(name, value) {
		const words = fnutil.splitWords(name, value, 4);

		return new BBX(fnutil.parseDec('width', words[0], 1, WIDTH_MAX),
			fnutil.parseDec('height', words[1], 1, HEIGHT_MAX),
			fnutil.parseDec('bbxoff', words[2], -WIDTH_MAX, WIDTH_MAX),
			fnutil.parseDec('bbyoff', words[3], -WIDTH_MAX, WIDTH_MAX));
	}

	rowSize() {
		return (this.width + 7) >> 3;
	}

	toString() {
		return `${this.width} ${this.height} ${this.xoff} ${this.yoff}`;
	}
}

// -- Base --
class Base {
	constructor() {
		this.props = new Map();
		this.bbx = null;
	}

	setProp(line, name, callback) {
		if (line === null || !line.startsWith(name)) {
			throw new Error(name + ' expected');
		}

		let value = line.substring(name.length).trimLeft();

		this.props.set(name, value);
		return callback == null ? value : callback(name, value);
	}

	static skipComments(line) {
		return line.length === 0 || line.startsWith('COMMENT') ? null : line;
	}
}

// -- Char --
class Char extends Base {
	constructor() {
		super();
		this.code = -1;
		this.swidth = null;
		this.dwidth = null;
		this.data = null;
	}

	static bitmap(data, rowSize) {
		const bitmap = data.toString('hex').toUpperCase();
		const regex = new RegExp(`.{${rowSize << 1}}`, 'g');
		return bitmap.replace(regex, '$&\n');
	}

	_read(input) {
		// HEADER
		let readNext = () => input.readLines(Base.skipComments);

		this.setProp(readNext(), 'STARTCHAR');
		this.code = this.setProp(readNext(), 'ENCODING', fnutil.parseDec);
		this.swidth = this.setProp(readNext(), 'SWIDTH', (name, value) => Width.parseS(value));
		this.dwidth = this.setProp(readNext(), 'DWIDTH', (name, value) => Width.parseD(value));
		this.bbx = this.setProp(readNext(), 'BBX', BBX.parse);

		let line = readNext();

		if (line !== null && line.startsWith('ATTRIBUTES')) {
			this.setProp(line, 'ATTRIBUTES');
			line = readNext();
		}

		// BITMAP
		if (this.setProp(line, 'BITMAP') !== '') {
			throw new Error('BITMAP expected');
		}

		const rowLen = this.bbx.rowSize() * 2;
		let bitmap = '';

		for (let y = 0; y < this.bbx.height; y++) {
			line = readNext();

			if (line === null) {
				throw new Error('bitmap data expected');
			}
			if (line.length === rowLen) {
				bitmap += line;
			} else {
				throw new Error('invalid bitmap line length');
			}
		}

		// FINAL
		if (readNext() !== 'ENDCHAR') {
			throw new Error('ENDCHAR expected');
		}

		if (bitmap.match(/^[\dA-Fa-f]+$/) != null) {
			this.data = Buffer.from(bitmap, 'hex');
		} else {
			throw new Error('invalid BITMAP data characters');
		}
		return this;
	}

	static read(input) {
		return (new Char())._read(input);
	}

	write(ofs) {
		let header = '';

		this.props.forEach((value, name) => {
			header += (name + ' ' + value).trimRight() + '\n';
		});
		ofs.writeLine(header + Char.bitmap(this.data, this.bbx.rowSize()) + 'ENDCHAR');
	}
}

// -- XLFD --
const XLFD = {
	FOUNDRY:          1,
	FAMILY_NAME:      2,
	WEIGHT_NAME:      3,
	SLANT:            4,
	SETWIDTH_NAME:    5,
	ADD_STYLE_NAME:   6,
	PIXEL_SIZE:       7,
	POINT_SIZE:       8,
	RESOLUTION_X:     9,
	RESOLUTION_Y:     10,
	SPACING:          11,
	AVERAGE_WIDTH:    12,
	CHARSET_REGISTRY: 13,
	CHARSET_ENCODING: 14
};

// -- Font --
const CHARS_MAX = 65535;

class Font extends Base {
	constructor() {
		super();
		this.chars = [];
		this.defaultCode = -1;
	}

	checkBold(prefix, verb = 'will') {
		let weight = this.xlfd[XLFD.WEIGHT_NAME];
		let compare = weight.toLowerCase();
		let consider = ['Normal', 'Bold'][this.getBold()];

		if (compare === 'medium') {
			compare = 'normal';
		}
		if (compare !== consider.toLowerCase()) {
			fnutil.warning(prefix, `weight "${weight}" ${verb} be considered ${consider}`);
		}
	}

	checkItalic(prefix, verb = 'will') {
		let slant = this.xlfd[XLFD.SLANT];
		let consider = ['Regular', 'Italic'][this.getItalic()];

		if (slant.toUpperCase() !== consider.substring(0, 1).toUpperCase()) {
			fnutil.warning(prefix, `slant "${slant}" ${verb} be considered ${consider}`);
		}
	}

	getAscent() {
		let ascent = this.props.get('FONT_ASCENT');

		if (ascent != null) {
			return fnutil.parseDec('FONT_ASCENT', ascent, -HEIGHT_MAX, HEIGHT_MAX);
		}
		return this.bbx.height + this.bbx.yoff;
	}

	getBold() {
		return Number(this.xlfd[XLFD.WEIGHT_NAME].toLowerCase().includes('bold'));
	}

	getItalic() {
		return Number(this.xlfd[XLFD.SLANT].match(/[IO]/i) != null);
	}

	_read(input) {
		// HEADER
		const readNext = () => input.readLines(Base.skipComments);
		let line = input.readLine();

		if (this.setProp(line, 'STARTFONT') !== '2.1') {
			throw new Error('STARTFONT 2.1 expected');
		}
		this.xlfd = this.setProp(readNext(), 'FONT', (name, value) => value.split('-', 16));

		if (this.xlfd.length !== 15 || this.xlfd[0] !== '') {
			throw new Error('non-XLFD font names are not supported');
		}
		this.setProp(readNext(), 'SIZE');
		this.bbx = this.setProp(readNext(), 'FONTBOUNDINGBOX', (name, value) => BBX.parse(name, value));
		line = readNext();

		if (line !== null && line.startsWith('STARTPROPERTIES')) {
			const numProps = this.setProp(line, 'STARTPROPERTIES', (name, value) => fnutil.parseDec(name, value));
			let startIndex = this.props.size;

			for (let i = 0; i < numProps; i++) {
				line = readNext();

				if (line === null) {
					throw new Error('property expected');
				}

				let match = line.match(/^(\w+)\s+([\d"].*)$/);

				if (match == null) {
					throw new Error('invalid property format');
				}

				let name = match[1];
				let value = match[2];

				if (name === 'DEFAULT_CHAR') {
					this.defaultCode = fnutil.parseDec(name, value);
				}

				this.props.set(name, value);
			}

			if (this.setProp(readNext(), 'ENDPROPERTIES') !== '') {
				throw new Error('ENDPROPERTIES expected');
			}
			if (this.props.size !== startIndex + numProps + 1) {
				fnutil.warning(input.location(), 'duplicate properties');
				this.props.set('STARTPROPERTIES', this.props.size);
			}
			line = readNext();
		}

		// GLYPHS
		const numChars = this.setProp(line, 'CHARS', (name, value) => fnutil.parseDec(name, value, 1, CHARS_MAX));

		for (let i = 0; i < numChars; i++) {
			this.chars.push(Char.read(input));
		}

		if (this.defaultCode !== -1 && this.chars.find(char => char.code === this.defaultCode) === -1) {
			throw new Error('invalid DEFAULT_CHAR');
		}

		// ENDING
		if (readNext() !== 'ENDFONT') {
			throw new Error('ENDFONT expected');
		}
		if (readNext() != null) {
			throw new Error('garbage after ENDFONT');
		}
		return this;
	}

	static read(input) {
		return (new Font())._read(input);
	}

	write(ofs) {
		this.props.forEach((value, name) => ofs.writeProp(name, value));
		this.chars.forEach(char => char.write(ofs));
		ofs.writeLine('ENDFONT');
	}
}

// EXPORTS
module.exports = Object.freeze({
	WIDTH_MAX,
	HEIGHT_MAX,
	SWIDTH_MAX,
	Width,
	BBX,
	Char,
	XLFD,
	CHARS_MAX,
	Font
});
