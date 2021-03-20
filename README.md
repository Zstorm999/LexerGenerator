# LexerGenerator
A C++ program that generates a lexer based on an input language


# Run the project on your machine
This project is provided only by its sources, but everything is present so that you can build it from scratch.

All you will need is cmake, which you can quickly and simply install on any OS (google "How to install CMake", you'll find plenty of tutorials explaining it much better than I).

There are different build that you can use for different purpose :

1. [TestBuild](#test-build), to run the different unit test and verify that your build works correctly  
2. [AppBuild](#app-build), to run the app in the command line (you can specify which files to read from and write to)

## TestBuild
The TestBuild app is used to run the unit tests included in the project. Building this target will include the gtest framework, but this framework is downloaded onto the build folder no matter what target you choose to build.

You can build this target using the following commands:

    mkdir build
    cd build 
    cmake ../
    cmake --build .
    cd ..

The target will be built at the root of the project.

## AppBuild
The AppBuild app is the main application, that you can run from the command line (it has no graphical interface !). No library is included in this executable, except for the C++ standard library. 

You can build this target using the following commands:

    mkdir build
    cd build 
    cmake ../
    cmake --build . --target AppBuild
    cd ..

The target will be built at the root of the project.

# Troubleshooting
If you find yourself having any problem with the project, please raise an issue on github. I will try to address the problem as soon as I can.