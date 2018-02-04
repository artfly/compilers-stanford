//
// Created by Artemiy on 2/4/18.
//

#ifndef UNTITLED_SYMBOLTABLE_H
#define UNTITLED_SYMBOLTABLE_H

#include <map>
#include <vector>
#include <stack>
#include <list>

template<typename SYM, typename DATA>
class SymbolTable {
public:
    typedef std::map<SYM, DATA> Scope;

    void enter_scope();

    void exit_scope();

    void add(std::pair<SYM, DATA *> symbol);

    DATA *lookup(SYM sym);

    DATA *probe(SYM sym);

private:

    std::list<Scope> scopes = std::list<Scope>();
};


#endif //UNTITLED_SYMBOLTABLE_H
