#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool IsDecreaseArray(vector<char> &v);
void show(vector<char> &v);
bool IsLegalOrder(string &s)
{
    vector<char> v;
    for (string::iterator iter=s.begin();iter!=s.end()-1;iter++)
    {
        v.clear();
        for (string::iterator iter_=iter+1;iter_!=s.end();iter_++)
        {
            if (*iter_<*iter)
                v.push_back(*iter_);
        }
        if (!IsDecreaseArray(v))
            return 0;
    }
    return 1;
}

bool IsDecreaseArray(vector<char> &v)
{
    if (v.empty())
        return 1;
    for (vector<char>::iterator iter=v.begin();iter!=v.end()-1;iter++)
        if (*iter<*(iter+1))
            return 0;
    return 1;
}

int main()
{
    string s="1234";
    int i=0;
    do{
        if (IsLegalOrder(s))
            cout<<s<<endl;
    }while (next_permutation(s.begin(),s.end()));
    return 0;
}
