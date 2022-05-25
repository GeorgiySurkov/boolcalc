#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <vector>
#include <cstring>
#include "formulaenode.h"
#include "errors.h"

class BooleanExpression {
    unsigned int truthTableSize;
    unsigned int N;
    bool *truthTable;
    bool *zhegalkinCoefficients;
    FormulaNode *root;

    FormulaNode *Postfix2Tree_(const char *);

    void Infix2Postfix_(const char *, char *);

    void InfixFilter_(const char *, char *);

    static const unsigned char ActionsTable[][7];

    static int ActionsRowNumber(char ch);

    static int ActionsColNumber(char ch);

    void fillWorkspace();

    void calcTruthTable();

    void calcJeg();

public:
    explicit BooleanExpression(const char *str = "");

    explicit BooleanExpression(FormulaNode *r);

    BooleanExpression(const BooleanExpression &other);

    BooleanExpression(BooleanExpression &&other) noexcept;

    BooleanExpression &operator=(const BooleanExpression &other);

    BooleanExpression &operator=(BooleanExpression &&other) noexcept;

    ~BooleanExpression();

    bool calc() const;

    void printTruthTable();

    [[nodiscard]] std::string str() const;

    explicit operator std::string() const;

    BooleanExpression dnf();

    BooleanExpression cnf();

    BooleanExpression zhegalkin();

    unsigned char getClassMask();

};

bool isFullSystem(std::vector<BooleanExpression> &);