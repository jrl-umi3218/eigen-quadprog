from conans import ConanFile, CMake, tools
import os
import subprocess

class EigenQuadProgTestConan(ConanFile):
    requires = "eigen-quadprog/latest@multi-contact/dev"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%sexample" % os.sep)
