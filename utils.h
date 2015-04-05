#pragma once

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#include <string>

std::string stringFromCFString(CFStringRef cfStr);
void printInputSourceProperty(TISInputSourceRef inputSource, CFStringRef property);

class CFStringWrap {
public:
    CFStringWrap(const std::string& str) {
        _cfStr = CFStringCreateWithBytes(NULL, (const UInt8*)str.c_str(), str.length(), kCFStringEncodingUTF8, FALSE);
    }

    CFStringRef cfString() const { return _cfStr; }

    ~CFStringWrap() {
        CFRelease(_cfStr);
        _cfStr = NULL;
    }

private:
    CFStringRef _cfStr;

};

class CFDictionaryWrap {
public:
    CFDictionaryWrap() {
        _cfDict = CFDictionaryCreateMutable(NULL, 0, NULL, NULL);
    }

    CFMutableDictionaryRef cfDict() const { return _cfDict; }

    void set(CFStringRef key, CFTypeRef val) {
        CFDictionarySetValue(_cfDict, key, val);
    }

    ~CFDictionaryWrap() {
        CFRelease(_cfDict);
        _cfDict = NULL;
    }

private:
    CFMutableDictionaryRef _cfDict;
};
