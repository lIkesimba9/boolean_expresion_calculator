#include "asttree.hpp"



AstTree::AstTree(std::shared_ptr<ExpresionNode> root, std::unordered_map<std::string, std::list<std::shared_ptr<VaribleNode>>> variables): root_(root),variables_(variables) {}

size_t AstTree::GetCountVariable() const {
    return variables_.size();
}

void AstTree::SetValueForVariable(std::vector<bool> values) {
    size_t i = 0;
    for (auto[name, list_nodes]: variables_) {
        for (auto node: list_nodes) {
            node->SetValue(values[i]);
        }
        i++;
    }
}

std::vector<std::string> AstTree::GetVariableNames() const {
    std::vector<std::string> names;
    for (auto[name, _]: variables_) {
        names.push_back(name);
    }
    return names;
}

bool AstTree::Exectute() {
    return root_->Execute();
}
