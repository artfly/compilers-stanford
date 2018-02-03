//
// Created by Artemiy on 2/1/18.
//

#ifndef CLASS_H
#define CLASS_H


#include <utility>
#include <vector>
#include <iostream>
#include "TreeNode.h"
#include "Feature.h"

class Class : public TreeNode {
public:
    Class(std::string name, std::string parent, std::vector<Feature> features, std::string filename) :
            name(std::move(name)), parent(std::move(parent)), features(std::move(features)),
            filename(std::move(filename)) {}

    std::string name;
    std::string parent;

    bool operator==(const Class &rhs) const {
        return static_cast<const TreeNode &>(*this) == static_cast<const TreeNode &>(rhs) &&
               name == rhs.name &&
               parent == rhs.parent &&
               filename == rhs.filename;
    }

    bool operator!=(const Class &rhs) const {
        return !(rhs == *this);
    }

    std::string filename;
private:

    std::vector<Feature> features;

};

namespace base_classes {

    static constexpr auto STR_TYPE = "String";
    static constexpr auto OBJ_TYPE = "Object";
    static constexpr auto SELF_TYPE = "SELF_TYPE";
    static constexpr auto INT_TYPE = "Int";
    static constexpr auto NO_CLASS_TYPE = "_no_class";
    static constexpr auto IO_TYPE = "IO";
    static constexpr auto BOOL_TYPE = "Bool";

    static constexpr auto BASE_FILENAME = "<basic class>";


    static const auto Object = Class(OBJ_TYPE,
                                          NO_CLASS_TYPE,
                                          {
                                                  Method("abort", std::vector<Formal>(), OBJ_TYPE, NoExpr()),
                                                  Method("type_name", std::vector<Formal>(), STR_TYPE, NoExpr()),
                                                  Method("copy", std::vector<Formal>(), SELF_TYPE, NoExpr())
                                          },
                                          BASE_FILENAME);

    static const auto IO = Class(IO_TYPE, OBJ_TYPE,
                                      {
                                              Method("out_string", {Formal("arg", STR_TYPE)}, SELF_TYPE, NoExpr()),
                                              Method("out_int", {Formal("arg", INT_TYPE)}, SELF_TYPE, NoExpr()),
                                              Method("in_int", std::vector<Formal>(), INT_TYPE, NoExpr()),
                                              Method("in_string", std::vector<Formal>(), STR_TYPE, NoExpr())
                                      },
                                      BASE_FILENAME);

    static const auto Int = Class(INT_TYPE, OBJ_TYPE, {Attribute("_val", "_prim_slot", NoExpr())}, BASE_FILENAME);

    static const auto Bool = Class(BOOL_TYPE, OBJ_TYPE, {Attribute("_val", "_prim_slot", NoExpr())},
                                        BASE_FILENAME);

    static const auto Str = Class(STR_TYPE,
                                       OBJ_TYPE,
                                       {
                                               Attribute("val", INT_TYPE, NoExpr()),
                                               Attribute("_str_field", "_prim_slot", NoExpr()),
                                               Method("length", std::vector<Formal>(), INT_TYPE, NoExpr()),
                                               Method("concat", {Formal("arg", STR_TYPE)}, STR_TYPE, NoExpr()),
                                               Method("substr", {Formal("arg", INT_TYPE), Formal("arg2", INT_TYPE)},
                                                      STR_TYPE, NoExpr())

                                       },
                                       BASE_FILENAME);
}


#endif //CLASS_H
