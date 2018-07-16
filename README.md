# Lex-Yacc
This is a team project for compiler course written in C++ with STL. We included two compoments in the project.

## Lex
Stimulating the flex, we designed and implemented a toy lexer for lexcial analyzing.

### features
* Support many [ERE](https://en.wikipedia.org/wiki/Regular_expression#POSIX_extended) syntax
* Convert RE to Reverse Polish notation
* Generate NFA according to suffix RE
* Optimize NFA to DFA with epsilon-closuring and subset construction
* Output compilable C codes with table-driven method

### User Guide
1. Prepare for a .l file
    The lexer accept a .l file with specific format, which read patterns(REs) and actions from the it. You can see an example file [here](https://github.com/lzy0505/Lex-Yacc/blob/master/Lex/Lex/fakelex.l).
2. Run the lexer
    
3. Compile lex.c

4. Do lexcial parsing


## Yacc

TODO
