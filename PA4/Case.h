//
// Created by Artemiy on 2/2/18.
//

#ifndef CASE_H
#define CASE_H

#include <utility>

#include "TreeNode.h"
#include "Expression.h"

class Expression;

class Case : TreeNode {
};


class Branch : Case {
public:
    Branch(std::string name, std::string type_decl, Expression &expr) : name(std::move(name)),
                                                                        type_decl(std::move(type_decl)),
                                                                        expr(expr) {}

private:
    std::string name;

    std::string type_decl;

    Expression &expr;
};

#endif //CASE_H
