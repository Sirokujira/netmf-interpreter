using System;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using System.Runtime.CompilerServices;

namespace CQ.NETMF.LEDMATRIX
{
    public class RGBLEDMatrix
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_Initialize(UInt32[] Pins);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_SelectLine(byte n);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_TurnOn();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_TurnOff();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_DrawLine8(byte pat, byte fcol, byte bcol);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_DrawLine64(byte pat, byte fcol, byte bcol);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_DrawPat(byte[] pat);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_DrawFont8x8(byte[] pat);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RGBLEDMatrix_GetFontBitmap(UInt16 unicode, byte[] pat);

        public RGBLEDMatrix(Cpu.Pin[] Pins)
        {
            UInt32[] pins = new UInt32[8];

            for (int i=0; i<8; i++) {
                pins[i] = (UInt32)Pins[i];
            }
            RGBLEDMatrix_Initialize(pins);
        }

        public void SelectLine(byte n)
        {
            RGBLEDMatrix_SelectLine(n);
        }

        public void TurnOn()
        {
            RGBLEDMatrix_TurnOn();
        }

        public void TurnOff()
        {
            RGBLEDMatrix_TurnOff();
        }

        public void DrawLine8(byte pat, byte fcol, byte bcol)
        {
            RGBLEDMatrix_DrawLine8(pat, fcol, bcol);
        }

        public void DrawLine64(byte pat, byte fcol, byte bcol)
        {
            RGBLEDMatrix_DrawLine64(pat, fcol, bcol);
        }

        public void DrawPat(byte[] pat)
        {
            RGBLEDMatrix_DrawPat(pat);
        }

        public void DrawFont8x8(byte[] pat)
        {
            RGBLEDMatrix_DrawFont8x8(pat);
        }

        public void GetFontBitmap(UInt16 unicode, byte[] pat)
        {
            RGBLEDMatrix_GetFontBitmap(unicode, pat);
        }
    }
}
