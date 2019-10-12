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
find_package(MdtLed REQUIRED)

add_executable(myApp source.cpp)
target_link_libraries(myApp Qt5::Widgets MdtLed)
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

### Use MdtLed in your project

From your build directory, configure your build:
```bash
cmake -D "CMAKE_PREFIX_PATH=path/to/Qt5;path/to/MdtLed" "path/to/YourSource"
```
