#include <iostream>
#include <string>
using namespace std;

void extract_num_to_replace(string &,int);
string deal_expression(string &);

int main()
{
    string s1;
    while(getline(cin,s1))
        cout<<deal_expression(s1)<<endl;
    return 0;
}

string deal_expression(string &s)
{
    int i;
    while (1)
    {
        if (i=(s.find_first_of(")"))!=string::npos)
            extract_num_to_replace(s,i);
        else if ((i=s.find_first_of("*/"))!=string::npos)
            extract_num_to_replace(s,i);
        else if ((i=s.find_first_of("+-"))!=string::npos)
            extract_num_to_replace(s,i);
        else return s;
    }
}

void extract_num_to_replace(string &in, int k)
{
    double num1,num2,num;
    string str_num1,str_num2,str_num;
    if (in[k]==')'){
        string::size_type i=in.find_last_of("(",k-1);
        std::copy(in.begin()+i+1,in.begin()+k,back_inserter(str_num1));
        in.replace(i,k-i+1,deal_expression(str_num1));
        return;
    }
    string::size_type i=in.find_last_of("+-*/",k-1);
    if (i==string::npos) i=-1;
    std::copy(in.begin()+i+1,in.begin()+k,back_inserter(str_num1));
    string::size_type j=in.find_first_of("+-*/",k+1);
    if (j==string::npos) j=in.size();
    if (j==k+1) {in.replace(k,2,(in[j]^in[k])?"-":"+"); return;}
    std::copy(in.begin()+k+1,in.begin()+j,back_inserter(str_num2));

    num1=stod(str_num1); num2=stod(str_num2);
    switch(in[k]){
        case '+' : num=num1+num2; break;
        case '-' : num=num1-num2; break;
        case '*' : num=num1*num2; break;
        case '/' : num=num1/num2; break;
    }
    str_num=to_string((long double)num);

    in.replace(i+1,j-i-1,str_num);
}
