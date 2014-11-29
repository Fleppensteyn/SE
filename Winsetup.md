#Getting a working build environment on windows

##Downloading a lot of stuff

###Git related
Get git: http://git-scm.com/download/win

Create a new directory for some stuff wherever you want, right click in explorer and click **Git Bash**.
This should open a bash shell, in which you can clone the following 2 repositories:
```
git clone https://github.com/Fleppensteyn/SE.git
git clone https://github.com/dlfcn-win32/dlfcn-win32.git
```
This'll get you our repository and some library you'll need to be able to compile it.

###Other downloads
Get wxWidgets source for windows: https://www.wxwidgets.org/downloads/

I grabbed the 7z as it's smaller and having a [7-zip](http://www.7-zip.org/) install should be handy anyway.

Unpack it wherever you want, though it might be easy to place it in the directory you created earlier in some subfolder like `wxw`.

Next step is getting the curl source: http://curl.haxx.se/download.html

I got the zip for 7.39.0, unpack it somewhere (preferably in the same directory as earlier).

##MinGW and msys

###Downloading and installing MinGW
Get mingw: http://sourceforge.net/projects/mingw/files/latest/download

Follow the installation, I personally don't care for the graphical interface, but whatever.
Make sure you know where MinGW is installed (`C:\MinGW` is the default, I'll be assuming this in the next steps).

We need to install more parts of MinGW now, so open a command prompt and:
```
cd C:\MinGW\bin
mingw-get install mingw32-base mingw32-gcc-g++ msys-base msys-unzip mingw32-pthreads-w32
```

###msys
If everything worked correctly msys will be installed in `C:\MinGW\msys`.
Navigate to and open `C:\MinGW\msys\1.0\msys.bat`.

This'll open msys for you. We'll be doing all building and whatever in msys, so you might want to add a link to it in your start menu or wherever you can quickly find it.
You might want to run `msys.bat` as an administrator to be able to copy dll's to `C:\Windows\System32` in a later step, but this can also be done manually.

Inside msys all paths work with forward slashes just like unix, all your existing drives should be mounted to their lowercase handle under / (so `C:\` is mapped to `/c/`).

After starting msys run the following to get access to the compilers among other things: `/postinstall/pi.sh`.
Answer questions, probably say `y` to most things and make sure you type the path correctly (e.g. `c:/MinGW`).

Now you should have an environment to build with, starting with the other dependencies for our program.

Navigate to that folder you made earlier (and if you unpacked some things elsewhere you'll need to go there too).

**Note:** You can run multiple instances of msys if you want to compile wxWidgets and libcurl at the same time (given that both of them take a while).

####dlfcn-win32
```
cd dlfcn-win32
./configure
make
make install
```

####libcurl
I'm assuming you downloaded 7.39.0, but I'm guessing you can modify the path by yourself if you didn't.
```
cd curl-7.39.0
./configure
make
make install
```

####wxWidgets
Assuming you unpacked to `wxw`, change it by yourself if you didn't.
```
cd wxw
./configure
make
make install
```
And to copy some dlls required to run do: `cp lib/*.dll /c/Windows/System32/`

Or copy the dlls from the `lib` subfolder to `C:\Windows\System32` manually.

After compiling those three things you should be set.

##Compiling our code
Go to our repository folder (the one you cloned at the start).
```
cd client/src
make
```
Use `./main.exe` inside msys to run it.

###Running it outside of msys
You're missing some files in System32 or in the same folder as main.exe.

If you have msys open as administrator and use the directories I advised this'll probably make it work
```
cp /c/MinGW/bin/libgcc_s_dw2-1.dll /c/MinGW/bin/libstdc++-6.dll /local/bin/libcurl-4.dll /c/Windows/System32/
```

Otherwise you can search for the dll's you're probably missing in these places.
```
C:\MinGW\bin\libgcc_s_dw2-1.dll
C:\MinGW\bin\libstdc++-6.dll
C:\MinGW\msys\1.0\local\bin\libcurl-4.dll
```
Get those in the same directory as main.exe or put them in `C:\Windows\System32` and you'll probably be able to run main.exe outside of msys.

