/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sTouchSensor_TECSGEN_H
#define sTouchSensor_TECSGEN_H

/*
 * signature   :  sTouchSensor
 * global name :  sTouchSensor
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sTouchSensor_VDES {
    struct tag_sTouchSensor_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sTouchSensor_VMT {
    bool_t         (*isPressed__T)( const struct tag_sTouchSensor_VDES *edp );
    void           (*initializePort__T)( const struct tag_sTouchSensor_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sTouchSensor_VDES *vdes; } Descriptor( sTouchSensor );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_STOUCHSENSOR_ISPRESSED          (1)
#define	FUNCID_STOUCHSENSOR_INITIALIZEPORT     (2)

#endif /* sTouchSensor_TECSGEN_H */
