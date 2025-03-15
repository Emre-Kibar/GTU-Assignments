all: exec

exec: 
	bison -d ./gpp_interpreter.y
	flex ./gpp_lexer.l
	gcc lex.yy.c gpp_interpreter.tab.c -o gpp_interpreter
	./gpp_interpreter