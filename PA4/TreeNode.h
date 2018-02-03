//
// Created by Artemiy on 2/1/18.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <ostream>


class TreeNode {
public:
    bool operator==(const TreeNode &rhs) const {
        return line_number == rhs.line_number;
    }

    bool operator!=(const TreeNode &rhs) const {
        return !(rhs == *this);
    }

public:
//    virtual ~TreeNode();
//
//    // TODO
//    virtual TreeNode * copy();
//
//    virtual void dump(std::ostream & os, int n);
//
//    // TODO
//    virtual TreeNode * set();

    int line_number;
};


#endif //TREENODE_H
