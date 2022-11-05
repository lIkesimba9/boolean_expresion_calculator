#include "tokeniser.hpp"

#include <vector>
#include <unordered_map>
#include <string>

Token Lexer::next() {
    while  (' ' == input_[cur_indx_input]){
        cur_indx_input++;
    }
    if (tokens_.count(input_[cur_indx_input])) {
        Token op = tokens_.at(input_[cur_indx_input]);
        cur_indx_input++;
        return op;
    }
    if (isnumber(input_[cur_indx_input])) {
        Token op = constants_.at(input_[cur_indx_input]);
        cur_indx_input++;
        return op;
    }
    if (isalpha(input_[cur_indx_input])) {
        std::string name_of_variable = "";
        while (isalnum(input_[cur_indx_input])) {
            name_of_variable.push_back(input_[cur_indx_input]);
            cur_indx_input++;
        }
        return {Variable{
            .name = name_of_variable
        }};
    }
    
    throw std::runtime_error("wrong token");
}

Token Lexer::next_token() {
    current_token_ = next();
    return current_token_;
}

Lexer::Lexer(std::string &&s) : input_(move(s)) { current_token_ = next(); }

Token Lexer::current_token() const {
    return current_token_;
}


std::list<Token> Lexer::get_list_tokens() {
    std::list<Token> list_tokens;
    Token cur_token = this->current_token();
    while(!std::holds_alternative<Eof>(cur_token)) {
        list_tokens.push_back(cur_token);
        cur_token = this->next_token();
    }
    return list_tokens;
}


bool check_operator_token(Token& token)
{
    if (token.Is<And>() || token.Is<Or>() || token.Is<Xor>() || token.Is<Not>() ||
        token.Is<Impl>() || token.Is<Nand>() || token.Is<Nxor>() || token.Is<Nor>())
        return true;
    else return false;
}

int get_precedence(Token& token) {
    if (token.Is<And>()) {
        return token.As<And>().precedence_;
    } else if (token.Is<Or>()) {
        return token.As<Or>().precedence_;
    } else if ( token.Is<Xor>() ) {
        return token.As<Xor>().precedence_;
    } else if ( token.Is<Not>()){
        return token.As<Not>().precedence_;
    } else if (token.Is<Impl>()){
        return token.As<Impl>().precedence_;
    } else if ( token.Is<Nand>()){
        return token.As<Nand>().precedence_;
    } else if ( token.Is<Nxor>()){
        return token.As<Nxor>().precedence_;
    } else if ( token.Is<Nor>()){
        return token.As<Nor>().precedence_;
    }
    return -1;
}
