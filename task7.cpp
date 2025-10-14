#include <bits/stdc++.h>
using namespace std;

bool checkvalidityifcnffile(vector<vector<int>> &v)
{
    for (int i = 0; i < v.size(); i++) 
    {
        vector<int> row = v[i];
        unordered_set<int> s;

        for (int j = 0; j < row.size(); j++)
            s.insert(row[j]);

        bool val = false;

        for (int j = 0; j < row.size(); j++) 
        {
            if (s.count(-row[j])) 
            {
                val = true;
                break;
            }
        }

        if (!val)
            return false;
    }
    return true;
}

bool checkvalidityfortask6(vector<vector<string>>&v) {
    for (int i = 0; i < v.size(); i++) {
        vector<string> row = v[i];
        unordered_set<string> s;

        for (int j = 0; j < row.size(); j++)
            s.insert(row[j]);

        bool val = false;

        for (int j = 0; j < row.size(); j++) 
        {
            string lit = row[j];
            string neg;
            if (!lit.empty() && lit[0] == '~') 
                neg = lit.substr(1);  // remove negation
            else 
                neg = "~" + lit;          // add negation

            if (s.count(neg)) 
            {
                val = true;
                break;
            }
        }

        if (!val) 
            return false;
    }
    return true;
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
        if (line[0] == 'p' || line[0] == 'c') continue;

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

int main() {
    string filepath;
    cout << "Enter the filepath: ";
    cin >> filepath;

    vector<vector<int>> v = readfile(filepath);
    cout<< checkvalidityifcnffile(v);

    return 0;
}