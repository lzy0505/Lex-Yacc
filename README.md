# Lex-Yacc
This is a team project for compiler course written in C++ with STL. We included two compoments in the project.

## Lex
Stimulating the flex, we designed and implemented a toy which can generate a simple lexer for lexcial analyzing.

### Features
* Support many [ERE](https://en.wikipedia.org/wiki/Regular_expression#POSIX_extended) syntax
* Convert RE to Reverse Polish notation
* Generate NFA according to suffix RE
* Optimize NFA to DFAo with epsilon-closuring, subset construction and equivalent classes construction
* Output compilable C codes with table-driven method

### User Guides
1. Prepare for a .l file

    The program accept a .l file with specific format, which read patterns(REs) and actions from the it. You can find an example file [here](https://github.com/lzy0505/Lex-Yacc/blob/master/Lex/Lex/fakelex.l).
2. Build and run the program

    Build the Lex solution with MS VS 2017.You will get a execuable file Lex.exe.
    The program have two mode. One is lex mode, for pure lexcial analysing, in which you will get a lexer that run independently, print the result in console. Another mode is yacc mode, which is designed as a part of yaccer, to be compiled with Yacc codes together.
    
    If you just want to do lexcial analyze, run
    ```
    .\Lex.exe lex path/to/file/lex.l
    ```
    If you just want to do syntax analyze as well, run
    ```
    .\Lex.exe yacc path/to/file/lex.l
    ```
    
3. Compile lex.c

    You can comiple the generated lex.c file with c compiler.
    ```
    clang .\lex.c -o lexer.exe
    ```

4. Do lexcial analysis
    
    Run
    ```
    .\lexer.exe path/to/file/test.c
    ```
    Then you can see the token sequence splited by space in the opening console window.


## Yacc

As a further step, we developed a easy tool which can generatr yaccer for syntax analysis. We selected LR(1) parsing as the parsing method. The generated yaccer output the productions sequence.


### Features
* Support .y files parsing
* Convert CFG to Layered NFA
* Solve shift-reduce/reduce-reduce conflicts
* Generate ACTION and GOTO table according to FA.
* Output compilable C codes with table-driven method

### User Guides
1. Prepare for a .y file

    The program accept a .y file with specific format, which read TOKEN definitions and CFGs from the it. You can find an example file [here](https://github.com/lzy0505/Lex-Yacc/blob/master/Yacc/Yacc/yacc.y).
2. Build and run the program

    Build the Yacc solution with MS VS 2017.You will get a execuable file Yacc.exe.
    
    Run
    ```
    .\Yacc.exe path/to/file/yacc.y
    ```
    
3. Compile y.tab.c and y.tab.h with lex.c
    
    Yaccer only accept token sequence as input, so you have to compile lex.c with y.tab.c and y.tab.h together to give yaccer the capability to generate token sequence from code files.
    
    The lex.c file should be gotten from yacc mode.

    Then do the compilation
    ```
    clang .\y.tab.c .\y.tab.h .\lex.c -o yaccer.exe
    ```

4. Do syntax analysis
    
    Run
    ```
    .\yaccerr.exe path/to/file/test.c
    ```
    Then you will see the production sequence in the opening console window.

