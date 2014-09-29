#pragma once
#include "pre.h"
#include <string>

std::string stringFromCFString(CFStringRef cfStr);
void printInputSourceProperty(TISInputSourceRef inputSource, CFStringRef property);