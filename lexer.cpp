#include "compiler.h"
#include <sstream>
#include <cctype>

std::vector<std::string> tokenize(const std::string &line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (ss >> token) {
        // Remove any trailing punctuation
        if (token.back() == ';' || token.back() == ',') {
            token.pop_back();
        }
        tokens.push_back(token);
    }
    return tokens;
}

void processLine(const std::string &line, std::vector<std::string> &output) {
    std::vector<std::string> tokens = tokenize(line);
    for (const auto &token : tokens) {
        output.push_back(token);
    }
}



void lex(const std::vector<std::string> &source, std::vector<std::string> &output) {
    for (const auto &line : source) {
        processLine(line, output);
    }
}
