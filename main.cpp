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
#include <set>
#include <tuple>
#include <unordered_map>
#include <iomanip>

#include "parser.hpp"
#include "tokeniser.hpp"
#include "asttree.hpp"


using namespace std;




int main(int argc, const char *argv[]) {
    
    string text;
    getline(cin, text);
    Lexer lexer(move(text));
    auto tokens = lexer.get_list_tokens();

    auto parser = Parser(move(tokens));
    auto ast_tree_ptr = parser.GetAstTree();
    
    const size_t N = ast_tree_ptr->GetCountVariable();
    vector<vector<bool>> values_collection;
    vector<bool> results;
    for (size_t i=0; i<(1<<N); ++i) {
        vector<bool> values(N, false);
        size_t number = i;
        size_t j = 0;
        while (number) {
            values[j] = number & 1;
            number = number >> 1;
            j++;
        }
        values_collection.push_back(values);
        ast_tree_ptr->SetValueForVariable(values);
        results.push_back(ast_tree_ptr->Exectute());
    }
    
    vector<string> name_collection = ast_tree_ptr->GetVariableNames();
    for (size_t i = 0; i < N; ++i) {
        cout << setw(5) << name_collection[i] << " ";
    }
    cout << setw(6) << "result" << endl;
    size_t j = 0;
    for(vector<bool>& values: values_collection) {
        
        for (size_t i = 0; i < N; ++i) {
            cout << setw(5) << values[i] << " ";
        }
        cout << setw(6) << results[j] << endl;
        j++;
    }

  
    return 0;
}
