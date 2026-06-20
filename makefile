.POSIX:	
.PHONY:	all clean install release source uninstall
.SUFFIXES:

PREFIX 	?= /usr/local

all:	pt

pt:	pt.c elements.c elements.h fmt.c fmt.h table.c table.h pt.h pt.g.c pt.g.h pt.l.c pt.l.h
	c99 -pedantic -o $@ pt.c pt.g.c pt.l.c elements.c fmt.c table.c

pt.l.c pt.l.h:	pt.l
	lex -D_POSIX_C_SOURCE=200809L -o pt.l.c pt.l

pt.g.c pt.g.h:	pt.g
	gengetopt <pt.g
	sed -E 's/(\\n)?[[:blank:]]+\(default=.*\)//' <pt.g.c >pt.g.c.tmp
	mv -f pt.g.c.tmp pt.g.c

elements.h:	elements.template.h elements.tsv
	cp elements.template.h elements.h
	./generate_elements_header <elements.tsv >> elements.h

elements.tsv:	elements.csv
	./csv2tsv elements.csv >elements.tsv

elements.csv:
	curl -o elements.csv 'https://raw.githubusercontent.com/dedolist/open-data/refs/heads/master/data/science/periodic-table-detailed/data.csv'

clean:
	rm -f pt elements.h pt.g.? pt.l.? pt*.tar.gz pt.1.gz Makefile

source:
	rm -f pt_source.tar.gz
	tar -cf pt_source.tar *.c *.h pt.g pt.l pt.1 csv2tsv makefile COPYING
	gzip pt_source.tar

release:	pt
	rm -f pt.tar.gz
	sed 6,43d makefile | sed '2c .PHONY:	install uninstall'> Makefile
	tar -cf pt.tar pt pt.1 Makefile COPYING
	gzip pt.tar

install:	pt
	mkdir -p $(PREFIX)/bin/
	install pt $(PREFIX)/bin/
	gzip -k pt.1
	mkdir -p $(PREFIX)/share/man/man1/
	install pt.1.gz $(PREFIX)/share/man/man1/

uninstall:
	rm $(PREFIX)/bin/pt
	rm $(PREFIX)/share/man/man1/pt.1.gz 
