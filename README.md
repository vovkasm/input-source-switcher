Command line input source switcher for Mac.
===========================================

Usage
-----

    input-source-switch [-h] [-l] [<input-source-id>]

    -h - show help message
    -l - list all selectable input sources
    -v - print version number

    If no arguments, show current input source
    If <input-source-id> - select specified input source

How to build
------------

    git clone https://github.com/vovkasm/input-source-switcher.git
    cd input-source-switcher
    mkdir build && cd build
    cmake ..
    make
    make install

How to develop with Xcode
-------------------------

    cd input-source-switcher
    mkdir xcode && cd xcode
    cmake -G Xcode ..
    open InputSourceSwitcher.xcodeproj

Author
------

Vladimir Timofeev

Licensing
---------

This projected is licensed under the terms of the MIT license.

