#include <unistd.h>
#include <iostream>
#include <string>

#include "issw_config.h"
#include "input_source_controller.h"

enum RunMode { RM_showSelected, RM_listAvailable, RM_showUsage, RM_showVersion, RM_skip };

int
main(int argc, char* argv[]) {
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
    InputSourceController ctrl;

    if (optind < argc) {
        argc -= optind;
        argv += optind;
        if (argc == 1) {
            try {
                ctrl.select(std::string(argv[0]));
                runMode = RM_showSelected;
            }
            catch (program_error& e) {
                std::cerr << e.what() << std::endl;
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
            ctrl.showSelected();
            break;
        case RM_listAvailable:
            ctrl.listAvailable();
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

    return 0;
}

