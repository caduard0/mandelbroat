#include <fstream>

#include "Utils.h"

std::string ReadFile(const char* path)
{
    std::string output;

    std::ifstream stream(path);

    if (stream.is_open()) {
        std::string line;
        while (getline(stream, line)) {
            output.append(line);
            output.append("\n");
        }

        stream.close();
    }

    return output;
}