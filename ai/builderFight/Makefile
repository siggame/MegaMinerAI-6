GENDIR=../../codegen/output/c
all:
	cp AI.cpp $(GENDIR)
	make -C $(GENDIR)
	cp $(GENDIR)/client .

clean:
	rm -f client

extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
