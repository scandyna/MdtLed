# MdtLed

LED indicator based on Qt5

MdtLed is based on [Qt5](https://www.qt.io)
and also uses tools like CMake and Conan.

Conan is optional, but using it is easier.

To install and configure the different tools, you could take a look at
[Build and install C++](https://gitlab.com/scandyna/build-and-install-cpp) .

# Using MdtLed

This section describes how to use MdtLed in your project with CMake.

Modify your CMakeLists.txt to use MdtLed:
```cmake
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Mdt0 COMPONENTS Led REQUIRED)

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
conan install path/to/YourSource
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
cmake -D "MDT_CMAKE_MODULE_PREFIX_PATH=some/path/to/MdtCMakeModules" "path/to/MdtLedSource"
cmake-gui .
```

At least check/select the QT_PREFIX_PATH and CMAKE_INSTALL_PREFIX .

Build and install MdtLed:
```bash
make -j4 && make install
```

MdtLed will be build and installed in the location specified by CMAKE_INSTALL_PREFIX .

### Use MdtLed in your project

From your build directory, configure your build:
```bash
cmake -D "CMAKE_PREFIX_PATH=path/to/Qt5;path/to/MdtLed" "path/to/YourSource"
```
