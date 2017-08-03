#import "ISSWInputSource.h"

@interface ISSWInputSource () {
    TISInputSourceRef _tisSource;
}
@end

@implementation ISSWInputSource

+ (instancetype)wrap:(TISInputSourceRef)tisSource {
    return [[ISSWInputSource alloc] initWithTISInputSource:tisSource];
}

+ (instancetype)wrapRelease:(TISInputSourceRef)tisSource {
    ISSWInputSource* source = [[ISSWInputSource alloc] initWithTISInputSource:tisSource];
    CFRelease(tisSource);
    return source;
}

- (instancetype)initWithTISInputSource:(TISInputSourceRef)tisSource {
    self = [super init];
    if (self) {
        _tisSource = tisSource;
        CFRetain(_tisSource);
    }
    return self;
}

- (TISInputSourceRef)TISInputSource {
    return _tisSource;
}

- (NSString*)sourceID {
    return (__bridge NSString*)TISGetInputSourceProperty(_tisSource, kTISPropertyInputSourceID);
}

- (NSArray<NSString *> *)languages {
    return (__bridge NSArray<NSString*>*)TISGetInputSourceProperty(_tisSource, kTISPropertyInputSourceLanguages);
}

- (void)dealloc {
    if (_tisSource != nil) CFRelease(_tisSource);
}

@end
