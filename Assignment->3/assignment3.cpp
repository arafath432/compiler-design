#include <bits/stdc++.h>
using namespace std;

struct Symbol {
    int SlNo;
    string Name;
    string Id;      
    string Type;    
    string Scope;   
    string Value;  
};

class SymbolTable {
    vector<Symbol> rows;
    int auto_id = 0;
public:
    void insert(const string &name, const string &idtype, const string &datatype,
                const string &scope, const string &value = "") {
        Symbol entry;
        entry.SlNo = ++auto_id;
        entry.Name = name;
        entry.Id = idtype;
        entry.Type = datatype;
        entry.Scope = scope;
        entry.Value = value;
        rows.push_back(entry);
    }

    bool update(const string &name, const string &field, const string &new_value,
                const string &scope = "") {
        for (auto &row : rows) {
            if (row.Name == name && (scope.empty() || row.Scope == scope)) {
                if (field == "Value") row.Value = new_value;
                else if (field == "Type") row.Type = new_value;
                else if (field == "Id") row.Id = new_value;
                return true;
            }
        }
        return false;
    }

    void display(ostream &out) {
        out << left << setw(6) << "Sl.No"
            << setw(8) << "Name"
            << setw(8) << "Id"
            << setw(10) << "Type"
            << setw(10) << "Scope"
            << setw(10) << "Value" << "\n";

        for (auto &r : rows) {
            out << left << setw(6) << r.SlNo
                << setw(8) << r.Name
                << setw(8) << r.Id
                << setw(10) << r.Type
                << setw(10) << r.Scope
                << setw(10) << r.Value << "\n";
        }
    }
};

vector<string> read_tokens(const string &filename) {
    ifstream f(filename);
    vector<string> tokens;
    if (!f) {
        cerr << "Error: cannot open " << filename << "\n";
        return tokens;
    }

    string content((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    string token;
    bool inside = false;

    for (char ch : content) {
        if (ch == '[') {
            inside = true;
            token.clear();
        } else if (ch == ']') {
            inside = false;
            if (!token.empty())
                tokens.push_back(token);
        } else if (inside) {
            token += ch;
        }
    }
    return tokens;
}

SymbolTable parse_tokens(const vector<string> &tokens) {
    SymbolTable st;
    vector<string> scope_stack = {"global"};
    string current_func;
    string dtype;

    auto cur_scope = [&]() { return scope_stack.back(); };

    for (size_t i = 0; i < tokens.size(); i++) {
        string tok = tokens[i];

        if (tok == "{") {
            scope_stack.push_back(current_func.empty() ? cur_scope() : current_func);
            continue;
        }
        if (tok == "}") {
            if (!scope_stack.empty()) scope_stack.pop_back();
            if (scope_stack.empty()) scope_stack.push_back("global");
            if (!current_func.empty() && cur_scope() == "global") current_func.clear();
            continue;
        }

        if (tok == "int" || tok == "float" || tok == "double" ||
            tok == "char" || tok == "void") {
            dtype = tok;
            if (i + 1 < tokens.size() && tokens[i+1].rfind("id ", 0) == 0) {
                string name = tokens[i+1].substr(3);

                if (i + 2 < tokens.size() && tokens[i+2] == "(") {
                    // function
                    st.insert(name, "func", dtype, "global");
                    current_func = name;
                    i += 2;
                    // skip parameters until ')'
                    while (i + 1 < tokens.size() && tokens[i+1] != ")") i++;
                    i++;
                } else {
                    string value;
                    if (i + 2 < tokens.size() && tokens[i+2] == "=") {
                        if (i + 3 < tokens.size()) value = tokens[i+3];
                    }
                    st.insert(name, "var", dtype, cur_scope(), value);
                    i += 2;
                }
            }
            continue;
        }

        if (tok.rfind("id ", 0) == 0) {
            string name = tok.substr(3);
            if (i + 1 < tokens.size() && tokens[i+1] == "=") {
                if (i + 2 < tokens.size() && tokens[i+2].rfind("id", 0) != 0) {
                    string valtok = tokens[i+2];
                    st.update(name, "Value", valtok, cur_scope());
                }
            }
        }
    }

    return st;
}

int main() {
    vector<string> tokens = read_tokens("input.txt");
    SymbolTable st = parse_tokens(tokens);

    ofstream fout("output.txt");
    st.display(fout);
    fout.close();

    cout << "Symbol table written to output.txt\n";
    return 0;
}
