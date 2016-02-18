# このファイルは tecsgen により自動生成されました
# Makefile.temp は gen の一つ上のディレクトリに移して使用します
#  % mv Makefile.temp Makefile
# 
# clean のデフォルト動作は $(GEN_DIR)/Makefile.* を削除します

# 変数 #_MVAR_#
TARGET = optional.exe
TIMESTAMP = tecsgen.timestamp
TECSGEN_EXE = tecsgen
CC = gcc
CFLAGS = -g -I . -I ../RUNTIME/tecs-runtime/target -I ../RUNTIME/tecs-runtime/include -I gen -Werror-implicit-function-declaration
LD = gcc
LDFLAGS = 
GEN_DIR = gen
SRC_DIR = src
vpath %.c $(SRC_DIR) $(GEN_DIR)

vpath %.h $(SRC_DIR) $(GEN_DIR)

# ルール #_MRUL_#
no_target :
	@echo "no target specified"
	@echo "at first or when edit .cdl files, do below"
	@echo "% make tecs"
	@echo "at second, do below"
	@echo "% make all"
	@echo "to clean"
	@echo "% make clean"

all : $(TARGET) 


# depend を include #_MDEP_#
-include gen/Makefile.tecsgen
-include gen/Makefile.depend

$(TARGET) : $(TIMESTAMP) $(CELLTYPE_COBJS) $(TECSGEN_COBJS) $(PLUGIN_COBJS)
	$(LD) $(LDFLGAS) -o $(TARGET) $(TECSGEN_COBJS) $(CELLTYPE_COBJS) $(PLUGIN_COBJS)

# For temporal construction using template code.
TEMPL_COBJS = \
 	$(GEN_DIR)/tSingleCellOptimizeCaller_templ.o \
 	$(GEN_DIR)/tSingleCellOptimizeCallee_templ.o \
 	$(GEN_DIR)/tVMTUselessOptimizeCaller_templ.o \
 	$(GEN_DIR)/tVMTUselessOptimizeCallee_templ.o \
 	$(GEN_DIR)/tSkeltonUselessOptimizeCaller_templ.o \
 	$(GEN_DIR)/tSkeltonUselessOptimizeCallee_templ.o \
 	$(GEN_DIR)/tMain_templ.o \
# TEMPL_COBJS terminater

TEMPL_SRCS = \
 	$(GEN_DIR)/tSingleCellOptimizeCaller_templ.c \
 	$(GEN_DIR)/tSingleCellOptimizeCallee_templ.c \
 	$(GEN_DIR)/tVMTUselessOptimizeCaller_templ.c \
 	$(GEN_DIR)/tVMTUselessOptimizeCallee_templ.c \
 	$(GEN_DIR)/tSkeltonUselessOptimizeCaller_templ.c \
 	$(GEN_DIR)/tSkeltonUselessOptimizeCallee_templ.c \
 	$(GEN_DIR)/tMain_templ.c \
# TEMPL_SRCS terminater

# テンプレートコードでメークしてみる場合 #_TCM_#
# $(TARGET) : $(TIMESTAMP) $(TECSGEN_COBJS) $(TEMPL_COBJS) $(PLUGIN_COBJS)
#	$(LD) $(LDFLGAS) -o $(TARGET) $(TECSGEN_COBJS) $(TEMPL_COBJS) $(PLUGIN_COBJS)

clean :
	rm -rf $(GEN_DIR)
	rm -f $(TECS_COBJS)
	rm -f $(TARGET)
	rm -f $(TIMESTAMP)

tecs : $(TIMESTAMP)

$(TIMESTAMP) : $(TECS_IMPORTS)
	$(TECSGEN_EXE) -I ../RUNTIME/tecs-runtime/target -I ../RUNTIME/tecs-runtime/include optional.cdl
#	tecsgen -U -I ../RUNTIME/tecs-runtime/target -I ../RUNTIME/tecs-runtime/include optional.cdl
#	tecsgen -t -U -I ../RUNTIME/tecs-runtime/target -I ../RUNTIME/tecs-runtime/include optional.cdl
	touch $(TIMESTAMP)

# Celltype: tSingleCellOptimizeCaller
$(GEN_DIR)/tSingleCellOptimizeCaller_tecsgen.o : $(GEN_DIR)/tSingleCellOptimizeCaller_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSingleCellOptimizeCaller_templ.o : $(GEN_DIR)/tSingleCellOptimizeCaller_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSingleCellOptimizeCaller.o : tSingleCellOptimizeCaller.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSingleCellOptimizeCallee
$(GEN_DIR)/tSingleCellOptimizeCallee_tecsgen.o : $(GEN_DIR)/tSingleCellOptimizeCallee_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSingleCellOptimizeCallee_templ.o : $(GEN_DIR)/tSingleCellOptimizeCallee_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSingleCellOptimizeCallee.o : tSingleCellOptimizeCallee.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tVMTUselessOptimizeCaller
$(GEN_DIR)/tVMTUselessOptimizeCaller_tecsgen.o : $(GEN_DIR)/tVMTUselessOptimizeCaller_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tVMTUselessOptimizeCaller_templ.o : $(GEN_DIR)/tVMTUselessOptimizeCaller_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tVMTUselessOptimizeCaller.o : tVMTUselessOptimizeCaller.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tVMTUselessOptimizeCallee
$(GEN_DIR)/tVMTUselessOptimizeCallee_tecsgen.o : $(GEN_DIR)/tVMTUselessOptimizeCallee_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tVMTUselessOptimizeCallee_templ.o : $(GEN_DIR)/tVMTUselessOptimizeCallee_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tVMTUselessOptimizeCallee.o : tVMTUselessOptimizeCallee.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSkeltonUselessOptimizeCaller
$(GEN_DIR)/tSkeltonUselessOptimizeCaller_tecsgen.o : $(GEN_DIR)/tSkeltonUselessOptimizeCaller_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSkeltonUselessOptimizeCaller_templ.o : $(GEN_DIR)/tSkeltonUselessOptimizeCaller_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSkeltonUselessOptimizeCaller.o : tSkeltonUselessOptimizeCaller.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSkeltonUselessOptimizeCallee
$(GEN_DIR)/tSkeltonUselessOptimizeCallee_tecsgen.o : $(GEN_DIR)/tSkeltonUselessOptimizeCallee_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSkeltonUselessOptimizeCallee_templ.o : $(GEN_DIR)/tSkeltonUselessOptimizeCallee_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSkeltonUselessOptimizeCallee.o : tSkeltonUselessOptimizeCallee.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tMain
$(GEN_DIR)/tMain_tecsgen.o : $(GEN_DIR)/tMain_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tMain_templ.o : $(GEN_DIR)/tMain_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tMain.o : tMain.c
	$(CC) -c $(CFLAGS) -o $@ $<

