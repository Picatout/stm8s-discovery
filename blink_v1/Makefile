###########################################################
# makefile for blink_v1
# adapted from https://github.com/erno-szabados/sdcc-stm8s
###########################################################
TARGET=blink.ihx

BOARD=stm8s105c6
PROGRAMMER=stlink

SDCC=sdcc
SDLD=sdld
LDFLAGS=--out-fmt-ihx
CFLAGS=
FLASH=stm8flash
HAL=../hal/
OBJECTS=clock_init.rel gpio.rel blink.rel
SYMBOLS=$(OBJECTS:.rel=.sym)
ASMS=$(OBJECTS:.rel=.asm)
LISTS=$(OBJECTS:.rel=.lst)
RSTS=$(OBJECTS:.rel=.rst)
MAP=$(TARGET:.ihx=.map)
LK=$(TARGET:.ihx=.lk)
CDB=$(TARGET:.ihx=.cdb)


.PHONY: all flash

all: clean $(TARGET) 

flash: $(TARGET)
	@echo
	@echo "***************"
	@echo "flashing device"
	@echo "***************"
	$(FLASH) -c $(PROGRAMMER) -p $(BOARD) -w $(TARGET)

%.rel: blink.c  $(HAL)gpio.c $(HAL)clock_init.c
	@echo
	@echo "***************"
	@echo "compiling files"
	@echo "***************"
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)gpio.c
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)clock_init.c
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c blink.c
	
$(TARGET): $(OBJECTS) 
	@echo
	@echo "***************"
	@echo "linking files"
	@echo "***************"
	$(SDCC) -mstm8 -lstm8 $(LDFLAGS) -o $@ $(OBJECTS) 

clean:
	@echo
	@echo "***************"
	@echo "cleaning files"
	@echo "***************"
	rm -f $(OBJECTS) $(SYMBOLS) $(ASMS) $(LISTS) $(RSTS)
	rm -f $(TARGET) $(MAP) $(LK) $(CDB)

.PHONY: all clean flash
