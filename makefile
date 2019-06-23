mooanalyzer: lex.yy.c mooanalyzer.tab.c
		gcc -g lex.yy.c mooanalyzer.tab.c -o mooanalyzer

lex.yy.c: mooanalyzer.tab.c mooanalyzer.l
		flex mooanalyzer.l

mooanalyzer.tab.c: mooanalyzer.y
		bison -d mooanalyzer.y

clean: 
		rm -rf lex.yy.c mooanalyzer.tab.c mooanalyzer.tab.h mooanalyzer mooanalyzer.dSYM

