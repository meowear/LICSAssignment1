#include <bits/stdc++.h>
using namespace std;

int priority(char c)
{
    switch(c)
    {
       
        case '>':
            return 1;
        case '+':
            return 2;
        case '*':
            return 3;
        case '~':
            return 4;
        default:
            return -1;

    }
}//priority function 

int isOperator(char c)
{
    if(c == '~' || c == '+' || c == '*' || c == '>')//four of the symbols are there
        return 1;
    return 0;

}

string infixtoprefix(string str)
{
    string ans="";//to hold the result
    
    stack<char> s;

    reverse(str.begin(),str.end());//reversing 

    for(int i=0;i<str.size();i++)
    {
       if(str[i]=='(')
            str[i]=')';
        else if(str[i]==')')
            str[i]='(';
    
    }//swapping ( and )the algo is okay???

    for(int i=0;i<str.size();i++)
    {   
        char c=str[i];
        if(isalnum(c))
            ans+=c;
        else if(c=='(')
            s.push(c);
        else if(c==')')
        {
            while(!s.empty() && s.top()!='(')
            {
                ans+=s.top();
                s.pop();
            
            }
            if (!s.empty())
                 s.pop();
        }
        else if(isOperator(c))
        {
            if(c=='>'||c=='~')
            {
                while(!s.empty()&& priority(c)<=priority(s.top()))
                {
                    ans+=s.top();
                    s.pop();
                }
            }//right associative
            else
            {
                while(!s.empty() && priority(c)<priority(s.top()))
                {
                    ans+=s.top();
                    s.pop();
                }
            }
            s.push(c);
        }//left associative
    
    }

    while(!s.empty())
    {
        ans+=s.top();
        s.pop();
    }//for remaining elements

    reverse(ans.begin(),ans.end());//reversing
     
    return ans;

}

vector<vector<int>> readfile(string filepath) {
    fstream file(filepath, ios::in);

    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filepath << endl;
        return {};
    }

    vector<vector<int>> v;
    string line;

    while (getline(file, line)) {
        if (line.empty() || line[0] == 'p' || line[0] == 'c') continue;

        vector<int> row;
        stringstream sinput(line);
        int num;
        while (sinput >> num) {
            if (num == 0) break;
            row.push_back(num);
        }

        v.push_back(row);
    }

    file.close();
    return v;
}

string clauseToPrefix(vector<int>& clause) {
    string s = "(+";
    for (int lit : clause) {
        s += " ";
        if (lit < 0)
            s += "~" + to_string(-lit);  // negative numbers → ~N
        else
            s += to_string(lit);          // positive numbers stay
    }
    s += ")";
    return s;
}

string cnfToPrefix(vector<vector<int>>& cnf) {
    if (cnf.empty()) return "";

    string prefix = clauseToPrefix(cnf[0]);

    for (size_t i = 1; i < cnf.size(); i++) {
        string nextClause = clauseToPrefix(cnf[i]);
        prefix = "(* " + prefix + " " + nextClause + ")";
    }

    return prefix;
}

int main() {

    string str;
    cout << "Enter the infix string:";
    getline(cin,str);
    cout<< infixtoprefix(str)<<endl;///using string formula input


    string filepath;//using the cnf file input
    cout << "Enter the filepath: " << endl;
    cin >> filepath;

    vector<vector<int>> v_infix = readfile(filepath);
    
    string prefix = cnfToPrefix(v_infix);
    cout << prefix << endl;

    return 0;
}
