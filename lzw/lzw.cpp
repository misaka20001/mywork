#include "lzw.h"
#include <new>
#include <cstring>

lzw_compress::lzw_compress(std::ofstream &fout)
{
    LZWToBytesIn = 0;
    LZWToBytesOut = 0;
    LZWCurrentBytesIn = 0;
    LZWCurrentBytesOut = 0;
    LZWErrorFlag = 0;
    havenibble = 0;

    LZWBestRatio = 100;
    LZWLastRatio = 100;

    _LZWOutInit(fout);
}

void lzw_compress::_LZWOutInit(std::ofstream &fout)
{
    char start_flag[] = MAGIC_NUMBER;
    std::cout<<start_flag<<"  "<<strlen(MAGIC_NUMBER)<<std::endl;
    fout.write( start_flag, strlen( start_flag )+1 );
}

int lzw_compress::_LZWOut(std::ofstream &fout, CodeType code)
{
    if ( havenibble ){
        olddata |= (code>>8) & 0x0f;
        fout.put(olddata);
        if ( fout.bad() ) return 4;
        fout.put(code);
        if ( fout.bad() ) return 4;
        LZWToBytesOut += 2;
        LZWCurrentBytesOut += 2;
        havenibble = 0;
    }else{
        olddata = (code>>4) & 0xff;
        fout.put(olddata);
        if ( fout.bad() ) return 4;
        LZWToBytesOut += 1;
        LZWCurrentBytesOut += 1;
        olddata = (code<<4) & 0xf0;
        havenibble = 1;
    }
    return 0;
}

int lzw_compress::_LZWOutFlush (std::ofstream &fout)
{
    if ( havenibble ){
        fout.put(olddata);
        if ( fout.bad() ) return 4;
        LZWToBytesOut += 1;
        LZWCurrentBytesOut += 1;
    }
    return 0;
}

IndexType lzw_compress::_LZWFind (CodeType currentcode, int in)
{
    IndexType ndx;
    int steps = 11, fullsearchtimes = 0;

    ndx = (currentcode << 7) ^ in;
    ndx = ndx % DICTIONARY_SIZE;

    while ( 1 ){
        if ( dictionary[ndx].code == UNUSED_FLAG ) break;
        if ( dictionary[ndx].previous == currentcode && \
                    dictionary[ndx].c == in )      break;

        ndx += steps;
        if ( ndx >= DICTIONARY_SIZE ){
            ndx -= DICTIONARY_SIZE;
            fullsearchtimes += 1;
            if (fullsearchtimes == 5) steps = 1;
        }
    }

    return ndx;
}


int lzw_compress::_LZWEncode (std::ifstream &fin, std::ofstream &fout, QProgressBar *bar)
{
    int in;
    CodeType i;
    IndexType freecode = FIRST_CODE_TO_USE;
    CodeType currentcode;
    IndexType idx;

    fin.seekg( 0, std::ios::end );
    int length = fin.tellg();
    fin.seekg( 0, std::ios::beg );

    bar->setRange( 0, length );
    bar->setValue( 0 );

    static int resettime=1;

    for (i=0; i<DICTIONARY_SIZE; i++)
        dictionary[i].code = UNUSED_FLAG;

    if ( (currentcode = fin.get()) == EOF )
        currentcode = END_OF_INPUT;
    else{
        LZWToBytesIn += 1;
        LZWCurrentBytesIn += 1;
        currentcode &= 0xff;

        while ( (in = fin.get()) != EOF ){
            LZWToBytesIn += 1;
            LZWCurrentBytesIn += 1;

            if ( LZWToBytesIn % 8196 == 0)
                bar->setValue( LZWToBytesIn );

            idx = _LZWFind( currentcode, in );
            if ( dictionary[idx].code == UNUSED_FLAG ){
                LZWErrorFlag = _LZWOut( fout, currentcode );

                if ( freecode < MAX_CODE ){
                    dictionary[idx].code = freecode++;
                    dictionary[idx].previous = currentcode;
                    dictionary[idx].c = in;
                }
                currentcode = in;

                if ( LZWCurrentBytesIn >= 10000 ){
                    unsigned int ratio;
                    ratio = ( LZWCurrentBytesOut * 100 ) / LZWCurrentBytesIn;

                    LZWCurrentBytesIn = 0;
                    LZWCurrentBytesOut = 0;

                    if ( ratio > LZWBestRatio ){
                        if ( ratio > 50 && ( ratio > 80 || ( ratio > LZWLastRatio + 10 ) ) ){
                            std::cout<<"the "<<resettime++<<"times to reset the dictionary\n";
                            std::cout<<"this time compressratio is about "<<ratio<<"%\n";

                            _LZWOut( fout, START_DICTIONARY_FLAG );
                            for ( i=0; i < DICTIONARY_SIZE; i++)
                                dictionary[i].code = UNUSED_FLAG;

                            freecode = FIRST_CODE_TO_USE;
                        }
                    }else{
                        LZWBestRatio = ratio;
                    }
                    LZWLastRatio = ratio;
                }
            }else{
                currentcode = dictionary[idx].code;
            }

            if ( LZWErrorFlag != 0 )
                break;
        }
    }

    LZWErrorFlag = _LZWOut( fout, currentcode );
    if ( ! LZWErrorFlag )
        LZWErrorFlag = _LZWOut( fout, END_OF_INPUT );
    if ( ! LZWErrorFlag )
        LZWErrorFlag = _LZWOutFlush( fout );

    if ( ! LZWErrorFlag ){
        std::cout<<"The input file contained "<<LZWToBytesIn<<" bytes"<<std::endl;
        std::cout<<"The output file contained "<<LZWToBytesOut<<" bytes"<<std::endl;

        if ( LZWToBytesIn != 0 )
            std::cout<<"The compression ratio is about "<<LZWToBytesOut*100/LZWToBytesIn<<"%"<<std::endl;
    }

    if ( fin.bad() )
        LZWErrorFlag = 1;
    if ( fout.bad() )
        LZWErrorFlag = 4;

    fin.close();
    fout.close();

    return LZWErrorFlag;

}

int lzw_compress::LZWEncode (std::ifstream &fin, std::ofstream &fout, QProgressBar *bar) { return _LZWEncode(fin,fout,bar); }

void lzw_compress::LZWErrorReason(int LZWError)
{
    std::cout<<"compression failed: ";
    switch ( LZWError ){
        case 1:
            std::cout<<"input error\n"; break;
        case 2:
            std::cout<<"malloc error\n"; break;
            break;
        case 4:
            std::cout<<"output error\n"; break;
        default:
            std::cout<<"unknown error\n"; break;
    }
}

lzw_decompress::lzw_decompress()
{
    DecodeBufferSize = 0;
    havenibble = 0;
    olddata = 0;
    incode = 0;
    freecode = FIRST_CODE_TO_USE;
    LZWErrorFlag = 0;
}

int lzw_decompress::_LZWInInit()
{
    if ( !DecodeBufferSize ){
        DecodeBufferSize = 1000;
        DecodeBuffer = new(std::nothrow) unsigned char[DecodeBufferSize];
        if ( DecodeBuffer == NULL ) return 2;
    }
    return 0;
}

int lzw_decompress::_LZWIn( std::ifstream &fin )
{
    int data;
    if ( havenibble ){
        incode = olddata << 8;
        if ( (data = fin.get()) == EOF ) return 4;
        incode |= ( data & 0xff );
        havenibble = 0;

        return 0;
    }else{
        if ( (data = fin.get()) == EOF ) return 4;
        incode = ( data & 0xff ) << 4;

        if ( (data = fin.get()) == EOF ) return 4;
        incode |= ( data >> 4 ) & 0x0f;

        olddata = data & 0x0f;
        havenibble = 1;

        return 0;
    }
}

int lzw_decompress::_LZWLoadBuffer( int count, CodeType code )
{
    if ( code >= freecode ){
        std::cout<<"LZWLoad : code "<<code<<" has out of range\n";
        return 0;
    }

    while ( code > PRESENT_MAX_CODE ){
        DecodeBuffer[count++] = dictionary[code].c;

        if ( count == DecodeBufferSize ){
            DecodeBufferSize += 1000;
            unsigned char* TempBuffer = new(std::nothrow) unsigned char[DecodeBufferSize];
            if ( TempBuffer == NULL ) return 0;
            memset( TempBuffer, 0, sizeof TempBuffer );
            memcpy( TempBuffer, DecodeBuffer, sizeof DecodeBuffer );
            delete [] DecodeBuffer;
            DecodeBuffer = TempBuffer;
            std::cout<<"DecodeBufferSize = "<<DecodeBufferSize<<std::endl;
        }

        code = dictionary[code].previous;
    }
    DecodeBuffer[count++] = code;

    return count;
}

int lzw_decompress::_LZWDecode( std::ifstream &fin, std::ofstream &fout, QProgressBar *bar )
{
    char buffer[10];
    unsigned int inchar;
    CodeType oldcode;
    unsigned int count;
    int currentByteIn = 0;

    fin.seekg( 0, std::ios::end );
    int length = fin.tellg();
    fin.seekg( 0, std::ios::beg );

    bar->setRange( 0, length );
    bar->setValue( 0 );

    fin.read( buffer, strlen( MAGIC_NUMBER ) + 1 );
    if ( strcmp ( buffer, MAGIC_NUMBER ) ){
        LZWErrorFlag = 1;
        goto done;
    }

    if ( LZWErrorFlag = _LZWInInit() ) goto done;

    while ( 1 ){
        freecode = FIRST_CODE_TO_USE;
        if ( LZWErrorFlag = _LZWIn( fin ) ) break;
        if ( incode == END_OF_INPUT ) break;

        inchar = incode;
        oldcode = incode;
        fout.put( incode );
        if ( fout.bad() ){
            LZWErrorFlag = 4;
            goto done;
        }

        while ( !( LZWErrorFlag = _LZWIn( fin ) ) ){
            if ( incode == END_OF_INPUT ) goto done;
            if ( incode == START_DICTIONARY_FLAG ) break;

            if ( havenibble ) currentByteIn += 2;
            else    currentByteIn += 1;

            if ( currentByteIn % 8196 == 0 )
                bar->setValue( currentByteIn );

            if ( incode >= freecode ){
                count = _LZWLoadBuffer( 1, oldcode );
                DecodeBuffer[0] = inchar;
            }else count = _LZWLoadBuffer( 0, incode );

            if ( count == 0 ){
                LZWErrorFlag = 2;
                goto done;
            }

            inchar = DecodeBuffer[ count-1 ];
            while ( count ){
                fout.put( DecodeBuffer[ --count ] );
                if ( fout.bad() ){
                    LZWErrorFlag = 4;
                    goto done;
                }
            }

            if ( freecode < MAX_CODE ){
                dictionary[ freecode ].c = inchar;
                dictionary[ freecode ].previous = oldcode;
                freecode++;
            }

            oldcode = incode;
        }
    }
done:
    fin.close();
    fout.close();
    return LZWErrorFlag;
}

int lzw_decompress::LZWDecode( std::ifstream &fin, std::ofstream &fout, QProgressBar *bar ){ return _LZWDecode( fin, fout, bar );}

void lzw_decompress::LZWErrorReason(int LZWError)
{
    std::cout<<"decompression failed: ";
    switch ( LZWError ){
        case 1:
            std::cout<<"invalid filetype\n"; break;
        case 2:
            std::cout<<"malloc error\n"; break;
        case 3:
            std::cout<<"input error\n";
            break;
        case 4:
            std::cout<<"output error\n"; break;
        default:
            std::cout<<"unknown error\n"; break;
    }
}









