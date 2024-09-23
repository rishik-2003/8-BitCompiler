#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <fstream>

void compile(const std::vector<std::string> &source);
void printAssembly(std::ofstream &outputFile);

#endif // PARSER_H
