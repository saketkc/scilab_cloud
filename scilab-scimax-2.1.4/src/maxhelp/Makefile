all: texi_yy.tab.h texi_lex.o texi_yy.tab.o execContext.o texiInterface.o texi2scidoc.o genListPnames.o
	gcc -o texi2scidoc texi2scidoc.o execContext.o texiInterface.o texi_yy.tab.o texi_lex.o genListPnames.o -ll

texi_lex.o: texi_lex.c
	gcc -c texi_lex.c

texi_yy.tab.o: texi_yy.tab.c
	gcc -c texi_yy.tab.c

texi_lex.c: texi_lex.lex
	flex texi_lex.lex ; mv -f lex.yy.c texi_lex.c

texi_yy.tab.c texi_yy.tab.h : texi_yy.y
	bison -d texi_yy.y

execContext.o: execContext.c
	gcc -c execContext.c

texiInterface.o: texiInterface.c
	gcc -c texiInterface.c

tex2scidoc.o : texi2scidoc.c
	gcc -c texi2scidoc.c

genListPnames.o : genListPnames.c
	gcc -c genListPnames.c

clean : 
	rm -f *.o texi_lex.c texi_yy.tab.* *~ texi2scidoc listPnames.txt