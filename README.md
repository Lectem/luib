#LUIB - Lectem's User Interface Bullshit

A small C++ UI library based (for now) on sf2dlib.


#Requirements
* [DevkitPro](devkitpro.org) with DevkitARM release 44+
* [ctrulib](https://github.com/smealum/ctrulib/) (latest working commit confirmed to work : [5a28a7](https://github.com/smealum/ctrulib/tree/5a28a7398a5777438a9c03bf97a492c6a7224306))
* [libsf2d](https://github.com/xerpi/sf2dlib/) (latest working commit confirmed to work : [bd014d](https://github.com/xerpi/sf2dlib/tree/bd014db1451291554e5d124d8bcdb21e9d220542)))

#Documentation


#FAQ

##My element isn't displayed !
The way LUIB displays text is really crappy for now, and is eating a lot of draw calls.
You probably reached the limit of draw calls for sf2dlib. Please consider using less text or use images instead.
Note : It will be fixed later on with texture caching.

##Why C++11 and not old C++ ?
Quick answer : Because.
Longer answer : Lambdas, smart pointers, move semantics, stuff.

##Why C++11, I like plain old C !
UI is a pain to develop and maintain in C only.

##Any plannings for a C API ?
No. 
Though if you really want one, you can fork the project and I'll gladly merge it if it's nicely done.
