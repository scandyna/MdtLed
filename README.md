# MdtLed

LED indicator based on Qt5

MdtLed is based on [Qt5](https://www.qt.io)
and also uses tools like [CMake](https://cmake.org) and [Conan](https://conan.io).

Conan is optional, but using it is easier.

To install and configure the different tools, you could take a look at
[Build and install C++ software](https://gitlab.com/scandyna/build-and-install-cpp) .

# Using MdtLed

This section describes how to use MdtLed in your project with CMake.

Modify your CMakeLists.txt to use MdtLed:
```cmake
find_package(Qt5 COMPONENTS Widgets REQUIRED)
   find_package(Mdt0 COMPONENTS Led REQUIRED)
find_package(Mdt0Led REQUIRED)

add_executable(myApp source.cpp)
target_link_libraries(myApp Qt5::Widgets Mdt0::Led)
```

## Using MdtLed with Conan

In your source directory, create a conanfile.txt with this content:
```conan
[requires]
MdtLed/0.1@scandyna/testing

[generators]
cmake_paths
```

Create a build directory and go to it:
```bash
mkdir build && cd build
```

Install the dependencies and configure the build:
```bash
conan install "path/to/YourSource"
cmake -D "CMAKE_TOOLCHAIN_FILE=conan_paths.cmake" "path/to/YourSource"
```

## Using MdtLed without Conan

### Build and install MdtLed

Install [MdtCMakeModules](https://github.com/scandyna/mdt-cmake-modules) which is required for the build configuration.

Get the sources:
```bash
git clone https://github.com/scandyna/MdtLed.git
```

Create a build directory and go to it:
```bash
mkdir build && cd build
```

Configure the build:
```bash
cmake -D "MDT_CMAKE_MODULE_PREFIX_PATH=path/to/MdtCMakeModules" -D "QT_PREFIX_PATH=path/to/Qt5/version/arch" "path/to/MdtLed-sources"
cmake-gui .
```

At least check/select the QT_PREFIX_PATH and CMAKE_INSTALL_PREFIX .

Build and install MdtLed:
```bash
make -j4 && make install
```

MdtLed will be build and installed in the location specified by CMAKE_INSTALL_PREFIX .

Example of a system wide install on a Debian MultiArch (`CMAKE_INSTALL_PREFIX=/usr`):
```
/usr/include/x86_64-linux-gnu/Mdt0/Mdt/Led.h
/usr/lib/x86_64-linux-gnu/libMdt0Led.so.0.x.y
/usr/lib/x86_64-linux-gnu/cmake/Mdt0/Mdt0Config.cmake
/usr/lib/x86_64-linux-gnu/cmake/Mdt0Led/Mdt0LedConfig.cmake
```

Example of a stand-alone install on Linux (`CMAKE_INSTALL_PREFIX=~/opt/MdtLed`):
```
~/opt/MdtLed/include/Mdt/Led.h
~/opt/MdtLed/lib/libMdt0Led.so.0.x.y
~/opt/MdtLed/lib/cmake/Mdt0Led/Mdt0LedConfig.cmake
```

If the selected generator support it, the DESTDIR install can be used.
For example, with make on Linux:
```bash
make install DESTDIR=/tmp/MdtLed
```
On a Debian MultiArch with ``CMAKE_INSTALL_PREFIX=/usr``, the result will be:
```
/tmp/MdtLed/usr/include/x86_64-linux-gnu/Mdt0/Mdt/Led.h
/tmp/MdtLed/usr/lib/x86_64-linux-gnu/libMdt0Led.so.0.x.y
/tmp/MdtLed/usr/lib/x86_64-linux-gnu/cmake/Mdt0/Mdt0Config.cmake
/tmp/MdtLed/usr/lib/x86_64-linux-gnu/cmake/Mdt0Led/Mdt0LedConfig.cmake
```

To install only a component using CMake prior to 3.15, the cmake_install.cmake script must be called.
For example, to install Mdt_Led_Dev, from the root of the build tree, call:
```bash
cmake -DCOMPONENT=Mdt_Led_Dev -P Led_Widgets/src/cmake_install.cmake
```
To use the DESTDIR mechanism, DESTDIR have to be exported (cannot be passed as -D). On Linux:
```bash
export DESTDIR=/tmp/MdtLed
cmake -DCOMPONENT=Mdt_Led_Dev -P Led_Widgets/src/cmake_install.cmake
```

### Configure the build of your project using MdtLed

From your build directory, configure your build:
```bash
cmake -D "CMAKE_PREFIX_PATH=path/to/Qt5;path/to/MdtLed" "path/to/YourSource"
```
