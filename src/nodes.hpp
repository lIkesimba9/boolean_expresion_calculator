#ifndef nodes_hpp
#define nodes_hpp


#include "tokeniser.hpp"

struct ExpresionNode {
    virtual bool Execute() = 0;
};


struct BinaryOperator : ExpresionNode {
    Token operator_;
    std::shared_ptr<ExpresionNode> left_node_;
    std::shared_ptr<ExpresionNode> right_node_;
    BinaryOperator(Token op, std::shared_ptr<ExpresionNode> left_node,
                   std::shared_ptr<ExpresionNode> right_node);
    bool Execute() override;
};

struct UnaryOperator: ExpresionNode {
    Token operator_;
    std::shared_ptr<ExpresionNode> node_;
    UnaryOperator(Token op, std::shared_ptr<ExpresionNode> node);
    bool Execute() override;
};

struct VaribleNode : ExpresionNode {
    Variable vars_;
    bool value_ = 0;
    explicit VaribleNode(Token token);
    void SetValue(bool value);
    bool Execute() override;
};

struct OneNode: ExpresionNode {
    bool Execute() override;
};

struct NullNode: ExpresionNode {
    bool Execute() override;
};



#endif /* nodes_hpp */
