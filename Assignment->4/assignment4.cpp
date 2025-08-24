#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cerr << "Error: input.txt not found\n";
        return 1;
    }

    unordered_map<char, char> braces = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };

    vector<pair<char, int>> li; 
    vector<string> bracket_messages;
    vector<string> variable_messages;

    set<pair<string, string>> variables; 

    string line;
    int lineNum = 0;

    while (getline(fin, line)) {
        lineNum++;

        
        for (char ch : line) {
            if (ch == '(' || ch == '{' || ch == '[') {
                li.push_back({ch, lineNum});
            } else if (braces.count(ch)) {
                if (!li.empty() && braces[ch] == li.back().first) {
                    li.pop_back();
                } else {
                    bracket_messages.push_back("Unmatched '" + string(1, ch) + "' on line " + to_string(lineNum));
                }
            }
        }

        
        stringstream ss(line);
        vector<string> tokens;
        string word;
        while (ss >> word) tokens.push_back(word);

        for (size_t i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "int" || tokens[i] == "float" ||
                tokens[i] == "char" || tokens[i] == "double") {

                if (i + 1 < tokens.size()) {
                    string var = tokens[i+1];
                    
                    if (!var.empty() && var.back() == ';') var.pop_back();

                    pair<string, string> value = {tokens[i], var};
                    if (variables.count(value)) {
                        variable_messages.push_back("Duplicate variable (" + tokens[i] + ", " + var + ") on line " + to_string(lineNum));
                    } else {
                        variables.insert(value);
                    }
                }
            }
        }
    }

   
    for (auto &p : li) {
        bracket_messages.push_back("Unmatched '" + string(1, p.first) + "' on line " + to_string(p.second));
    }

    
    if (bracket_messages.empty()) {
        fout << "Brackets are balanced\n";
    } else {
        for (auto &msg : bracket_messages) fout << msg << "\n";
    }

    if (variable_messages.empty()) {
        fout << "No duplicate variable declared!";
    } else {
        for (auto &msg : variable_messages) fout << msg << "\n";
    }

    fin.close();
    fout.close();

    cout << "Check complete. See output.txt\n";
    return 0;
}
