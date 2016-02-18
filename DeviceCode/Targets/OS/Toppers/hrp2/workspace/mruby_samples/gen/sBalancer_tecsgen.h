/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sBalancer_TECSGEN_H
#define sBalancer_TECSGEN_H

/*
 * signature   :  sBalancer
 * global name :  sBalancer
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sBalancer_VDES {
    struct tag_sBalancer_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sBalancer_VMT {
    void           (*control__T)( const struct tag_sBalancer_VDES *edp, float32_t forward, float32_t turn, float32_t gyro, float32_t gyroOffset, float32_t leftRevolution, float32_t rightRevolution, float32_t battery, int8_t* pwm_l, int8_t* pwm_r );
    void           (*init__T)( const struct tag_sBalancer_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sBalancer_VDES *vdes; } Descriptor( sBalancer );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SBALANCER_CONTROL               (1)
#define	FUNCID_SBALANCER_INIT                  (2)

#endif /* sBalancer_TECSGEN_H */
