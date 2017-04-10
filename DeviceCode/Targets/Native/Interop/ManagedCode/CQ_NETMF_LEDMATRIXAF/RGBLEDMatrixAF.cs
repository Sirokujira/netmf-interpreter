using System;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using System.Runtime.CompilerServices;

namespace CQ.NETMF.LEDMATRIXAF
{
    public class RGBLEDMatrixAF
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_Initialize(UInt32[] Pins);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_SelectLine(byte n);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_TurnOn();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_TurnOff();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_DrawLineColor2(UInt32 pat1, byte[] fcol1, byte[] bcol1, UInt32 pat2, byte[] fcol2, byte[] bcol2);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_DrawScreenColor2(UInt32[] pat1, UInt32 off1, byte[] fcol1, byte[] bcol1, UInt32[] pat2, UInt32 off2, byte[] fcol2, byte[] bcol2, UInt32 loop);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_DrawScreenColor2(byte[] pat1, UInt32 off1, byte[] fcol1, byte[] bcol1, UInt32[] pat2, UInt32 off2, byte[] fcol2, byte[] bcol2, UInt32 loop);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_DrawScreenColor64(byte[] pat1, UInt32 off1, byte[] pat2, UInt32 off2, UInt32 loop);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_GetFontBitmap(UInt16 unicode, byte[] pat);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_SetFontsToBuf(UInt16[] unicode, byte[] buf);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_SetFontsToBuf(UInt16[] unicode, UInt32[] buf);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_RotateXBufColor2(UInt32[] buf, Int32 rx);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_Pset(byte[] buf, Int32 x, Int32 y, byte col_type, byte col);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_Line(byte[] buf, Int32 x1, Int32 y1, Int32 x2, Int32 y2, byte col_type, byte col);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrixAF_Circle(byte[] buf, Int32 x, Int32 y, Int32 r, byte col_type, byte col);

        public RGBLEDMatrixAF(Cpu.Pin[] Pins)
        {
            UInt32[] pins = new UInt32[12];

            for (int i=0; i<12; i++) {
                pins[i] = (UInt32)Pins[i];
            }
            RGBLEDMatrixAF_Initialize(pins);
        }

        public void SelectLine(byte n)
        {
            RGBLEDMatrixAF_SelectLine(n);
        }

        public void TurnOn()
        {
            RGBLEDMatrixAF_TurnOn();
        }

        public void TurnOff()
        {
            RGBLEDMatrixAF_TurnOff();
        }

        public void DrawLineColor2(UInt32 pat1, byte[] fcol1, byte[] bcol1, UInt32 pat2, byte[] fcol2, byte[] bcol2)
        {
            RGBLEDMatrixAF_DrawLineColor2(pat1, fcol1, bcol1, pat2, fcol2, bcol2);
        }

        public void DrawScreenColor2(UInt32[] pat1, UInt32 off1, byte[] fcol1, byte[] bcol1, UInt32[] pat2, UInt32 off2, byte[] fcol2, byte[] bcol2, UInt32 loop)
        {
            RGBLEDMatrixAF_DrawScreenColor2(pat1, off1, fcol1, bcol1, pat2, off2, fcol2, bcol2, loop);
        }

        public void DrawScreenColor64(byte[] col1, UInt32 off1, byte[] col2, UInt32 off2, UInt32 loop)
        {
            RGBLEDMatrixAF_DrawScreenColor64(col1, off1, col2, off2, loop);
        }

        public void GetFontBitmap(UInt16 unicode, byte[] pat)
        {
            RGBLEDMatrixAF_GetFontBitmap(unicode, pat);
        }

        public void SetFontsToBuf(UInt16[] unicode, byte[] pat)
        {
            RGBLEDMatrixAF_SetFontsToBuf(unicode, pat);
        }

        public void RotateXBufColor2(UInt32[] buf, Int32 rx)
        {
            RGBLEDMatrixAF_RotateXBufColor2(buf, rx);
        }

        public void Pset(byte[] buf, Int32 x, Int32 y, byte col_type, byte col)
        {
            RGBLEDMatrixAF_Pset(buf, x, y, col_type, col);
        }

        public void Line(byte[] buf, Int32 x1, Int32 y1, Int32 x2, Int32 y2, byte col_type, byte col)
        {
            RGBLEDMatrixAF_Line(buf, x1, y1, x2, y2, col_type, col);
        }

        public void Circle(byte[] buf, Int32 x, Int32 y, Int32 r, byte col_type, byte col)
        {
            RGBLEDMatrixAF_Circle(buf, x, y, r, col_type, col);
        }
    }
}
