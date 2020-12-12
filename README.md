![Build](https://img.shields.io/github/workflow/status/vfragoso/libtinymt/CMake?label=CMake%20Build&style=plastic)

# libtinymt
TinyMT is an efficient MersenneTwister pseudo random number generator proposed by Mutsuo Saito (Hiroshima University) and Makoto Matsumoto (The University of Tokyo).

This code implements TinyMT for 32 and 64 bits using C++ classes and it is heavily inspired on TinyMT version 1.1.2; see repo https://github.com/MersenneTwister-Lab/TinyMT.

# Unit Tests
The code provides unit tests implemented using GTest. To enable these tests, enable the flag ```-DBUILD_TESTING=On```. CMake will automatically will clone GTest from GitHub and will build the tests appropriately. Note that GTest requires a compiler that supports C++ 11.

# LICENSE
This project uses the 3-Clause BSD license. See [LICENSE](LICENSE) file for more information.

# NOTICE
This project includes components from TinyMT. For more licensing information see the [NOTICE](NOTICE) file.
