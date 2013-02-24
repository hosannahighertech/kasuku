kasuku
======

Media Player from Tanzania Developers Foundation

=======
Installation Process
=====================
There are no Downloads yet since the development is on run.
However If you plan to build the sources and test for yourself
Then here are procedures:
1. Download MsysGit and install it (leavel all installer option to default unless you know what you are doing)
http://code.google.com/p/msysgit/downloads/list?q=full+installer+official+git

2. If you don't want to use the Cloning procedure above (not recommended for longtime testers) just skip it

3. Go to Kasuku repository
- If you skipped step 1 then download zip file by clicking on left side of the  repository labelled "zip"
- If you did not skip step 1 open folder you want to clone your files and right click it and select "git bash here". For Linux users just open terminal and cd to directory of choice. Both terminals can receive now the following command

git clone https://github.com/hosannahighertech/kasuku.git

For those who opted for zip file, just unzip contents and follow the next procedures


4. After the directory is cloned/unzipped then you can cd to that directory. You will see CodeLite workspace there. Now If you don't have CodeLite installed, download it from http://codelite.org. Choose CodeLite with mingw and wxWidgets 29 for easy. Alternatively you can compile yourself wxwidgets of version of your choice but not less than 2.9.4

5. Open CodeLite and then open workspace
Workspace->Open Workspace
- Point your codelite dialog to the path of your workspace in cloned directory.

Building VLC
=======================
Above procedures presumes that you have installed Libvlc: The Engine behind Kasuku
if not then follow below procedures

1. Ubuntu 
---------------------------------
-Install VLC media as easiest way to get plugins
-Install developing headers by terminal command
sudo apt-get install libvlc-dev

Windows
============
Download VLC .7z file (http://sourceforge.net/projects/vlc/files/2.0.5/win32/)
Unzip the folders include and lib in subfolder of application
add the path to include/ in the CodeLite compiler (right click project settings)
add the path to lib/ in CodeLite linker path. Then add the lib names in libraries
Recompile your program

