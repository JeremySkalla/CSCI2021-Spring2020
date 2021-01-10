CFLAGS = -Wall -Werror -g -Og
CC     = gcc $(CFLAGS)
SHELL  = /bin/bash
CWD    = $(shell pwd | sed 's/.*\///g')

PROGRAMS = \
	loadfunc \

all : $(PROGRAMS)

clean :
	rm -f $(PROGRAMS) *.o vgcore.* a.out

############################################################
# 'make zip' to create zip for submission
AN=p5
zip : clean clean-tests
	rm -f $(AN)-code.zip
	cd .. && zip "$(CWD)/$(AN)-code.zip" -r "$(CWD)"
	@echo Zip created in $(AN)-code.zip
	@if (( $$(stat -c '%s' $(AN)-code.zip) > 10*(2**20) )); then echo "WARNING: $(AN)-code.zip seems REALLY big, check there are no abnormally large test files"; du -h $(AN)-code.zip; fi
	@if (( $$(unzip -t $(AN)-code.zip | wc -l) > 256 )); then echo "WARNING: $(AN)-code.zip has 256 or more files in it which may cause submission problems"; fi


############################################################
# loadfunc problem
loadfunc : loadfunc.c
	$(CC) -o $@ $^

############################################################
# TESTING TARGETS
test-setup :
	@chmod u+rx testy

test: loadfunc
	./testy test_loadfunc.org $(testnum)

test-engagement: loadfunc
	./testy test_loadfunc_engagement.org $(testnum)

clean-tests : clean
	rm -rf test-results
