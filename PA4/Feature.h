//
// Created by Artemiy on 2/1/18.
//

#ifndef FEATURE_H
#define FEATURE_H


#include <utility>
#include <vector>
#include "TreeNode.h"
#include "Expression.h"

class Feature : TreeNode {
};


class Formal : public TreeNode {
public:
    Formal(std::string name, std::string type_decl) : name(std::move(name)), type_decl(std::move(type_decl)) {}

private:
    std::string name;

    std::string type_decl;
};


class Method : public Feature {
public:
    // TODO: default values
    Method(std::string name, std::vector<Formal> formals, std::string return_type, const Expression &expr) :
            name(std::move(name)), return_type(std::move(return_type)), formals(std::move(formals)), expr(expr) {}

private:
    std::string name;

    std::string return_type;

    std::vector<Formal> formals;

    Expression expr;
};


class Attribute : public Feature {
public:
    Attribute(std::string name, std::string type_decl, const Expression &init) :
            name(std::move(name)), type_decl(std::move(type_decl)), init(init) {}

private:
    std::string name;

    std::string type_decl;

    Expression init;
};

#endif //FEATURE_H
