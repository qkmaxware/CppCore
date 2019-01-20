#include "System.Cli.hpp"
#include "System.Os.hpp"
#include <sstream>
#include <map>

namespace System {
namespace Cli {

CliCommand::CliCommand() : args(), commands(), options(), actions(), name(), desc(), version() {}

CliCommand::CliCommand(std::string format) : args(), commands(), options(), actions(), name(), desc(), version() {
    std::stringstream buf(format);
    std::string word;
    while(buf){
        //Read word
        buf >> word;
        if(word.size() < 1)
            continue;
        //Check its type
        CliArgumentType type{CliArgumentType::LITERAL};
        if(word[0] == '<' && word[word.size() - 1] == '>') {
            type = CliArgumentType::REQUIRED;
            word.erase(0, 1);
            word.erase(word.size() - 1);
        } else if(word[0] == '[' && word[word.size() - 1] == ']') {
            type = CliArgumentType::OPTIONAL;
            word.erase(0, 1);
            word.erase(word.size() - 1);
        }
        this->args.push_back({
            word,
            type,
            "" //Default value
        });
    }
}

CliCommand& CliCommand::Version(const Semver& version) {
    this->version = version;
    return *this;
}

CliCommand& CliCommand::Name(const std::string& name) {
    this->name = name;
    return *this;
}

CliCommand& CliCommand::Description(const std::string& desc) {
    this->desc = desc;
    return *this;
}

CliCommand& CliCommand::Invoke(const System::Functional::Action& ref) {
    this->actions.push_back(ref);
    return *this;
}

CliCommand& CliCommand::Arg(const CliArgument& ref) {
    this->args.push_back(ref);
    return *this;
}

CliCommand& CliCommand::Option(const CliOption& ref)  {
    this->options.push_back(ref);
    return *this;
}

CliCommand& CliCommand::Option(char flag, std::string name, std::string desc, std::string def, std::regex validator) {
    this->options.push_back({
        flag,
        name,
        desc,
        def,
        validator,
        true
    });
    return *this;
}

CliCommand& CliCommand::Command(std::string format) {
    this->commands.push_back(Command(format));
    return this->commands.back();
}

CliCommand& CliCommand::Command(const CliCommand& cmd) {
    this->commands.push_back(cmd);
    return this->commands.back();
}

bool CliCommand::Parse(int argc, char** argv) {
    //Create vector string list
    std::vector<std::string> argList;
    for(int i=0;i<argc;i++)
        argList.push_back(argv[i]);
    //Parse
    return Parse(argList);
}

bool CliCommand::Parse(const std::vector<std::string>& argList) {
    //While indices are in range, parse provided options
    size_t i{0}, j{0};
    std::vector<CliArgument> args;
    while(i < this->args.size()) {
        if(i >= argList.size()) {
            //No provided arg
            if(this->args[i].type != CliArgumentType::OPTIONAL) {
                //Throw Error as required argument is missing TODO
                return false;
            } else {
                args.push_back(this->args[i]);
            }
        } else {
            //Arg provided
            CliArgument arg;
            arg.name = this->args[i].name;
            arg.type = this->args[i].type;
            arg.value = argList[i];
            j++;
            //if(!std::regex_match(arg.value,this->args[i].validator)) {
                //Throw Error, validator failed TODO
            //}
        }
        i++;
    }
    //Parse options in the form of -<flag>+ or --name=value
    std::string arg; 
    std::map<std::string, std::string> optsByName;
    std::map<char, std::string> optsByFlag;
    while(j < argList.size()) {
        arg = argList[j];
        //--name=value
        if(arg.size() > 2 && arg[0] == '-' && arg[1] == '-') {
            std::size_t loc = arg.find_first_of('=');
            if(loc != std::string::npos) {
                //=value found
                std::string optName = arg.substr(2, loc);
                std::string optValue = arg.substr(loc, arg.size());
                optsByName[optName] = optValue;
            } else {
                optsByName[arg.substr(2, arg.size())] = "";
            }
        } 
        //-f or -fgq 
        else if(arg.size() > 1 && arg[0] == '-') {
            //No value, use default
            for(std::string::const_iterator it = arg.begin() + 1; it < arg.end(); it++){
                optsByFlag[*it] = "";
            }
        }
        else {
            break;
        }
        j++;
    }
    //Coalesce options
    std::map<std::string, std::string> value;
    for(auto option : this->options) {
        std::map<std::string,std::string>::iterator nit = optsByName.find(option.name);
        if(nit != optsByName.end()){
            //Full name provided
            value[option.name] = optsByName[option.name];
            //Verify regex
            if(!std::regex_match(optsByName[option.name], option.validator)) {
                return false;
            }
            continue;
        }
        std::map<char,std::string>::iterator fit = optsByFlag.find(option.flag);
        if(fit != optsByFlag.end()){
            //Flag provided
            value[option.name] = optsByFlag[option.flag];
            //Verify regex
            if(!std::regex_match(optsByName[option.name], option.validator)) {
                return false;
            }
            continue;
        }
        //Nothing found, do default or break
        if(!option.optional) {
            return false;
        } else {
            value[option.name] = option.value;
            //Verify regex
            if(!std::regex_match(optsByName[option.name], option.validator)) {
                return false;
            }
        }
    }
    //If --help or -h is specified, show auto-generated help document and do not continue further
    if(value.find("help") != value.end()){
        this->PrintHelp(std::cout);
        return true;
    }
    //Parse sub-commands
    std::vector<std::string> subvector(argList.begin(), argList.begin() + j);
    bool b{false};
    for(auto command : this->commands) {
        b = command.Parse(subvector);
        if(b)
            break;
    }
    //Run through actions for this particular command and invoke them
    for(auto action : this->actions) {
        action();
    }
    return true;
}

void CliCommand::PrintHelp(std::ostream& stream) {
    //Version
    stream << "Version: " << this->version.major << "." << this->version.minor << "." << this->version.revision << System::Os::EOL;
    //Usage
    stream << "Usage: ";
    for(auto arg : this->args) {
        if (arg.type == CliArgumentType::LITERAL)
            stream << arg.name << " ";
        else if (arg.type == CliArgumentType::OPTIONAL)
            stream << "[" << arg.name << "] ";
        else if (arg.type == CliArgumentType::REQUIRED)
            stream << "<" << arg.name << "> ";
    }
    if(this->options.size() > 0)
        stream << "[options...] ";
    if(this->commands.size() > 0)
        stream << "[sub-command]";

    //Description
    stream << System::Os::EOL << System::Os::EOL;
    stream << this->desc;
    stream << System::Os::EOL << System::Os::EOL;

    //Options
    if(this->options.size() > 0) {
        stream << "Options:" << System::Os::EOL;
        for(auto opt : this->options) {
            stream << "\t-" << opt.flag << ", --" << opt.name << " " << opt.description;
            if(!opt.optional)
                stream << "(Required)";
            stream << System::Os::EOL;
        }
        stream << System::Os::EOL;
    }

    //Sub-commands
    if(this->commands.size() > 0) {
        stream << "Sub-commands:" << System::Os::EOL;
        for(auto cmd : this->commands) {
            stream << "\t" << cmd.name << " " << cmd.desc << System::Os::EOL;
        }
    }   
}

}
}