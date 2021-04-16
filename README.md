# LexerGenerator
A C++ program that generates a lexer based on an input language.

## Input language
Input is based on regex (regular expressions). The following conventions apply for the notation of such expressions :

* `a` matches the letter 'a'
* `st` matches the string s, followed by the string t
* `s|t` matches the string s or the string t
* `s*` matches any number of occurrence of the string s, including 0
* `s+` matches one or more occurrence of the string s

All previously mentioned strings can indeed refer themselves to regular expressions. Priority rules are : 

1. You can put parenthesis to prioritize any expression over another. Parenthesis are always evaluated first.
2. `*` and `+` prioritize over other symbols,
3. Then `|`,
4. Finally single letters are evaluated,

This convention can introduce some problem, in particular when one wants to define a language containing any of the "operator characters". That's why the escape character `\` is defined.
You can use it different ways:

1. To escape previously mentioned characters, simply write `\` followed by the character you want (for example '\\*'). You can also escape parenthesis this way.
2. `\` itself can be escaped using another `\` in front of it, i.e. '\\\\'.
3. Standard C notation for non-printable characters apply, such as `\n` for a new line or `\t` for a tabulation.
4. You can escape a single white space by writing '\ ' if you ever need to. 
 

## Output and restoring DFA
This projects works with internal DFA (Deterministic Finite Automata). You do not need to know what they are in order to use the generator, but you should know how they are stored in files: 

    one integer, the number of final states
    the list of final states, one per line
    one integer, the number of states
    for each state
        two integers, the state number and the number of transition
        the list of all transitions starting from this state, one per line

The format for final states is:
    
    state : token

The format for transitions is:

    arrivalState : pattern

If you need an example, the file [testAutomaton.txt](testres/testAutomaton.txt) provides one in a human readable format.

Knowing this is not essential to use the project itself, but it can be if you need your own implementation of DFA, but you do not want to rewrite the complete generator (some algorithm inside can be pretty complicated...)

# Run the project on your machine
This project is provided only by its sources, but everything is present so that you can build it from scratch.

All you will need is CMake, which you can quickly and simply install on any OS (google "How to install CMake", you'll find plenty of tutorials explaining it much better than I).

There are different build that you can use for different purpose :

1. [TestBuild](#build-the-tests), to run the different unit test and verify that your build works correctly  
2. [AppBuild](#build-the-app), to run the app in the command line (you can specify which files to read from and write to)
3. [LexerGenerator](#build-the-library), to create the library that you can use later in other projects. (Work in progress)

Once you have built the project, the executable can be found at the root of the project. You can simply run it from the command line, as there is no GUI version planned (and there is no need for one).

## Build the tests
The TestBuild app is used to run the unit tests included in the project. Building this target will include the gtest framework, but this framework is downloaded onto the build folder no matter what target you choose to build.

You can build this target using the following commands:

    mkdir build
    cd build 
    cmake ../
    cmake --build .
    cd ..

The target will be built at the root of the project.

## Build the app
The AppBuild app is the main application, that you can run from the command line (it has no graphical interface !). No library is included in this executable, except for the C++ standard library. 

You can build this target using the following commands:

    mkdir build
    cd build 
    cmake ../
    cmake --build . --target AppBuild
    cd ..

The target will be built at the root of the project.

Warning : This build is not finished yet, it will compile but is useless at the time.

## Build the library
The library is built via the LexerGenerator rule. It is useful if you want to import the project in any other personal project.

You can build the target using the following commands : 

    mkdir build
    cd build 
    cmake ../
    cmake --build . --target LexerGenerator
    cd ..

Once build, the library is available in the lib folder. Headers are located in the [includes](includes) folder.

# Troubleshooting
If you find yourself having any problem with the project, please raise an issue on github. I will try to address the problem as soon as I can.

If you want to debug the project yourself, you can do so but PLEASE do not modify the unit tests, as I use them as a basis for other projects (you can add unit tests if necessary though).
