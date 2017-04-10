using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;
//using Microsoft.SPOT.Hardware;

namespace CQ.NETMF.LCD
{
    public static class LCDDevice
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void LCDDevice_LCD_Initialize();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void LCDDevice_LCD_Clear();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void LCDDevice_LCD_BitBltEx(uint x, uint y, uint width, uint height, byte[] data);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void LCDDevice_LCD_WriteFormattedChar(UInt16 c);

        static LCDDevice()
        {
            LCDDevice_LCD_Initialize();
            LCDDevice_LCD_Clear();
        }

        public static void Clear()
        {
            LCDDevice_LCD_Clear();
        }

        public static void BitBltEx(uint x, uint y, uint width, uint height, byte[] data)
        {
            LCDDevice_LCD_BitBltEx(x, y, width, height, data);
        }

        public static void WriteFormattedChar(Char c)
        {
            LCDDevice_LCD_WriteFormattedChar(c);
        }
    }
}
