#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED

#include <iostream>
#include <fstream>
#include <QProgressBar>

#define PRESENT_MAX_CODE        256
#define END_OF_INPUT            256
#define START_DICTIONARY_FLAG   257
#define FIRST_CODE_TO_USE       258
#define MAX_CODE                4096
#define UNUSED_FLAG             4096
#define DICTIONARY_SIZE         5021

typedef unsigned short CodeType;
typedef unsigned short IndexType;
typedef unsigned long  CountType;
typedef unsigned short ErrorType;

#define MAGIC_NUMBER "LZW12"

typedef struct Dictionary_compress{
    unsigned char c;
    CodeType code;
    CodeType previous;
}Dictionary_compress;

typedef struct Dictionary_decompress{
    unsigned char c;
    CodeType previous;
}Dictionary_decompress;

class lzw_compress{
    private:
    Dictionary_compress dictionary[DICTIONARY_SIZE];

    CountType LZWToBytesIn;
    CountType LZWToBytesOut;
    CountType LZWCurrentBytesIn;
    CountType LZWCurrentBytesOut;
    ErrorType LZWErrorFlag;

    unsigned int LZWBestRatio;
    unsigned int LZWLastRatio;

    int havenibble;
    int olddata;


    private:
    int _LZWEncode (std::ifstream &fin, std::ofstream &fout, QProgressBar *bar);
    IndexType _LZWFind (CodeType currentcode, int in);
    void _LZWOutInit (std::ofstream &fout);
    int _LZWOutFlush (std::ofstream &fout);
    int _LZWOut (std::ofstream &fout, CodeType code);

    public:
    lzw_compress(std::ofstream &fout);
    int LZWEncode (std::ifstream &fin, std::ofstream &fout, QProgressBar *bar);
    void LZWErrorReason (int LZWError);
    ~lzw_compress(){}
};

class lzw_decompress{
    private:
    Dictionary_decompress dictionary[MAX_CODE];

    unsigned char* DecodeBuffer;
    unsigned int DecodeBufferSize;
    ErrorType LZWErrorFlag;
    IndexType freecode;

    int havenibble;
    int olddata;
    CodeType incode;

    private:
    int _LZWInInit();
    int _LZWIn( std::ifstream &fin );
    int _LZWLoadBuffer( int count, CodeType code );
    int _LZWDecode( std::ifstream &fin, std::ofstream &fout, QProgressBar *bar );

    public:
    lzw_decompress();
    int LZWDecode( std::ifstream &fin, std::ofstream &fout, QProgressBar *bar );
    void LZWErrorReason (int LZWError);
    ~lzw_decompress(){ delete [] DecodeBuffer; }
};

#endif // LZW_H_INCLUDED
