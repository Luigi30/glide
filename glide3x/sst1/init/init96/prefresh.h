/////////////////////////////////////////////////////////////////////////////
//
// PREFRESH.H
//
// This module contains refresh values for ProMotion.
//
// Copyright 1994-1996 Alliance Semiconductor Corporation
//
/////////////////////////////////////////////////////////////////////////////


#ifndef WORD
typedef unsigned short WORD;
#endif

#ifndef BYTE
typedef unsigned char BYTE;
#endif

#ifndef _REFRESH_DEFS
#define _REFRESH_DEFS
#pragma pack(1)

// FIFO Overflow registers.
typedef struct{
	BYTE    HRM;
	BYTE    HRNM;
	BYTE    LR;
	BYTE  VClk;											// Vclk for 3210, based on pixel depth
}OVERFLOW, *POVERFLOW;

// Values for a particular resolution,refresh, bitdepth.
typedef struct{
	int     VRefresh;
	WORD    HTotal;
	WORD    HDispEnd;
	WORD    HBlankStart;
	WORD    HSyncStart;
	WORD    HSyncEnd;
	WORD    HBlankEnd;
	WORD    VTotal;
	WORD    VDispEnd;
	WORD    VBlankStart;
	WORD    VSyncStart;
	WORD    VSyncEnd;
	WORD    VBlankEnd;
	WORD    VOverflow;
	BYTE    MiscOutput;                     // h,v polarity for refresh rate
	BYTE    VClk;                           // vclk for chips >= 6422
	OVERFLOW OverFlow[5];   				// Overflow FIFO values for 8,16,32
}REF_TABLE, *PREF_TABLE;

// Video Clocks for CH9294 Version G
enum{
	VC_25,VC_28,VC_40,VC_72,VC_50,VC_XX,VC_36,VC_45,VC_130,
	VC_120,VC_80,VC_31,VC_110,VC_65,VC_75,VC_94,VC_100,VC_135,
	VC_144,VC_160,VC_188,VC_47,VC_56,VC_49,VC_78,VC_108,VC_157,
	VC_175,VC_202,VC_41,VC_53,VC_77
};

#pragma pack()
#endif // _REFRESH_DEFS


#ifdef DEFINE_REFRESH_DATA

#define NA 255
#define INVALID_MODE 255

unsigned short aIndexToVClk[] = {
	25,										//	VC_25,
	28,										//	VC_28,
	40,										//	VC_40,
	72,										//	VC_72,
	50,										//	VC_50,
	00,										//	VC_XX,
	36,										//	VC_36,
	45,										//	VC_45,
	130,									//	VC_130,
	120,									//	VC_120,
	80,										//	VC_80,
	31,										//	VC_31,
	110,									//	VC_110,
	65,										//	VC_65,
	75,										//	VC_75,
	94,										//	VC_94,
	100,									//	VC_100,
	135,									//	VC_135,
	144,									//	VC_144,
	160,									//	VC_160,
	188,									//	VC_188,
	47,										//	VC_47,
	56,										//	VC_56,
	49,										//	VC_49,
	78,										//	VC_78,
	108,									//	VC_108,
	157,									//	VC_157,
	175,									//	VC_175,
	202,									//	VC_202,
	41,										//	VC_41,
	53,										//	VC_53,
	77										//	VC_77
};


// Tables of CRTC adjustments to a mode for a specified refresh.

REF_TABLE aRefUnsupported[]={
	{0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x000, 0x000, 0x000, 0x000, 0x0, 0x00, 0x00, 0x00, VC_50,
	{{11,7,21,VC_50},{28,19,30,VC_110},{INVALID_MODE}}}
};

REF_TABLE aRef640x480[]={
	{60, 0x5F, 0x4F, 0x50, 0x52, 0x1E, 0x22, 0x20B, 0x1DF, 0x1E7, 0x1EA, 0xC, 0x04, 0x3E, 0xC0,VC_25,
	{{1,0,16,VC_25},{3,2,17,VC_50},{10,6,21,VC_75},{0,2,0,VC_75},{1,0,16,VC_25}}},
	{72, 0x62, 0x4F, 0x50, 0x52, 0x17, 0x26, 0x206, 0x1DF, 0x1E7, 0x1E8, 0xB, 0xFF, 0x3E, 0xC0,VC_31,
	{{1,0,16,VC_31},{6,3,19,VC_65},{15,10,23,VC_94},{0,2,0,VC_94},{1,0,16,VC_31}}},
	{75, 0x63, 0x4F, 0x50, 0x51, 0x19, 0x27, 0x1F2, 0x1DF, 0x1E0, 0x1E0, 0x3, 0xF2, 0x1F, 0xC0,VC_31,
	{{1,0,16,VC_31},{6,3,19,VC_65},{15,10,23,VC_94},{0,2,0,VC_94},{1,0,16,VC_31}}},
/* Removed for all chips prior to 6424, 85Hz is available for 6422 if VesaTimings Switch is set for VESA Table
	{85, 0x62, 0x4F, 0x50, 0x53, 0x19, 0x26, 0x1FB, 0x1DF, 0x1E0, 0x1E0, 0x3, 0xFB, 0x1F, 0xC0,VC_36,
	{{1,0,16,VC_36},{6,3,19,VC_72},{15,10,23,VC_110},{0,2,0,VC_110}}},
	{100, 0x5F, 0x4F, 0x50, 0x55, 0x1D, 0x22, 0x206, 0x1DF, 0x1E0, 0x1E5, 0xA, 0xF9, 0x3E, 0xC0,VC_41,
	{{4,3,17,VC_40},{9,6,20,VC_80},{18,13,24,VC_120},{3,5,1,VC_120}}},
	{120, 0x63, 0x4F, 0x50, 0x54, 0x02, 0x24, 0x217, 0x1DF, 0x1E0, 0x1E4, 0x1, 0x0A, 0x3E, 0xC0,VC_53,
	{{7,6,19,VC_94},{12,9,22,VC_108},{21,16,26,VC_157},{6,8,3,VC_157}}},
*/
	{0}
};

REF_TABLE aRef640x480VESA[]={
	{60, 0x5F, 0x4F, 0x50, 0x52, 0x1E, 0x22, 0x20B, 0x1DF, 0x1E7, 0x1E9, 0xB, 0x04, 0x3E, 0xC0,VC_25,
	{{1,0,16,VC_25},{3,2,17,VC_50},{10,6,21, VC_75},{0,2,0,VC_75},{1,0,16,VC_25}}},
	{72, 0x63, 0x4F, 0x50, 0x53, 0x18, 0x27, 0x206, 0x1DF, 0x1E7, 0x1E8, 0xB, 0xFF, 0x3E, 0xC0,VC_31,
	{{1,0,16,VC_31},{6,3,19,VC_65},{15,10,23,VC_94},{0,2,0,VC_94},{1,0,16,VC_31}}},
	{75, 0x64, 0x4F, 0x50, 0x52, 0x1A, 0x27, 0x1F2, 0x1DF, 0x1E0, 0x1E0, 0x3, 0xF2, 0x1F, 0xC0,VC_31,
	{{1,0,16,VC_31},{6,3,19,VC_65},{15,10,23,VC_94},{0,2,0,VC_94},{1,0,16,VC_31}}},
	{85, 0x63, 0x4F, 0x50, 0x54, 0x1A, 0x27, 0x1FB, 0x1DF, 0x1E0, 0x1E0, 0x3, 0xFB, 0x1F, 0xC0,VC_36,
	{{2,1,17,VC_36},{6,4,19,VC_72},{17,11,24,VC_110},{0,2,0,VC_110},{2,1,17,VC_36}}},
	{100, 0x5F, 0x4F, 0x50, 0x55, 0x1D, 0x22, 0x206, 0x1DF, 0x1E0, 0x1E5, 0xA, 0xF9, 0x3E, 0xC0,VC_41,
	{{4,3,17,VC_40},{9,6,20,VC_80},{18,13,24,VC_120},{3,5,1,VC_120},{4,3,17,VC_40}}},
	{120, 0x63, 0x4F, 0x50, 0x54, 0x02, 0x24, 0x217, 0x1DF, 0x1E0, 0x1E4, 0x1, 0x0A, 0x3E, 0xC0,VC_53,
	{{7,6,19,VC_94},{12,9,21,VC_108},{21,16,25,VC_157},{6,8,3,VC_157},{7,6,19,VC_94}}},
	{0}
};


REF_TABLE aRef800x600[]={
	{56, 0x7B, 0x63, 0x64, 0x66, 0x0F, 0x3E, 0x26F, 0x257, 0x258, 0x258, 0xA, 0x6F, 0xF0, 0x0,VC_36,
	{{2,1,17,VC_36},{6,4,19,VC_72},{17,11,24,VC_72},{0,9,0,VC_72},{2,1,17,VC_36}}},
	{60, 0x80, 0x63, 0x64, 0x68, 0x18, 0x02, 0x272, 0x257, 0x258, 0x258, 0xC, 0x72, 0xF0, 0x0,VC_40,
	{{2,1,17,VC_40},{7,4,19,VC_80},{19,12,25,VC_80},{0,9,0,VC_80},{2,1,17,VC_40}}},
	{72, 0x7D, 0x63, 0x64, 0x6A, 0x19, 0x00, 0x29C, 0x257, 0x258, 0x27C, 0x2, 0x9C, 0xF0, 0x0,VC_50,
	{{3,2,17,VC_50},{17,17,20,VC_94},{25,19,27,VC_94},{0,9,0,VC_94},{3,2,17,VC_50}}},
	{75, 0x7F, 0x63, 0x64, 0x65, 0x0F, 0x02, 0x26F, 0x257, 0x258, 0x258, 0xB, 0x6F, 0xF0, 0x0,VC_50,
	{{3,2,17,VC_50},{17,17,20,VC_94},{25,19,27,VC_94},{0,9,0,VC_94},{3,2,17,VC_50}}},
/* Removed for all chips prior to 6424, 85Hz is available for 6422 if VesaTimings Switch is set for VESA Table
	{85, 0x7F, 0x63, 0x64, 0x65, 0x0F, 0x02, 0x26F, 0x257, 0x258, 0x258, 0xB, 0x6F, 0xF0, 0x0,VC_56,
	{{3,2,17,VC_56},{17,17,20,VC_94},{INVALID_MODE},{INVALID_MODE}}},
//      {{3,2,17,VC_56},{17,17,20,VC_94},{25,19,28,VC_94},{0,8,0,VC_94}}},
	{100, 0x79, 0x63, 0x64, 0x66, 0x12, 0x3C, 0x285, 0x257, 0x258, 0x25F, 0xE, 0x7A, 0xF0, 0x0,VC_65,
	{{6,5,18,VC_56},{20,20,21,VC_130},{INVALID_MODE},{INVALID_MODE}}},
	{120, 0x7A, 0x63, 0x64, 0x68, 0x11, 0x3D, 0x277, 0x257, 0x258, 0x25C, 0xE, 0x6E, 0xF0, 0x0,VC_77,
	{{9,8,20,VC_56},{23,23,23,VC_157},{INVALID_MODE},{INVALID_MODE}}},
*/
	{0}
};

REF_TABLE aRef800x600VESA[]={
	{56, 0x7B, 0x63, 0x64, 0x67, 0x10, 0x3E, 0x26F, 0x257, 0x258, 0x258, 0xA, 0x6F, 0xF0, 0x0,VC_36,
	{{2,1,17,VC_36},{6,4,19,VC_72},{17,11,24,VC_72},{0,9,0,VC_72},{2,1,17,VC_36}}},
	{60, 0x7F, 0x63, 0x63, 0x69, 0x19, 0x03, 0x272, 0x257, 0x258, 0x258, 0xC, 0x72, 0xF0, 0x0,VC_40,
	{{2,1,17,VC_40},{7,4,19,VC_80},{19,12,25,VC_80},{0,9,0,VC_80},{2,1,17,VC_40}}},
	{72, 0x7D, 0x63, 0x64, 0x6B, 0x1A, 0x01, 0x298, 0x257, 0x258, 0x27C, 0x2, 0x98, 0xF0, 0x0,VC_50,
	{{3,2,17,VC_50},{17,17,20,VC_94},{25,19,27,VC_94},{0,9,0,VC_94},{3,2,17,VC_50}}},
	{75, 0x7F, 0x63, 0x63, 0x66, 0x10, 0x02, 0x26F, 0x257, 0x258, 0x258, 0xB, 0x6F, 0xF0, 0x0,VC_49,
	{{3,2,17,VC_49},{17,17,20,VC_94},{25,19,27,VC_94},{0,9,0,VC_94},{3,2,17,VC_49}}},
	{85, 0x7E, 0x63, 0x63, 0x68, 0x10, 0x02, 0x275, 0x257, 0x258, 0x258, 0xB, 0x76, 0xF0, 0x0,VC_56,
	{{4,2,18,VC_56},{11,7,21,VC_110},{9,9,20,VC_94},{INVALID_MODE},{4,2,18,VC_56}}},
      //{{4,2,18,VC_56},{11,7,21,VC_110},{25,19,28,VC_94},{0,8,0,VC_94}}},
	{100, 0x79, 0x63, 0x64, 0x66, 0x12, 0x3C, 0x285, 0x257, 0x258, 0x25F, 0xE, 0x7A, 0xF0, 0x0,VC_65,
	{{6,5,18,VC_56},{20,20,21,VC_130},{12,11,21,VC_120},{INVALID_MODE},{6,5,18,VC_56}}},
	{120, 0x7A, 0x63, 0x64, 0x68, 0x11, 0x3D, 0x277, 0x257, 0x258, 0x25C, 0xE, 0x6E, 0xF0, 0x0,VC_77,
	{{9,8,20,VC_56},{23,23,23,VC_157},{INVALID_MODE},{INVALID_MODE},{9,8,20,VC_56}}},
	{0}
};

REF_TABLE aRef1024x768[]={
	{43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x000, 0x000, 0x000, 0x000, 0x0, 0x00, 0x00, 0x00,VC_45,
	{{2,0,17,VC_45},{9,5,21,VC_45},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE}}},
	{60, 0xA2, 0x7F, 0x80, 0x82, 0x13, 0x26, 0x324, 0x2FF, 0x300, 0x302, 0x8, 0x24, 0xFD, 0xC0,VC_65,
	{{5,3,18,VC_65},{15,9,23,VC_65},{INVALID_MODE},{INVALID_MODE},{5,3,18,VC_65}}},
	{70, 0xA1, 0x7F, 0x80, 0x82, 0x13, 0x24, 0x324, 0x2FF, 0x300, 0x302, 0x8, 0x24, 0xFD, 0xC0,VC_75,
	{{6,4,19,VC_75},{17,11,24,VC_75},{INVALID_MODE},{INVALID_MODE},{6,4,19,VC_75}}},
	{72, 0xA4, 0x7F, 0x80, 0x81, 0x12, 0x24, 0x324, 0x2FF, 0x300, 0x302, 0x8, 0x24, 0xFD, 0x0, VC_78,
	{{7,4,19,VC_80},{18,12,25,VC_80},{INVALID_MODE},{INVALID_MODE},{7,4,19,VC_80}}},
	{75, 0xA3, 0x7F, 0x80, 0x83, 0x0F, 0x22, 0x31E, 0x2FF, 0x300, 0x300, 0x3, 0x1E, 0xFD, 0x0, VC_78,
	{{7,4,19,VC_80},{19,12,25,VC_80},{INVALID_MODE},{INVALID_MODE},{7,4,19,VC_80}}},
/* Removed for all chips prior to 6424, 85Hz is available for 6422 if VesaTimings Switch is set for VESA Table
	{85, 0xA6, 0x7F, 0x80, 0x85, 0x0F, 0x22, 0x31E, 0x2FF, 0x300, 0x300, 0x3, 0x1E, 0xFD, 0x0, VC_94,
	{{7,4,19,VC_94},{19,12,25,VC_94},{INVALID_MODE}}},
	{100, 0xA3, 0x7F, 0x80, 0x81, 0x0C, 0x11, 0x330, 0x2FF, 0x300, 0x307, 0x9, 0x2D, 0xFD, 0x0, VC_108,
	{{10,7,21,VC_108},{INVALID_MODE},{INVALID_MODE}}},
*/
	{0}
};

REF_TABLE aRef1024x768VESA[]={
	{43, 0x99, 0x7f, 0x80, 0x81, 0x17, 0x9c, 0x32f, 0x2ff, 0x300, 0x300, 0x8, 0x2e, 0xfd, 0x00,VC_45,
	{{2,0,17,VC_45},{9,5,21,VC_45},{10,10,20,VC_45},{INVALID_MODE},{INVALID_MODE}}},
	{60, 0xA3, 0x7F, 0x7F, 0x83, 0x14, 0x27, 0x324, 0x2FF, 0x300, 0x302, 0x8, 0x24, 0xFD, 0xC0,VC_65,
	{{5,3,18,VC_65},{15,9,23,VC_65},{11,11,21},{11,11,21},{5,3,18,VC_65}}},
	{70, 0xA1, 0x7F, 0x7F, 0x83, 0x14, 0x24, 0x324, 0x2FF, 0x300, 0x302, 0x8, 0x24, 0xFD, 0xC0,VC_75,
	{{6,4,19,VC_75},{17,11,24,VC_75},{13,13,23},{13,13,23},{6,4,19,VC_75}}},
	{72, 0xA4, 0x7F, 0x80, 0x81, 0x12, 0x24, 0x324, 0x2FF, 0x300, 0x302, 0x8, 0x24, 0xFD, 0x0, VC_78,
	{{7,4,19,VC_80},{18,12,25,VC_80},{14,14,24},{14,14,24},{7,4,19,VC_80}}},
	{75, 0x9F, 0x7F, 0x7F, 0x82, 0x0E, 0x23, 0x31E, 0x2FF, 0x300, 0x300, 0x3, 0x1E, 0xFD, 0x0, VC_78,
	{{7,4,19,VC_80},{19,12,25,VC_80},{16,16,25},{16,16,25},{7,4,19,VC_80}}},
	{85, 0xA7, 0x7F, 0x7F, 0x86, 0x12, 0x2A, 0x326, 0x2FF, 0x300, 0x300, 0x3, 0x27, 0xFD, 0x0, VC_94,
	{{7,4,19,VC_94},{19,12,25,VC_94},{18,18,27},{18,18,27},{7,4,19,VC_94}}},
	{100, 0xA1, 0x7F, 0x80, 0x81, 0x0C, 0x11, 0x330, 0x2FF, 0x300, 0x307, 0x9, 0x2D, 0xFD, 0x0, VC_108,
	{{12,9,22,VC_108},{7,7,19,VC_108},{INVALID_MODE},{INVALID_MODE},{12,9,22,VC_108}}},
	{0}
};

REF_TABLE aRef1152x864[]={
	{60, 0xB4, 0x8F, 0x90, 0x94, 0x04, 0x37, 0x382, 0x35F, 0x360, 0x360, 0x3, 0x82, 0xFF, 0x0,VC_80,
	{{7,4,19,VC_80},{19,12,25,VC_80},{INVALID_MODE},{INVALID_MODE},{7,4,19,VC_80}}},
	{70, 0xB4, 0x8F, 0x90, 0x94, 0x00, 0x38, 0x38E, 0x35F, 0x360, 0x360, 0x3, 0x8F, 0xFF, 0x0,VC_94,
	{{9,6,20,VC_94},{22,15,27,VC_94},{INVALID_MODE},{INVALID_MODE},{9,6,20,VC_94}}},
	{72, 0xB1, 0x8F, 0x90, 0x94, 0x04, 0x34, 0x382, 0x35F, 0x360, 0x360, 0x3, 0x82, 0xFF, 0x0,VC_94,
	{{9,6,20,VC_94},{22,15,27,VC_94},{INVALID_MODE},{INVALID_MODE},{9,6,20,VC_94}}},
	{75, 0xB4, 0x8F, 0x90, 0x97, 0x07, 0x37, 0x382, 0x35F, 0x360, 0x360, 0x3, 0x82, 0xFF, 0x0,VC_100,
	{{11,7,21,VC_110},{28,19,30,VC_110},{INVALID_MODE},{INVALID_MODE},{11,7,21,VC_110}}},
/* Removed for all chips prior to 6424, 85Hz is available for 6422 if VesaTimings Switch is set for VESA Table
	{85, 0xBF, 0x8F, 0x90, 0x98, 0x08, 0x03, 0x388, 0x35F, 0x360, 0x361, 0x4, 0x89, 0xFF, 0x0,VC_120,
	{{14,10,22,VC_120},{31,22,31,VC_120},{INVALID_MODE}}},
*/
	{0}
};

REF_TABLE aRef1152x864VESA[]={
	{60, 0xB4, 0x8F, 0x90, 0x94, 0x04, 0x37, 0x382, 0x35F, 0x360, 0x360, 0x3, 0x82, 0xFF, 0x0,VC_80,
	{{7,4,19,VC_80},{19,12,25,VC_80},{17,17,25},{17,17,25},{7,4,19,VC_80}}},
	{70, 0xB4, 0x8F, 0x90, 0x94, 0x00, 0x38, 0x38E, 0x35F, 0x360, 0x360, 0x3, 0x8F, 0xFF, 0x0,VC_94,
	{{9,6,20,VC_94},{22,15,27,VC_94},{19,19,27},{19,19,27},{9,6,20,VC_94}}},
	{75, 0xC3, 0x8F, 0x90, 0x98, 0x08, 0x36, 0x382, 0x35F, 0x360, 0x360, 0x3, 0x82, 0xFF, 0x0,VC_108,
	{{11,7,21,VC_108},{9,8,19,VC_120},{INVALID_MODE},{INVALID_MODE},{11,7,21,VC_108}}},
	{85, 0xBF, 0x8F, 0x90, 0x98, 0x08, 0x03, 0x388, 0x35F, 0x360, 0x361, 0x4, 0x89, 0xFF, 0x0,VC_120,
	{{14,10,22,VC_120},{8,8,19,VC_120},{INVALID_MODE},{INVALID_MODE},{14,10,22,VC_120}}},
	{0}
};

REF_TABLE aRef1280x1024[]={
	{43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x000, 0x000, 0x000, 0x000, 0x0, 0x00, 0x00, 0x0,VC_75,
	{{6,3,19,VC_75},{15,9,24,VC_75},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE}}},
	/*
	{60, 0xC2, 0x9F, 0xA0, 0xA1, 0x15, 0x02, 0x029, 0x3FF, 0x000, 0x001, 0x5, 0x29, 0x52, 0x0,VC_100,
	{{12,8,22,VC_50},{INVALID_MODE},{INVALID_MODE}}},
	{60, 0xD3, 0x9F, 0xA0, 0xAB, 0x1F, 0x16, 0x029, 0x3FF, 0x000, 0x001, 0x5, 0x29, 0x52, 0x0,VC_108,
	{{INVALID_MODE},{26,18,27,VC_108},{INVALID_MODE}}},
	*/
	//VESA Settings for 60 Hz
	{60, 0xCE, 0x9F, 0x9F, 0xA6, 0x14, 0x12, 0x028, 0x3FF, 0x3FF, 0x000, 0x3, 0x29, 0x52, 0x0, VC_108,
	{{12,8,22,VC_50},{26,18,27,VC_110},{INVALID_MODE},{INVALID_MODE},{12,8,22,VC_50}}},
	{72, 0xCE, 0x9F, 0xA0, 0xA2, 0x16, 0x11, 0x029, 0x3FF, 0x000, 0x001, 0x5, 0x29, 0x52, 0x0,VC_130,
	{{15,9,23,VC_65},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE},{15,9,23,VC_65}}},
	//VESA Settings for 75 Hz
	{75, 0xCE, 0x9F, 0x9F, 0xA2, 0x14, 0x12, 0x028, 0x3FF, 0x3FF, 0x000, 0x3, 0x28, 0x52, 0x0, VC_135,
	{{15,9,23,VC_72},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE},{15,9,23,VC_72}}},
	//{75, 0xDC, 0x9F, 0xA0, 0xA2, 0x16, 0x1F, 0x029, 0x3FF, 0x000, 0x001, 0x5, 0x29, 0x52, 0x0,VC_135,
	//{{15,9,23,VC_72},{INVALID_MODE},{INVALID_MODE}}},
/* Removed for all chips prior to 6424, 85Hz is available for 6422 if VesaTimings Switch is set for VESA Table
	{85, 0xD2, 0x9F, 0x9F, 0xA5, 0x19,0x15, 0x02C, 0x3FF, 0x3FF, 0x000, 0x3, 0x2D, 0x5A, 0x0, VC_157,
	{{18,12,24,VC_157},{INVALID_MODE},{INVALID_MODE}}},
*/
	{0}
};

REF_TABLE aRef1280x1024VESA[]={
	{43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x000, 0x000, 0x000, 0x000, 0x0, 0x00, 0x00, 0x0, VC_75,
	{{6,3,19,VC_75},{5,5,18,VC_75},{INVALID_MODE},{INVALID_MODE},{6,3,19,VC_75}}},
	{60, 0xCE, 0x9F, 0x9F, 0xA6, 0x14, 0x12, 0x028, 0x3FF, 0x3FF, 0x000, 0x3, 0x29, 0x52, 0x0, VC_108,
	{{12,8,22,VC_50},{7,7,19,VC_110},{INVALID_MODE},{19,19,27},{12,8,22,VC_50}}},
	{72, 0xCE, 0x9F, 0xA0, 0xA2, 0x16, 0x11, 0x029, 0x3FF, 0x000, 0x001, 0x5, 0x29, 0x52, 0x0, VC_130,
	{{15,9,23,VC_65},{10,10,20,VC_65},{INVALID_MODE},{INVALID_MODE},{15,9,23,VC_65}}},
	{75, 0xCE, 0x9F, 0x9F, 0xA2, 0x14, 0x12, 0x028, 0x3FF, 0x3FF, 0x000, 0x3, 0x28, 0x52, 0x0, VC_135,
	{{15,9,23,VC_72},{10,10,20,VC_65},{INVALID_MODE},{INVALID_MODE},{15,9,23,VC_72}}},
	{85, 0xD2, 0x9F, 0x9F, 0xA5, 0x19,0x15, 0x02C, 0x3FF, 0x3FF, 0x000, 0x3, 0x2D, 0x5A, 0x0, VC_157,
	{{18,12,24,VC_157},{13,12,21,VC_157},{INVALID_MODE},{INVALID_MODE},{18,12,24,VC_157}}},
	{0}
};

REF_TABLE aRef1600x1200[]={
	{43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x000, 0x000, 0x000, 0x000, 0x0, 0x00, 0x00, 0x00,VC_135,
	{{4,4,17,VC_45},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE}}},
	{60, 0x09, 0xC7, 0xC8, 0xCB, 0x1F, 0x0C, 0x0E0, 0x0AF, 0x0B0, 0x0B0, 0x3, 0x0E0, 0x10, 0x0, VC_160,
	{{18,12,25,VC_80},{14,14,22},{INVALID_MODE},{INVALID_MODE},{18,12,25,VC_80}}},
	{65, 0x09, 0xC7, 0xC8, 0xCB, 0x1F, 0x0C, 0x0E0, 0x0AF, 0x0B0, 0x0B0, 0x3, 0x0E0, 0x10, 0x0, VC_175,
	{{18,12,25,VC_80},{INVALID_MODE},{INVALID_MODE},{INVALID_MODE},{18,12,25,VC_80}}},
//      {70, 0x09, 0xC7, 0xC8, 0xCB, 0x1F, 0x0C, 0x0E0, 0x0AF, 0x0B0, 0x0B0, 0x3, 0x0E0, 0x10, 0x0, VC_188,
//      {{22,15,27,VC_94},{INVALID_MODE},{INVALID_MODE}}},
	{0}
};


// Arrays of Non-VESA/VESA CRTC tables
REF_TABLE* apRefTables[]= {
	aRef640x480,aRef800x600,aRef1024x768,aRef1152x864,aRef1280x1024,aRef1600x1200,aRefUnsupported};
REF_TABLE* apRefTablesVESA[]= {
	aRef640x480VESA,aRef800x600VESA,aRef1024x768VESA,aRef1152x864VESA,aRef1280x1024VESA,aRef1600x1200,aRefUnsupported};

#ifdef REFRESH_CAPS			// For Win95, refresh tables are moved here from physsetm.c.
// 8 bit
// Refresh rates available at specified Resolution
int aResAvailRefresh1[][CREFRESH] = {
	{60,72,75,85,100,120,NA, NA},					//640x480
	{56,60,72,75,85, 100,120,NA},					//800x600
	{60,70,75,85,100,NA, NA, NA},					//1024x768
	{60,70,75,85,NA, NA, NA, NA},					//1152x864
	{60,72,75,85,NA, NA, NA, NA},					//1280x1024
	{60,NA,NA,NA,NA, NA, NA, NA},					//1600x1200
	{NA,NA,NA,NA,NA, NA, NA, NA}					//Unsupported
};

// 16 bit
// Refresh rates available at specified Resolution
int aResAvailRefresh2[][CREFRESH]= {
	{60,72,75,85,100,120,NA, NA},					//640x480
	{56,60,72,75,85, 100,120,NA},					//800x600
	{60,70,75,85,NA, NA, NA, NA},					//1024x768
	{60,70,75,NA,NA, NA, NA, NA},					//1152x864
	{60,72,75,85,NA, NA, NA, NA},					//1280x1024
	{60,NA,NA,NA,NA, NA, NA, NA},					//1600x1200
	{NA,NA,NA,NA,NA, NA, NA, NA}					//Unsupported
};

// 24 bit
// Refresh rates available at specified Resolution
int aResAvailRefresh3[][CREFRESH] = {
	{60,72,75,NA,NA, NA, NA, NA},						//640x480
	{56,60,72,75,NA, NA, NA, NA},						//800x600
	{60,70,75,85,NA, NA, NA, NA},						//1024x768
	{60,70,NA,NA,NA, NA, NA, NA},						//1152x864
	{60,NA,NA,NA,NA, NA, NA, NA},						//1280x1024
	{NA,NA,NA,NA,NA, NA, NA, NA},						//1600x1200
	{NA,NA,NA,NA,NA, NA, NA, NA}						//Unsupported
};

// 32 bit
// Refresh rates available at specified Resolution
int aResAvailRefresh4[][CREFRESH] =	{
	{60,72,75,85,100,120,NA, NA},						//640x480
	{56,60,72,75,85,100,120, NA},						//800x600
	{60,70,75,85,NA, NA, NA, NA},						//1024x768
	{60,70,NA,NA,NA, NA, NA, NA},						//1152x864
	{NA,NA,NA,NA,NA, NA, NA, NA},						//1280x1024
	{NA,NA,NA,NA,NA, NA, NA, NA},						//1600x1200
	{NA,NA,NA,NA,NA, NA, NA, NA} 						//Unsupported
};

// 4 bit
// Refresh rates available at specified Resolution
int aResAvailRefresh5[][CREFRESH] =	{
	{60,72,75,85,100,120,NA, NA},					//640x480
	{56,60,72,75,85, 100,120,NA},					//800x600
	{60,70,75,85,100,NA, NA, NA},					//1024x768
	{60,70,75,85,NA, NA, NA, NA},					//1152x864
	{60,75,85,NA, NA,NA, NA, NA},					//1280x1024
	{60,NA,NA,NA,NA, NA, NA, NA},					//1600x1200
	{NA,NA,NA,NA,NA, NA, NA, NA}					//Unsupported
};


PARES_AVAIL_REFRESH apaResAvailRefresh[]=	{
		aResAvailRefresh5,  //4bpp
		aResAvailRefresh1,
		aResAvailRefresh2,
		aResAvailRefresh3,
		aResAvailRefresh4
};
#endif

#endif  //_REFRESH_DATA