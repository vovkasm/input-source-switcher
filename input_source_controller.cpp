#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#include <iostream>
#include <sstream>

#include "formatters.h"
#include "input_source_controller.h"
#include "utils.h"

InputSourceController::InputSourceController() {
    
}

void
InputSourceController::showSelected() const {
    TISInputSourceRef is = TISCopyCurrentKeyboardInputSource();
    std::cout << InputSourceFormatter(is) << std::endl;
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
        std::cout << InputSourceFormatter(inputSource) << std::endl;
    }

    CFRelease(sourceList);
}

void
InputSourceController::select(const std::string& isId) const {
    TISInputSourceRef is = findInputSource(isId);
    if (is != NULL) {
        TISSelectInputSource(is);
        CFRelease(is);
    }
    else {
        throw program_error(std::string("Error: Cant find input source with id=") + isId);
    }
}

TISInputSourceRef
InputSourceController::findInputSource(const std::string& name) const {
    TISInputSourceRef is = findInputSourceById(name);
    if (is == NULL) {
        is = findInputSourceByLang(name);
    }

    return is;
}

TISInputSourceRef
InputSourceController::findInputSourceById(const std::string& isId) const {
    CFStringWrap isIdStr(isId);
    CFDictionaryWrap filter;
    filter.set(kTISPropertyInputSourceID, isIdStr.cfString());

    TISInputSourceRef is = NULL;

    CFArrayRef sourceList = TISCreateInputSourceList(filter.cfDict(), false);
    if (sourceList != NULL && CFArrayGetCount(sourceList) == 1) {
        is = (TISInputSourceRef)CFArrayGetValueAtIndex(sourceList, 0);
        CFRetain(is);
        CFRelease(sourceList);
    }

    return is;
}

TISInputSourceRef
InputSourceController::findInputSourceByLang(const std::string& lang) const {
    CFDictionaryWrap filter;
    filter.set(kTISPropertyInputSourceIsEnabled, kCFBooleanTrue);
    filter.set(kTISPropertyInputSourceIsSelectCapable, kCFBooleanTrue);

    CFArrayRef sourceList = TISCreateInputSourceList(filter.cfDict(), false);
    if (sourceList == NULL)
        return NULL;

    CFStringWrap requiredLangName(lang);

    TISInputSourceRef is = NULL;

    CFIndex cnt = CFArrayGetCount(sourceList);
    for (CFIndex i = 0; i < cnt; ++i) {
        TISInputSourceRef inputSource = (TISInputSourceRef)CFArrayGetValueAtIndex(sourceList, i);
        CFArrayRef inputSourceLanguages = (CFArrayRef)TISGetInputSourceProperty(inputSource, kTISPropertyInputSourceLanguages);
        CFIndex inputSourceLanguagesCount = CFArrayGetCount(inputSourceLanguages);
        for (CFIndex langIdx = 0; langIdx < inputSourceLanguagesCount; ++langIdx) {
            CFStringRef langName = (CFStringRef)CFArrayGetValueAtIndex(inputSourceLanguages, langIdx);
            if (CFStringCompare(langName, requiredLangName.cfString(), 0) == kCFCompareEqualTo) {
                is = inputSource;
                goto found;
            }
        }
    }
found:

    if (is) CFRetain(is);
    CFRelease(sourceList);

    return is;
}

// vim-xkbswitch interface
extern "C" {
    static char buffer[1024];

    const char* Xkb_Switch_getXkbLayout(const char* /* unused */) {
        // Hack to update current input source for programs that do not use standard runloop (MacVim in console mode for ex)
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);

        buffer[0] = '\0';
        try {
            InputSourceController ctrl;
            TISInputSourceRef is = TISCopyCurrentKeyboardInputSource();

            std::ostringstream os;
            os << InputSourceFormatter(is);
            CFRelease(is);

            const std::string& name = os.str();
            int len = name.length();
            if (len < 1024 && len > 0) {
                char* after_last = std::copy(name.begin(), name.end(), buffer);
                *after_last = '\0';
            }
        }
        catch( ... ) {
        }

        return buffer;
    }

    const char* Xkb_Switch_setXkbLayout(const char* newgrp) {
        try {
            InputSourceController ctrl;
            std::string is_id(newgrp);
            ctrl.select(is_id);
        }
        catch( ... ) {
        }

        return NULL;
    }
}

