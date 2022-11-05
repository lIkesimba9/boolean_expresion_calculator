#ifndef parser_hpp
#define parser_hpp

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

#include "tokeniser.hpp"
#include "nodes.hpp"
#include "asttree.hpp"


class Parser {
    std::list<Token> token_collection_;
    std::shared_ptr<AstTree> ast_tree_;
    
    std::queue<Token> make_postfix_notation();
    
    std::shared_ptr<AstTree> build_ast_tree(std::queue<Token>& tokens_queue);
    
public:
    std::shared_ptr<AstTree> GetAstTree() const;
    
    
    Parser(std::list<Token> &&token_collection);
};

#endif /* parser_hpp */
