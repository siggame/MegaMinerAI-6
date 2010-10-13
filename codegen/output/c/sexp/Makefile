sources = lex.yy.cpp $(wildcard *.cpp)
objects = $(sources:%.cpp=%.o)
libclient_objects = $(sources:%.cpp=libclient_%.o)
deps = $(sources:%.cpp=%.d)

all: sexp.a libclient_sexp.a

clean:
	rm -f $(objects) $(libclient_objects) $(deps) sexp.a libclient_sexp.a

lex.yy.cpp: sexp.l
	 flex --outfile=lex.yy.cpp --header-file=lex.yy.h sexp.l

%.d: %.cpp
	@set -e; rm -f $@; \
	(dirname $< | tr '\n' '/'; $(CC) -MM $(CPPFLAGS) $<) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

libclient_%.o: override CFLAGS += -fPIC
libclient_%.o: %.cpp %.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean all

libclient_sexp.a: ${libclient_objects}
	ar cr $@ $^
	ranlib $@

sexp.a: ${objects}
	ar cr $@ $^
	ranlib $@

-include $(deps)

