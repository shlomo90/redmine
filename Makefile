CC=gcc
CFLAGS=-g

# init takes user-api-key, redmine-remote-server, name
# open tracks new issue.
# close untracks the issue.
# edit open the issue description and edit (using vi)
# status shows current issues opened.
# switch changes from current remote-redmine-server to another one.
# fetch gets target issues's description or opened descriptions
# push uploads target descriptions to remote server.
PROG=redmine

all:: $(PROG)

redmine: redmine.o init.o file.o open.o redmine.h
	$(CC) $(CFLAGS) -o redmine redmine.o init.o file.o open.o

redmine.o: redmine.c redmine.h
	$(CC) $(CFLAGS) -c redmine.c $(LIB_PATH) $(LIBS)

file.o: file.c redmine.h
	$(CC) $(CFLAGS) -c file.c $(LIB_PATH) $(LIBS)

init: init.o file.o redmine.h
	$(CC) $(CFLAGS) -o init init.o file.o

clean:
	rm -rf *.o $(PROG)
