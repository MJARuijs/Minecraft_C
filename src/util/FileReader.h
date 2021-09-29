#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class FileReader {

public:
    static std::string getContent(const std::string & fileName) {
        std::string content;
        std::string line;
        std::ifstream file(fileName, std::ios::in);

        if (file.is_open()) {
            while (getline(file, line)) {
                content += line + "\n";
            }
            file.close();
        }
        return content;
    }

    static std::vector<std::string> getLines(const std::string & fileName) {
        std::vector<std::string> lines;

        std::string line;
        std::ifstream file(fileName, std::ios::in);

        if (file.is_open()) {
            while (getline(file, line)) {
                lines.emplace_back(line);
            }
            file.close();
        }

        return lines;
    }
};
