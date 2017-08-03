@import Foundation;

@interface ISSWController : NSObject

- (void)showCurrentSource;
- (void)listAvailableSources;
- (BOOL)selectSource:(NSString*)sourceId;

@end
