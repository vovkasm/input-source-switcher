#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#include "utils.h"

#include <iostream>

std::string
stringFromCFString(CFStringRef cfStr) {
    CFIndex length = CFStringGetLength(cfStr);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8);
    char * buffer = new char [maxSize];
    buffer[0] = '\0';
    CFStringGetCString(cfStr, buffer, maxSize, kCFStringEncodingUTF8);
    std::string ret(buffer);
    delete[] buffer;
    return ret;
}

void
printInputSourceProperty(TISInputSourceRef inputSource, CFStringRef property) {
    CFTypeRef value = (CFTypeRef)TISGetInputSourceProperty(inputSource, property);
    if (value == NULL) return;

    CFRetain(value);
    CFTypeID valueType = CFGetTypeID(value);
    if (valueType == CFBooleanGetTypeID()) {
        std::cout << stringFromCFString(property) << " : " << (CFBooleanGetValue((CFBooleanRef)value) ? "yes" : "no") << std::endl;
    }
    else if (valueType == CFStringGetTypeID()) {
        std::cout << stringFromCFString(property) << " : " << stringFromCFString((CFStringRef)value) << std::endl;
    }
    else if (valueType == CFArrayGetTypeID()) {
        std::cout << stringFromCFString(property) << " : [";
        CFIndex len = CFArrayGetCount((CFArrayRef)value);
        for (CFIndex i = 0; i < len; ++i) {
            const void* elem = CFArrayGetValueAtIndex((CFArrayRef)value, i);
            if (elem != NULL) {
                if (CFGetTypeID(elem) == CFStringGetTypeID()) {
                    if (i > 0) {
                        std::cout << ',';
                    }
                    std::cout << '"' << stringFromCFString((CFStringRef)elem) << '"';
                }
            }

        }

        std::cout << "]" << std::endl;
    }
    CFRelease(value);
}
