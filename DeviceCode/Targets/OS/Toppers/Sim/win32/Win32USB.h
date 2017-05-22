//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2011 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: WIN32USB.h 88 2011-04-05 11:03:57Z nagasima $
#ifndef WIN32USBH
#define WIN32USBH

//------------------------------------------------------------------------------
// 0x00
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP0R
{
	uint32_t : 16;				// 0
	uint32_t CTR_RX : 1;		// 0
	uint32_t DTOG_RX : 1;		// 0
	uint32_t STAT_RX : 2;		// 0
	uint32_t SETUP : 1;		// 0
	uint32_t EP : 1;			// 0
	uint32_t TYPE : 2;			// 0
	uint32_t EP_KIND : 1;		// 0
	uint32_t CTR_TX : 1;		// 0
	uint32_t DTOG_TX : 1;		// 0
	uint32_t STAT_TX : 2;		// 0
	uint32_t EA : 4;			// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x04
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP1R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x08
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP2R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x0C
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP3R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x10
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP4R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x14
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP5R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x18
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP6R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x1C
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_EP7R
{
	uint32_t : 16;					// 0
	uint32_t CTR_RX : 1;			// 0
	uint32_t DTOG_RX : 1;			// 0
	uint32_t STAT_RX : 2;			// 0
	uint32_t SETUP : 1;				// 0
	uint32_t EP : 1;				// 0
	uint32_t TYPE : 2;				// 0
	uint32_t EP_KIND : 1;			// 0
	uint32_t CTR_TX : 1;			// 0
	uint32_t DTOG_TX : 1;			// 0
	uint32_t STAT_TX : 2;			// 0
	uint32_t EA : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x40
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_CNTR
{
	uint32_t : 16;					// 0
	uint32_t CTRM : 1;				// 0
	uint32_t PMAOVRM : 1;			// 0
	uint32_t ERRM : 1;				// 0
	uint32_t WKUPM : 1;				// 0
	uint32_t SUSPM : 1;				// 0
	uint32_t RESETM : 1;			// 0
	uint32_t SOFM : 1;				// 0
	uint32_t ESOFM : 1;				// 0
	uint32_t : 3;					// 0
	uint32_t RESUME : 1;			// 0
	uint32_t FSUSP : 1;				// 0
	uint32_t LPMODE : 1;			// 0
	uint32_t PDWN : 1;				// 1
	uint32_t FRES : 1;				// 1
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x44
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_ISTR
{
	uint32_t : 16;					// 0
	uint32_t CTR : 1;				// 0
	uint32_t PMAOVR : 1;			// 0
	uint32_t ERR : 1;				// 0
	uint32_t WKUP : 1;				// 0
	uint32_t SUSP : 1;				// 0
	uint32_t RESET : 1;				// 0
	uint32_t SOF : 1;				// 0
	uint32_t ESOF : 1;				// 0
	uint32_t : 3;					// 0
	uint32_t DIR : 1;				// 0
	uint32_t EP_ID : 4;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x48
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_FNR
{
	uint32_t : 16;					// 0
	uint32_t RXDP : 1;				// 0
	uint32_t RXDM : 1;				// 0
	uint32_t LCK : 1;				// 0
	uint32_t LSOF : 2;				// x
	uint32_t FN : 11;				// x
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x4C
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_DADDR
{
	uint32_t : 24;					// 0
	uint32_t EF : 1;				// 0
	uint32_t ADD : 7;				// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// 0x50
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB_BTABLE
{
	uint32_t : 16;					// 0
	uint32_t BTABLE : 13;			// 0
	uint32_t : 3;					// 0
};
#pragma pack(pop)

//------------------------------------------------------------------------------
// USB full speed device interface (USB)
//------------------------------------------------------------------------------
#pragma pack(push, 1)
struct TUSB
{
	TUSB_EP0R EP0R;						// 0x00
	TUSB_EP1R EP1R;						// 0x04
	TUSB_EP2R EP2R;						// 0x08
	TUSB_EP3R EP3R;						// 0x0C
	TUSB_EP4R EP4R;						// 0x10
	TUSB_EP5R EP5R;						// 0x14
	TUSB_EP6R EP6R;						// 0x18
	TUSB_EP7R EP7R;						// 0x1C
	uint32_t Reserved[0x40 - 0x20];
	TUSB_CNTR CNTR;						// 0x40
	TUSB_ISTR ISTR;						// 0x44
	TUSB_FNR FNR;						// 0x48
	TUSB_DADDR DADDR;					// 0x4C
	TUSB_BTABLE BTABLE;					// 0x50
};
#pragma pack(pop)

//---------------------------------------------------------------------------
#endif // WIN32USBH
