CFLAGS=-Wall -Werror

all: monitrtsp
monitrtsp: monitrtsp.o
	$(CC) -o monitrtsp.exe monitrtsp.o $(CFLGAGS) $(LDFLAGS)
clean:
	rm -rf *.o *.exe
