#ifndef tokeniser_hpp
#define tokeniser_hpp

#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <list>

struct Variable {
    std::string name;
};

struct And {
    int precedence_ = 4;
};
struct Or {
    int precedence_ = 3;
};
struct Xor {
    int precedence_ = 1;
};
struct Not {
    int precedence_ = 5;
};

struct Impl { // - импликациия
    int precedence_ = 2;
};
struct Nor { // ? arrow pirsa
    int precedence_ = 4;
};
struct Nand { // | Sheffer
    int precedence_ = 4;
};

struct Nxor { // ~ equals
    int precedence_ = 1;
};

struct LeftBracket {};
struct RightBracket {};

struct Eof {};



struct Null {};

struct One {};

using TokenBase = std::variant<Variable, And, Or, Xor, Not, Impl, Nor, Nand, Nxor, LeftBracket, RightBracket, Eof, Null, One>;

struct Token : TokenBase {
    
    template <typename T>[[nodiscard]] bool Is() {
        return std::holds_alternative<T>(*this);
    }
    
    template <typename T> const T &As() const { return std::get<T>(*this); }
};
    
bool check_operator_token(Token& token);
int get_precedence(Token& token);
    
class Lexer {
    const std::unordered_map<char, Token> tokens_ = {
        {'+', {Or{}}}, {'*', {And{}}},  {'^', {Xor{}}},
        {'!', {Not{}}}, {'1', {One{}}}, {'0', {Null{}}},
        {'-', {Impl{}}}, {'|', {Nand{}}}, {'~', {Nxor{}}},
        {'?', {Nor{}}},
        {'.', {Eof{}}}, {'(', {LeftBracket{}}}, {')', {RightBracket{}}},
    };
    
    const std::unordered_map<char, Token> constants_ = {
        {'1', {One{}}}, {'0', {Null{}}}
    };
    
    
    
private:
    size_t cur_indx_input = 0;
    
    Token current_token_;
    std::string input_;
    
    Token next();
    Token current_token() const;
    Token next_token();

public:

    explicit Lexer(std::string &&s);
    
    std::list<Token> get_list_tokens();

};

#endif /* tokeniser_hpp */
