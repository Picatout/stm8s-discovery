CC=sdcc
LD=sdld
LDFLAGS=--out-fmt-ihx
CFLAGS=
FLASH=stm8flash
OBJECTS=init.rel main.rel
SYMBOLS=$(OBJECTS:.rel=.sym)
ASMS=$(OBJECTS:.rel=.asm)
LISTS=$(OBJECTS:.rel=.lst)
RSTS=$(OBJECTS:.rel=.rst)
TARGET=adpcm.ihx
MAP=$(TARGET:.ihx=.map)
LK=$(TARGET:.ihx=.lk)
CDB=$(TARGET:.ihx=.cdb)

BOARD=stm8s105c6
PROGRAMMER=stlink

.PHONY: all clean flash

all: $(TARGET)

flash: $(TARGET)
	$(FLASH) -c $(PROGRAMMER) -p $(BOARD) -w $(TARGET)

%.rel: %.c
	$(CC) -mstm8 -lstm8 $(CFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CC) -mstm8 -lstm8 $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(SYMBOLS) $(ASMS) $(LISTS) $(RSTS)
	rm -f $(TARGET) $(MAP) $(LK) $(CDB)

.PHONY: all clean flash
