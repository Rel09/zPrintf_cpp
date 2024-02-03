#include "zprintf.h"
#include <fstream>
#include <pthread.h>

// ------------ Windows ------------ (GCC & MSCV Tested)
#if defined(_WIN32) || defined(_WIN64)
#include "os/zwindows.h"
// ------------  MacOS  ------------ (GCC Tested)
#elif defined(__APPLE__)
#include "os/zmacos.h"
#endif

// Public     
void             Z::PRINTF(const bool is_stdout, const char* format, ...) {
    static Z        staticInstance;


    std::ostream*   OUTPUT = _selectOutput(is_stdout);
    std::ofstream*  OUTPUT_FILE = _selectFile(is_stdout);
    bool            isFileOpen = (OUTPUT_FILE && OUTPUT_FILE->is_open());

    // Print Timestamp
    if (OUTPUT) *OUTPUT << getTimestamp(true);
    if (OUTPUT_FILE) *OUTPUT_FILE << getTimestamp(false);

    // Print All
    va_list         args;
    va_start(args, format);
    while (*format) {
        if (_isRightFormat(format, 'd') || _isRightFormat(format, 'i')) {
            int i = va_arg(args, int);
            if (isFileOpen) *OUTPUT_FILE << i;
            if (OUTPUT) *OUTPUT << i;
            format++;
        }
        else if (_isRightFormat(format, 'f')) {
            float i = va_arg(args, double);
            if (isFileOpen) *OUTPUT_FILE << i;
            if (OUTPUT) *OUTPUT << i;
            format++;
        }
        else if (_isRightFormat(format, 's')) {
            const char* str = va_arg(args, const char*);
            const char *i = str ? str : "(null)";
            if (isFileOpen) *OUTPUT_FILE << i;
            if (OUTPUT) *OUTPUT << i;
            format++;
        }
        else if (_isRightFormat(format, 'c')) {
            char i = static_cast<char>(va_arg(args, int));
            if (isFileOpen) *OUTPUT_FILE << i;
            if (OUTPUT) *OUTPUT << i;
            format++;
        }
        else if (_isRightFormat(format, 'u')) {
            unsigned int i = va_arg(args, unsigned int);
            if (isFileOpen) *OUTPUT_FILE << i;
            if (OUTPUT) *OUTPUT << i;
            format++;
        }
        else {
            char i = *format;
            if (isFileOpen) *OUTPUT_FILE << i;
            if (OUTPUT) *OUTPUT << i;
        }

        format++;
    }
    if (isFileOpen) *OUTPUT_FILE << "\n";
    if (OUTPUT) *OUTPUT << "\n";
    va_end(args);
}

// Private
std::ostream* Z::_STDOUT = 0;
std::ostream* Z::_STDERR = 0;
std::ofstream* Z::_STDOUT_FILE = 0; 
std::ofstream* Z::_STDERR_FILE = 0;

std::ofstream*   Z::_selectFile(const bool is_stdout) {
    if (LOG >= 1 && LOG <= 3) {
        if ((LOG == 1 || LOG == 3) && is_stdout) {   
            if (!_STDOUT_FILE) _STDOUT_FILE = new std::ofstream(FILENAME_STDOUT);        
            return _STDOUT_FILE;
        }
        else if ((LOG == 2 || LOG == 3) && !is_stdout) {  
            if (!_STDERR_FILE) _STDERR_FILE = new std::ofstream(FILENAME_STDERR);    
            return _STDERR_FILE;  
        }
    }
    return 0;
}
std::ostream*    Z::_selectOutput(const bool is_stdout) {
    if (DEBUG >= 1 && DEBUG <= 3) {
        if ((DEBUG == 1 || DEBUG == 3) && is_stdout) {
            if (!_STDOUT) _STDOUT = new std::ostream(std::cout.rdbuf());
            return _STDOUT;
        }
        else if ((DEBUG == 2 || DEBUG == 3) && !is_stdout) { 
            if (!_STDERR) _STDERR = new std::ostream(std::cerr.rdbuf());
            return _STDERR;
        }
    }
    return 0;
}
bool             Z::_isRightFormat(const char *format, const char c) {
    return (*format == '%' && *(format + 1) == c);
}

Z::Z(){}
Z::~Z(){
    if (_STDOUT) delete _STDOUT;
    if (_STDERR) delete _STDERR;
    if (_STDOUT_FILE) {
        if (_STDOUT_FILE->is_open()) _STDOUT_FILE->close();
        delete _STDOUT_FILE;
    } 
    if (_STDERR_FILE) {
        if (_STDERR_FILE->is_open()) _STDERR_FILE->close();
        delete _STDERR_FILE;
    }
}
