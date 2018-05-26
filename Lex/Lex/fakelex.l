%{
#include <stdio.h>

%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P           ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS          ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%%
"/*"			addToken("below are comments");
"//"[^\n]*      addToken("below are comments");


"auto"			{ 
	 addToken("AUTO"); 
	}
"_Bool"			{ 
	 addToken("BOOL"); 
	}
"break"			{ 
	addToken("BREAK"); 
	}
"case"			{ 
	 addToken("CASE"); 
	}
"char"			{ 
	 addToken("CHAR"); 
	}
"_Complex"		{ 
	 addToken("COMPLEX"); 
	}
"const"			{ 
	 addToken("CONST"); 
	}
"continue"		{ 
	 addToken("CONTINUE"); 
	}
"default"		{ 
	 addToken("DEFAULT"); 
	}
"do"			{ 
	 addToken("DO"); 
	}
"double"		{ 
	 addToken("DOUBLE"); 
	}
"else"			{ 
	 addToken("ELSE"); 
	}
"enum"			{ 
	 addToken("ENUM"); 
	}
"extern"		{ 
	 addToken("EXTERN"); 
	}
"float"			{ 
	 addToken("FLOAT"); 
	}
"for"			{ 
	 addToken("FOR"); 
	}
"goto"			{ 
	 addToken("GOTO"); 
	}
"if"			{ 
	 addToken("IF"); 
	}
"_Imaginary"		{ 
	 addToken("IMAGINARY"); 
	}
"inline"		{ 
	 addToken("INLINE"); 
	}
"int"			{ 
	 addToken("INT"); 
	}
"long"			{ 
	 addToken("LONG"); 
	}
"register"		{ 
	 addToken("REGISTER"); 
	}
"restrict"		{ 
	 addToken("RESTRICT"); 
	}
"return"		{ 
	 addToken("RETURN"); 
	}
"short"			{ 
	 addToken("SHORT"); 
	}
"signed"		{ 
	 addToken("SIGNED"); 
	}
"sizeof"		{ 
	 addToken("SIZEOF"); 
	}
"static"		{ 
	 addToken("STATIC"); 
	}
"struct"		{ 
	 addToken("STRUCT"); 
	}
"switch"		{ 
	 addToken("SWITCH"); 
	}
"typedef"		{ 
	 addToken("TYPEDEF"); 
	}
"union"			{ 
	 addToken("UNION"); 
	}
"unsigned"		{ 
	 addToken("UNSIGNED"); 
	}
"void"			{ 
	 addToken("VOID"); 
	}
"volatile"		{ 
	 addToken("VOLATILE"); 
	}
"while"			{ 
	 addToken("WHILE"); 
	}

{L}({L}|{D})*		{ 
	 addToken("IDENTIFIER"); 
	}

0[xX]{H}+{IS}?		{ 
	 addToken("CONSTANT"); 
	}
0[0-7]*{IS}?		{ 
	 addToken("CONSTANT"); 
	}
[1-9]{D}*{IS}?		{ 
	 addToken("CONSTANT"); 
	}
L?'(\\.|[^\\'\n])+'	{ 
	 addToken("CONSTANT"); 
	}

{D}+{E}{FS}?		{ 
	 addToken("CONSTANT"); 
	}
{D}*"."{D}+{E}?{FS}?	{ 
	 addToken("CONSTANT"); 
	}
{D}+"."{D}*{E}?{FS}?	{ 
	 addToken("CONSTANT"); 
	}
0[xX]{H}+{P}{FS}?	{ 
	 addToken("CONSTANT"); 
	}
0[xX]{H}*"."{H}+{P}{FS}?     { 
	 addToken("CONSTANT"); 
	}
0[xX]{H}+"."{H}*{P}{FS}?     {
	addToken("CONSTANT"); 
	}

L?\"(\\.|[^\\"\n])*\"	{ 
	 addToken("STRING_LITERAL"); 
	}

"..."			{ 
	 addToken("ELLIPSIS"); 
	}
">>="			{ 
	 addToken("RIGHT_ASSIGN"); 
	}
"<<="			{ 
	 addToken("LEFT_ASSIGN"); 
	}
"+="			{ 
	 addToken("ADD_ASSIGN"); 
	}
"-="			{ 
	 addToken("SUB_ASSIGN"); 
	}
"*="			{ 
	 addToken("MUL_ASSIGN"); 
	}
"/="			{ 
	 addToken("DIV_ASSIGN"); 
	}
"%="			{ 
	 addToken("MOD_ASSIGN"); 
	}
"&="			{ 
	 addToken("AND_ASSIGN"); 
	}
"^="			{ 
	 addToken("XOR_ASSIGN"); 
	}
"|="			{ 
	 addToken("OR_ASSIGN"); 
	}
">>"			{ 
	 addToken("RIGHT_OP"); 
	}
"<<"			{ 
	 addToken("LEFT_OP"); 
	}
"++"			{ 
	 addToken("INC_OP"); 
	}
"--"			{ 
	 addToken("DEC_OP"); 
	}
"->"			{ 
	 addToken("PTR_OP"); 
	}
"&&"			{ 
	 addToken("AND_OP"); 
	}
"||"			{ 
	 addToken("OR_OP"); 
	}
"<="			{ 
	 addToken("LE_OP"); 
	}
">="			{ 
	 addToken("GE_OP"); 
	}
"=="			{ 
	 addToken("EQ_OP"); 
	}
"!="			{ 
	 addToken("NE_OP"); 
	}
";"			{ 
	addToken(";"); 
	}
("{"|"<%")		{ 
	 addToken("{"); 
	}
("}"|"%>")		{ 
	 addToken("}"); 
	}
","			{ 
	 addToken(","); 
	}
":"			{ 
	 addToken(":"); 
	}
"="			{ 
	 addToken("="); 
	}
"("			{ 
	 addToken("("); 
	}
")"			{ 
	 addToken(")"); 
	}
("["|"<:")		{ 
	 addToken("["); 
	}
("]"|":>")		{ 
	 addToken("]"); 
	}
"."			{ 
	 addToken("."); 
	}
"&"			{ 
	 addToken("&"); 
	}
"!"			{ 
	 addToken("!"); 
	}
"~"			{ 
	 addToken("~"); 
	}
"-"			{ 
	 addToken("-"); 
	}
"+"			{ 
	 addToken("+"); 
	}
"*"			{ 
	 addToken("*"); 
	}
"/"			{ 
	 addToken("/"); 
	}
"%"			{ 
	 addToken("%%"); 
	}
"<"			{ 
	addToken("<"); 
	}
">"			{ 
	 addToken(">"); 
	}
"^"			{ 
	 addToken("^"); 
	}
"|"			{ 
	 addToken("|"); 
	}
"?"			{ 
	 addToken("?"); 
	}

[ \t\v\n\f]		addToken("SPACE"); 
.			addToken("DOT"); 

%%

int yywrap(void)
{
	return 1;
}