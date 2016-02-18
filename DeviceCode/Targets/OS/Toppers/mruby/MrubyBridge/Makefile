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
TARGET = SimpleSample.exe
TIMESTAMP = tecsgen.timestamp
# TECSGEN_EXE = tecsgen
# exerb 版を使う場合は、上記に替えて、以下を有効にしてください
TECSGEN_EXE = tecsgen.exe
BASE_DIR = .
CC = gcc
CFLAGS = -I $(BASE_DIR)/. -I $(TECSPATH)/../test/cygwin -I $(TECSPATH) -I $(TECSPATH)/mruby -I $(TECSPATH)/posix -I $(TECSPATH)/rpc -I $(MRUBYPATH)/include -I $(GEN_DIR) -D "Inline=static inline"
LD = gcc
LDFLAGS = -lmruby -L$(MRUBYPATH)/lib -lm
GEN_DIR = $(BASE_DIR)/gen
SRC_DIR = $(BASE_DIR)/src
_TECS_OBJ_DIR = $(GEN_DIR)/
#   _TECS_OBJ_DIR   # should end with '/'
PRE_TECSGEN_TARGET =
POST_TECSGEN_TARGET =

vpath %.c $(SRC_DIR) $(GEN_DIR)  $(TECSPATH)/../test/cygwin $(TECSPATH) $(TECSPATH)/mruby $(TECSPATH)/posix $(TECSPATH)/rpc $(MRUBYPATH)/include
vpath %.h $(SRC_DIR) $(GEN_DIR)  $(TECSPATH)/../test/cygwin $(TECSPATH) $(TECSPATH)/mruby $(TECSPATH)/posix $(TECSPATH)/rpc $(MRUBYPATH)/include

OTHER_OBJS =                      # Add objects out of tecs care.
# OTHER_OBJS = $(_TECS_OBJ_DIR)vasyslog.o

# Additional VARS
# CHANGE this into suitable path
MRUBYPATH = ..

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

tecs : $(PRE_TECSGEN_TARGET) $(TIMESTAMP) $(POST_TECSGEN_TARGET)

$(TIMESTAMP) : $(TECS_IMPORTS)
	$(TECSGEN_EXE)  -I $(TECSPATH)/../test/cygwin SimpleSample.cdl
	touch $(TIMESTAMP)

# generic target for objs
$(_TECS_OBJ_DIR)%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(_TECS_OBJ_DIR)tSample.o : tSample.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
$(_TECS_OBJ_DIR)nMruby_tTECSInitializer.o : nMruby_tTECSInitializer.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
$(_TECS_OBJ_DIR)nMruby_tCharPointer.o : nMruby_tCharPointer.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
$(_TECS_OBJ_DIR)nMruby_tMrubyProc.o : nMruby_tMrubyProc.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
$(_TECS_OBJ_DIR)nMruby_tsSample.o : nMruby_tsSample.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
$(_TECS_OBJ_DIR)nMruby_tsSample_Initializer.o : nMruby_tsSample_Initializer.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
$(_TECS_OBJ_DIR)nC2TECS_tnPosix_sMain.o : nC2TECS_tnPosix_sMain.c
	$(CC) -c $(CFLAGS) -o $@ $<
 
