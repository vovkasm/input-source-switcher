#include "formatters.h"
#include "utils.h"
#include <iostream>

std::ostream&
InputSourceFormatter::write(std::ostream& os) const {
    CFStringRef value = (CFStringRef)TISGetInputSourceProperty(_is, kTISPropertyInputSourceID);
    return os << stringFromCFString(value);
}

std::ostream& operator<<(std::ostream& os, const InputSourceFormatter& is) {
    return is.write(os);
}
