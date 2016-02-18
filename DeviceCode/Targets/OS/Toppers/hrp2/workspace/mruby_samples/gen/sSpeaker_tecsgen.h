/*
 * このファイルは tecsgen により自動生成されました
 * このファイルを編集して使用することは、意図されていません
 */
#ifndef sSpeaker_TECSGEN_H
#define sSpeaker_TECSGEN_H

/*
 * signature   :  sSpeaker
 * global name :  sSpeaker
 * context     :  task
 */

#ifndef TOPPERS_MACRO_ONLY

/* シグニチャディスクリプタ #_SD_# */
struct tag_sSpeaker_VDES {
    struct tag_sSpeaker_VMT *VMT;
};

/* シグニチャ関数テーブル #_SFT_# */
struct tag_sSpeaker_VMT {
    ER             (*setVolume__T)( const struct tag_sSpeaker_VDES *edp, uint8_t volume );
    ER             (*playTone__T)( const struct tag_sSpeaker_VDES *edp, uint16_t frequency, int32_t duration );
    ER             (*stop__T)( const struct tag_sSpeaker_VDES *edp );
};

/* シグニチャディスクリプタ(動的結合用) #_SDES_# */
typedef struct { struct tag_sSpeaker_VDES *vdes; } Descriptor( sSpeaker );
#endif /* TOPPERS_MACRO_ONLY */

/* function id */
#define	FUNCID_SSPEAKER_SETVOLUME              (1)
#define	FUNCID_SSPEAKER_PLAYTONE               (2)
#define	FUNCID_SSPEAKER_STOP                   (3)

#endif /* sSpeaker_TECSGEN_H */
