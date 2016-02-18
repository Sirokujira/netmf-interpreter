/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sColorSensor_TECSGEN_H
#define sColorSensor_TECSGEN_H

/*
 * signature   :  sColorSensor
 * global name :  sColorSensor
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sColorSensor_VDES {
    struct tag_sColorSensor_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sColorSensor_VMT {
    colorid_t      (*getColor__T)( const struct tag_sColorSensor_VDES *edp );
    uint8_t        (*getReflect__T)( const struct tag_sColorSensor_VDES *edp );
    uint8_t        (*getAmbient__T)( const struct tag_sColorSensor_VDES *edp );
    void           (*initializePort__T)( const struct tag_sColorSensor_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sColorSensor_VDES *vdes; } Descriptor( sColorSensor );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SCOLORSENSOR_GETCOLOR           (1)
#define	FUNCID_SCOLORSENSOR_GETREFLECT         (2)
#define	FUNCID_SCOLORSENSOR_GETAMBIENT         (3)
#define	FUNCID_SCOLORSENSOR_INITIALIZEPORT     (4)

#endif /* sColorSensor_TECSGEN_H */
