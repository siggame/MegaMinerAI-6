GENDIR=../../client/c
all:
	mv $(GENDIR)/AI.cpp tempAIcpp.txt
	mv $(GENDIR)/AI.h tempAIh.txt
	cp *.cpp *.h $(GENDIR)
	make -C $(GENDIR)
	mv $(GENDIR)/client .
	mv tempAIcpp.txt $(GENDIR)/AI.cpp 
	mv tempAIh.txt   $(GENDIR)/AI.h 

clean:
	rm -f client
	make -C $(GENDIR) clean
extra_clean: clean
	rm -rf *~
	rm -rf *.gamelog
	
	
