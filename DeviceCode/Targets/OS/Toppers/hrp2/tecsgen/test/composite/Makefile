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
TARGET = composite.exe
TIMESTAMP = tecsgen.timestamp
TECSGEN_EXE = tecsgen
BASE_DIR = .
CC = gcc
CFLAGS = -I $(BASE_DIR)/. -I $(BASE_DIR)/../cygwin -I $(BASE_DIR)/../../tecs -I $(BASE_DIR)/../RUNTIME/runtime/include -I $(BASE_DIR)/../RUNTIME/runtime/test -I $(BASE_DIR)/src -I $(TECSPATH) -I $(TECSPATH)/mruby -I $(TECSPATH)/posix -I $(TECSPATH)/rpc -I $(GEN_DIR) -D "Inline=static inline"
LD = gcc
LDFLAGS =
GEN_DIR = $(BASE_DIR)/gen_comp
SRC_DIR = $(BASE_DIR)/src
_TECS_OBJ_DIR = $(GEN_DIR)/
#   _TECS_OBJ_DIR   # should end with '/'
PRE_TECSGEN_TARGET =
POST_TECSGEN_TARGET =

vpath %.c $(SRC_DIR) $(GEN_DIR)  ../cygwin ../../tecs ../RUNTIME/runtime/include ../RUNTIME/runtime/test src $(TECSPATH) $(TECSPATH)/mruby $(TECSPATH)/posix $(TECSPATH)/rpc
vpath %.h $(SRC_DIR) $(GEN_DIR)  ../cygwin ../../tecs ../RUNTIME/runtime/include ../RUNTIME/runtime/test src $(TECSPATH) $(TECSPATH)/mruby $(TECSPATH)/posix $(TECSPATH)/rpc

# OTHER_OBJS =                      # Add objects out of tecs care.
OTHER_OBJS = $(_TECS_OBJ_DIR)vasyslog.o

# ルール #_MRUL_#
allall: tecs
	make all     # in order to include generated Makefile.tecsgen & Makefile.depend

all : $(TARGET)


# depend を include #_MDEP_#
-include $(GEN_DIR)/Makefile.tecsgen
-include $(GEN_DIR)/Makefile.depend

$(TARGET) : $(TIMESTAMP) $(CELLTYPE_COBJS) $(TECSGEN_COBJS) $(PLUGIN_COBJS) $(OTHER_OBJS)
	$(LD) -g -o $(TARGET) $(TECSGEN_COBJS) $(CELLTYPE_COBJS) $(PLUGIN_COBJS) $(OTHER_OBJS) $(LDFLAGS)
clean :
	rm -f $(CELLTYPE_COBJS) $(TECSGEN_COBJS) $(PLUGIN_COBJS) $(OTHER_OBJS) $(TARGET)  $(TIMESTAMP)
	rm -rf $(GEN_DIR)

tecs : $(PRE_TECSGEN_TARGET) $(TIMESTAMP) $(POST_TECSGEN_TARGET)

$(TIMESTAMP) : $(TECS_IMPORTS)
	$(TECSGEN_EXE)  -I ../cygwin -I ../../tecs -I ../RUNTIME/runtime/include -I ../RUNTIME/runtime/test -I src --gen=gen_comp composite.cdl
	touch $(TIMESTAMP)

# generic target for objs
$(_TECS_OBJ_DIR)%.o : %.c
	$(CC) -g -c $(CFLAGS) -o $@ $<

