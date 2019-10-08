# Design Patterns

## Overview
This repo is a slate to various Design Patterns.

## Build Instructions
* Create a new directory, **build**
* Cd into **build**, run **cmake -DCMAKE_BUILD_TYPE=Debug ..** for debug configuration and **cmake -DCMAKE_BUILD_TYPE=Release ..** for release configuration
* Run **make**, after the above command completes
* Targets are copied over to **{Project.Dir}/bin/{Target}/dp**

## Pre-requisites
* C++17 compiler. gcc/clang/vc++ later versions support C++17 features. To install one, either build from source or use a package manager for your platform. `std::filesystem` needs to be supported by your compiler
* CMake. Version 3.7.0 or greater. The project uses CMake to generate the build files  

## Tests
Not implemented.

## License
Free as in free speech.

## Contributions & Questions
Send me a mail on <raj@diskodev.com> or tweet me at <https://twitter.com/#!/rajkumar_p>
