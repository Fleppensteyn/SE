Setup Guide for Curriculum Builder/Viewer
=========================================

Quick Guide
-----------
A quick list of things that will be enough to figure it out when you're somewhat used to building software.
####Desktop client
[Download](https://github.com/Fleppensteyn/SE/releases) a Windows binary if you don't care about editing the code.

Or build these libraries:
* [wxWidgets 3.x](https://www.wxwidgets.org/)
* [libcurl](http://curl.haxx.se/download.html)

And run `make` in our `client/src` directory.

####Website
Get some web server like [nginx](http://nginx.org/), and [php5](http://php.net/) with the [php-sqlite](http://php.net/manual/en/book.sqlite3.php) extension.

Use the repository directory structure and make the `www` the website root. Edit `config.php` to contain absolute paths for `DATA_ROOT` and `WWW_ROOT`.


Desktop client
--------------
If you're only interested in using the program and you use Windows, then you can use the latest one from the [releases on GitHub](https://github.com/Fleppensteyn/SE/releases).

For other operating systems and when you plan to modify the code you're going to need a working environment for building including getting the requirements.

A good place to start is getting the source code, either you have a supplied copy already or you can clone the repository on [GitHub](https://github.com/Fleppensteyn/SE).
```
git clone https://github.com/Fleppensteyn/SE.git
```

The source code can be found in the `client/src/` subdirectory and we include a Makefile to make building the project relatively easy.

If you're looking for a more extensive guide to set up an environment on windows we wrote one already and you can find it [here](Winsetup.md).

###Required libraries for building

First of all you'll need some of the basic requirements for building software using a Makefile, something like the package `build-essentials` on Ubuntu, the "Command Line Tools" on Mac OS X or MinGW/msys on Windows.

We have 2 main dependencies, wxWidgets (GUI) and libcurl (HTTP requests).
Depending on your platform there might be binaries available for these, but you can always build them from source too.

####wxWidgets 3.x
You can find out more on the [site](https://www.wxwidgets.org/).
We tested with wxWidgets 3.0.2, but you're probably fine if you use later versions as well.
While it does take a while to finish, the best way to get a working environment is to build from source.
Grab the sources on the [downloads page](https://www.wxwidgets.org/downloads/).

Building it is rather straightforward, an example:
```
mkdir build-dir
cd build-dir
../configure
make
make install
```
There are also packages for [Ubuntu/Debian](http://codelite.org/LiteEditor/WxWidgets30Binaries#toc2).
If you're building on Mac OS X you might run into some problems, try the wxWidgets portion of [this guide](http://codelite.org/Developers/BuildingCodeLiteOnAMac), it might save you some time.
And when building some of [these guides](https://wiki.wxwidgets.org/Install) might help as well.

Our Makefile currently uses `wx-config` to determine several of the compile flags, so if you've downloaded pre-built binaries it might be worth checking if it is actually installed on your path.

####libcurl
Download the sources [here](http://curl.haxx.se/download.html).
We tested with 7.39.0, but other versions might work as well.

Building libcurl is about as straightforward as it gets:
```
mkdir build-dir
cd build-dir
../configure
make
make install
```
There are also binaries available for various platforms, but we never tried those since it doesn't take much time to build from sources and it seems to work well.

Our Makefile currently uses `curl-config` to determine several of the compile flags, so if you've downloaded pre-built binaries it might be worth checking if it is actually installed on your path.

####Other libraries
These are included in the repository and automatically built into the project, so you don't need to worry about getting them elsewhere.

Links: [SQLite](http://www.sqlite.org/) | [smallsha1](https://code.google.com/p/smallsha1/).

###Building our project
Navigate to `client/src/` and type `make`.

After a short while of building it will probably finish and you can run it by typing `./CurriculumBuilder`.

###Important files
There are a lot of files in the project, and these are some of the important ones:

####Used at runtime
* **CurriculumBuilder**
  - The executable for the program
* **client.db**
  - The SQLite database (editing with external tools possible, but in no way advised)
* **API_URL**
  - The url for the api on the website, so if you can use your own hosting
  - If the file is unreadable it will use the default `http://se.putman.pw/api.php`
  - When there are errors they will be shown in the status bar
* **client_icon.ico**
  - The icon (not required for the static windows builds, might not show up on Mac OS X)

####Used for development
* **Makefile**
  - Cross-platform Makefile, uses `wx-config` and `curl-config` for includes and flags.
* **sqlite.zip**
  - Unpacked into `client/src/sqlite/` by the Makefile, included this way to save some space on the repository.
* **Makefile.w32static**
  - Compiling a static Windows binary using MinGW, more info below.
* **icon.res**
  - Compiled resource file used to embed icon in the static build
* **iconres.rs**
  - Used to compile a resource file with the icon for the static build

All of the remaining files are just the code, you can look at the [class diagram](uml/UML_Class_Diagram_client.png) for more of an idea of the structure.

###Static builds for Windows
This is a small explanation of an approach to doing this, not incredibly detailed.
I'm doing this in an msys setup like the one I described earlier.

For this to work you need to build wxWidgets and libcurl again, because you need static libraries.
You probably want to use a different prefix during configuration this time to not replace your working dynamic libraries and to make building a lot easier.

From now on I'll assume the prefix `/c/build/statwx` (mapped to `C:\build\statwx\` outside msys).

####Building static wxWidgets
Navigate to the source directory again and do something like this:
```
mkdir static-build
cd static-build
../configure --disable-debug_flag --disable-shared --enable-unicode --prefix /c/build/statwx
make
make install
```

####Building static libcurl
Libcurl is very extensive in possible protocols and everything, but we only use simple HTTP requests so to make the static building less complex we disable almost everything during configuration.
Navigate to the source directory again and do something like this:
```
mkdir static-build
cd static-build
../configure --disable-shared --prefix=/c/build/statwx --disable-ftp --disable-ldap --disable-telnet --disable-dict --disable-tftp --disable-imap --disable-pop3 --disable-smtp --without-ssl --disable-gopher --disable-rtsp --disable-file --disable-debug --disable-manual
make
make install
```

####Building the static binary
If you used a different prefix for the static libraries, modify `Makefile.w32static` with your own prefix.

Navigate to `client/src/` and type `make -f Makefile.w32static clean` to clean up object files compiled against different wxWidgets/libcurl.

Type `make -f Makefile.w32static` and wait for it to finish.

Now you have `CurriculumBuilderStatic.exe`, bundle it with `client.db` and `API_URL` and you have a distributable package.
If there's any errors then they are probably solvable, but we're not officially supporting this type of build.

Website
-------
The website, in contrast, is rather easy to set up.
The requirements are a web server and php5 with the php-sqlite extension.
We used [nginx](http://nginx.org/) with [php5-fpm](http://php.net/manual/en/install.fpm.php) because we wanted to have low memory consumption (running on a 128MiB RAM vps).

For our website you only need to make the `www` folder public and put `config.php` in the directory directly below it.
The way we structure it on the repository works well, so we advise you just keep it that way.
In the `config.php` file you need to make sure that the `DATA_ROOT` and `WWW_ROOT` point to the correct directories using an absolute path.

We use two SQLite databases, one with data from the client `client.db` and another with data for user accounts `server.db`.
The client uses `api.php` for logging in and uploading the database and the other files in `www`, so you'll want to change the `API_URL` file you use with the client to your new `api.php` location in order to use your own hosting (our hosting won't last forever).

Databases
---------
As mentioned before we are using two different databases on the server and one database on the client side.
The database for the client contains all the courses and curricula and it can be exported to the website.
The website has the client database you exported and the database with user accounts that is only used to log in on the website or from the client.

We include databases with the correct structure and test data from the concept document.
But if you want to create your own databases you can generate them using the [sql files we provide](databases/).
* **courses.sql**
  - The structure for the `courses` table.
  - Including all the courses from the concept document.
* **curriculum.sql**
  - The structure for the 7 curriculum related tables.
  - An approximation of the curricula from the concept document.
* **usertable.sql**
  - Structure for the server-side users table.
  - Contains a few test accounts.

This should be enough to get you set up.