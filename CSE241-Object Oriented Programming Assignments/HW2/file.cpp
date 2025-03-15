#include "file.h"
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
using std::string;

namespace myOS{
    const string file::getCurrentDateFormatted() {
        // Get the current time point
        auto currentTimePoint = std::chrono::system_clock::now();

        // Convert the time point to a time_t object
        time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

        // Convert the time_t object to a string representation
        char currentTimeStr[100];
        strftime(currentTimeStr, sizeof(currentTimeStr), "%b %d %H:%M", localtime(&currentTime));
        
        return currentTimeStr;  
    }
}