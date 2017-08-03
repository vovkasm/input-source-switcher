#include <unistd.h>
#include <iostream>
#include <string>

#include <Carbon/Carbon.h>

#include "issw_config.h"

#import "ISSWController.h"

enum RunMode { RM_showSelected, RM_listAvailable, RM_showUsage, RM_showVersion, RM_skip };

int
main(int argc, char* argv[]) {
    @autoreleasepool {
        // Workaround from http://lists.apple.com/archives/carbon-dev/2008/Sep/msg00009.html
        //
        ReceiveNextEvent(0, NULL, 0, 0, NULL);

        RunMode runMode = RM_showSelected;

        int ch;

        while ((ch = getopt(argc, argv, "hlV")) != -1) {
            switch (ch) {
                case 'l':
                    runMode = RM_listAvailable;
                    break;
                case 'V':
                    runMode = RM_showVersion;
                    break;
                case 'h':
                case '?':
                default:
                    runMode = RM_showUsage;
            }
        }

        ISSWController* newCtrl = [[ISSWController alloc] init];

        if (optind < argc) {
            argc -= optind;
            argv += optind;
            if (argc == 1) {
                BOOL res = [newCtrl selectSource:[NSString stringWithCString:argv[0] encoding:NSUTF8StringEncoding]];
                if (res) {
                    runMode = RM_showSelected;
                } else {
                    runMode = RM_showUsage;
                }
            }
            else {
                std::cerr << "Error: too many arguments" << std::endl;
                runMode = RM_showUsage;
            }
        }

        switch (runMode) {
            case RM_showSelected:
                [newCtrl showCurrentSource];
                break;
            case RM_listAvailable:
                [newCtrl listAvailableSources];
                break;
            case RM_showUsage:
                std::cout << "Usage: issw [-hlV] [<input-source-id>]" << std::endl;
                break;
            case RM_showVersion:
                std::cout << "Input Source Switcher version " << InputSourceSwitcher_VERSION_MAJOR << "." << InputSourceSwitcher_VERSION_MINOR << std::endl;
                break;
            case RM_skip:
                break;
        }
    }

    return 0;
}

