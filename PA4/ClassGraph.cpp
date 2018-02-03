//
// Created by Artemiy on 2/3/18.
//

#include <utility>
#include <vector>
#include <cassert>
#include "Class.h"
#include "ClassGraph.h"

ClassGraph::ClassGraph(std::vector<Class> classes_, std::ostream &err_stream_) :
        classes(std::move(classes_)), semant_errors(0), err_stream(err_stream_) {

    add_base_classes();
    auto colors = std::vector<Color>(classes.size(), WHITE);
    // don't traverse Object
    auto pos = std::distance(classes.begin(), std::find_if(classes.begin(), classes.end(),
                                                           [](const Class &cl) { return cl == base_classes::Object; }));
    assert(pos >= 0 && pos < colors.size());
    colors[pos] = BLACK;

    for (auto it = classes.begin(); it != classes.end(); ++it) {
        if (colors[std::distance(classes.begin(), it)] == WHITE) {
            visit(std::make_pair(*it, std::distance(classes.begin(), it)), colors);
        }
    }
}

std::ostream &ClassGraph::semant_error(const Class &cl) {
    semant_errors++;
    err_stream << cl.filename << ":" << cl.line_number << ": ";
    return err_stream;
}

void ClassGraph::add_base_classes() {
    auto base = {base_classes::IO, base_classes::Bool, base_classes::Int, base_classes::Str, base_classes::Object};
    classes.insert(classes.end(), std::begin(base), std::end(base));
}

void ClassGraph::visit(std::pair<const Class &, size_t> cl, std::vector<ClassGraph::Color> &colors) {
    colors[cl.second] = GREY;
    auto parent = std::find_if(classes.begin(), classes.end(),
                               [&cl](const Class &cur) { return cur.name == cl.first.parent; });

    if (parent == classes.end()) {
        // parent not found
        semant_error(cl.first);
        return;
    }

    switch (colors[std::distance(classes.begin(), parent)]) {
        case GREY:
            // cycle found
            semant_error(cl.first);
            break;
        case BLACK:
            colors[cl.second] = BLACK;
            break;
        default:
            visit(std::make_pair(*parent, std::distance(classes.begin(), parent)), colors);
    }
}