//
// Created by Artemiy on 2/1/18.
//

#ifndef CLASS_H
#define CLASS_H

#include <utility>

#include "NodeVisitor.h"

class Feature;

class Class : public TreeNode {
public:
    Class(std::string name, std::string parent, std::string filename,
          const std::vector<const Feature *> &features, int line_number = 0) :
            TreeNode(line_number), name(std::move(name)), parent(std::move(parent)),
            filename(std::move(filename)), features(features) {}

    void accept(const NodeVisitor &visitor) const override {
        visitor.visit(*this);
    }

    const std::string &get_name() const {
        return name;
    }

    const std::string &get_parent() const {
        return parent;
    }

    const std::string &get_filename() const {
        return filename;
    }

    const std::vector<const Feature *> &get_features() const {
        return features;
    }

private:

    const std::string name;
    const std::string parent;
    const std::string filename;

    const std::vector<const Feature *> features;
};

namespace base_classes {

    namespace types {
        static constexpr auto STR_TYPE = "String";
        static constexpr auto OBJ_TYPE = "Object";
        static constexpr auto SELF_TYPE = "SELF_TYPE";
        static constexpr auto INT_TYPE = "Int";
        static constexpr auto NO_CLASS_TYPE = "_no_class";
        static constexpr auto IO_TYPE = "IO";
        static constexpr auto BOOL_TYPE = "Bool";
    }

    static constexpr auto FILENAME = "<basic class>";

    namespace methods {
        // Object methods
        static const auto ABORT = Method("abort", types::OBJ_TYPE, {}, NoExpr());
        static const auto TYPE_NAME = Method("type_name", types::STR_TYPE, {}, NoExpr());
        static const auto COPY = Method("copy", types::SELF_TYPE, {}, NoExpr());

        // IO methods
        static const auto OUT_STRING = Method("out_string", types::SELF_TYPE, {Formal("arg", types::STR_TYPE)}, NoExpr());
        static const auto OUT_INT = Method("out_int", types::SELF_TYPE, {Formal("arg", types::INT_TYPE)}, NoExpr());
        static const auto IN_INT = Method("in_int", types::INT_TYPE, {}, NoExpr());
        static const auto IN_STRING = Method("in_string", types::STR_TYPE, {}, NoExpr());

        // String methods
        static const auto LENGTH = Method("length", types::INT_TYPE, {}, NoExpr());
        static const auto CONCAT = Method("concat", types::STR_TYPE, {Formal("arg", types::STR_TYPE)}, NoExpr());
        static const auto SUBSTR = Method("substr", types::STR_TYPE, {Formal("f", types::INT_TYPE), Formal("t", types::INT_TYPE)}, NoExpr());
    }

    namespace attributes {
        // Int attributes
        static const Attribute INT_VAL = Attribute("_val", "_prim_slot_", NoExpr());

        // Bool attributes
        static const Attribute BOOL_VAL = Attribute("_val", "_prim_slot", NoExpr());

        //String attributes
        static const Attribute STR_LEN = Attribute("len", types::INT_TYPE, NoExpr());
        static const Attribute STR_VAL = Attribute("_val", "_prim_slot", NoExpr());
    }

    static const auto Object = Class(types::OBJ_TYPE, types::NO_CLASS_TYPE, FILENAME,
                                     {&methods::ABORT, &methods::TYPE_NAME, &methods::COPY});

    static const auto IO = Class(types::IO_TYPE, types::OBJ_TYPE, FILENAME,
                                 {&methods::OUT_STRING, &methods::OUT_INT, &methods::IN_INT, &methods::IN_STRING});

    static const auto Int = Class(types::INT_TYPE, types::OBJ_TYPE, FILENAME, {&attributes::INT_VAL});

    static const auto Bool = Class(types::BOOL_TYPE, types::OBJ_TYPE, FILENAME, {&attributes::BOOL_VAL});

    static const auto Str = Class(types::STR_TYPE, types::OBJ_TYPE, FILENAME,
                                  {&attributes::STR_LEN, &attributes::STR_VAL,
                                   &methods::LENGTH, &methods::CONCAT, &methods::SUBSTR});
}

#endif //CLASS_H
