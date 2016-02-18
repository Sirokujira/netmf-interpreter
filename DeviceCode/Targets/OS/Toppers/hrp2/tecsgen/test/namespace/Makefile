# このファイルは tecsgen により自動生成されました
# Makefile.temp は gen の一つ上のディレクトリに移して使用します
#  % mv Makefile.temp Makefile
# 
# clean のデフォルト動作は $(GEN_DIR)/Makefile.* を削除します
#
# このファイルは GNU make で gcc を用い POSIX 環境で動作するモジュールをビルドするのに適切なように生成されています
# vpath, CFLAGS, OTHER_OBJS などを調整する必要があるかもしれません
# 他の環境やターゲットの場合、このファイルを元に変更する必要があります

# 変数 #_MVAR_#
TARGET = namespace.exe
TIMESTAMP = tecsgen.timestamp
TECSGEN_EXE = tecsgen
BASE_DIR = .
CC = gcc
CFLAGS = -I ../cygwin -I ../../tecs -I $(GEN_DIR) -D "Inline=static inline"
LD = gcc
LDFLAGS = 
GEN_DIR = $(BASE_DIR)/gen
SRC_DIR = $(BASE_DIR)/src
_TECS_OBJ_DIR = $(GEN_DIR)/
#   _TECS_OBJ_DIR   # should be end with '/'

vpath %.c $(SRC_DIR) $(GEN_DIR)  ../cygwin
vpath %.h $(SRC_DIR) $(GEN_DIR)  ../cygwin

OTHER_OBJS =                       # Add objects out of tecs care.
# OTHER_OBJS = $(_TECS_OBJ_DIR)vasyslog.o

# ルール #_MRUL_#
allall: tecs
	make all

all : $(TARGET)


# depend を include #_MDEP_#
-include $(GEN_DIR)/Makefile.tecsgen
-include $(GEN_DIR)/Makefile.depend

$(TARGET) : $(TIMESTAMP) $(CELLTYPE_COBJS) $(TECSGEN_COBJS) $(PLUGIN_COBJS) $(OTHER_OBJS)
	$(LD) -o $(TARGET) $(TECSGEN_COBJS) $(CELLTYPE_COBJS) $(PLUGIN_COBJS) $(OTHER_OBJS) $(LDFLAGS)

clean :
	rm -f $(CELLTYPE_COBJS) $(TECSGEN_COBJS) $(PLUGIN_COBJS) $(OTHER_OBJS) $(TARGET)  $(TIMESTAMP)
	rm -rf $(GEN_DIR)

tecs : $(TIMESTAMP)

$(TIMESTAMP) : $(TECS_IMPORTS)
	$(TECSGEN_EXE)  -I ../cygwin namespace.cdl
	touch $(TIMESTAMP)

# generic target for objs
$(_TECS_OBJ_DIR)%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

tKernel.o : tKernel.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tAppl.o : tAppl.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tOSEKAppl.o : tOSEKAppl.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
nAlloc_tAlloc.o : nAlloc_tAlloc.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
TOPPERS_tKernel.o : TOPPERS_tKernel.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
TOPPERS_tAppl.o : TOPPERS_tAppl.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
OSEK_tKernel.o : OSEK_tKernel.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
