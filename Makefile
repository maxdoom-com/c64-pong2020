PROJECT=pong2020.prg
SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
RM=rm -f

all: $(PROJECT)

$(PROJECT): $(SOURCES)
	cl65 -t c64 -O -o $@ $^

test: $(PROJECT)
	x64 $<

re: clean all

clean:
	$(RM) $(PROJECT) $(OBJECTS)

install: all
	mount /mnt/mmcblk0p1/
	cp $(PROJECT) /mnt/mmcblk0p1/
	umount /mnt/mmcblk0p1/
