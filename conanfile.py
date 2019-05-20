from conans import ConanFile, CMake

class ParametrizableConan(ConanFile):
    name = "Parametrizable"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = "cmake/*", "include/*", "src/*"

    description = """Provides an interface to attach parameters to objects and manipulate them via a Qt UI"""

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_EXAMPLES"] = False
        cmake.configure(source_dir="%s/cmake" % self.source_folder)
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = [self.name]
