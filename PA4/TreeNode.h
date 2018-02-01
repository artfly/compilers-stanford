//
// Created by Artemiy on 2/1/18.
//

#ifndef TREENODE_H
#define TREENODE_H

#include <ostream>


class TreeNode {
public:
    virtual ~TreeNode() = 0;

    // TODO
    virtual TreeNode * copy() = 0;

    virtual void dump(std::ostream & os, int n) = 0;

    // TODO
    virtual TreeNode * set() = 0;

protected:
    int line_number = 0;
};


#endif //TREENODE_H
