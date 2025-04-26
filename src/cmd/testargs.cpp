#include "utils/Arguments/Arguments.h"
#include <iostream>

/**
 * @brief Entry point for testing command-line argument parsing.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit code.
 */
int main(int argc, char *argv[]) {
    try {
        Arguments args(argc, argv);

        std::cout << "Parsed arguments:" << std::endl;
        for (const auto &pair : args.data) {
            std::cout << "  " << pair.first << " = " << pair.second << std::endl;
        }
    } catch (const Exceptions::MissingArguments &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
