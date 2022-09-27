prefix = arm-none-eabi

build_dir = build
src_dir = src

# project name & config 
target = rspll
debug = 1
opt = -Og

# sources 
asm_sources +=
c_sources += src/main.c
c_sources += $(wildcard src/net_lwip_webserver/*.c)
# c_sources += $(wildcard src/peripheral/src/*.c)
c_sources += src/peripheral/src/systick.c
c_sources += src/peripheral/src/usb.c
c_sources += src/peripheral/src/led.c
# add tinyusb
c_sources += $(wildcard src/tinyusb/src/*.c)
c_sources += $(wildcard src/tinyusb/src/device/*.c)
c_sources += $(wildcard src/tinyusb/src/class/*/*.c)
c_sources += $(wildcard src/tinyusb/src/portable/synopsys/dwc2/*.c)
c_sources += $(wildcard src/tinyusb/src/common/*.c)
# lwip 
c_sources += $(wildcard src/lwip/src/core/*.c)
c_sources += $(wildcard src/lwip/src/core/ipv4/*.c)
c_sources += $(wildcard src/lwip/src/core/ipv6/*.c)
c_sources += src/lwip/src/netif/ethernet.c
c_sources += src/lwip/src/netif/slipif.c
c_sources += src/lwip/src/apps/http/httpd.c
c_sources += src/lwip/src/apps/http/fs.c


# defines
defs += -DUSE_STDPERIPH_DRIVER
defs += -DSTM32F411xE

# includes 
includes += -Isrc
includes += -Isrc/peripheral/inc

includes += -Isrc/tinyusb/src
includes += -Isrc/tinyusb/src/portable/st/synopsys
includes += -Isrc/tinyusb/src/common
includes += -Isrc/net_lwip_webserver

# lwip
includes += -Isrc/lwip/src/include
includes += -Isrc/lwip/src/include/lwip/apps

# include platform support file
include src/platform/makefile