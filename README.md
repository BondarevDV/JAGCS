# JAGCS
Joint architecture ground control station. Or just another ground control station:)

[![Build Status](https://travis-ci.org/MishkaRogachev/JAGCS.svg?branch=master)](https://travis-ci.org/MishkaRogachev/JAGCS)

Can be used as ground software for the MAVLink compatible drones, but other information protocols can be integrated.
Build with Qt and works on Windows/Linux/Android(Mac support will be later).


### Source code
Clone using git with command
```
git clone --recursive https://github.com/MishkaRogachev/JAGCS.git
```

### Dependencies
 
  * C++14 compiler
  * Qt 5.9 or higher
  * CMake 3.0 or higher

  GCC version 4.9 or higher required for MapBox GL QtLocation plugin
  ANGLE API is required for MapBox GL under windows

### Building desktop(Windows/Linux/Mac) application
```
mkdir build
cd build
cmake ..
make
```
### Building Android application
Cause https://bugreports.qt.io/browse/QTBUG-54666, use workaround, comment line with # 
```
set_property(TARGET Qt5::Core PROPERTY INTERFACE_COMPILE_FEATURES cxx_decltype)
```
in Qt5CoreConfigExtras.cmake file

```
mkdir build_android
cd build_android
export CMAKE_PREFIX_PATH=<path to Qt Android CMake, like "/opt/Qt/5.9.2/android_armv7/lib/cmake">
export ANDROID_API_LEVEL=16 (or needed)
export ANDROID_COMPILER_VERSION=4.9
export JAVA_HOME=<path to java, like "/usr/lib/jvm/java-8-openjdk-amd64">
export ANDROID_SDK=<path to android SDK>
export ANDROID_NDK=<path to android NDK>
cmake .. -DCMAKE_TOOLCHAIN_FILE=`pwd`/../3rdparty/qt-android-cmake/toolchain/android.toolchain.cmake
make -j5
adb install -r ./bin/QtApp-debug.apk
```

![alt tag](https://raw.githubusercontent.com/MishkaRogachev/JAGCS/master/ui.png)
