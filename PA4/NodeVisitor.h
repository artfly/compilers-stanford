//
// Created by Artemiy on 2/4/18.
//

#ifndef UNTITLED_NODEVISITOR_H
#define UNTITLED_NODEVISITOR_H

#include "TreeNode.h"

class Class;
class Program;
class Formal;
class Method;
class Attribute;
class Branch;
class Assign;
class Dispatch;
class StaticDispatch;
class Cond;
class Loop;
class TypCase;
class Block;
class Let;
class Plus;
class Sub;
class Mul;
class Divide;
class Neg;
class LessThan;
class Eq;
class LessOrEq;
class Complement;
class IntConst;
class BoolConst;
class StringConst;
class New;
class IsVoid;
class NoExpr;
class Object;

class NodeVisitor {
public:
    virtual ~NodeVisitor() = default;

    virtual void visit(const Program &program) const = 0;

    virtual void visit(const Class &cl) const = 0;

    virtual void visit(const Method &method) const = 0;

    virtual void visit(const Attribute &attribute) const = 0;

    virtual void visit(const Formal &formal) const = 0;

    virtual void visit(const Branch &branch) const = 0;

    virtual void visit(const Assign &assign) const = 0;

    virtual void visit(const Dispatch &dispatch) const = 0;

    virtual void visit(const StaticDispatch &dispatch) const = 0;

    virtual void visit(const Cond &cond) const = 0;

    virtual void visit(const Loop &loop) const = 0;

    virtual void visit(const TypCase &typ_case) const = 0;

    virtual void visit(const Block &block) const = 0;

    virtual void visit(const Let &let) const = 0;

    virtual void visit(const Plus &plus) const = 0;

    virtual void visit(const Sub &sub) const = 0;

    virtual void visit(const Mul &mul) const = 0;

    virtual void visit(const Divide &divide) const = 0;

    virtual void visit(const Neg &neg) const = 0;

    virtual void visit(const LessThan &less_than) const = 0;

    virtual void visit(const Eq &eq) const = 0;

    virtual void visit(const LessOrEq &less_or_eq) const = 0;

    virtual void visit(const Complement &complement) const = 0;

    virtual void visit(const IntConst &int_const) const = 0;

    virtual void visit(const BoolConst &bool_const) const = 0;

    virtual void visit(const StringConst &string_const) const = 0;

    virtual void visit(const New &new_expr) const = 0;

    virtual void visit(const IsVoid &is_void) const = 0;

    virtual void visit(const NoExpr &no_expr) const = 0;

    virtual void visit(const Object &object) const = 0;
};


#endif //UNTITLED_NODEVISITOR_H
