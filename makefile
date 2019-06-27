mooanalyzer: lex.yy.c mooanalyzer.tab.c
		gcc -g lex.yy.c mooanalyzer.tab.c funcs.c -o mooanalyzer

lex.yy.c: mooanalyzer.tab.c mooanalyzer.l
		flex mooanalyzer.l

mooanalyzer.tab.c: mooanalyzer.y funcs.h funcs.c allocatedMemory.h
		bison -d mooanalyzer.y

clean: 
		rm -rf lex.yy.c mooanalyzer.tab.c mooanalyzer.tab.h mooanalyzer mooanalyzer.dSYM

