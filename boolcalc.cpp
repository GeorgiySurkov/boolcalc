#include <fstream>
#include <iostream>
#include <vector>
#include "lib/cstring.h"
#include "boolexpr.h"

using std::vector;

vector<BooleanExpression> read_file(std::ifstream &file) {
    vector<BooleanExpression> expressions;
    char str[256];
    while (file.peek() != EOF) {
        file.getline(str, 256);
        expressions.emplace_back(str);
    }
    return expressions;
}

void printHelpMessage() {
    std::cout << "Boolcalc - simple boolean calculator.\n"
                 "    -h, ?                   - view this help message.\n"
                 "\n"
                 "    -calc input output      - calculate expression from input and\n"
                 "                              save result to output.\n"
                 "\n"
                 "    -cnf input output       - build сonjunctive normal form\n"
                 "                              and save result to output.\n"
                 "\n"
                 "    -dnf input output       - build disjunctive normal form\n"
                 "                              and save result to output.\n"
                 "\n"
                 "    -zh input output        - build Zhegalkin polynomial\n"
                 "                              and save result to output.\n"
                 "\n"
                 "    -table input            - print truth table for expressions\n"
                 "                              from input.\n"
                 "\n"
                 "    -isfull input output    - check if system of boolean expressions\n"
                 "                              is full and save result to output.\n"
                 "\n"
              << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Wrong commands" << std::endl;
        std::cerr << "Type 'boolcalc -h' for help message" << std::endl;
        return 1;
    }
    if (mstd::strcmp(argv[1], "-calc") == 0) {
        std::ifstream inFile(argv[2]);
        std::ofstream outFile(argv[3]);
        if (!inFile.is_open()) {
            std::cerr << "Can't open file " << argv[2] << std::endl;
            return 1;
        }
        if (!outFile.is_open()) {
            std::cerr << "Can't open file " << argv[3] << std::endl;
            return 1;
        }
        auto exprs = read_file(inFile);
        for (auto & expression : exprs) {
            outFile << expression.calc() << std::endl;
        }
    } else if (mstd::strcmp(argv[1], "-cnf") == 0) {
        std::ifstream inFile(argv[2]);
        std::ofstream outFile(argv[3]);
        if (!inFile.is_open()) {
            std::cerr << "Can't open file " << argv[2] << std::endl;
            return 1;
        }
        if (!outFile.is_open()) {
            std::cerr << "Can't open file " << argv[3] << std::endl;
            return 1;
        }
        auto exprs = read_file(inFile);
        for (auto & expression : exprs) {
            outFile << expression.cnf().str() << std::endl;
        }
    } else if (mstd::strcmp(argv[1], "-dnf") == 0) {
        std::ifstream inFile(argv[2]);
        std::ofstream outFile(argv[3]);
        if (!inFile.is_open()) {
            std::cerr << "Can't open file " << argv[2] << std::endl;
            return 1;
        }
        if (!outFile.is_open()) {
            std::cerr << "Can't open file " << argv[3] << std::endl;
            return 1;
        }
        auto exprs = read_file(inFile);
        for (auto & expression : exprs) {
            outFile << expression.dnf().str() << std::endl;
        }
    } else if (mstd::strcmp(argv[1], "-zh") == 0) {
        std::ifstream inFile(argv[2]);
        std::ofstream outFile(argv[3]);
        if (!inFile.is_open()) {
            std::cerr << "Can't open file " << argv[2] << std::endl;
            return 1;
        }
        if (!outFile.is_open()) {
            std::cerr << "Can't open file " << argv[3] << std::endl;
            return 1;
        }
        auto exprs = read_file(inFile);
        for (auto & expression : exprs) {
            outFile << expression.zhegalkin().str() << std::endl;
        }
    } else if (mstd::strcmp(argv[1], "-table") == 0) {
        std::ifstream inFile(argv[2]);
        if (!inFile.is_open()) {
            std::cerr << "Can't open file " << argv[2] << std::endl;
            return 1;
        }
        auto exprs = read_file(inFile);
        for (auto & expression : exprs) {
            expression.printTruthTable();
            std::cout << std::endl;
        }
    } else if (mstd::strcmp(argv[1], "-isfull") == 0) {
        std::ifstream inFile(argv[2]);
        std::ofstream outFile(argv[3]);
        if (!inFile.is_open()) {
            std::cerr << "Can't open file " << argv[2] << std::endl;
            return 1;
        }
        if (!outFile.is_open()) {
            std::cerr << "Can't open file " << argv[3] << std::endl;
            return 1;
        }
        auto exprs = read_file(inFile);
        if (isFullSystem(exprs)) {
            outFile << "yes";
        } else {
            outFile << "no";
        }
    } else if (mstd::strcmp(argv[1], "-h") == 0 || mstd::strcmp(argv[1], "?") == 0) {
        printHelpMessage();
    } else {
        std::cerr << "Unknown command" << argv[1] << std::endl;
        return 1;
    }
}
