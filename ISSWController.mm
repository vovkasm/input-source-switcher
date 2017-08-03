#import "ISSWController.h"
#import "ISSWInputSource.h"

@import Carbon;

void ISSWPrint(NSString* format, ...) NS_FORMAT_FUNCTION(1,2) NS_NO_TAIL_CALL;

@implementation ISSWController

#pragma mark - Public methods

- (void)showCurrentSource {
    ISSWInputSource* source = [self currentSource];
    ISSWPrint(@"%@\n", source.sourceID);
}

- (void)listAvailableSources {
    NSArray* sourcesList = [self allSelectableSources];

    for (ISSWInputSource* source in sourcesList) {
        ISSWPrint(@"%@\n", source.sourceID);
    }
}

- (BOOL)selectSource:(NSString *)pattern {
    ISSWInputSource* is = [self findInputSource:pattern];
    if (is != nil) {
        OSStatus status = TISSelectInputSource([is TISInputSource]);
        if (status == noErr) {
            return YES;
        } else {
            return NO;
        }
    }
    else {
        NSLog(@"Error: Cant find input source with id=%@", pattern);
        return NO;
    }
}

- (ISSWInputSource*)currentSource {
    return [ISSWInputSource wrapRelease:TISCopyCurrentKeyboardInputSource()];
}

#pragma mark - Helper methods

- (ISSWInputSource*)findInputSource:(NSString*)pattern {
    NSArray<ISSWInputSource*>* sourcesList = [self allSelectableSources];

    // find by id
    for (ISSWInputSource* source in sourcesList) {
        if ([pattern isEqualToString:source.sourceID]) {
            return source;
        }
    }

    // find by language
    for (ISSWInputSource* source in sourcesList) {
        if ([source.languages containsObject:pattern]) {
            return source;
        }
    }

    return nil;
}

- (NSArray*)allSelectableSources {
    NSDictionary* filter = @{
                             (__bridge NSString*)kTISPropertyInputSourceIsEnabled: @(YES),
                             (__bridge NSString*)kTISPropertyInputSourceIsSelectCapable: @(YES)
                             };

    NSMutableArray* list = [NSMutableArray array];

    CFArrayRef origList = TISCreateInputSourceList((__bridge CFDictionaryRef)filter, false);
    if (list == nil) return list;
    CFIndex origListCount = CFArrayGetCount(origList);
    for (CFIndex i = 0; i < origListCount; ++i) {
        TISInputSourceRef origSource = (TISInputSourceRef)CFArrayGetValueAtIndex(origList, i);
        [list addObject:[ISSWInputSource wrap:origSource]];
    }
    CFRelease(origList);

    return list;
}

@end

void ISSWPrint(NSString* format, ...) {
    va_list args;
    va_start(args, format);
    NSString* outString = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);

    [[NSFileHandle fileHandleWithStandardOutput] writeData:[outString dataUsingEncoding:NSUTF8StringEncoding]];
}

// vim-xkbswitch interface
extern "C" {
    static char buffer[1024];

    const char* Xkb_Switch_getXkbLayout(const char* /* unused */) {
        // Hack to update current input source for programs that do not use standard runloop (MacVim in console mode for ex)
        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0, false);

        buffer[0] = '\0';
        ISSWController* ctrl = [[ISSWController alloc] init];
        ISSWInputSource* source = [ctrl currentSource];

        [source.sourceID getCString:buffer maxLength:1024 encoding:NSUTF8StringEncoding];

        return buffer;
    }

    const char* Xkb_Switch_setXkbLayout(const char* newgrp) {
        ISSWController* ctrl = [[ISSWController alloc] init];

        NSString* inputName = [NSString stringWithCString:newgrp encoding:NSUTF8StringEncoding];
        [ctrl selectSource:inputName];

        return NULL;
    }
}
