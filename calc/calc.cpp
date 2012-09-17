#include <iostream>
#include <cstdlib>
#include <cctype>
#include <stack>
#include <list>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

enum OP{
    OP_POWER=4,
    OP_MULI=3,
    OP_DIVI=3,
    OP_PLUS=2,
    OP_SUB=2,
    OP_LSBR=1,
    OP_RSBR=1,
    OP_END=0,
    OP_ERROR=-1
};

double extract_num(string&, int*, int);
double calc_num(double, char, double);
int test(char);
void deal_space(string &);
void deal_expression(string &);

bool inline is_a_operate_sign(char c)
{return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^');}
bool inline is_legal_char(char c)
{return (isdigit(c) || test(c)!=OP_ERROR);}

stack<double> num;
stack<char> op;


int main()
{

    string exp;
    getline(cin,exp);
    deal_space(exp);
    deal_expression(exp);

    return 0;
}

void deal_space(string &express)
{
    for (string::iterator s=express.begin();s!=express.end();)
    {
        if (*s==' ')
        {
            int i=1;
            while(*(s+i)==' ') i++;
            s=express.erase(s,s+i);
        }
        else
            s++;
    }
    express.push_back('\0');
}

double extract_num(string &c, int* k, int sign)
{
    int start=*k;
    string str;
    while (c[*k] >= '0' && c[*k] <= '9' || c[*k] == '.')
        (*k)++;
    std::copy(c.begin()+start,c.begin()+(*k),back_inserter(str));
    double x=atof(str.c_str());
    return sign?(-x):(x);
}

double calc_num(double x,char op,double y)
{
    switch (op)
    {
        case '*': x *= y; break;
        case '/': x /= y; break;
        case '+': x += y; break;
        case '-': x -= y; break;
        case '^': x = pow(x, y); break;
        default : cout << "Error!!\n"; break;
    }
    return x;
}


int test(char op)
{
    switch (op)
    {
        case '^'  : return OP_POWER;
        case '*'  : return OP_MULI;
        case '/'  : return OP_DIVI;
        case '+'  : return OP_PLUS;
        case '-'  : return OP_SUB;
        case '('  : return OP_LSBR;
        case ')'  : return OP_RSBR;
        case '\0' : return OP_END;
        default   : return OP_ERROR;
    }
}

void deal_expression(string &exp)
{
    op.push('\0');
    int flag = 1,sign_flag=0,k=0,lbr_count=0;
    char c;

    while (flag)
    {
        c=exp[k];

        if (!is_legal_char(c))
        {
            cerr<<"you have a illegal char in expression\n";
            exit(EXIT_FAILURE);
        }
        else if (c >= '0' && c <= '9' || c == '.')
        {
            num.push(extract_num(exp, &k, sign_flag));
            sign_flag=0;
        }
        else if (c == '(' || (test(c) > test(op.top()) && c!=')'))
        {
            if (c== '(' )
                lbr_count++;
            op.push(c);
            k++;
        }
        else if (is_a_operate_sign(c) && (is_a_operate_sign(exp[k-1])) || (k==0 && c!=')'))
        {
            if (c=='+' || c=='-')
                sign_flag=(c=='-');
            else
            {
                cerr<<"error expressions!\n";
                exit(EXIT_FAILURE);
            }
            k++;
        }
        else if (c == '\0' && op.top()=='\0') flag = 0;
        else if (c == ')' && op.top()=='(')
        {
            op.pop();
            k++;
            lbr_count--;
        }
        else if (c == ')' && lbr_count==0 )
        {
            cerr<<"brackets do not match!\n";
            exit(EXIT_FAILURE);
        }
        else if (test(c) <= test(op.top()))
        {
            double y = num.top();
            num.pop();
            double x = num.top();
            num.pop();
            c = op.top();
            op.pop();

            num.push(calc_num(x,c,y));
        }
    }
    cout << endl << exp << " = " << num.top() << endl << endl;
}



