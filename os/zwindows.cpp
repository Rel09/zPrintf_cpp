#include "zwindows.h"
#include <cstring>

const std::string  getTimestamp(const bool isPrint) {
    static std::string T(30, '\0');

    // Dont print anything
    if (!((isPrint && (TIMESTAMP == 1 || TIMESTAMP == 3)) || (!isPrint && ((TIMESTAMP == 2 || TIMESTAMP == 3)))))
        return "";

    // [DD-MM-YY] [HH:MM:SS]
    else if (TIMESTAMP_STYLE == 0) {
        time_t rawtime;
        struct tm timeinfo;
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(&T[0], 30, "[%d-%m-%y] [%H:%M:%S] ", &timeinfo);
    }

    // [Tue Jan 30 02:54:25 2024]
    else if (TIMESTAMP_STYLE == 1) {
        time_t rawtime;
        struct tm timeinfo;
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(&T[0], T.size(), "[%a %b %d %H:%M:%S %Y] ", &timeinfo);
    }
    
    // [30 Jan HH:MM:SS] 
    else if (TIMESTAMP_STYLE == 2) {
        time_t rawtime;
        struct tm timeinfo;
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(&T[0], T.size(), "[%d %b %H:%M:%S] ", &timeinfo);
    }

    // [HH:MM:SS] 
    else if (TIMESTAMP_STYLE == 3) {
        time_t rawtime;
        struct tm timeinfo;
        time(&rawtime);
        localtime_s(&timeinfo, &rawtime);
        strftime(&T[0], T.size(), "[%H:%M:%S] ", &timeinfo);
    }

    T.resize(strlen(T.c_str()));
    return T;
}
