GENDIR=../../client/c
all:
	cp *.cpp *.h $(GENDIR)
	make -C $(GENDIR)
	cp $(GENDIR)/client .

clean:
	rm -f client
	make -C $(GENDIR) clean
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
