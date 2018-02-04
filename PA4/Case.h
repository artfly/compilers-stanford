//
// Created by Artemiy on 2/2/18.
//

#ifndef CASE_H
#define CASE_H

#include "TreeNode.h"

class Expression;

class Case : public TreeNode {
public:
    explicit Case(int line_number = 0) : TreeNode(line_number) {}
};


class Branch : public Case {
public:
    Branch(std::string name, std::string type_decl, const Expression &expr, int line_number = 0) :
            Case(line_number), name(std::move(name)), type_decl(std::move(type_decl)), expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

    const std::string &get_type_decl() const {
        return type_decl;
    }

    const Expression &get_expr() const {
        return expr;
    }

private:
    const std::string name;

    const std::string type_decl;

    const Expression &expr;
};

#endif //CASE_H
