//
// Created by Artemiy on 2/2/18.
//

#ifndef CLASSGRAPH_H
#define CLASSGRAPH_H


#include <utility>
#include <map>
#include <iostream>
#include <vector>

#include "Class.h"

class ClassGraph {
public:
    explicit ClassGraph(std::vector<Class> classes_, std::ostream &err_stream_ = std::cerr);

    std::ostream &semant_error(const Class &cl);

private:
    enum Color {
        WHITE, GREY, BLACK
    };

    void add_base_classes();

    void visit(std::pair<const Class &, size_t> cl, std::vector<Color> &colors);

    std::vector<Class> classes;
    int semant_errors = 0;
    std::ostream &err_stream;
};

#endif //CLASSGRAPH_H
