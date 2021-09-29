#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace StringUtils {

    static inline std::string ltrim(const std::string &s) {
        std::string result = s;
        result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        return result;
    }

    static inline std::string rtrim(const std::string &s) {
        std::string result = s;
        result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), result.end());
        return result;
    }

    static inline std::string trim(const std::string &s) {
        std::string startTrim = ltrim(s);
        return rtrim(startTrim);
    }

    static std::string removeSuffix(const std::string & original, const std::string & suffix) {
        if (suffix.length() > original.length()) {
            return original;
        }

        char result[original.length() - suffix.length()];
        std::size_t length = original.copy(result, original.length() - suffix.length(), 0);
        result[length] = '\0';
        return result;
    }

    static std::string removePrefix(const std::string & original, const std::string & prefix) {
        if (prefix.length() > original.length()) {
            return original;
        }

        char result[original.length() - prefix.length()];
        std::size_t length = original.copy(result, original.length() - prefix.length(), prefix.length());
        result[length] = '\0';
        return result;
    }

    static bool startsWith(const std::string & original, const std::string & start) {
        if (start.length() > original.length()) {
            return false;
        }

        if (original == start) {
            return true;
        }

        int result = original.compare(0, start.length(), start);
        if (result == 0) {
            return true;
        }
        return false;
    }

    static bool endsWith(const std::string & original, const std::string & ending) {
        if (ending.length() > original.length()) {
            return false;
        }

        if (original == ending) {
            return true;
        }

        int result = original.compare(original.length() - ending.length(), ending.length(), ending);
        if (result == 0) {
            return true;
        }
        return false;
    }

    static std::vector<std::string> split(const std::string & line, const std::string & delimiter) {
        std::vector<std::string> values;
        std::string copiedLine = line;
        int position;

        std::string value;

        while ((position = copiedLine.find(delimiter)) != std::string::npos) {
            value = copiedLine.substr(0, position);
            values.emplace_back(value);
            copiedLine.erase(0, position + delimiter.length());
        }
        if (copiedLine.size() != 0) {
            values.emplace_back(copiedLine.substr(0, copiedLine.size()));
        }
        return values;
    }

    static std::vector<std::string> split(const std::string & line, char delimiter) {
        std::vector<std::string> values;
        std::string copiedLine = line;
        int position;

        std::string value;

        while ((position = copiedLine.find(delimiter)) != std::string::npos) {
            value = copiedLine.substr(0, position);
            values.emplace_back(value);
            copiedLine.erase(0, position + 1);
        }

        if (copiedLine.size() != 0) {
            values.emplace_back(copiedLine.substr(0, copiedLine.size()));
        }
        return values;
    }

};