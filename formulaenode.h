#pragma once

#include <string>
#include <iostream>
#include <cmath>
#include "errors.h"
#include "avltree.h"
#include "lib/avl_map.h"
#include "helpers.h"

namespace global {
    extern mstd::map<unsigned int, bool> Workspace;

    extern void nextArgumentsSet();
}

//------------------------------------------------------
// FormulaNode
//------------------------------------------------------
class FormulaNode {
public:
    [[nodiscard]] virtual bool calc() const = 0;

    virtual void fillWorkspace() const = 0;

    [[nodiscard]] virtual std::string str() const = 0;

    [[nodiscard]] virtual FormulaNode *clone() const = 0;

    virtual ~FormulaNode() = default;
};

//------------------------------------------------------
// NumNode
//------------------------------------------------------
class NumNode final : public FormulaNode {
    const bool num;
public:
    explicit NumNode(bool x) : num(x) {}

    [[nodiscard]] bool calc() const final { return num; }

    void fillWorkspace() const final {}

    [[nodiscard]] std::string str() const final {
        return std::to_string(num);
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new NumNode(num);
    }
};

//------------------------------------------------------
// BinNode
//------------------------------------------------------
class BinNode : public FormulaNode {
protected:
    FormulaNode *left, *right;
public:
    BinNode(FormulaNode *L, FormulaNode *R) : left(L), right(R) {}

    ~BinNode() override {
        delete left;
        delete right;
        left = right = nullptr;
    }

    void fillWorkspace() const override {
        left->fillWorkspace();
        right->fillWorkspace();
    }
};

//------------------------------------------------------
// ConjunctionNode
//------------------------------------------------------
class ConjunctionNode final : public BinNode {
public:
    ConjunctionNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final { return left->calc() && right->calc(); }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " & " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new ConjunctionNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// DisjunctionNode
//------------------------------------------------------
class DisjunctionNode final : public BinNode {
public:
    DisjunctionNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final { return left->calc() || right->calc(); }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " v " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new DisjunctionNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// ImplicationNode
//------------------------------------------------------
class ImplicationNode final : public BinNode {
public:
    ImplicationNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final { return !(left->calc()) || right->calc(); }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " > " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new ImplicationNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// ConverseImplicationNode
//------------------------------------------------------
class ConverseImplicationNode final : public BinNode {
public:
    ConverseImplicationNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final {
        return left->calc() || !(right->calc());
    }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " < " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new ConverseImplicationNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// ExclusiveOrNode
//------------------------------------------------------
class ExclusiveOrNode final : public BinNode {
public:
    ExclusiveOrNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final {
        return xor_(left->calc(), right->calc());
    }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " + " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new ExclusiveOrNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// BiconditionalNode
//------------------------------------------------------
class BiconditionalNode final : public BinNode {
public:
    BiconditionalNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final {
        return left->calc() == right->calc();
    }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " = " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new BiconditionalNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// ShefferStrokeNode
//------------------------------------------------------
class ShefferStrokeNode final : public BinNode {
public:
    ShefferStrokeNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final {
        bool l = left->calc(), r = right->calc();
        return !l || !r;
    }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " | " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new ShefferStrokeNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// PiercesArrowNode
//------------------------------------------------------
class PierceArrowNode final : public BinNode {
public:
    PierceArrowNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}

    [[nodiscard]] bool calc() const final {
        bool l = left->calc(), r = right->calc();
        return !l && !r;
    }

    [[nodiscard]] std::string str() const final {
        return "(" + left->str() + " ^ " + right->str() + ")";
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new PierceArrowNode(left->clone(), right->clone());
    }
};

//------------------------------------------------------
// ParamNode
//------------------------------------------------------
class ParamNode final : public FormulaNode {
    const unsigned int ch;
public:
    explicit ParamNode(unsigned int s) : ch(s) {}

    [[nodiscard]] bool calc() const final {
        auto pos = global::Workspace.find(ch);
        if (pos != global::Workspace.end()) {
            return pos->second;
        } else {
            bool tmp;
            std::cout << "x" << ch << " = ";
            std::cin >> tmp;
            std::cin.ignore();
            global::Workspace.insert({ch, tmp});
            return tmp;
        }
    }

    void fillWorkspace() const final {
        auto pos = global::Workspace.find(ch);
        if (pos == global::Workspace.end()) {
            global::Workspace.insert({ch, false});
        }
    }

    [[nodiscard]] std::string str() const final {
        return "x" + std::to_string(ch);
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new ParamNode(ch);
    }
};

//------------------------------------------------------
// UnaryNode
//------------------------------------------------------
class UnaryNode : public FormulaNode {
protected:
    FormulaNode *next;
public:
    explicit UnaryNode(FormulaNode *node) : next(node) {}

    ~UnaryNode() override {
        delete next;
        next = nullptr;
    }

    void fillWorkspace() const override {
        next->fillWorkspace();
    }
};

//------------------------------------------------------
// NegationNode
//------------------------------------------------------
class NegationNode final : public UnaryNode {
public:
    explicit NegationNode(FormulaNode *node) : UnaryNode(node) {}

    [[nodiscard]] bool calc() const final { return !next->calc(); }

    [[nodiscard]] std::string str() const final {
        return "~" + next->str();
    }

    [[nodiscard]] FormulaNode *clone() const final {
        return new NegationNode(next->clone());
    }
};
