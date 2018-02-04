//
// Created by Artemiy on 2/1/18.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "NodeVisitor.h"
#include "Case.h"

class Expression : public TreeNode {
public:
    explicit Expression(int line_number = 0) : TreeNode(line_number) {}
};


class Assign : public Expression {
public:
    Assign(std::string name, const Expression &expr, int line_number = 0) : Expression(line_number),
                                                                        name(std::move(name)),
                                                                        expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

    const Expression &get_expr() const {
        return expr;
    }

private:
    const std::string name;

    const Expression &expr;
};


class Dispatch : public Expression {
public:

    Dispatch(const Expression &expr, std::string name, const std::vector<Expression *> &actual, int line_number = 0) :
            Expression(line_number), expr(expr), name(std::move(name)), actual(actual) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }

    const std::string &get_name() const {
        return name;
    }

    const std::vector<Expression *> &get_actual() const {
        return actual;
    }

private:
    const Expression &expr;

    const std::string name;

    const std::vector<Expression *> actual;
};


class StaticDispatch : public Expression {
public:
    StaticDispatch(const Expression &expr, std::string name, const std::vector<Expression *> &actual,
                   std::string type_name, int line_number = 0) :
            Expression(line_number), expr(expr), name(std::move(name)),
            actual(actual), type_name(std::move(type_name)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }

    const std::string &get_name() const {
        return name;
    }

    const std::vector<Expression *> &get_actual() const {
        return actual;
    }

    const std::string &get_type_name() const {
        return type_name;
    }

private:
    const Expression &expr;

    const std::string name;

    const std::vector<Expression *> actual;

    const std::string type_name;

};


class Cond : public Expression {
public:
    Cond(const Expression &predicate, const Expression &then_expr, const Expression &if_expr, int line_number = 0) :
            Expression(line_number), predicate(predicate), then_expr(then_expr), if_expr(if_expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_predicate() const {
        return predicate;
    }

    const Expression &get_then_expr() const {
        return then_expr;
    }

    const Expression &get_if_expr() const {
        return if_expr;
    }

private:
    const Expression &predicate;

    const Expression &then_expr;

    const Expression &if_expr;
};


class Loop : public Expression {
public:
    Loop(const Expression &predicate, const Expression &body, int line_number = 0) : Expression(line_number),
                                                                                     predicate(predicate),
                                                                                     body(body) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_predicate() const {
        return predicate;
    }

    const Expression &get_body() const {
        return body;
    }

private:
    const Expression &predicate;

    const Expression &body;
};

class TypCase : public Expression {
public:
    TypCase(const Expression &expr, const std::vector<Case *> &cases, int line_number = 0) : Expression(line_number),
                                                                                             expr(expr),
                                                                                             cases(cases) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }

    const std::vector<Case *> &get_cases() const {
        return cases;
    }

private:
    const Expression &expr;

    const std::vector<Case *> &cases;
};

class Block : public Expression {
public:
    explicit Block(const Expression &expr, int line_number = 0) : Expression(line_number), expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }
private:
    const Expression &expr;
};

class Let : public Expression {
public:
    Let(std::string identifier, std::string type_decl, const Expression &init,
        const Expression &body, int line_number = 0) :
            Expression(line_number), identifier(std::move(identifier)),
            type_decl(std::move(type_decl)), init(init), body(body) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_identifier() const {
        return identifier;
    }

    const std::string &get_type_decl() const {
        return type_decl;
    }

    const Expression &get_init() const {
        return init;
    }

    const Expression &get_body() const {
        return body;
    }

private:
    const std::string identifier;

    const std::string type_decl;

    const Expression &init;

    const Expression &body;
};


class Plus : public Expression {
public:
    Plus(const Expression &addend, const Expression &augend, int line_number = 0) : Expression(line_number),
                                                                                addend(addend),
                                                                                augend(augend) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_addend() const {
        return addend;
    }

    const Expression &get_augend() const {
        return augend;
    }

private:
    const Expression &addend;

    const Expression &augend;
};


class Sub : public Expression {
public:
    Sub(const Expression &minuend, const Expression &subtrahend, int line_number = 0) : Expression(line_number),
                                                                                        minuend(minuend),
                                                                                        subtrahend(subtrahend) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_minuend() const {
        return minuend;
    }

    const Expression &get_subtrahend() const {
        return subtrahend;
    }

private:
    const Expression &minuend;

    const Expression &subtrahend;
};


class Mul : public Expression {
public:

    Mul(const Expression &multiplier, const Expression &multiplicand, int line_number = 0) : Expression(line_number),
                                                                                             multiplier(multiplier),
                                                                                             multiplicand(multiplicand) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_multiplier() const {
        return multiplier;
    }

    const Expression &get_multiplicand() const {
        return multiplicand;
    }

private:
    const Expression &multiplier;

    const Expression &multiplicand;
};


class Divide : public Expression {
public:
    Divide(const Expression &dividend, const Expression &divisor, int line_number = 0) : Expression(line_number),
                                                                                         dividend(dividend),
                                                                                         divisor(divisor) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_dividend() const {
        return dividend;
    }

    const Expression &get_divisor() const {
        return divisor;
    }

private:
    const Expression &dividend;

    const Expression &divisor;
};


class Neg : public Expression {
public:
    explicit Neg(const Expression &expr, int line_number = 0) : Expression(line_number), expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }

private:
    const Expression &expr;
};


class LessThan : public Expression {
public:
    LessThan(const Expression &e1, const Expression &e2, int line_number = 0) : Expression(line_number),
                                                                                e1(e1),
                                                                                e2(e2) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_e1() const {
        return e1;
    }

    const Expression &get_e2() const {
        return e2;
    }

private:
    const Expression &e1;

    const Expression &e2;
};


class Eq : public Expression {
public:
    Eq(const Expression &e1, const Expression &e2, int line_number = 0) : Expression(line_number), e1(e1), e2(e2) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_e1() const {
        return e1;
    }

    const Expression &get_e2() const {
        return e2;
    }

private:
    const Expression &e1;

    const Expression &e2;
};


class LessOrEq : public Expression {
public:
    LessOrEq(const Expression &e1, const Expression &e2, int line_number = 0) : Expression(line_number),
                                                                                e1(e1), e2(e2) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_e1() const {
        return e1;
    }

    const Expression &get_e2() const {
        return e2;
    }

private:
    const Expression &e1;

    const Expression &e2;
};


class Complement : public Expression {
public:
    explicit Complement(const Expression &expr, int line_number = 0) : Expression(line_number), expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }

private:
    const Expression &expr;
};


class IntConst : public Expression {
public:
    explicit IntConst(std::string token, int line_number = 0) : Expression(line_number), token(std::move(token)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_token() const {
        return token;
    }

private:
    const std::string token;
};


class BoolConst : Expression {
public:
    typedef int Boolean;

    explicit BoolConst(const Boolean val, int line_number = 0) : Expression(line_number), val(val) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Boolean get_val() const {
        return val;
    }

private:
    const Boolean val;
};


class StringConst : public Expression {
public:
    explicit StringConst(std::string token, int line_number = 0) : Expression(line_number), token(std::move(token)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_token() const {
        return token;
    }

private:
    const std::string token;
};


class New : public Expression {
public:
    explicit New(std::string type_name, int line_number = 0) : Expression(line_number), type_name(std::move(type_name)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_type_name() const {
        return type_name;
    }

private:
    const std::string type_name;
};


class IsVoid : public Expression {
public:
    explicit IsVoid(const Expression &expr, int line_number = 0) : Expression(line_number), expr(expr) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const Expression &get_expr() const {
        return expr;
    }

private:
    const Expression &expr;
};


class NoExpr : public Expression {
public:
    explicit NoExpr(int line_number = 0) : Expression(line_number) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }
};


class Object : public Expression {
public:
    explicit Object(std::string name, int line_number = 0) : Expression(line_number), name(std::move(name)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

private:
    const std::string name;
};

#endif //EXPRESSION_H
