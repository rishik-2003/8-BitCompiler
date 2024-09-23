#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

struct Instruction {
    std::string opcode;
    std::string arg1;
    std::string arg2;
    std::string arg3;
};

std::unordered_map<std::string, int> variables;
std::vector<Instruction> instructions;
int regCount = 0;

std::string getRegister() {
    return "R" + std::to_string(regCount++);
}

void emit(const std::string &opcode, const std::string &arg1, const std::string &arg2 = "", const std::string &arg3 = "") {
    instructions.push_back({opcode, arg1, arg2, arg3});
}

void compileAssignment(const std::string &var, int value) {
    std::string reg = getRegister();
    emit("MOV", reg, std::to_string(value));
    variables[var] = regCount - 1;
}

void compileExpression(const std::string &var, const std::string &lhs, const std::string &op, const std::string &rhs) {
    std::string regLhs = "R" + std::to_string(variables[lhs]);
    std::string regRhs = "R" + std::to_string(variables[rhs]);
    std::string resultReg = getRegister();

    if (op == "+") {
        emit("ADD", resultReg, regLhs, regRhs);
    } else if (op == "-") {
        emit("SUB", resultReg, regLhs, regRhs);
    } else if (op == "*") {
        emit("MUL", resultReg, regLhs, regRhs);
    } else if (op == "&") {
        emit("AND", resultReg, regLhs, regRhs);
    } else if (op == "|") {
        emit("OR", resultReg, regLhs, regRhs);
    }

    variables[var] = regCount - 1;
}

void compile(const std::vector<std::string> &source) {
    for (const auto &line : source) {
        if (line.find("let") != std::string::npos) {
            size_t equalPos = line.find("=");
            std::string var = line.substr(4, equalPos - 5);
            int value = std::stoi(line.substr(equalPos + 2));
            compileAssignment(var, value);
        } else if (line.find("=") != std::string::npos) {
            size_t equalPos = line.find("=");
            std::string var = line.substr(0, equalPos - 1);
            size_t opPos = line.find_first_of("+-*&|");
            std::string lhs = line.substr(equalPos + 2, opPos - equalPos - 3);
            std::string op = line.substr(opPos, 1);
            std::string rhs = line.substr(opPos + 2);
            compileExpression(var, lhs, op, rhs);
        }
    }
}

void printAssembly(std::ofstream &outputFile) {
    for (const auto &inst : instructions) {
        outputFile << inst.opcode << " " << inst.arg1;
        if (!inst.arg2.empty()) outputFile << ", " << inst.arg2;
        if (!inst.arg3.empty()) outputFile << ", " << inst.arg3;
        outputFile << std::endl;
    }
}

std::vector<std::string> readSource(const std::string &filename) {
    std::vector<std::string> source;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        source.push_back(line);
    }
    return source;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }
    std::string sourceFile = argv[1];
    std::vector<std::string> source = readSource(sourceFile);
    compile(source);

    std::ofstream outputFile("output.asm");
    printAssembly(outputFile);
    outputFile.close();

    return 0;
}
