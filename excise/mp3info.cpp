#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct mp3info
{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char date[4];
    char other[30];
    char type[1];
};

void print_mp3info(mp3info &file)
{
    ofstream fout("/home/xiana/3.txt");
    fout<<file.tag<<endl<<file.title<<endl
        <<file.artist<<endl<<file.album<<endl
        <<file.date<<endl<<file.other<<endl<<file.type<<endl;
    return;
}


int main(int argc,char **argv)
{
    ifstream mp3;
    mp3info mp3_info;
    mp3.open("/home/xiana/IBelieve.mp3");

    if ( !mp3.is_open() )
        cerr<<"couldn't open this file\n";

    mp3.seekg(-128,ios::end);

    mp3.read(mp3_info.tag,3);
    mp3.read(mp3_info.title,30);
    mp3.read(mp3_info.artist,30);
    mp3.read(mp3_info.album,30);
    mp3.read(mp3_info.date,4);
    mp3.read(mp3_info.other,30);
    mp3.read(mp3_info.type,1);

    print_mp3info(mp3_info);

    return 0;
}
