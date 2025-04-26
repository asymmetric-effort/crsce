#include "utils/Arguments/Arguments.h"

Arguments::Arguments(int argc, char *argv[]){
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg.rfind("--", 0) == 0) { // starts with --
            std::string key = arg.substr(2);
            if (i + 1 < argc && std::string(argv[i + 1]).rfind("-", 0) != 0) {
                data[key] = argv[++i]; // next token is the value
            } else {
                data[key] = "true"; // no value, set true
            }
        } else if (arg.rfind("-", 0) == 0) { // starts with single -
            std::string key = arg.substr(1);
            if (i + 1 < argc && std::string(argv[i + 1]).rfind("-", 0) != 0) {
                data[key] = argv[++i]; // next token is the value
            } else {
                throw Exceptions::MissingArguments("Missing value for argument: -" + key);
            }
        } else {
            throw Exceptions::MissingArguments("Unexpected argument format: " + arg);
        }
    }

    if (data.empty()) {
        throw Exceptions::MissingArguments("No arguments found.");
    }
}
