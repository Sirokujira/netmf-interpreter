$IF TOPPERS_SAFEG_SECURE$
$INTPRI_CFGINT_VALID = { -16,-17,...,-31 }$
$ELSE$$IF TOPPERS_SAFEG_NONSECURE$
$INTPRI_CFGINT_VALID = { -1,-2,...,-15 }$
$ELSE$
$INTPRI_CFGINT_VALID = { -1,-2,...,-31 }$
$END$$END$

$INCLUDE"chip.tf"$
