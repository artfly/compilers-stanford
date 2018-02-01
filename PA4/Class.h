//
// Created by Artemiy on 2/1/18.
//

#ifndef CLASS_H
#define CLASS_H


#include <utility>
#include <vector>
#include "TreeNode.h"
#include "Feature.h"

class Class : TreeNode {
public:
    Class(std::string name, std::string parent, std::vector<Feature> features, std::string filename) :
            name(std::move(name)), parent(std::move(parent)), features(std::move(features)),
            filename(std::move(filename)) {}

private:
    std::string name;

    std::string parent;

    std::vector<Feature> features;

    std::string filename;
};


#endif //CLASS_H
