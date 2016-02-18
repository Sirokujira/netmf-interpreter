/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sGyroSensor_TECSGEN_H
#define sGyroSensor_TECSGEN_H

/*
 * signature   :  sGyroSensor
 * global name :  sGyroSensor
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sGyroSensor_VDES {
    struct tag_sGyroSensor_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sGyroSensor_VMT {
    int16_t        (*getAngle__T)( const struct tag_sGyroSensor_VDES *edp );
    int16_t        (*getRate__T)( const struct tag_sGyroSensor_VDES *edp );
    ER             (*reset__T)( const struct tag_sGyroSensor_VDES *edp );
    float32_t      (*calibrate__T)( const struct tag_sGyroSensor_VDES *edp, int32_t times );
    void           (*initializePort__T)( const struct tag_sGyroSensor_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sGyroSensor_VDES *vdes; } Descriptor( sGyroSensor );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SGYROSENSOR_GETANGLE            (1)
#define	FUNCID_SGYROSENSOR_GETRATE             (2)
#define	FUNCID_SGYROSENSOR_RESET               (3)
#define	FUNCID_SGYROSENSOR_CALIBRATE           (4)
#define	FUNCID_SGYROSENSOR_INITIALIZEPORT      (5)

#endif /* sGyroSensor_TECSGEN_H */
