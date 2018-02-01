//
// Created by Artemiy on 2/1/18.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H


#include <utility>
#include <vector>
#include "TreeNode.h"
#include "Case.h"

class Expression : TreeNode {
};


class Assign : public Expression {
public:
    Assign(std::string name, const Expression &expr) : name(std::move(name)), expr(expr) {}

private:
    std::string name;

    Expression expr;
};


class Dispatch : public Expression {
public:
    Dispatch(const Expression &expr, std::string name, std::vector<Expression> actual) : expr(expr),
                                                                                         name(std::move(
                                                                                                 name)),
                                                                                         actual(std::move(
                                                                                                 actual)) {}

private:
    Expression expr;

    std::string name;

    std::vector<Expression> actual;
};


class StaticDispatch : public Expression {
public:
    StaticDispatch(const Expression &expr, std::string name, std::vector<Expression> actual,
                   std::string type_name) : expr(expr), name(std::move(name)), actual(std::move(actual)), type_name(
            std::move(type_name)) {}

private:
    Expression expr;

    std::string name;

    std::vector<Expression> actual;

    std::string type_name;

};


class Cond : public Expression {
public:
    Cond(const Expression &predicate, const Expression &then_expr, const Expression &if_expr) : predicate(predicate),
                                                                                                then_expr(then_expr),
                                                                                                if_expr(if_expr) {}

private:
    Expression predicate;

    Expression then_expr;

    Expression if_expr;
};


class Loop : public Expression {
public:
    Loop(const Expression &predicate, const Expression &body) : predicate(predicate), body(body) {}

private:
    Expression predicate;

    Expression body;
};

class TypCase : public Expression {
public:
    TypCase(const Expression &expr, std::vector<Case> cases) : expr(expr), cases(std::move(cases)) {}

private:
    Expression expr;

    std::vector<Case> cases;
};

class Block : public Expression {
public:
    explicit Block(const Expression &expr) : expr(expr) {}

private:
    Expression expr;
};

class Let : public Expression {
public:
    Let(std::string identifier, std::string type_decl, const Expression &init, const Expression &body)
            : identifier(std::move(identifier)), type_decl(std::move(type_decl)), init(init), body(body) {}

private:
    std::string identifier;

    std::string type_decl;

    Expression init;

    Expression body;
};


class Plus : public Expression {
public:
    Plus(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class Sub : public Expression {
public:
    Sub(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class Mul : public Expression {
public:
    Mul(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class Divide : public Expression {
public:
    Divide(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class Neg : public Expression {
public:
    explicit Neg(const Expression &expr) : expr(expr) {}

private:
    Expression expr;
};


class LessThan : public Expression {
public:
    LessThan(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class Eq : public Expression {
public:
    Eq(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class LessOrEq : public Expression {
public:
    LessOrEq(const Expression &e1, const Expression &e2) : e1(e1), e2(e2) {}

private:
    Expression e1;

    Expression e2;
};


class Complement : public Expression {
public:
    explicit Complement(const Expression &expr) : expr(expr) {}

private:
    Expression expr;
};


class IntConst : public Expression {
public:
    explicit IntConst(std::string token) : token(std::move(token)) {}

private:
    std::string token;
};


class BoolConst : Expression {
public:
    typedef int Boolean;

    explicit BoolConst(Boolean val) : val(val) {}

private:
    Boolean val;
};


class StringConst : public Expression {
public:
    explicit StringConst(std::string token) : token(std::move(token)) {}

private:
    std::string token;
};


class New : public Expression {
public:
    explicit New(std::string type_name) : type_name(std::move(type_name)) {}

private:
    std::string type_name;
};


class IsVoid : public Expression {
public:
    explicit IsVoid(const Expression &expr) : expr(expr) {}

private:
    Expression expr;
};


class NoExpr : public Expression {
};


class Object : public Expression {
public:
    explicit Object(std::string name) : name(std::move(name)) {}

private:
    std::string name;
};

#endif //EXPRESSION_H
