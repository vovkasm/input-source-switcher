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
    CFRelease(is);  
}

void
InputSourceController::listAvailable() const {
    CFDictionaryWrap filter;

    filter.set(kTISPropertyInputSourceIsEnabled, kCFBooleanTrue);
    filter.set(kTISPropertyInputSourceIsSelectCapable, kCFBooleanTrue);

    CFArrayRef sourceList = TISCreateInputSourceList(filter.cfDict(), false);
    if (sourceList == NULL)
        return;

    CFIndex cnt = CFArrayGetCount(sourceList);
    for (CFIndex i = 0; i < cnt; ++i) {
        TISInputSourceRef inputSource = (TISInputSourceRef)CFArrayGetValueAtIndex(sourceList, i);
        printInputSourceProperty(inputSource, kTISPropertyInputSourceID);
        printInputSourceProperty(inputSource, kTISPropertyInputSourceLanguages);
    }

    CFRelease(sourceList);
}

void
InputSourceController::select(const std::string& isId) const {
    CFStringWrap isIdStr(isId);
    CFDictionaryWrap filter;

    filter.set(kTISPropertyInputSourceID, isIdStr.cfString());

    CFArrayRef sourceList = TISCreateInputSourceList(filter.cfDict(), false);
    if (sourceList != NULL && CFArrayGetCount(sourceList) == 1) {
        TISInputSourceRef is = (TISInputSourceRef)CFArrayGetValueAtIndex(sourceList, 0);
        TISSelectInputSource(is);
        CFRelease(sourceList);
    }
    else {
        throw program_error(std::string("Error: Cant find input source with id=") + isId);
    }
}
