# eigen-quadprog

[![License](https://img.shields.io/github/license/jrl-umi3218/eigen-quadprog)](https://opensource.org/licenses/LGPL-3.0)
[ ![Download](https://api.bintray.com/packages/gergondet/multi-contact/eigen-quadprog%3Amulti-contact/images/download.svg) ](https://bintray.com/gergondet/multi-contact/eigen-qld%3Amulti-contact/_latestVersion)
[![CI](https://github.com/jrl-umi3218/eigen-quadprog/workflows/CI%20of%20eigen-quadprog/badge.svg?branch=master)](https://github.com/jrl-umi3218/eigen-quadprog/actions?query=workflow%3A%22CI+of+eigen-quadprog%22)
[![Documentation](https://img.shields.io/badge/doxygen-online-brightgreen?logo=read-the-docs&style=flat)](http://jrl-umi3218.github.io/eigen-quadprog/doxygen/HEAD/index.html)

eigen-quadprog allow to use the QuadProg QP solver with the Eigen3 library.

## Installing

### Ubuntu LTS (16.04, 18.04, 20.04)

```bash
# Make sure you have required tools
sudo apt install apt-transport-https lsb-release
# Add our key
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key 892EA6EE273707C6495A6FB6220D644C64666806
# Add our repository (stable versions)
sudo sh -c 'echo "deb https://dl.bintray.com/gergondet/multi-contact-release $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/multi-contact.list'
# Use this to setup the HEAD version
# sudo sh -c 'echo "deb https://dl.bintray.com/gergondet/multi-contact-head $(lsb_release -sc) main" | sudo tee /etc/apt/sources.list.d/multi-contact.list'
# Update packages list
sudo apt update
# Install packages
sudo apt install libeigen-quadprog-dev
```

### Conan

Install the latest version using [conan](https://conan.io/)

```bash
conan remote add multi-contact https://api.bintray.com/conan/gergondet/multi-contact
# Install the latest release
conan install eigen-qld/latest@multi-contact/stable
# Or install the latest development version
# conan install eigen-qld/latest@multi-contact/dev
```


### Manual

#### Dependencies

To compile you need the following tools:

 * [Git]()
 * [CMake]() >= 2.8
 * [pkg-config]()
 * [doxygen]()
 * [g++]()
 * [gfortran]() (-DUSE_F2C=OFF)
 * [gcc]() (-DUSE_F2C=ON)
 * [Boost](http://www.boost.org/doc/libs/1_58_0/more/getting_started/unix-variants.html) >= 1.49
 * [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) >= 3.2

#### Building

```sh
git clone --recursive https://github.com/jrl-umi3218/eigen-quadprog
cd eigen-quadprog
mkdir _build
cd _build
cmake [options] ..
make && make intall
```

##### CMake options

 * `BUILD_TESTING` Enable unit tests building (ON/OFF, default: ON)
 * `USE_F2C` Build with fortran source code translated in C (slower runtime) (ON/OFF, default: OFF).
