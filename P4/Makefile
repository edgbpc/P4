CC	= g++
CFLAGS	= 

TARGET1	= comp
OBJS1	= main.o
OBJS2	= scanner.o
OBJS3	= parser.o
OBJS4   = statSem.o
OBJS5   = codeGen.o

CXXFLAGS = -std=c++11

.SUFFIXES: .c .o

all:	$(TARGET1)

comp:	$(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)
		$(CC) $(CFLAGS) $(CXXFLAGS) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) -o $@


.c.o:
		$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	/bin/rm -f *.o *.dat *.asm  *~ $(TARGET1)
