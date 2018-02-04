//
// Created by Artemiy on 2/1/18.
//

#ifndef FEATURE_H
#define FEATURE_H


#include <utility>
#include <vector>
#include "TreeNode.h"
#include "Expression.h"

class Feature : public TreeNode {
public:
    explicit Feature(int line_number = 0) : TreeNode(line_number) {}
};


class Formal : public TreeNode {
public:
    Formal(std::string name, std::string type_decl, int line_number = 0) :
            TreeNode(line_number), name(std::move(name)), type_decl(std::move(type_decl)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

    const std::string &get_type_decl() const {
        return type_decl;
    }

private:
    const std::string name;

    const std::string type_decl;
};


class Method : public Feature {
public:
    Method(std::string name, std::string return_type, std::vector<Formal> formals,
           const Expression &expr, int line_number = 0) :
            Feature(line_number), name(std::move(name)),
            return_type(std::move(return_type)), formals(std::move(formals)), expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

    const std::string &get_return_type() const {
        return return_type;
    }

    const std::vector<Formal> &get_formals() const {
        return formals;
    }

    const Expression &get_expr() const {
        return expr;
    }

private:
    const std::string name;

    const std::string return_type;

    const std::vector<Formal> formals;

    const Expression &expr;
};


class Attribute : public Feature {
public:
    Attribute(std::string name, std::string type_decl, const Expression &init, int line_number = 0) :
            Feature(line_number), name(std::move(name)), type_decl(std::move(type_decl)), init(init) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

    const std::string &get_type_decl() const {
        return type_decl;
    }

    const Expression &get_init() const {
        return init;
    }

private:
    const std::string name;

    const std::string type_decl;

    const Expression &init;
};

#endif //FEATURE_H
