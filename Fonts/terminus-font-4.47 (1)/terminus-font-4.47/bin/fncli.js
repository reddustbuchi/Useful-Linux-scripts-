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

// -- Options --
class Options {
	constructor(needArgs, helpText, versionText) {
		needArgs.forEach(name => {
			if (!name.match(/^(-[^-]|--[^=]+)$/)) {
				throw new Error(`invalid option name "${name}"`);
			}
		});
		this.excstk = false;
		this.needArgs = needArgs;
		this.helpText = helpText;
		this.versionText = versionText;
	}

	process(args, nonopt) {
		const POSIXLY_CORRECT = this.posixlyCorrect();
		let optind;

		for (optind = 0; optind < args.length; optind++) {
			let arg = args[optind];

			if (POSIXLY_CORRECT && !arg.startsWith('-')) {
				break;
			} else if (arg === '-' || !arg.startsWith('-')) {
				nonopt.push(arg);
			} else if (arg === '--') {
				optind++;
				break;
			} else {
				let name, optarg;

				if (!arg.startsWith('--')) {
					for (;;) {
						name = arg.substring(0, 2);
						optarg = name !== arg ? arg.substring(2) : null;

						if (this.needsArg(name) || optarg == null) {
							break;
						}
						this.parse(name, null);
						arg = '-' + optarg;
					}
				} else if (arg.indexOf('=') >= 3) {
					name = arg.split('=', 1)[0];
					if (!this.needsArg(name)) {
						throw new Error(`option "${name}" does not take an argument`);
					}
					optarg = arg.substring(name.length + 1);
				} else {
					name = arg;
					optarg = null;
				}

				if (optarg === null && Number(this.needsArg(name)) > 0) {
					if (++optind === args.length) {
						throw new Error(`option "${name}" requires an argument`);
					}
					optarg = args[optind];
				}
				this.parse(name, optarg);
			}
		}

		nonopt.concat(process.argv.slice(optind));
	}

	posixlyCorrect() {  // eslint-disable-line class-methods-use-this
		return process.env['POSIXLY_CORRECT'] != null;
	}

	needsArg(name) {
		return this.needArgs.includes(name);
	}

	parse(name) {
		if (name === '--excstk') {
			this.excstk = true;
		} else if (name === '--help' && this.helpText != null) {
			process.stdout.write(this.helpText);
			process.exit(0);
		} else if (name === '--version' && this.versionText != null) {
			process.stdout.write(this.versionText);
			process.exit(0);
		} else {
			let suffix = this.needsArg(name) ? ' (taking an argument?)' : '';

			suffix += (this.helpText != null) ? ', try --help' : '';
			throw new Error(`unknown option "${name}"${suffix}`);
		}
	}
}

// -- START --
function start(programName, options, mainProgram) {  // eslint-disable-line consistent-return
	try {
		const version = process.version.match(/^v?(\d)+\.(\d+)/);

		if (version.length < 3) {
			throw new Error('unable to obtain node version');
		} else if ((parseInt(version[1]) * 1000 + parseInt(version[2])) < 6009) {
			throw new Error('node version 6.9.0 or later required');
		}

		var nonopt = [];

		options.process(process.argv.slice(2), nonopt);
		return mainProgram(nonopt, options.params);  // params variable or property
	} catch (e) {
		if (options.excstk) {
			throw e;
		} else {
			process.stderr.write(`${process.argv.length >= 2 ? process.argv[1] : programName}: ${e.message}\n`);
			process.exit(1);
		}
	}
}

// EXPORTS
module.exports = Object.freeze({
	Options,
	start
});
