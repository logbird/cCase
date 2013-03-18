PROFILES=main.c util.c npc.c
PROOBJS=$(PROFILES:.c=.o)
PROFLAGS= -g
TARGET=running

all:$(TARGET)


$(TARGET) : $(PROOBJS)
	gcc -o $(TARGET) $(PROOBJS)

%.o:%.c
	gcc -c -o $@ $<

clean:
	rm -rf $(PROOBJS)
	rm -rf $(TARGET)
 
