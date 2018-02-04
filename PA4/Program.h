//
// Created by Artemiy on 2/2/18.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include <utility>
#include <vector>
#include <ostream>
#include "NodeVisitor.h"

class Class;

class Program : public TreeNode {
public:
    explicit Program(std::vector<Class> classes, int line_number = 0) : TreeNode(line_number),
                                                                        classes(std::move(classes)) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    bool operator==(const Program &rhs) const {
        return static_cast<const TreeNode &>(*this) == static_cast<const TreeNode &>(rhs) &&
               classes == rhs.classes;
    }

    bool operator!=(const Program &rhs) const {
        return !(rhs == *this);
    }

    const std::vector<Class> &get_classes() const {
        return classes;
    }

private:
    const std::vector<Class> classes;
};

#endif //PROGRAM_H
