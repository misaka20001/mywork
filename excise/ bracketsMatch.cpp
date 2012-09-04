#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cassert>

struct StkElement{
        char opener;
        int line_no;
    };

class Stack{
    private:
    StkElement *m_base;
    int m_top;
    int m_min_stack;
    int m_max_stack;
    int m_stack_size;
    public:
    Stack(int how_many);
    void ClearStack();
    int push(StkElement *s);
    int pop(StkElement *s);
    StkElement * ViewElement(int where);
};

Stack::Stack(int how_many)
{
    assert(how_many>0);
    m_stack_size=how_many;
    m_min_stack=0;
    m_max_stack=how_many-1;
    m_top=-1;
    m_base=new StkElement[how_many];
    if (!m_base)
    return;
}

void Stack::ClearStack()
{
    m_top=-1;
}

int Stack::push(StkElement *s)
{
    if (m_top==m_max_stack)
    return 0;
    m_top++;
    memmove(&(m_base[m_top]),s,sizeof(StkElement));
    return 1;
}

int Stack::pop(StkElement *s)
{
    if (m_top==-1)
    return 0;
    memmove(s,&(m_base[m_top]),sizeof(StkElement));
    m_top--;
    return 1;
}

StkElement* Stack::ViewElement(int where)
{
    if (m_top==-1)
    return (NULL);
    return (&(m_base[m_top-where]));
}

int main()
{
    std::ifstream fin;
    std::cout<<"please enter file path\n";
    char file[20];
    fgets(file,20,stdin);
    file[strlen(file)-1]=0;
    fin.open(file);
    if(!fin.is_open())
    {
        std::cerr<<"couldn't open this file\n";
        return 0;
    }
    Stack s(40);
    StkElement *stk_el=new StkElement;
    if(!stk_el)
    {
        std::cerr<<"error\n";
        return 0;
    }
    int line_count=0,i;
    char c,buffer[128];
    while(!fin.eof())
    {
        line_count++;
        fin.getline(buffer,127);
        for(i=0;buffer[i];i++)
        {
            switch(c=buffer[i])
            {
                case '(':
                case '{':
                case '[':
                stk_el->opener=c;
                stk_el->line_no=line_count;
                if(!s.push(stk_el))
                {
                    std::cerr<<"out of stack size\n";
                    return 0;
                }
                break;
                case ')':
                case '}':
                case ']':
                if (!s.pop(stk_el))
                    std::cerr<<"stray "<<c<<" at line "<<line_count<<std::endl;
                else
                {
                    std::cout<<"now c is "<<c<<" pre is "<<stk_el->opener<<std::endl;
                }
                if ( (c==')' && stk_el->opener!='(' ) ||
                     (c=='}' && stk_el->opener!='{' ) ||
                     (c==']' && stk_el->opener!='[' ) )
                     std::cerr<<c<<" at line "<<line_count<<" doesn't match "<<stk_el->opener<<" at line "<<stk_el->line_no<<std::endl;
                     break;
                default:
                continue;
            }
        }
    }

    if (!s.ViewElement(0))
        while(s.pop(stk_el)!=0)
        std::cerr<<c<<" at line "<<line_count<<" doesn't match "<<stk_el->opener<<" at line "<<stk_el->line_no<<std::endl;
        std::cerr<<"error check completed\n";
        fin.close();
        return 1;
}
