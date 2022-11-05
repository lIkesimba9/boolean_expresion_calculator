#ifndef asttree_hpp
#define asttree_hpp

#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <stack>
#include <queue>

#include "nodes.hpp"


struct AstTree {
    std::shared_ptr<ExpresionNode> root_;
    std::unordered_map<std::string, std::list<std::shared_ptr<VaribleNode>>> variables_;
    AstTree(std::shared_ptr<ExpresionNode> root, std::unordered_map<std::string, std::list<std::shared_ptr<VaribleNode>>> variables);
    void SetValueForVariable(std::vector<bool> values);
    size_t GetCountVariable() const;
    std::vector<std::string> GetVariableNames() const;
    bool Exectute() ;
};

#endif /* asttree_hpp */
