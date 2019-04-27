###########################################################
# makefile for blink_v1
# adapted from https://github.stm8s_mon/erno-szabados/sdcc-stm8s
###########################################################
TARGET=stm8eForth.ihx

BOARD=stm8s105c6
PROGRAMMER=stlink

SDAS=sdasstm8
SDCC=sdcc
SDLD=sdld
LDFLAGS=--out-fmt-ihx
CFLAGS=
FLASH=stm8flash
INC=../inc/
INCLUDES=$(INC)stm8s105.inc
BUILD=build/
OBJECTS=$(BUILD)stm8eForth.rel
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

%.rel: stm8eForth.asm
	@echo
	@echo "***************"
	@echo "stm8ef assembling"
	@echo "***************"
	$(SDAS) -o stm8eForth.rel stm8eForth.asm 

$(TARGET): $(OBJECTS) $(INCLUDES)
	@echo
	@echo "***************"
	@echo "linking files"
	@echo "***************"
	$(SDCC) -mstm8 -lstm8 $(LDFLAGS) -o $@ $(OBJECTS) 
	@ls -gG $(TARGET)
	
test: 
	$(SDAS) -l -o test.rel test.asm

    	
clean:
	@echo
	@echo "***************"
	@echo "cleaning files"
	@echo "***************"
	rm -f $(OBJECTS) $(SYMBOLS) $(ASMS) $(LISTS) $(RSTS)
	rm -f $(TARGET) $(MAP) $(LK) $(CDB)

.PHONY: all clean flash
