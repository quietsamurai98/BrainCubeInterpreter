# BrainCubeInterpreter
An interpreter for the [BrainCube](https://github.com/quietsamurai98/BrainCube) programming language.

## Building
So far, I have only tried building the project on a 64 bit Windows 10 computer, using MinGW and the Code::Blocks build tool.
It _should_ work with any compiler that supports the C++ Standard Library and conio.h, but it has only been tested with MinGW.  
**Note**: This project uses conio.h, meaning it is _only compatible with Windows_. I am planning to add Mac/UNIX support in the near future.

## Usage
After launching the executable, you will be asked if you want to enable parser logging, and the path to the BrainCube source code file.  
If parser logging is enabled, the following items will be logged to the console:  
 * The contents of the source code file.
 * The source code, after removing comments and whitespace characters.
 * A message describing each successfully parsed expression.
 
The path to the BrainCube source code file must not be wrapped in quotes, or contain backslashes.  
The path may be absolute or relative to the location of main.cpp, and must point directly to the source code file.  

Both the parser and the interpreter have very little in the way of error logging.  
If the program encounters an issue, it may show an error message and exit, but it could also silently halt or just straight up crash.

## To Do
 * Add Mac/UNIX support by finding a portable alternative to `getch()`
 * Improve parser error handling
   * Detect undeclared variables.
   * Give the line number of the source code where the error occurred.
   * Catch more kinds of errors.
   * Add warnings in addition to errors.
 * Improve the interpreter
   * Make it faster.
   * Make it more memory efficient.
   * Add debugging support.
   * Improve the garbage collector.

