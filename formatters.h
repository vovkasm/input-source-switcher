#pragma once
#include "pre.h"
#include <iosfwd>

class InputSourceFormatter {
public:
    InputSourceFormatter(TISInputSourceRef inputSource) : _is(inputSource) {
        CFRetain(_is);
    }
    ~InputSourceFormatter() {
        CFRelease(_is);
    }
    std::ostream& write(std::ostream& os) const;

private:
    TISInputSourceRef _is;
};

std::ostream& operator<<(std::ostream& os, const InputSourceFormatter& is);
