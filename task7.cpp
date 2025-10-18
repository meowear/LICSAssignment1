#include <bits/stdc++.h>
using namespace std;

// Integer CNF check (for DIMACS-style CNF)
bool checkvalidityifcnffile(vector<vector<int>> &v) {
    int validCount = 0, invalidCount = 0;

    for (int i = 0; i < v.size(); i++) {
        vector<int> row = v[i];
        unordered_set<int> s(row.begin(), row.end());

        bool val = false;
        for (int j = 0; j < row.size(); j++) {
            if (s.count(-row[j])) {
                val = true;
                break;
            }
        }

        if (val)
            validCount++;
        else
            invalidCount++;
    }

    cout << "Valid clauses: " << validCount << endl;
    cout << "Invalid clauses: " << invalidCount << endl;

    return invalidCount == 0;
}

// String CNF check
bool checkvalidityfortask6(vector<vector<string>> &v) {
    int validCount = 0, invalidCount = 0;

    for (int i = 0; i < v.size(); i++) {
        vector<string> row = v[i];
        unordered_set<string> s(row.begin(), row.end());

        bool val = false;
        for (int j = 0; j < row.size(); j++) {
            string lit = row[j];
            string neg = (!lit.empty() && lit[0] == '~') ? lit.substr(1) : "~" + lit;

            if (s.count(neg)) {
                val = true;
                break;
            }
        }

        if (val)
            validCount++;
        else
            invalidCount++;
    }

    cout << "Valid clauses: " << validCount << endl;
    cout << "Invalid clauses: " << invalidCount << endl;

    return invalidCount == 0;
}

// Read DIMACS CNF file
vector<vector<int>> readfile(string filepath) {
    fstream file(filepath, ios::in);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filepath << endl;
        return {};
    }

    vector<vector<int>> v;
    string line;

    while (getline(file, line)) {
        if (line[0] == 'p' || line[0] == 'c')
            continue;

        vector<int> row;
        stringstream sinput(line);
        int num;
        while (sinput >> num) {
            if (num == 0)
                break;
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
    bool valid = checkvalidityifcnffile(v);

    cout << "The formula is " << (valid ? "VALID" : "INVALID") << endl;

    return 0;
}
