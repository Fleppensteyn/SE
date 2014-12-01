Curriculum Builder/Viewer
=========================

A project for Software Engineering 2014, developed by group 8.

##Description
A simple and intuitive desktop client to edit curricula with a drag-and-drop interface and the ability to export to a website so that other people can also view what you created.

##Requirements

###Desktop client
We developed this to work on Windows, Linux and Mac OS X, though Mac compatibility is more difficult to test in virtual machines.

Our Windows build setup is a bit complex, you can read a guide on how to set it up [here](Winsetup.md).

What you'll probably need:
* [wxWidgets 3.x](https://www.wxwidgets.org/)
* [libcurl](http://curl.haxx.se/download.html) (tested with 7.39.0)

We advise you to build these from source on all platforms, but for something like Ubuntu you can get pre-built binaries as long as you also get the development headers.

What we already include:
* [SQLite amalgamation](http://www.sqlite.org/) included [here](client/src/sqlite.zip)
* [smallsha1](https://code.google.com/p/smallsha1/) included [here](client/src/sha1)

###Website
Written in php, using php-sqlite for the database. Tested on nginx with php5-fpm, but it should work in most other environments.