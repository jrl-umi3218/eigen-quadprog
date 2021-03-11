# -*- coding: utf-8 -*-
#

from conans import python_requires
import conans.tools as tools
from conans.tools import SystemPackageTool, Version
import os

base = python_requires("Eigen3ToPython/latest@multi-contact/dev")

class EigenQuadProgConan(base.Eigen3ToPythonConan):
    name = "eigen-quadprog"
    version = "1.1.0"
    description = "QuadProg QP solver through Eigen3 library"
    topics = ("robotics", "optimization", "qp", "python")
    url = "https://github.com/jrl-umi3218/eigen-quadprog"
    homepage = "https://github.com/jrl-umi3218/eigen-quadprog"
    author = "Pierre Gergondet <pierre.gergondet@gmail.com>"
    license = "BSD-2-Clause"
    exports = ["LICENSE"]
    exports_sources = ["CMakeLists.txt", "conan/CMakeLists.txt", "binding/*", "cmake/*", "doc/*", "src/*"]
    generators = "cmake"
    settings = "os", "arch", "compiler", "build_type"
    requires = (
        "eigen/3.3.4@conan/stable"
    )

    def config_options(self):
        del self.options.python2_version
        del self.options.python3_version

    # build_requirements and system_requirements taken from https://github.com/conan-community/conan-lapack to fetch a Fortran compiler
    def build_requirements(self):
        if self.settings.os == "Windows":
            self.build_requires("mingw_installer/latest@multi-contact/3rd-party")
        elif self.settings.os == "Macos":
            self.build_requires("gfortran/10.2")

    def system_requirements(self):
        installer = SystemPackageTool()
        if tools.os_info.is_linux:
            if tools.os_info.with_pacman or \
                tools.os_info.with_yum:
                installer.install("gcc-fortran")
            else:
                installer.install("gfortran")
                versionfloat = Version(self.settings.compiler.version.value)
                if self.settings.compiler == "gcc":
                    if versionfloat < "5.0":
                        installer.install("libgfortran-{}-dev".format(versionfloat))
                    else:
                        installer.install("libgfortran-{}-dev".format(int(versionfloat.major)))

    def package_id(self):
        pass
