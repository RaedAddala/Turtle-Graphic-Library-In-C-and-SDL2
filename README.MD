This Project Was Made Using **Visual Studio 2019** AS IDE, **C++**, **SDL2**.

## Why SDL2 : 

SDL2 is a great abstraction of the different OSs API so using SDL2 you can create a multi-platform application without actually dealing with their APIs 
and their different approaches to creating and handling windows, IO, threads, etc...

Also, it is a great abstraction of the process of creating windows, handling events, and threads, dealing with different hardware (different Joysticks and controllers) 
and putting pixels on the screen. So we have a program that works on all the major platforms and that is easier to write and maintain.

## NOTE :

+ SDL2 is dynamically linked to the project. So you need to put the DLL File to your executable directory. **(They must be in the same directory or else the loader 
will search for the DLL inside your *%PATH%* Directories (which may lead to version conflicts<sup> (1) </sup>))**.
+ All the Project Dependencies are Found in the Dependencies Folder.
+ Add the Include Folder to your Include argument when Compiling.
+ Add the libraries found in the Corresponding (*x64* or *x86* depending on your platform target) lib Folder to your *-l* argument when Compiling.


+ **To Change the Output Presented, change the code written in the *TurtleMagic.cpp* file.** 

<sup> (1) </sup> : In my case, I have nim installed in my system and apparently, it uses SDL2.dll (the x32 version). So, When I compiled, linked and started my x32 build, it worked. However, that wasn't the case for the x64 build and it didn't show me the DLL missing error due to the system always loading the nim DLL that I mentioned.
I didn't find the problem until I checked the loaded DLLs and their corresponding paths **(the Windows Debugger is just so awesome)**. It turned out that I was using an x86 DLL with the x64 DLL lib file which lead to the conflicts.

*This is a gem That I found when I was trying to make sense of the error : * 

CppCon 2017: “Everything You Ever Wanted to Know about DLLs” :https://www.youtube.com/watch?v=JPQWQfDhICA
