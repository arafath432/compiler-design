#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream inputFile("input.c");

    regex kw_patterns(R"(\b(?:char|int|float|if|else)\b)");
    regex variable_patterns(R"([a-zA-Z_]\w*)");
    regex number_patterns(R"(\d+(\.\d+)?)");
    regex oparator_patterns(R"(<=|>=|==|!=|[+\-*/=<>])");
    regex perenthisis_patterns(R"([{()}])");
    regex separator_patterns(R"([,;'])");

    string text;
    char c;

    while (inputFile.get(c))
    {
        text += c;
    }

    size_t pos(0);
    while (pos < text.length())
    {
        bool match = false;

        for (int i = 0; i < 1; i++)
        {
            smatch m;
            string sub = text.substr(pos);
            if (regex_search(sub, m, kw_patterns, regex_constants::match_continuous))
            {
                cout << "[kw " << m.str() << "]";
                match = true;
                pos += m.length();
                break;
            }
            if (regex_search(sub, m, variable_patterns, regex_constants::match_continuous))
            {
                cout << "[id " << m.str() << "]";
                match = true;
                pos += m.length();
                break;
            }
            if (regex_search(sub, m, number_patterns, regex_constants::match_continuous))
            {
                cout << "[num " << m.str() << "]";
                match = true;
                pos += m.length();
                break;
            }
            if (regex_search(sub, m, oparator_patterns, regex_constants::match_continuous))
            {
                cout << "[op " << m.str() << "]";
                match = true;
                pos += m.length();
                break;
            }
            if (regex_search(sub, m, perenthisis_patterns, regex_constants::match_continuous))
            {
                cout << "[per " << m.str() << "]";
                match = true;
                pos += m.length();
                break;
            }
            if (regex_search(sub, m, separator_patterns, regex_constants::match_continuous))
            {
                cout << "[sep " << m.str() << "]";
                match = true;
                pos += m.length();
                break;
            }
        }
        if (!match)
        {
            pos++;
        }
    }

    cout << endl;

    return 0;
}