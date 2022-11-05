#include "parser.hpp"


std::queue<Token> Parser::make_postfix_notation() {
    std::queue<Token> queue_;
    std::stack<Token> stack_;
    for (Token token: this->token_collection_) {
        
        if (check_operator_token(token)) {
            while (
                   (!stack_.empty() && check_operator_token(stack_.top()) &&  !stack_.top().Is<LeftBracket>()) &&
                   (get_precedence(stack_.top()) >= get_precedence(token))
            ) {
                    queue_.push(stack_.top());
                    stack_.pop();
            }
            stack_.push(token);
        }

        if (token.Is<LeftBracket>()) {
            stack_.push(token);
        }
        if (token.Is<RightBracket>()) {
            while(!stack_.empty() and !stack_.top().Is<LeftBracket>()) {
                queue_.push(stack_.top());
                stack_.pop();
            }
            if (stack_.top().Is<LeftBracket>()) {
                stack_.pop();
                if (!stack_.empty() && check_operator_token(stack_.top())) {
                    queue_.push(stack_.top());
                    stack_.pop();
                }
            }
        }
        if (token.Is<Variable>() || token.Is<Null>() || token.Is<One>()) {
            queue_.push(token);
        }

        
    }
    
    while (!stack_.empty()) {
        if (stack_.top().Is<LeftBracket>()) {
            std::runtime_error("OPEN BRACKET NOT CLOSE");
        }
        queue_.push(stack_.top());
        stack_.pop();
    }

    return queue_;
}


std::shared_ptr<AstTree> Parser::build_ast_tree(std::queue<Token>& tokens_queue) {
    std::stack<std::shared_ptr<ExpresionNode>> nodes;
    std::unordered_map<std::string, std::list<std::shared_ptr<VaribleNode>>> variables;
    
    while (!tokens_queue.empty()) {
        Token token = tokens_queue.front();
        tokens_queue.pop();
        
        if (token.Is<Variable>()) {
            auto ptr_on_variable_node = std::make_shared<VaribleNode>(token);
            nodes.push(ptr_on_variable_node);
            variables[ptr_on_variable_node->vars_.name].push_back(ptr_on_variable_node);
        }
        if (token.Is<Null>()) {
            nodes.push(std::make_shared<NullNode>());
        }
        if (token.Is<One>()) {
            nodes.push(std::make_shared<OneNode>());
        }
        if (check_operator_token(token)) {
            if (token.Is<Not>()) {
                if (nodes.size() < 1)
                    std::runtime_error("1 parametr need for NOT operation");
                auto op = nodes.top();
                nodes.pop();
                nodes.push(std::make_shared<UnaryOperator>(token, op));
            } else {
                if (nodes.size() < 2)
                    std::runtime_error("2 parametr need for binary operation");
                auto right_op = nodes.top();
                nodes.pop();
                auto left_op = nodes.top();
                nodes.pop();
                nodes.push(std::make_shared<BinaryOperator>(token, left_op, right_op));
            }
        }
        
    }
    if (nodes.size() != 1){
        std::runtime_error("fault build ast tree!");
    }
    
    return std::make_shared<AstTree>(nodes.top(), variables);
    
    
    
}


std::shared_ptr<AstTree> Parser::GetAstTree() const {
    return ast_tree_;
}
    

    
Parser::Parser(std::list<Token> &&token_collection) : token_collection_(token_collection) {
        
    std::queue<Token> tokens_queue = this->make_postfix_notation();
    ast_tree_ = this->build_ast_tree(tokens_queue);
}
