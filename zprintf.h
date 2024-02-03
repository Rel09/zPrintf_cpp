#pragma once
#include <iostream>
#include <stdarg.h>

#define ZPRINTF Z::PRINTF

#define DEBUG 1
//      0 = Don't print anything
//      1 = Display stdout messages
//      2 = Display stderr messages
//      3 = Display all messages
#define LOG 2
//      0 = Don't save to File
//      1 = Save stdout to FILENAME_STDOUT
//      2 = Save stderr to FILENAME_STDERR
//      3 = Both
#define TIMESTAMP 3
//      0 - Don't Display
//      1 - Print only
//      2 - File only
//      3 - Both
#define TIMESTAMP_STYLE 3
//      0 = [DD-MM-YY] [HH:MM:SS]
//      1 = [Tue Jan 01 HH:MM:SS YYYY]
//      2 = [30 Jan HH:MM:SS]
//      3 = [HH:MM:SS]
#define FILENAME_STDERR "STDERR_LOG.txt"
#define FILENAME_STDOUT "STDOUT_LOG.txt"

class Z {
public:
    static void             PRINTF(const bool is_stdout, const char* format, ...);
private:
    static std::ostream*    _STDOUT;
    static std::ostream*    _STDERR;
    static std::ofstream*   _STDOUT_FILE;
    static std::ofstream*   _STDERR_FILE;
    
    static std::ofstream    *_selectFile(const bool is_stdout);
    static std::ostream     *_selectOutput(const bool is_stdout);
    static bool             _isRightFormat(const char* format, const char c);
    
    Z();
    ~Z();
};

// ------ Extra Stuff :) ------
#define zuint8_t   unsigned char
#define zuint16_t  unsigned short
#define zuint32_t  unsigned int
#define zuint64_t  unsigned long long

#define zint8_t    char
#define zint16_t   short
#define zint32_t   int
#define zint64_t   long long
// --------- Colors ---------
// Reset Color
#define zRESET       "\x1B[0m"

/// Effects
#define zBOLD        "\x1B[1m"
#define zUNDERLINE   "\x1B[4m"
#define zREVERSED    "\x1B[7m"

// Colors
#define zBLACK       "\x1B[30m"
#define zRED         "\x1B[31m"
#define zGREEN       "\x1B[32m"
#define zYELLOW      "\x1B[33m"
#define zBLUE        "\x1B[34m"
#define zMAGENTA     "\x1B[35m"
#define zCYAN        "\x1B[36m"
#define zWHITE       "\x1B[37m"
#define zBRIGHT_RED     "\x1B[91m"
#define zBRIGHT_GREEN   "\x1B[92m"
#define zBRIGHT_YELLOW  "\x1B[93m"
#define zBRIGHT_BLUE    "\x1B[94m"
#define zBRIGHT_MAGENTA "\x1B[95m"
#define zBRIGHT_CYAN    "\x1B[96m"

// Background's Colors
#define zBG_BLACK    "\x1B[40m"
#define zBG_RED      "\x1B[41m"
#define zBG_GREEN    "\x1B[42m"
#define zBG_YELLOW   "\x1B[43m"
#define zBG_BLUE     "\x1B[44m"
#define zBG_MAGENTA  "\x1B[45m"
#define zBG_CYAN     "\x1B[46m"
#define zBG_WHITE    "\x1B[47m"
