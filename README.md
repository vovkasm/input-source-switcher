Command line input source switcher for Mac.
===========================================

About
-----

This small utility for Apple OS X allows to easily switch input sources from a command line.
It's main purpose is to be used as a service in [vim-xkbswitch](https://github.com/lyokha/vim-xkbswitch) plugin.

Usage
-----

    issw [-h] [-l] [<input-source-id>]

    -h - show help message
    -l - list all selectable input sources
    -V - print version number

    If no arguments are specified, it prints the current input source.
    If <input-source-id> is specified, it selects the specified input source.

How to build
------------

    git clone https://github.com/vovkasm/input-source-switcher.git
    cd input-source-switcher
    cmake -B build
    cmake --build build
    cmake --install build

How to develop with Xcode
-------------------------

    cd input-source-switcher
    mkdir xcode && cd xcode
    cmake -G Xcode ..
    open InputSourceSwitcher.xcodeproj

Caveats
-------

There is an old bug in macOS related to handling input sources for CJK languages. If you're using the default APIs, when switching languages from the command line (i.e., without creating a GUI application), the switch won't work correctly for languages with composite input (like Japanese and Chinese). @laishulu has implemented a workaround for this issue in his implementation of a similar utility, available at [https://github.com/laishulu/macism](https://github.com/laishulu/macism). If this issue affects you, it's worth checking out his project.

Author
------

Vladimir Timofeev

Licensing
---------

This projected is licensed under the terms of the MIT license.
