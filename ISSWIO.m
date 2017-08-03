#import "ISSWIO.h"

void ISSWPrint(NSString* format, ...) {
    va_list args;
    va_start(args, format);
    NSString* outString = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);

    [[NSFileHandle fileHandleWithStandardOutput] writeData:[outString dataUsingEncoding:NSUTF8StringEncoding]];
}

void ISSWPrintError(NSString* format, ...) {
    va_list args;
    va_start(args, format);
    NSString* outString = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);

    [[NSFileHandle fileHandleWithStandardError] writeData:[outString dataUsingEncoding:NSUTF8StringEncoding]];
}
