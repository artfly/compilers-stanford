//
// Created by Artemiy on 2/1/18.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <ostream>

class NodeVisitor;

class TreeNode {
public:
    explicit TreeNode(int line_number = 0) : line_number(line_number) {}

    virtual ~TreeNode() = default;

    virtual void accept(const NodeVisitor &visitor) const = 0;

    const int get_line_number() const {
        return line_number;
    }

    bool operator==(const TreeNode &rhs) const {
        return line_number == rhs.line_number;
    }

    bool operator!=(const TreeNode &rhs) const {
        return !(rhs == *this);
    }

private:
    const int line_number;
};


#endif //TREENODE_H
