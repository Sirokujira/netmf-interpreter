# このファイルは tecsgen により自動生成されました
# Makefile.temp は gen の一つ上のディレクトリに移して使用します
#  % mv Makefile.temp Makefile
# 
# clean のデフォルト動作は $(GEN_DIR)/Makefile.* を削除します

# 変数 #_MVAR_#
TARGET = romram.exe
TECSGEN_EXE = tecsgen
CC = gcc
CFLAGS = -I . -I ../RUNTIME/tecs-runtime/target -I ../RUNTIME/tecs-runtime/include -I gen -I src -I gen
LD = gcc
LDFLAGS = 
GEN_DIR = gen
SRC_DIR = src
vpath %.c $(SRC_DIR) $(GEN_DIR)

# ルール #_MRUL_#
no_target :
	@echo "no target specified"
	@echo "at first or when edit .cdl files, do below"
	@echo "% make tecsgen"
	@echo "at second, do below"
	@echo "% make all"
	@echo "to clean"
	@echo "% make clean"

all : $(TARGET) 


# depend を include #_MDEP_#
-include gen/Makefile.tecsgen
-include gen/Makefile.depend

$(TARGET) : tecsgen.timestamp $(CELLTYPE_COBJS) $(TECSGEN_COBJS) $(PLUGIN_COBJS)
	$(LD) $(LDFLGAS) -o $(TARGET) $(TECSGEN_COBJS) $(CELLTYPE_COBJS) $(PLUGIN_COBJS)

# For temporal construction using template code.
TEMPL_COBJS = \
 	$(GEN_DIR)/tCt_templ.o \
 	$(GEN_DIR)/tCt2_templ.o \
 	$(GEN_DIR)/tOmit_templ.o \
 	$(GEN_DIR)/tIdx_is_id_templ.o \
 	$(GEN_DIR)/tSingle_idx_is_id_templ.o \
 	$(GEN_DIR)/tVarInitByAttr_templ.o \
 	$(GEN_DIR)/tSingle_templ.o \
 	$(GEN_DIR)/tSCt_no_CB_no_INIB_templ.o \
 	$(GEN_DIR)/tSCt_a_CB_no_INIB_templ.o \
 	$(GEN_DIR)/tSCt_no_CB_a_INIB_templ.o \
 	$(GEN_DIR)/tSCt_a_CB_a_INIB_templ.o \
 	$(GEN_DIR)/tCt_no_CB_no_INIB_templ.o \
 	$(GEN_DIR)/tCt_a_CB_no_INIB_templ.o \
 	$(GEN_DIR)/tCt_no_CB_a_INIB_templ.o \
 	$(GEN_DIR)/tCt_a_CB_a_INIB_templ.o \
 	$(GEN_DIR)/tCt_no_CB_no_INIB_init_templ.o \
 	$(GEN_DIR)/tMain_templ.o \
# TEMPL_COBJS terminater

TEMPL_SRCS = \
 	$(GEN_DIR)/tCt_templ.c \
 	$(GEN_DIR)/tCt2_templ.c \
 	$(GEN_DIR)/tOmit_templ.c \
 	$(GEN_DIR)/tIdx_is_id_templ.c \
 	$(GEN_DIR)/tSingle_idx_is_id_templ.c \
 	$(GEN_DIR)/tVarInitByAttr_templ.c \
 	$(GEN_DIR)/tSingle_templ.c \
 	$(GEN_DIR)/tSCt_no_CB_no_INIB_templ.c \
 	$(GEN_DIR)/tSCt_a_CB_no_INIB_templ.c \
 	$(GEN_DIR)/tSCt_no_CB_a_INIB_templ.c \
 	$(GEN_DIR)/tSCt_a_CB_a_INIB_templ.c \
 	$(GEN_DIR)/tCt_no_CB_no_INIB_templ.c \
 	$(GEN_DIR)/tCt_a_CB_no_INIB_templ.c \
 	$(GEN_DIR)/tCt_no_CB_a_INIB_templ.c \
 	$(GEN_DIR)/tCt_a_CB_a_INIB_templ.c \
 	$(GEN_DIR)/tCt_no_CB_no_INIB_init_templ.c \
 	$(GEN_DIR)/tMain_templ.c \
# TEMPL_SRCS terminater

# テンプレートコードでメークしてみる場合 #_TCM_#
# $(TARGET) : tecsgen.timestamp $(TECSGEN_COBJS) $(TEMPL_COBJS) $(PLUGIN_COBJS)
#	$(LD) $(LDFLGAS) -o $(TARGET) $(TECSGEN_COBJS) $(TEMPL_COBJS) $(PLUGIN_COBJS)

clean :
	rm -rf $(GEN_DIR)
	rm -f $(TECS_COBJS)
	rm -f $(TARGET)
	rm -f tecsgen.timestamp

tecsgen : tecsgen.timestamp

tecsgen.timestamp : $(TECS_IMPORTS)
	$(TECSGEN_EXE)  -R -u -i -I../RUNTIME/tecs-runtime/target -I../RUNTIME/tecs-runtime/include -Igen -Isrc romram.cdl
	# tecsgen -u -i -I../RUNTIME/tecs-runtime/target -I../RUNTIME/tecs-runtime/include -Igen -Isrc romram.cdl
	touch tecsgen.timestamp

# Celltype: tCt
$(GEN_DIR)/tCt_tecsgen.o : $(GEN_DIR)/tCt_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt_templ.o : $(GEN_DIR)/tCt_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt.o : tCt.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tCt2
$(GEN_DIR)/tCt2_tecsgen.o : $(GEN_DIR)/tCt2_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt2_templ.o : $(GEN_DIR)/tCt2_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt2.o : tCt2.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tOmit
$(GEN_DIR)/tOmit_tecsgen.o : $(GEN_DIR)/tOmit_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tOmit_templ.o : $(GEN_DIR)/tOmit_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tOmit.o : tOmit.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tIdx_is_id
$(GEN_DIR)/tIdx_is_id_tecsgen.o : $(GEN_DIR)/tIdx_is_id_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tIdx_is_id_templ.o : $(GEN_DIR)/tIdx_is_id_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tIdx_is_id.o : tIdx_is_id.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSingle_idx_is_id
$(GEN_DIR)/tSingle_idx_is_id_tecsgen.o : $(GEN_DIR)/tSingle_idx_is_id_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSingle_idx_is_id_templ.o : $(GEN_DIR)/tSingle_idx_is_id_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSingle_idx_is_id.o : tSingle_idx_is_id.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tVarInitByAttr
$(GEN_DIR)/tVarInitByAttr_tecsgen.o : $(GEN_DIR)/tVarInitByAttr_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tVarInitByAttr_templ.o : $(GEN_DIR)/tVarInitByAttr_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tVarInitByAttr.o : tVarInitByAttr.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSingle
$(GEN_DIR)/tSingle_tecsgen.o : $(GEN_DIR)/tSingle_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSingle_templ.o : $(GEN_DIR)/tSingle_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSingle.o : tSingle.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSCt_no_CB_no_INIB
$(GEN_DIR)/tSCt_no_CB_no_INIB_tecsgen.o : $(GEN_DIR)/tSCt_no_CB_no_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSCt_no_CB_no_INIB_templ.o : $(GEN_DIR)/tSCt_no_CB_no_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSCt_no_CB_no_INIB.o : tSCt_no_CB_no_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSCt_a_CB_no_INIB
$(GEN_DIR)/tSCt_a_CB_no_INIB_tecsgen.o : $(GEN_DIR)/tSCt_a_CB_no_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSCt_a_CB_no_INIB_templ.o : $(GEN_DIR)/tSCt_a_CB_no_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSCt_a_CB_no_INIB.o : tSCt_a_CB_no_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSCt_no_CB_a_INIB
$(GEN_DIR)/tSCt_no_CB_a_INIB_tecsgen.o : $(GEN_DIR)/tSCt_no_CB_a_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSCt_no_CB_a_INIB_templ.o : $(GEN_DIR)/tSCt_no_CB_a_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSCt_no_CB_a_INIB.o : tSCt_no_CB_a_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tSCt_a_CB_a_INIB
$(GEN_DIR)/tSCt_a_CB_a_INIB_tecsgen.o : $(GEN_DIR)/tSCt_a_CB_a_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tSCt_a_CB_a_INIB_templ.o : $(GEN_DIR)/tSCt_a_CB_a_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tSCt_a_CB_a_INIB.o : tSCt_a_CB_a_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tCt_no_CB_no_INIB
$(GEN_DIR)/tCt_no_CB_no_INIB_tecsgen.o : $(GEN_DIR)/tCt_no_CB_no_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt_no_CB_no_INIB_templ.o : $(GEN_DIR)/tCt_no_CB_no_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt_no_CB_no_INIB.o : tCt_no_CB_no_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tCt_a_CB_no_INIB
$(GEN_DIR)/tCt_a_CB_no_INIB_tecsgen.o : $(GEN_DIR)/tCt_a_CB_no_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt_a_CB_no_INIB_templ.o : $(GEN_DIR)/tCt_a_CB_no_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt_a_CB_no_INIB.o : tCt_a_CB_no_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tCt_no_CB_a_INIB
$(GEN_DIR)/tCt_no_CB_a_INIB_tecsgen.o : $(GEN_DIR)/tCt_no_CB_a_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt_no_CB_a_INIB_templ.o : $(GEN_DIR)/tCt_no_CB_a_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt_no_CB_a_INIB.o : tCt_no_CB_a_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tCt_a_CB_a_INIB
$(GEN_DIR)/tCt_a_CB_a_INIB_tecsgen.o : $(GEN_DIR)/tCt_a_CB_a_INIB_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt_a_CB_a_INIB_templ.o : $(GEN_DIR)/tCt_a_CB_a_INIB_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt_a_CB_a_INIB.o : tCt_a_CB_a_INIB.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tCt_no_CB_no_INIB_init
$(GEN_DIR)/tCt_no_CB_no_INIB_init_tecsgen.o : $(GEN_DIR)/tCt_no_CB_no_INIB_init_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tCt_no_CB_no_INIB_init_templ.o : $(GEN_DIR)/tCt_no_CB_no_INIB_init_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tCt_no_CB_no_INIB_init.o : tCt_no_CB_no_INIB_init.c
	$(CC) -c $(CFLAGS) -o $@ $<

# Celltype: tMain
$(GEN_DIR)/tMain_tecsgen.o : $(GEN_DIR)/tMain_tecsgen.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(GEN_DIR)/tMain_templ.o : $(GEN_DIR)/tMain_templ.c
	$(CC) -c $(CFLAGS) -o $@ $<

tMain.o : tMain.c
	$(CC) -c $(CFLAGS) -o $@ $<

