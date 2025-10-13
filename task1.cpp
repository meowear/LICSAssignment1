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

int main()
{
    string str;
    cout << "Enter the infix string:";
    getline(cin,str);
    cout<< infixtoprefix(str);
}