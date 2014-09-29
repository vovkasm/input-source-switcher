#include "pre.h"
#include "input_source_controller.h"
#include "utils.h"
#include <iostream>

InputSourceController::InputSourceController() {
    
}

void
InputSourceController::showSelected() const {
    TISInputSourceRef is = TISCopyCurrentKeyboardInputSource();
    printInputSourceProperty(is, kTISPropertyInputSourceID);
}

void
InputSourceController::listAvailable() const {
    CFStringRef keys[] = {kTISPropertyInputSourceIsEnabled, kTISPropertyInputSourceIsSelectCapable};
    CFTypeRef vals[] = {kCFBooleanTrue, kCFBooleanTrue};
    CFDictionaryRef filterDict = CFDictionaryCreate(NULL, (const void**)keys, (const void**)vals, (CFIndex)2, NULL, NULL);
    CFArrayRef sourceList = TISCreateInputSourceList(filterDict, false);
    if (sourceList == NULL)
        return;

    CFIndex cnt = CFArrayGetCount(sourceList);
    for (CFIndex i = 0; i < cnt; ++i) {
        TISInputSourceRef inputSource = (TISInputSourceRef)CFArrayGetValueAtIndex(sourceList, i);
        printInputSourceProperty(inputSource, kTISPropertyInputSourceID);

    }
}

void
InputSourceController::select(const std::string& isId) const {
    CFStringRef keys[] = {kTISPropertyInputSourceID};
    CFTypeRef vals[] = {CFStringCreateWithBytes(NULL, (const UInt8*)isId.c_str(), isId.length(), kCFStringEncodingUTF8, FALSE)};
    CFDictionaryRef filterDict = CFDictionaryCreate(NULL, (const void**)keys, (const void**)vals, (CFIndex)1, NULL, NULL);
    CFArrayRef sourceList = TISCreateInputSourceList(filterDict, false);
    if (sourceList != NULL && CFArrayGetCount(sourceList) == 1) {
        TISInputSourceRef is = (TISInputSourceRef)CFArrayGetValueAtIndex(sourceList, 0);
        TISSelectInputSource(is);
    }
    else {
        throw program_error(std::string("Error: Cant find input source with id=") + isId);
    }
}
