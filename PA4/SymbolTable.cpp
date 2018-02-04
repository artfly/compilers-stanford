//
// Created by Artemiy on 2/4/18.
//

#include "SymbolTable.h"

template<typename SYM, typename DATA>
void SymbolTable<SYM, DATA>::enter_scope() {
    scopes.push_front(Scope());
}

template<typename SYM, typename DATA>
void SymbolTable<SYM, DATA>::exit_scope() {
    scopes.pop_front();
}

template<typename SYM, typename DATA>
void SymbolTable<SYM, DATA>::add(std::pair<SYM, DATA *> symbol) {
    auto scope = scopes.front();
    scope.insert(symbol);
}

template<typename SYM, typename DATA>
DATA *SymbolTable<SYM, DATA>::lookup(SYM sym) {
    for (auto scope : scopes) {
        auto it = scope.find(sym);
        if (it != scope.end()) {
            return *it;
        }
    }
    return nullptr;
}

template<typename SYM, typename DATA>
DATA *SymbolTable<SYM, DATA>::probe(SYM sym) {
    auto scope = scopes.front();
    auto it = scope.find(sym);
    return it == scope.end() ? nullptr : *it;
}
