//
// Created by Artemiy on 2/2/18.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include "TreeNode.h"
#include "Class.h"

class Program : public TreeNode {
public:
    explicit Program(const std::vector<Class> &classes) : classes(classes) {}

private:
    std::vector<Class> classes;
};

#endif //PROGRAM_H
