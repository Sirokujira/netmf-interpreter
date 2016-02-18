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
TARGET = rpc_test.exe
TIMESTAMP = tecsgen.timestamp
TECSGEN_EXE = tecsgen
BASE_DIR = .
CC = gcc
CFLAGS = -I $(BASE_DIR)/. -I $(BASE_DIR)/../cygwin -I $(BASE_DIR)/../../tecs -I $(BASE_DIR)/../../tecs/rpc -I $(GEN_DIR) -D "Inline=static inline"
LD = gcc
LDFLAGS = -lpthread
GEN_DIR = $(BASE_DIR)/gen
SRC_DIR = $(BASE_DIR)/src
_TECS_OBJ_DIR = $(GEN_DIR)/
#   _TECS_OBJ_DIR   # should be end with '/'

vpath %.c $(SRC_DIR) $(GEN_DIR)  ../cygwin ../../tecs ../../tecs/rpc
vpath %.h $(SRC_DIR) $(GEN_DIR)  ../cygwin ../../tecs ../../tecs/rpc

OTHER_OBJS =                       # Add objects out of tecs care.
# OTHER_OBJS = $(_TECS_OBJ_DIR)vasyslog.o

# ルール #_MRUL_#
allall: tecs
	make all     # in order to include generated Makefile.tecsgen & Makefile.depend

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
	$(TECSGEN_EXE)  -I ../cygwin -I ../../tecs -I ../../tecs/rpc rpc_test.cdl
	touch $(TIMESTAMP)

# generic target for objs
$(_TECS_OBJ_DIR)%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

tTask.o : tTask.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tKernel.o : tKernel.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tSemaphore.o : tSemaphore.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tEventflag.o : tEventflag.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tDataqueuePeer.o : tDataqueuePeer.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tSysLog.o : tSysLog.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tTDR.o : tTDR.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tRPCSharedChannelMan.o : tRPCSharedChannelMan.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tRPCSharedTaskMain.o : tRPCSharedTaskMain.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tPPAllocator.o : tPPAllocator.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tDataqueueAdaptor.o : tDataqueueAdaptor.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tAlloc.o : tAlloc.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tSample.o : tSample.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tSimple.o : tSimple.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tMarshaler_sSample.o : tMarshaler_sSample.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
tUnmarshaler_sSample.o : tUnmarshaler_sSample.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
