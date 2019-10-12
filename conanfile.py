from conans import ConanFile, CMake, tools

class MdtLedConan(ConanFile):
  name = "MdtLed"
  version = "0.1"
  license = "LGPL-3.0-only"
  url = "https://github.com/scandyna/MdtLed"
  description = "LED indicator based on Qt5"
  generators = "cmake"
  exports_sources="*" # Conan seems to be smart enough to not copy test_package/build

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def package(self):
    cmake = CMake(self)
    cmake.install()

  #def package_info(self):
    #self.
