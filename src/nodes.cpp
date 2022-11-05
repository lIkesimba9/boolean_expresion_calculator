#include "nodes.hpp"




BinaryOperator::BinaryOperator(Token op, std::shared_ptr<ExpresionNode> left_node,
               std::shared_ptr<ExpresionNode> right_node)
: operator_(op), left_node_(left_node), right_node_(right_node) {}


bool BinaryOperator::Execute() {
    if (operator_.Is<And>()) {
        return left_node_->Execute() & right_node_->Execute();
    } else if (operator_.Is<Or>()) {
        return left_node_->Execute() | right_node_->Execute();
    } else if (operator_.Is<Xor>()) {
        return left_node_->Execute() ^ right_node_->Execute();
    }  else if (operator_.Is<Nand>()) {
        return !(left_node_->Execute() & right_node_->Execute());
    } else if (operator_.Is<Nxor>()) {
        return !(left_node_->Execute() ^ right_node_->Execute());
    } else if (operator_.Is<Nor>())   {
        return !(left_node_->Execute() | right_node_->Execute());
    }  else { // Impication
        return left_node_->Execute() <= right_node_->Execute();
    }
}


UnaryOperator::UnaryOperator(Token op, std::shared_ptr<ExpresionNode> node)
: operator_(op), node_(node) {}

bool UnaryOperator::Execute() {
    return !node_->Execute();
}

VaribleNode::VaribleNode(Token token) : vars_(token.As<Variable>()) {}

void VaribleNode::SetValue(bool value) { value_ = value; }

bool VaribleNode::Execute() { return value_; }

bool OneNode::Execute() { return 1; }

bool NullNode::Execute() { return 0; }

