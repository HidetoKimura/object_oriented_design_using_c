CC = gcc

LIBS =  

CFLAGS = -g -Wall
LDFLAGS = $(LIBS)

TARGET = view_sample
OBJS   = main.o view_class.o view_carnavi_ood.o
#OBJS   = main.o view_class.o view_carnavi_std.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

