$ 
$     パス2のコア依存テンプレート（ARM用）
$ 

$ 
$ DEF_EXCで使用できるCPU例外ハンドラ番号
$ 
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel/kernel.tf"$

$DEFAULT_EXC_HANDLER[0] = "default_exc_handler"$
$DEFAULT_EXC_HANDLER[1] = "default_undef_handler"$
$DEFAULT_EXC_HANDLER[2] = "default_swi_handler"$
$DEFAULT_EXC_HANDLER[3] = "default_prefetchabort_handler"$
$DEFAULT_EXC_HANDLER[4] = "default_dataabort_handler"$
$DEFAULT_EXC_HANDLER[5] = "default_exc_handler"$
$DEFAULT_EXC_HANDLER[6] = "default_exc_handler"$

$ 
$  例外ハンドラテーブル
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_exch_table[TNUM_EXCH] = {$NL$
$JOINEACH excno {0,1,...,6} ",\n"$ 
    $number = excno|(prcid<<16)$
	$IF LENGTH(EXC.EXCNO[number])$
		$TAB$(FP)($EXC.EXCHDR[number]$)
	$ELSE$
		$TAB$(FP)(_kernel_$DEFAULT_EXC_HANDLER[excno]$)
	$END$
	$SPC$$FORMAT("/* %d */", +excno)$
$END$
$NL$};$NL$
$NL$

$END$

$ 
$  例外ハンドラアクセステーブル
$ 
const FP* const _kernel_p_exch_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_exch_table
$END$
$NL$};$NL$
$NL$
