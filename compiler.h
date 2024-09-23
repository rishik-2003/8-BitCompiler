#ifndef COMPILER_H
#define COMPILER_H

#include <string>
#include <vector>

struct Instruction {
    std::string opcode;
    std::string arg1;
    std::string arg2;
    std::string arg3;
};

#endif // COMPILER_H
