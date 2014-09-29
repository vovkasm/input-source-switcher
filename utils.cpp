#include "utils.h"
#include <iostream>

std::string
stringFromCFString(CFStringRef cfStr) {
    CFIndex length = CFStringGetLength(cfStr);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
    char * buffer = (char *)malloc(maxSize);
    buffer[0] = '\0';
    CFStringGetCString(cfStr, buffer, maxSize, kCFStringEncodingUTF8);
    std::string ret(buffer);
    free(buffer);
    return ret;
}

void
printInputSourceProperty(TISInputSourceRef inputSource, CFStringRef property) {
    CFTypeRef value = (CFTypeRef)TISGetInputSourceProperty(inputSource, property);
    if (CFGetTypeID(value) == CFBooleanGetTypeID()) {
        std::cout << stringFromCFString(property) << " : " << (CFBooleanGetValue((CFBooleanRef)value) ? "yes" : "no") << std::endl;
    }
    else if (CFGetTypeID(value) == CFStringGetTypeID()) {
        std::cout << stringFromCFString(property) << " : " << stringFromCFString((CFStringRef)value) << std::endl;
    }
}
