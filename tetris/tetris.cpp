#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
using namespace std;

int tetris[8][4]={{2134667,566426},{2134097,2134090,2134032,2135114},{33361,2101826},{4227649,2626112},
                    {4617,4617},{4234,300112,2134656,33793},{2134658,33809,4232,300096},{-1}};
#define init_tetris() do{ for(int *t=tetris[0];*t>=0;++t) if (!(*t)) *t=*(t-2);}while(0)

struct Point{int x,y;};
static string playername;
static int score=0;
static int level=1;

Point operator+(Point a,Point b){return {a.x+b.x,a.y+b.y};}
struct Block{int type,direction,color;Point p;}Next;

inline void set_attr(int attr){cout<<"\033["<<attr<<"m";}
inline void set_pos(Point p){cout<<"\033["<<p.y+1<<";"<<p.x+1<<"H";}
template <typename T> inline void put_char(Point p,T ch,int attr=0){set_attr(attr);set_pos(p);cout<<ch;}
inline void set_point(Point *t,int m_tetris,int i){t->x=(m_tetris>>(-6*i+21))&7;t->y=(m_tetris>>(-6*i+18))&7;}
inline int set_color(int n){return 31+n;}
inline void hide_cursor(){cout<<"\033[?25l";}

void draw(Block b,bool erase=false);
void redraw(Block before,Block after);

class play_area
{
    int row,col,*p;
public:
	play_area(int r,int c):row(r),col(c),p(new int[r*c]){};
	~play_area(){delete p;}
	int check(int r,int c){return 0<=r&&r<row&&0<=c&&c<col;}
	int& get(int r,int c){return p[col*r+c];}
	int at(int r,int c){return check(r,c)?p[col*r+c]:1;}

	bool test_crash(Block b)
	{
	    int m_tetris=tetris[b.type][b.direction];
	    Point t;
	    for(int i=0;i!=4;++i)
	    {
	        set_point(&t,m_tetris,i);
			if(at(b.p.y+t.y,b.p.x+t.x))
                return false;
		}
		return true;
	}

	friend void draw(Block b,bool erase)
	{
        int m_tetris=tetris[b.type][b.direction];
        Point t;
        for (int i=0;i!=4;++i)
        {
            set_point(&t,m_tetris,i);
            put_char(b.p+t,(erase?' ':'#'),set_color(b.color));
        }
    }

    friend void redraw(Block before,Block after){draw(before,true);draw(after);}

	void redraw()
	{
		Point p;
		for(p.y=0;p.y!=row;++p.y)
			for(p.x=0;p.x!=col;++p.x)
				put_char(p,(at(p.y,p.x)?'#':' '),set_color(at(p.y,p.x)-1));

		set_attr(30);
		for(p.x=col,p.y=0;p.y!=row;++p.y)put_char(p,'|');
		for(p.x=0,p.y=row;p.x!=col+1;++p.x)put_char(p,'+');
		for (p.x=col+4,p.y=0;p.y<=14;p.y+=5)
		{
		    switch( p.y )
		    {
		        case 0:  put_char(p,"playername",set_color(Next.color));
                         p.y+=2;
                         put_char(p,playername);
                         break;
                case 7:  put_char(p,"score");
                         p.y+=2;
                         put_char(p,score);
                         break;
                case 14: put_char(p,"next shape");
                         break;
		    }
		    Block temp=Next;
		    temp.p={col+4,16};
            erase(); draw(temp);
		}
		hide_cursor();
	}

	void clear_line(Block b,int color=0)
	{
	    Point t;
	    int m_tetris=tetris[b.type][b.direction];
		for(int i=0;i!=4;++i)
		{
            set_point(&t,m_tetris,i);
            get(b.p.y+t.y,b.p.x+t.x)=color+1;
		}

		for(int i=row-1;i>=0;--i)
		{
			bool full_flag=true;
			bool empty_flag=true;
			for(int k=0;k!=col;++k)
                if (at(i,k)) empty_flag=false;
                else full_flag=false;

			if(full_flag && !empty_flag)
			{
			    for (int j=i;j>0;j--)
                    for(int k=0;k!=col;++k)
                        get(j,k)=get(j-1,k);
				score+=level*100;
				i++;
			}
			else if (!full_flag && empty_flag)
                break;
		}
		redraw();
	}

	void erase()
	{
        Point t;
        for (t.x=col+4;t.x<col+8;++t.x)
            for (t.y=16;t.y<20;++t.y)
                put_char(t,' ');
    }

    void gameover()
    {
        Point t;
        for (t.x=0; t.x<col; ++t.x)
        {
            for (t.y=0; t.y<row; ++t.y)
                put_char(t,'#');
            usleep(10000);
        }
    }
};

unsigned int get_microsecond()
{
    timeval t;
    gettimeofday(&t, NULL);
	return t.tv_sec * 1000000 + t.tv_usec;
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int main(int argc,char*argv[])
{

    cout<<"enter your name :\n";
    getline(cin,playername);
    cout<<"enter level u want to play (1-10) :\n";
    cin>>level;

	srand(time(0));
	system("stty raw -echo");
    system("clear");

	play_area a(20,20);
	init_tetris();
	Block pre={rand()%7,rand()%4,rand()%6,{0,0}};
	Next={rand()%7,rand()%4,rand()%6,{0,0}};
	int n=get_microsecond()+500000/level+50000;
	a.redraw();draw(pre);

	while(1)
	{
		if(!kbhit())
		{
			if(n<get_microsecond())
			{
				Block before=pre;pre.p.y+=1;
				if(a.test_crash(pre))redraw(before,pre);
				else
				{
					a.clear_line(before,pre.color);
					pre=Next;
					Next={rand()%7,rand()%4,rand()%6,{0,0}};
					a.redraw();
					if(a.test_crash(pre))draw(pre);
					else break;
				}
				n=get_microsecond()+500000/level+50000;
			}
			usleep(5000);
		}
		else
		{
			Block before=pre;
			switch(cin.get())
			{
				case 27:
					if(cin.get()==91)
					{
						switch(cin.get())
						{
							case 65:    pre.direction=(pre.direction+1)%4; break;
							case 66:    pre.p.y+=1;break;
							case 67:    pre.p.x+=1;break;
							case 68:    pre.p.x-=1;break;
						}
						if(a.test_crash(pre))redraw(before,pre);
						else pre=before;
					}
					else cin.get();
					break;
				case 'q': goto over;
			}
		}
	}
over:	a.gameover();
	return 0;
}


