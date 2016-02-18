/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sUltrasonicSensor_TECSGEN_H
#define sUltrasonicSensor_TECSGEN_H

/*
 * signature   :  sUltrasonicSensor
 * global name :  sUltrasonicSensor
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sUltrasonicSensor_VDES {
    struct tag_sUltrasonicSensor_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sUltrasonicSensor_VMT {
    int16_t        (*getDistance__T)( const struct tag_sUltrasonicSensor_VDES *edp );
    bool_t         (*listen__T)( const struct tag_sUltrasonicSensor_VDES *edp );
    void           (*initializePort__T)( const struct tag_sUltrasonicSensor_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sUltrasonicSensor_VDES *vdes; } Descriptor( sUltrasonicSensor );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SULTRASONICSENSOR_GETDISTANCE   (1)
#define	FUNCID_SULTRASONICSENSOR_LISTEN        (2)
#define	FUNCID_SULTRASONICSENSOR_INITIALIZEPORT (3)

#endif /* sUltrasonicSensor_TECSGEN_H */
