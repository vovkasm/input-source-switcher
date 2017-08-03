@import Foundation;
@import Carbon;

@interface ISSWInputSource : NSObject

@property (readonly) NSString* sourceID;
@property (readonly) NSArray<NSString*>* languages;
@property (readonly) TISInputSourceRef TISInputSource;

+ (instancetype)wrap:(TISInputSourceRef)tisSource;
+ (instancetype)wrapRelease:(TISInputSourceRef)tisSource;

- (instancetype)initWithTISInputSource:(TISInputSourceRef)tisSource;

@end
