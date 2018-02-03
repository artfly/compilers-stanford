#include <iostream>
#include "Class.h"
#include "ClassGraph.h"


int main(int argc, char **argv) {
    Class a = Class("A", "B", {}, "test.cool");
    Class b = Class("B", "C", {}, "testb.cool");
    Class c = Class("C", "A", {}, "testc.cool");
    ClassGraph classGraph = ClassGraph({a, b, c});
}