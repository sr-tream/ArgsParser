/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  SR_team <sr-tream@yandex.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ArgsParser.h"
#include <regex>

ArgsParser::ArgsParser(int &argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
		unparsed_args.push_back(argv[i]);
	parse();
}

ArgsParser::ArgsParser(const std::deque<std::string> &args)
{
	unparsed_args = args;
	parse();
}

void ArgsParser::addUnparsedArg(const std::string &arg, const bool &reparse_now)
{
	unparsed_args.push_back(arg);
	if (reparse_now)
		parse();
}

void ArgsParser::addUnparsedArgs(const std::deque<std::string> &args, const bool &reparse_now)
{
	for (auto &arg : args)
		unparsed_args.push_back(arg);
	if (reparse_now)
		parse();
}

void ArgsParser::parse()
{
	const std::regex reArg(R"(--?.+)");
	const std::regex reMultiArgs(R"(-(\w{2,}))");
	std::cmatch cap;
	
	defined_args.clear();
	parsed_args.clear();
	
	std::string active_arg = "";
	std::deque<std::string> active_args;
	for (auto &arg : unparsed_args){
		if (std::regex_match(arg.c_str(), cap, reArg)){
			for (auto &aarg : active_args)
				parsed_args[active_arg].push_back(aarg);
			if (std::regex_match(arg.c_str(), cap, reMultiArgs)){
				for (auto &ch : cap[1].str()){
					active_arg = std::string("-") + ch;
					defined_args[active_arg] = true;
				}
			} else {
				active_arg = arg;
				defined_args[active_arg] = true;
			}
			active_args.clear();
		} else
			active_args.push_back(arg);
	}
	for (auto &aarg : active_args)
		parsed_args[active_arg].push_back(aarg);
}

bool ArgsParser::isDefined(const std::string &name, const std::string &shortName)
{
	return defined_args["--" + name] || defined_args[std::string("-") + shortName[0]];
}

std::deque<std::string> ArgsParser::values(const std::string& name, const std::string &shortName)
{
	std::deque<std::string> result = parsed_args["--" + name];
	
	for (auto &arg : parsed_args[std::string("-") + shortName[0]])
		result.push_back(arg);
	
	return result;
}

std::deque<std::string> ArgsParser::args()
{
	return parsed_args[""];
}
