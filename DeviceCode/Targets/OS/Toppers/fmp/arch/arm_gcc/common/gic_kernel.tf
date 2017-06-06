$ 
$     パス2のチップ依存テンプレート（GIC用）
$ 

$ 
$ ATT_ISRのターゲット依存のチェック
$ どのプロセッサでも受け付け可能な割込み番号は，初期割付け可能プロセッサにのみ
$ 割付け可能である．
$ 
$FUNCTION TARGET_CHECK_ATT_ISR$
	$IF ((ISR.INTNO[ARGV[1]] & 0xffff0000) == 0) 
		&& ((1 << (CLASS_AFFINITY_INI[ISR.CLASS[ARGV[1]]] - 1)) != CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("processor affinity of `0x%1$x\' in %2% is not match with class %3% processor affinity mask `0x%4$x\'."), +ISR.INTNO[ARGV[1]], "ATT_ISR", ISR.CLASS[ARGV[1]], +CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$$END$
	$END$
$END$

$ 
$  割込みハンドラテーブル
$ 
$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_inh_table[TNUM_INH] = {$NL$
$FOREACH inhno RANGE(0, (TNUM_INH - 1))$
	$minhno = inhno | (prcid << intno_cpu_shift)$
	$IF LENGTH(INH.INHNO[inhno]) && (CLASS_AFFINITY_INI[INH.CLASS[inhno]] == prcid)$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$IF LENGTH(INH.INHNO[minhno]) && (CLASS_AFFINITY_INI[INH.CLASS[minhno]] == prcid)$
			$TAB$(FP)($INH.INTHDR[minhno]$),
		$ELSE$
			$TAB$(FP)(_kernel_default_int_handler),
		$END$
	$END$
	$SPC$$FORMAT("/* 0x%x */", +minhno)$$NL$
$END$
};$NL$
$NL$

$END$$NL$

$ 
$  割込みハンドラアクセステーブル
$ 
const FP* const _kernel_p_inh_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_inh_table
$END$
$NL$};$NL$
$NL$

$ 
$  割込み属性テーブル
$ 
$NL$
$FOREACH prcid RANGE(1, TNUM_PRCID)$
$ 
$  プライベート割込み用
$ 
const uint8_t _kernel_prc$prcid$_private_cfgint_table[TNUM_INH] = {$NL$
$FOREACH inhno RANGE(0, (GIC_INTNO_SPI0 - 1))$
	$minhno = inhno | (prcid << intno_cpu_shift)$
	$IF LENGTH(INH.INHNO[minhno]) && (CLASS_AFFINITY_INI[INH.CLASS[minhno]] == prcid)$
		$TAB$1U,
	$ELSE$
		$TAB$0U,
	$END$
	$SPC$$FORMAT("/* 0x%x */", +minhno)$$NL$
$END$
};$NL$
$NL$

$END$$NL$

$ 
$  割込み属性アクセステーブル
$ 
const uint8_t* const _kernel_p_private_cfgint_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
	$TAB$_kernel_prc$prcid$_private_cfgint_table
$END$
$NL$};$NL$
$NL$

$ 
$  グローバル割込み用
$ 
const uint8_t _kernel_global_cfgint_table[TNUM_INH] = {$NL$
$FOREACH inhno RANGE(GIC_INTNO_SPI0, (TNUM_INH - 1))$
	$cfgint_exist = 0$
	$IF LENGTH(INH.INHNO[inhno])$
		$cfgint_exist = 1$
	$ELSE$
		$FOREACH prcid RANGE(1, TNUM_PRCID)$
			$minhno = inhno | (prcid << intno_cpu_shift)$
			$IF LENGTH(INH.INHNO[minhno])$
				$cfgint_exist = 1$
			$END$
		$END$
	$END$

	$IF cfgint_exist == 1$
		$TAB$1U,
	$ELSE$
		$TAB$0U,
	$END$
	$SPC$$FORMAT("/* 0x%x */", +inhno)$$NL$
$END$
};$NL$
$NL$