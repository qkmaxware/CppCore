#ifndef _SYSTEM_CLI_HPP
#define _SYSTEM_CLI_HPP

#include "System.Functional.hpp"
#include <iostream>
#include <regex>
#include <vector>

namespace System {
namespace Cli {

/**
 * A struct representing a semantic version in the form of "Major Version"."Minor Version"."Patch Number"
 */
struct Semver {
    /**
     * Major version number
     */ 
    int major = 0;
    /**
     * Minor version number
     */ 
    int minor = 0;
    /**
     * Patch or revision number
     */ 
    int revision = 0;

    /**
     * Compare if two semantic versions are equivalent 
     */
    bool operator== (const Semver& other) {
        return major == other.major && minor == other.minor && revision == other.revision;
    }
    /**
     * Compare if two semantic versions are not equivalent 
     */
    bool operator != (const Semver& other) {
        return major != other.major || minor != other.minor || revision != other.revision;
    }
    /**
     * Compare if one semantic version is less than another
     */
    bool operator < (const Semver& other) {
        return major < other.major
            || ( major == other.major && minor < other.minor)
            || ( major == other.major && minor == other.minor && revision < other.revision);
    }
    /**
     * Compare if one semantic version is greater than another
     */
    bool operator > (const Semver& other) {
        return major > other.major
            || ( major == other.major && minor > other.minor)
            || ( major == other.major && minor == other.minor && revision > other.revision);
    }
    /**
     * Compare if one semantic version is less than or equal to another
     */
    bool operator >= (const Semver& other) {
        return (*this > other) || (*this == other);
    }
    /**
     * Compare if one semantic version is greater than or equal to another
     */
    bool operator <= (const Semver& other){
        return (*this < other) || (*this == other);
    }
};

/**
 * Struct representing a command line option. 
 * Options have:
 * - a short flag which is specified by a single character on the command line eg: '-f'
 * - a long name which is specified by two dashes on the command line eg: '--name'
 * - a description that is used for auto-generated help
 * - a default value if the flag is not specified by the user
 * - a regular expression which is used to validate if an option's value is correct
 * - an optional specifier which allows for certain options to be required or not
 */ 
struct CliOption {
    /**
     * Single character to use as a command line flag for this option
     */
    char flag = 0;
    /**
     * Fully quantified name to use as a command line option
     */
    std::string name = "";
    /**
     * A description of what this option is suppose to do 
     */
    std::string description = "";
    /**
     * The default value of this option if not specified 
     */
    std::string value = "";
    /**
     * A regular expression used to validate if the value is allowed. Default value is [\s\S]* which matches everything. 
     */
    std::regex validator = std::regex("[\\s\\S]*");
    /**
     * Flag to specify if this option is required or not 
     */
    bool optional = true;
};

/**
 * Type specifier for command line positional arguments. 
 * Literal, required, or optional.
 */ 
enum struct CliArgumentType {
    LITERAL, REQUIRED, OPTIONAL
};

/**
 * Struct representing a command line positional argument.
 * Arguments have a name, a default value, and can be required or optional
 */ 
struct CliArgument {
    /**
     * Name of this command line positional argument 
     */
    std::string name = "";
    /**
     * The type of this command line positional argument
     */
    CliArgumentType type = CliArgumentType::LITERAL;
    /**
     * The default value of this command line positional argument 
     */
    std::string value = "";
};

/**
 * Class that represents a terminal (Cli) command. Cli commands can have positional arguments, options, and sub-commands.
 * When a CliCommand is determined to be the one a user wants than it can execute actions based on the provided arguments and options.
 * 
 * //Example use
 * System::Cli::CliCommand program;
 * program
 *		.Name("Hello World")
 *		.Description("An app that says Hello World")
 *		.Version({1,0,0});
 * program.Invoke([]() {
 *		std::cout << "Hello World" << std::endl;
 * });
 * program.Parse(argc, argv);
 */ 
class CliCommand {
    private:
        /**
         * List of all positional arguments for this command 
         */
        std::vector<CliArgument> args;
        /**
         * List of all sub-commands
         */
        std::vector<CliCommand> commands;
        /**
         * List of all options allowed for this command
         */
        std::vector<CliOption> options;
        /**
         * List of function pointers which are to be invoked if this command is chosen 
         */
        std::vector<System::Functional::Action> actions;
        /**
         * The name of this command 
         */
        std::string name;
        /**
         * The description of what this command does 
         */
        std::string desc;
        /**
         * The semantic version associated with this command 
         */
        Semver version;
                    
    public:
        /**
         * Default constructor 
         */
        CliCommand();
        /**
         * Create a command based off a formatted string. 
         * "command" represents a literal, "<arg>" represents a required argument, "[arg]" represents an optional argument.
         * example: run <file> [environment]
         */
        CliCommand(std::string format); //Strings like “pull <source> [file]” will match “pull x” or “pull x y”
        
        /**
         * Set the version number 
         */
        CliCommand& Version(const Semver& version);
        /**
         * Set the command name 
         */
        CliCommand& Name(const std::string& name);
        /**
         * Set the command description 
         */
        CliCommand& Description(const std::string& desc);
        /**
         * Add a function for this command to invoke 
         */
        CliCommand& Invoke(const System::Functional::Action& ref);
        /**
         * Add a positional argument to this command's format 
         */
        CliCommand& Arg(const CliArgument& ref); //Also handled by the CliCommand(string) constructor
        /**
         * Add a command line option
         */
        CliCommand& Option(const CliOption& ref);
        /**
         * Add a command line option
         */
        CliCommand& Option(char flag, std::string name, std::string desc = "", std::string def = "", std::regex validator = std::regex("[\\s\\S]*"));
        /**
         * Create a new sub-command with the given format
         */
        CliCommand& Command(std::string format);
        /**
         * Create a new sub-command from another
         */
        CliCommand& Command(const CliCommand& cmd);
        /**
         * Try to run the command with the given arguments.
         * @returns true if the command is successfully executed
         */
        bool Parse(int argc, char** argv);
        /**
         * Try to run the command with the given arguments 
         * @returns true if the command is successfully executed
         */
        bool Parse(const std::vector<std::string>& argList);
        /**
         * Print help message to an output stream (usually cout)
         * @param stream to print help information to 
         */
        void PrintHelp(std::ostream& stream);
};


}
}

#endif