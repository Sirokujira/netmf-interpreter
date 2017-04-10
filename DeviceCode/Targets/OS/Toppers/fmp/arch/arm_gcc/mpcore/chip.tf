$ 
$     パス2のチップ依存テンプレート（MPCORE用）
$ 

$ 
$ 有効なCPU例外ハンドラ番号
$ 
$EXCNO_VALID = { 
	0x10001,0x10002,0x10003,0x10004,0x10006;
	0x20001,0x20002,0x20003,0x20004,0x20006;
	0x30001,0x30002,0x30003,0x30004,0x30006;
	0x40001,0x40002,0x40003,0x40004,0x40006
}$

$
$  Interrupt numbers usable in ATT_ISR and their corresponding handlers
$
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INTNO_VALID$

$ 
$  DEF_INTで使用できる割込みハンドラ番号
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$

$ 
$  CFG_INTで使用できる割込み番号と割込み優先度
$ 
$INTNO_CFGINT_VALID  = INTNO_VALID$
$INTPRI_CFGINT_VALID = RANGE(TMIN_INTPRI, -1)$

$ 
$  ARM依存テンプレートのインクルード
$ 
$INCLUDE"../common/core.tf"$

$ 
$  GIC依存テンプレートのインクルード
$ 
$INCLUDE"../common/gic_kernel.tf"$
