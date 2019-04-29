###########################################################
# makefile for blink_v1
# adapted from https://github.stm8s_mon/erno-szabados/sdcc-stm8s
###########################################################
TARGET=stm8s_mon.ihx

BOARD=stm8s105c6
PROGRAMMER=stlink

SDCC=sdcc
SDLD=sdld
LDFLAGS=--out-fmt-ihx
CFLAGS=
FLASH=stm8flash
HAL=../hal/
INC=../inc/
LIB=../lib/
INCLUDES=$(INC)stm8s105.h $(INC)discovery.h
BUILD=build/
OBJECTS=$(BUILD)clock_init.rel $(BUILD)gpio.rel $(BUILD)stm8s_mon.rel $(BUILD)timer.rel $(BUILD)itc.rel $(BUILD)uart.rel\
$(BUILD)strings.rel
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

%.rel: stm8s_mon.c  $(HAL)gpio.c $(HAL)clock_init.c $(HAL)timer.c $(HAL)itc.c
	@echo
	@echo "***************"
	@echo "stm8s_monpiling files"
	@echo "***************"
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)gpio.c  -o $(BUILD)gpio.rel
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)clock_init.c -o $(BUILD)clock_init.rel
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)itc.c -o $(BUILD)itc.rel
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)timer.c -o $(BUILD)timer.rel
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(HAL)uart.c -o $(BUILD)uart.rel
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c stm8s_mon.c -o $(BUILD)stm8s_mon.rel
	$(SDCC) -mstm8 -lstm8 $(CFLAGS) -c $(LIB)strings.c -o $(BUILD)strings.rel

$(TARGET): $(OBJECTS) $(INCLUDES)
	@echo
	@echo "***************"
	@echo "linking files"
	@echo "***************"
	$(SDCC) -mstm8 -lstm8 $(LDFLAGS) -o $@ $(OBJECTS) 
	@ls -gG $(TARGET)
	
clean:
	@echo
	@echo "***************"
	@echo "cleaning files"
	@echo "***************"
	rm -f $(OBJECTS) $(SYMBOLS) $(ASMS) $(LISTS) $(RSTS)
	rm -f $(TARGET) $(MAP) $(LK) $(CDB)

.PHONY: all clean flash
