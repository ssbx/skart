Build
-----
[![Build status](https://ci.appveyor.com/api/projects/status/jhnm6oxd26bc7f38?svg=true)](https://ci.appveyor.com/project/ssbx/federation)

Initialize submodules, build directory and compile all:
```sh
$ git submodule init
$ git submodule update
$ rm -rf build 
$ mkdir build
$ cd build 
$ cmake ..
$ make all
```

