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

#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <string>
#include <deque>
#include <unordered_map>

/**
 * @brief Class for parse command line arguments
 */
class ArgsParser
{
public:
	ArgsParser() {}
	/**
	 * @brief Create class with arguments
	 * @detail The automatical parse arguments
	 */
	ArgsParser(int &argc, char **argv);
	/**
	 * @brief Create class with arguments
	 * @detail The automatical parse arguments
	 */
	ArgsParser(const std::deque<std::string> &args);
	
	/**
	 * @brief Add argument for parse
	 * @param arg Argument for parse
	 * @param reparse_now Reparse all arguments after add the argument
	 */
	void addUnparsedArg(const std::string &arg, const bool &reparse_now = false);
	/**
	 * @brief Add arguments for parse
	 * @param args Arguments for parse
	 * @param reparse_now Reparse all arguments after add the arguments
	 */
	void addUnparsedArgs(const std::deque<std::string> &args, const bool &reparse_now = true);
	
	/**
	 * @brief Parse all arguments
	 */
	void parse();
	
	/**
	 * @brief Check has argument is defined
	 * @param name long name of argument (--arg)
	 * @param shortName short name of argument (-a)
	 * @return has defined
	 */
	bool isDefined(const std::string &name, const std::string &shortName = "");
	/**
	 * @brief Get values for argument
	 * @param name long name of argument (--arg)
	 * @param shortName short name of argument (-a)
	 * @return list of values
	 */
	std::deque<std::string> values(const std::string &name, const std::string &shortName = "");
	/**
	 * @brief Get values which were transferred without arguments
	 * @return list of values
	 */
	std::deque<std::string> args();

private:
	std::deque<std::string> unparsed_args;
	std::unordered_map<std::string, bool> defined_args;
	std::unordered_map<std::string, std::deque<std::string>> parsed_args;
};

#endif // ARGSPARSER_H
