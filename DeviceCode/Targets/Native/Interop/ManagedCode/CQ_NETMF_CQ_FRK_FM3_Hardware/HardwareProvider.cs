using System;
using System.IO.Ports;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;

namespace CQ.NETMF.CQ_FRK_FM3.Hardware
{
    public class HardwareProvider : Microsoft.SPOT.Hardware.HardwareProvider
    {
        static HardwareProvider()
        {
            Microsoft.SPOT.Hardware.HardwareProvider.Register(new HardwareProvider()); 
        }
    }
        public static class Pins
    {
        internal const Cpu.Pin GPIO_PIN_0_0 = (Cpu.Pin)0x00;
        internal const Cpu.Pin GPIO_PIN_0_1 = (Cpu.Pin)0x01;
        internal const Cpu.Pin GPIO_PIN_0_2 = (Cpu.Pin)0x02;
        internal const Cpu.Pin GPIO_PIN_0_3 = (Cpu.Pin)0x03;
        internal const Cpu.Pin GPIO_PIN_0_4 = (Cpu.Pin)0x04;
        internal const Cpu.Pin GPIO_PIN_0_5 = (Cpu.Pin)0x05;
        internal const Cpu.Pin GPIO_PIN_0_6 = (Cpu.Pin)0x06;
        internal const Cpu.Pin GPIO_PIN_0_7 = (Cpu.Pin)0x07;
        internal const Cpu.Pin GPIO_PIN_0_8 = (Cpu.Pin)0x08;
        internal const Cpu.Pin GPIO_PIN_0_9 = (Cpu.Pin)0x09;
        internal const Cpu.Pin GPIO_PIN_0_A = (Cpu.Pin)0x0A;
        internal const Cpu.Pin GPIO_PIN_0_B = (Cpu.Pin)0x0B;
        internal const Cpu.Pin GPIO_PIN_0_C = (Cpu.Pin)0x0C;
        internal const Cpu.Pin GPIO_PIN_0_D = (Cpu.Pin)0x0D;
        internal const Cpu.Pin GPIO_PIN_0_E = (Cpu.Pin)0x0E;
        internal const Cpu.Pin GPIO_PIN_0_F = (Cpu.Pin)0x0F;

        internal const Cpu.Pin GPIO_PIN_1_0 = (Cpu.Pin)0x10;
        internal const Cpu.Pin GPIO_PIN_1_1 = (Cpu.Pin)0x11;
        internal const Cpu.Pin GPIO_PIN_1_2 = (Cpu.Pin)0x12;
        internal const Cpu.Pin GPIO_PIN_1_3 = (Cpu.Pin)0x13;
        internal const Cpu.Pin GPIO_PIN_1_4 = (Cpu.Pin)0x14;
        internal const Cpu.Pin GPIO_PIN_1_5 = (Cpu.Pin)0x15;
        internal const Cpu.Pin GPIO_PIN_1_6 = (Cpu.Pin)0x16;
        internal const Cpu.Pin GPIO_PIN_1_7 = (Cpu.Pin)0x17;
        internal const Cpu.Pin GPIO_PIN_1_8 = (Cpu.Pin)0x18;
        internal const Cpu.Pin GPIO_PIN_1_9 = (Cpu.Pin)0x19;
        internal const Cpu.Pin GPIO_PIN_1_A = (Cpu.Pin)0x1A;
        internal const Cpu.Pin GPIO_PIN_1_B = (Cpu.Pin)0x1B;
        internal const Cpu.Pin GPIO_PIN_1_C = (Cpu.Pin)0x1C;
        internal const Cpu.Pin GPIO_PIN_1_D = (Cpu.Pin)0x1D;
        internal const Cpu.Pin GPIO_PIN_1_E = (Cpu.Pin)0x1E;
        internal const Cpu.Pin GPIO_PIN_1_F = (Cpu.Pin)0x1F;

        internal const Cpu.Pin GPIO_PIN_2_0 = (Cpu.Pin)0x20;
        internal const Cpu.Pin GPIO_PIN_2_1 = (Cpu.Pin)0x21;
        internal const Cpu.Pin GPIO_PIN_2_2 = (Cpu.Pin)0x22;
        internal const Cpu.Pin GPIO_PIN_2_3 = (Cpu.Pin)0x23;
        internal const Cpu.Pin GPIO_PIN_2_4 = (Cpu.Pin)0x24;
        internal const Cpu.Pin GPIO_PIN_2_5 = (Cpu.Pin)0x25;
        internal const Cpu.Pin GPIO_PIN_2_6 = (Cpu.Pin)0x26;
        internal const Cpu.Pin GPIO_PIN_2_7 = (Cpu.Pin)0x27;
        internal const Cpu.Pin GPIO_PIN_2_8 = (Cpu.Pin)0x28;
        internal const Cpu.Pin GPIO_PIN_2_9 = (Cpu.Pin)0x29;
        internal const Cpu.Pin GPIO_PIN_2_A = (Cpu.Pin)0x2A;
        internal const Cpu.Pin GPIO_PIN_2_B = (Cpu.Pin)0x2B;
        internal const Cpu.Pin GPIO_PIN_2_C = (Cpu.Pin)0x2C;
        internal const Cpu.Pin GPIO_PIN_2_D = (Cpu.Pin)0x2D;
        internal const Cpu.Pin GPIO_PIN_2_E = (Cpu.Pin)0x2E;
        internal const Cpu.Pin GPIO_PIN_2_F = (Cpu.Pin)0x2F;

        internal const Cpu.Pin GPIO_PIN_3_0 = (Cpu.Pin)0x30;
        internal const Cpu.Pin GPIO_PIN_3_1 = (Cpu.Pin)0x31;
        internal const Cpu.Pin GPIO_PIN_3_2 = (Cpu.Pin)0x32;
        internal const Cpu.Pin GPIO_PIN_3_3 = (Cpu.Pin)0x33;
        internal const Cpu.Pin GPIO_PIN_3_4 = (Cpu.Pin)0x34;
        internal const Cpu.Pin GPIO_PIN_3_5 = (Cpu.Pin)0x35;
        internal const Cpu.Pin GPIO_PIN_3_6 = (Cpu.Pin)0x36;
        internal const Cpu.Pin GPIO_PIN_3_7 = (Cpu.Pin)0x37;
        internal const Cpu.Pin GPIO_PIN_3_8 = (Cpu.Pin)0x38;
        internal const Cpu.Pin GPIO_PIN_3_9 = (Cpu.Pin)0x39;
        internal const Cpu.Pin GPIO_PIN_3_A = (Cpu.Pin)0x3A;
        internal const Cpu.Pin GPIO_PIN_3_B = (Cpu.Pin)0x3B;
        internal const Cpu.Pin GPIO_PIN_3_C = (Cpu.Pin)0x3C;
        internal const Cpu.Pin GPIO_PIN_3_D = (Cpu.Pin)0x3D;
        internal const Cpu.Pin GPIO_PIN_3_E = (Cpu.Pin)0x3E;
        internal const Cpu.Pin GPIO_PIN_3_F = (Cpu.Pin)0x3F;

        internal const Cpu.Pin GPIO_PIN_4_0 = (Cpu.Pin)0x40;
        internal const Cpu.Pin GPIO_PIN_4_1 = (Cpu.Pin)0x41;
        internal const Cpu.Pin GPIO_PIN_4_2 = (Cpu.Pin)0x42;
        internal const Cpu.Pin GPIO_PIN_4_3 = (Cpu.Pin)0x43;
        internal const Cpu.Pin GPIO_PIN_4_4 = (Cpu.Pin)0x44;
        internal const Cpu.Pin GPIO_PIN_4_5 = (Cpu.Pin)0x45;
        internal const Cpu.Pin GPIO_PIN_4_6 = (Cpu.Pin)0x46;
        internal const Cpu.Pin GPIO_PIN_4_7 = (Cpu.Pin)0x47;
        internal const Cpu.Pin GPIO_PIN_4_8 = (Cpu.Pin)0x48;
        internal const Cpu.Pin GPIO_PIN_4_9 = (Cpu.Pin)0x49;
        internal const Cpu.Pin GPIO_PIN_4_A = (Cpu.Pin)0x4A;
        internal const Cpu.Pin GPIO_PIN_4_B = (Cpu.Pin)0x4B;
        internal const Cpu.Pin GPIO_PIN_4_C = (Cpu.Pin)0x4C;
        internal const Cpu.Pin GPIO_PIN_4_D = (Cpu.Pin)0x4D;
        internal const Cpu.Pin GPIO_PIN_4_E = (Cpu.Pin)0x4E;
        internal const Cpu.Pin GPIO_PIN_4_F = (Cpu.Pin)0x4F;

        internal const Cpu.Pin GPIO_PIN_5_0 = (Cpu.Pin)0x50;
        internal const Cpu.Pin GPIO_PIN_5_1 = (Cpu.Pin)0x51;
        internal const Cpu.Pin GPIO_PIN_5_2 = (Cpu.Pin)0x52;
        internal const Cpu.Pin GPIO_PIN_5_3 = (Cpu.Pin)0x53;
        internal const Cpu.Pin GPIO_PIN_5_4 = (Cpu.Pin)0x54;
        internal const Cpu.Pin GPIO_PIN_5_5 = (Cpu.Pin)0x55;
        internal const Cpu.Pin GPIO_PIN_5_6 = (Cpu.Pin)0x56;
        internal const Cpu.Pin GPIO_PIN_5_7 = (Cpu.Pin)0x57;
        internal const Cpu.Pin GPIO_PIN_5_8 = (Cpu.Pin)0x58;
        internal const Cpu.Pin GPIO_PIN_5_9 = (Cpu.Pin)0x59;
        internal const Cpu.Pin GPIO_PIN_5_A = (Cpu.Pin)0x5A;
        internal const Cpu.Pin GPIO_PIN_5_B = (Cpu.Pin)0x5B;
        internal const Cpu.Pin GPIO_PIN_5_C = (Cpu.Pin)0x5C;
        internal const Cpu.Pin GPIO_PIN_5_D = (Cpu.Pin)0x5D;
        internal const Cpu.Pin GPIO_PIN_5_E = (Cpu.Pin)0x5E;
        internal const Cpu.Pin GPIO_PIN_5_F = (Cpu.Pin)0x5F;

        internal const Cpu.Pin GPIO_PIN_6_0 = (Cpu.Pin)0x60;
        internal const Cpu.Pin GPIO_PIN_6_1 = (Cpu.Pin)0x61;
        internal const Cpu.Pin GPIO_PIN_6_2 = (Cpu.Pin)0x62;
        internal const Cpu.Pin GPIO_PIN_6_3 = (Cpu.Pin)0x63;
        internal const Cpu.Pin GPIO_PIN_6_4 = (Cpu.Pin)0x64;
        internal const Cpu.Pin GPIO_PIN_6_5 = (Cpu.Pin)0x65;
        internal const Cpu.Pin GPIO_PIN_6_6 = (Cpu.Pin)0x66;
        internal const Cpu.Pin GPIO_PIN_6_7 = (Cpu.Pin)0x67;
        internal const Cpu.Pin GPIO_PIN_6_8 = (Cpu.Pin)0x68;
        internal const Cpu.Pin GPIO_PIN_6_9 = (Cpu.Pin)0x69;
        internal const Cpu.Pin GPIO_PIN_6_A = (Cpu.Pin)0x6A;
        internal const Cpu.Pin GPIO_PIN_6_B = (Cpu.Pin)0x6B;
        internal const Cpu.Pin GPIO_PIN_6_C = (Cpu.Pin)0x6C;
        internal const Cpu.Pin GPIO_PIN_6_D = (Cpu.Pin)0x6D;
        internal const Cpu.Pin GPIO_PIN_6_E = (Cpu.Pin)0x6E;
        internal const Cpu.Pin GPIO_PIN_6_F = (Cpu.Pin)0x6F;

        internal const Cpu.Pin GPIO_PIN_7_0 = (Cpu.Pin)0x70;
        internal const Cpu.Pin GPIO_PIN_7_1 = (Cpu.Pin)0x71;
        internal const Cpu.Pin GPIO_PIN_7_2 = (Cpu.Pin)0x72;
        internal const Cpu.Pin GPIO_PIN_7_3 = (Cpu.Pin)0x73;
        internal const Cpu.Pin GPIO_PIN_7_4 = (Cpu.Pin)0x74;
        internal const Cpu.Pin GPIO_PIN_7_5 = (Cpu.Pin)0x75;
        internal const Cpu.Pin GPIO_PIN_7_6 = (Cpu.Pin)0x76;
        internal const Cpu.Pin GPIO_PIN_7_7 = (Cpu.Pin)0x77;
        internal const Cpu.Pin GPIO_PIN_7_8 = (Cpu.Pin)0x78;
        internal const Cpu.Pin GPIO_PIN_7_9 = (Cpu.Pin)0x79;
        internal const Cpu.Pin GPIO_PIN_7_A = (Cpu.Pin)0x7A;
        internal const Cpu.Pin GPIO_PIN_7_B = (Cpu.Pin)0x7B;
        internal const Cpu.Pin GPIO_PIN_7_C = (Cpu.Pin)0x7C;
        internal const Cpu.Pin GPIO_PIN_7_D = (Cpu.Pin)0x7D;
        internal const Cpu.Pin GPIO_PIN_7_E = (Cpu.Pin)0x7E;
        internal const Cpu.Pin GPIO_PIN_7_F = (Cpu.Pin)0x7F;

        internal const Cpu.Pin GPIO_PIN_8_0 = (Cpu.Pin)0x80;
        internal const Cpu.Pin GPIO_PIN_8_1 = (Cpu.Pin)0x81;
        internal const Cpu.Pin GPIO_PIN_8_2 = (Cpu.Pin)0x82;
        internal const Cpu.Pin GPIO_PIN_8_3 = (Cpu.Pin)0x83;
        internal const Cpu.Pin GPIO_PIN_8_4 = (Cpu.Pin)0x84;
        internal const Cpu.Pin GPIO_PIN_8_5 = (Cpu.Pin)0x85;
        internal const Cpu.Pin GPIO_PIN_8_6 = (Cpu.Pin)0x86;
        internal const Cpu.Pin GPIO_PIN_8_7 = (Cpu.Pin)0x87;
        internal const Cpu.Pin GPIO_PIN_8_8 = (Cpu.Pin)0x88;
        internal const Cpu.Pin GPIO_PIN_8_9 = (Cpu.Pin)0x89;
        internal const Cpu.Pin GPIO_PIN_8_A = (Cpu.Pin)0x8A;
        internal const Cpu.Pin GPIO_PIN_8_B = (Cpu.Pin)0x8B;
        internal const Cpu.Pin GPIO_PIN_8_C = (Cpu.Pin)0x8C;
        internal const Cpu.Pin GPIO_PIN_8_D = (Cpu.Pin)0x8D;
        internal const Cpu.Pin GPIO_PIN_8_E = (Cpu.Pin)0x8E;
        internal const Cpu.Pin GPIO_PIN_8_F = (Cpu.Pin)0x8F;

        internal const Cpu.Pin GPIO_PIN_9_0 = (Cpu.Pin)0x90;
        internal const Cpu.Pin GPIO_PIN_9_1 = (Cpu.Pin)0x91;
        internal const Cpu.Pin GPIO_PIN_9_2 = (Cpu.Pin)0x92;
        internal const Cpu.Pin GPIO_PIN_9_3 = (Cpu.Pin)0x93;
        internal const Cpu.Pin GPIO_PIN_9_4 = (Cpu.Pin)0x94;
        internal const Cpu.Pin GPIO_PIN_9_5 = (Cpu.Pin)0x95;
        internal const Cpu.Pin GPIO_PIN_9_6 = (Cpu.Pin)0x96;
        internal const Cpu.Pin GPIO_PIN_9_7 = (Cpu.Pin)0x97;
        internal const Cpu.Pin GPIO_PIN_9_8 = (Cpu.Pin)0x98;
        internal const Cpu.Pin GPIO_PIN_9_9 = (Cpu.Pin)0x99;
        internal const Cpu.Pin GPIO_PIN_9_A = (Cpu.Pin)0x9A;
        internal const Cpu.Pin GPIO_PIN_9_B = (Cpu.Pin)0x9B;
        internal const Cpu.Pin GPIO_PIN_9_C = (Cpu.Pin)0x9C;
        internal const Cpu.Pin GPIO_PIN_9_D = (Cpu.Pin)0x9D;
        internal const Cpu.Pin GPIO_PIN_9_E = (Cpu.Pin)0x9E;
        internal const Cpu.Pin GPIO_PIN_9_F = (Cpu.Pin)0x9F;

        internal const Cpu.Pin GPIO_PIN_A_0 = (Cpu.Pin)0xA0;
        internal const Cpu.Pin GPIO_PIN_A_1 = (Cpu.Pin)0xA1;
        internal const Cpu.Pin GPIO_PIN_A_2 = (Cpu.Pin)0xA2;
        internal const Cpu.Pin GPIO_PIN_A_3 = (Cpu.Pin)0xA3;
        internal const Cpu.Pin GPIO_PIN_A_4 = (Cpu.Pin)0xA4;
        internal const Cpu.Pin GPIO_PIN_A_5 = (Cpu.Pin)0xA5;
        internal const Cpu.Pin GPIO_PIN_A_6 = (Cpu.Pin)0xA6;
        internal const Cpu.Pin GPIO_PIN_A_7 = (Cpu.Pin)0xA7;
        internal const Cpu.Pin GPIO_PIN_A_8 = (Cpu.Pin)0xA8;
        internal const Cpu.Pin GPIO_PIN_A_9 = (Cpu.Pin)0xA9;
        internal const Cpu.Pin GPIO_PIN_A_A = (Cpu.Pin)0xAA;
        internal const Cpu.Pin GPIO_PIN_A_B = (Cpu.Pin)0xAB;
        internal const Cpu.Pin GPIO_PIN_A_C = (Cpu.Pin)0xAC;
        internal const Cpu.Pin GPIO_PIN_A_D = (Cpu.Pin)0xAD;
        internal const Cpu.Pin GPIO_PIN_A_E = (Cpu.Pin)0xAE;
        internal const Cpu.Pin GPIO_PIN_A_F = (Cpu.Pin)0xAF;

        internal const Cpu.Pin GPIO_PIN_B_0 = (Cpu.Pin)0xB0;
        internal const Cpu.Pin GPIO_PIN_B_1 = (Cpu.Pin)0xB1;
        internal const Cpu.Pin GPIO_PIN_B_2 = (Cpu.Pin)0xB2;
        internal const Cpu.Pin GPIO_PIN_B_3 = (Cpu.Pin)0xB3;
        internal const Cpu.Pin GPIO_PIN_B_4 = (Cpu.Pin)0xB4;
        internal const Cpu.Pin GPIO_PIN_B_5 = (Cpu.Pin)0xB5;
        internal const Cpu.Pin GPIO_PIN_B_6 = (Cpu.Pin)0xB6;
        internal const Cpu.Pin GPIO_PIN_B_7 = (Cpu.Pin)0xB7;
        internal const Cpu.Pin GPIO_PIN_B_8 = (Cpu.Pin)0xB8;
        internal const Cpu.Pin GPIO_PIN_B_9 = (Cpu.Pin)0xB9;
        internal const Cpu.Pin GPIO_PIN_B_A = (Cpu.Pin)0xBA;
        internal const Cpu.Pin GPIO_PIN_B_B = (Cpu.Pin)0xBB;
        internal const Cpu.Pin GPIO_PIN_B_C = (Cpu.Pin)0xBC;
        internal const Cpu.Pin GPIO_PIN_B_D = (Cpu.Pin)0xBD;
        internal const Cpu.Pin GPIO_PIN_B_E = (Cpu.Pin)0xBE;
        internal const Cpu.Pin GPIO_PIN_B_F = (Cpu.Pin)0xBF;

        internal const Cpu.Pin GPIO_PIN_C_0 = (Cpu.Pin)0xC0;
        internal const Cpu.Pin GPIO_PIN_C_1 = (Cpu.Pin)0xC1;
        internal const Cpu.Pin GPIO_PIN_C_2 = (Cpu.Pin)0xC2;
        internal const Cpu.Pin GPIO_PIN_C_3 = (Cpu.Pin)0xC3;
        internal const Cpu.Pin GPIO_PIN_C_4 = (Cpu.Pin)0xC4;
        internal const Cpu.Pin GPIO_PIN_C_5 = (Cpu.Pin)0xC5;
        internal const Cpu.Pin GPIO_PIN_C_6 = (Cpu.Pin)0xC6;
        internal const Cpu.Pin GPIO_PIN_C_7 = (Cpu.Pin)0xC7;
        internal const Cpu.Pin GPIO_PIN_C_8 = (Cpu.Pin)0xC8;
        internal const Cpu.Pin GPIO_PIN_C_9 = (Cpu.Pin)0xC9;
        internal const Cpu.Pin GPIO_PIN_C_A = (Cpu.Pin)0xCA;
        internal const Cpu.Pin GPIO_PIN_C_B = (Cpu.Pin)0xCB;
        internal const Cpu.Pin GPIO_PIN_C_C = (Cpu.Pin)0xCC;
        internal const Cpu.Pin GPIO_PIN_C_D = (Cpu.Pin)0xCD;
        internal const Cpu.Pin GPIO_PIN_C_E = (Cpu.Pin)0xCE;
        internal const Cpu.Pin GPIO_PIN_C_F = (Cpu.Pin)0xCF;

        internal const Cpu.Pin GPIO_PIN_D_0 = (Cpu.Pin)0xD0;
        internal const Cpu.Pin GPIO_PIN_D_1 = (Cpu.Pin)0xD1;
        internal const Cpu.Pin GPIO_PIN_D_2 = (Cpu.Pin)0xD2;
        internal const Cpu.Pin GPIO_PIN_D_3 = (Cpu.Pin)0xD3;
        internal const Cpu.Pin GPIO_PIN_D_4 = (Cpu.Pin)0xD4;
        internal const Cpu.Pin GPIO_PIN_D_5 = (Cpu.Pin)0xD5;
        internal const Cpu.Pin GPIO_PIN_D_6 = (Cpu.Pin)0xD6;
        internal const Cpu.Pin GPIO_PIN_D_7 = (Cpu.Pin)0xD7;
        internal const Cpu.Pin GPIO_PIN_D_8 = (Cpu.Pin)0xD8;
        internal const Cpu.Pin GPIO_PIN_D_9 = (Cpu.Pin)0xD9;
        internal const Cpu.Pin GPIO_PIN_D_A = (Cpu.Pin)0xDA;
        internal const Cpu.Pin GPIO_PIN_D_B = (Cpu.Pin)0xDB;
        internal const Cpu.Pin GPIO_PIN_D_C = (Cpu.Pin)0xDC;
        internal const Cpu.Pin GPIO_PIN_D_D = (Cpu.Pin)0xDD;
        internal const Cpu.Pin GPIO_PIN_D_E = (Cpu.Pin)0xDE;
        internal const Cpu.Pin GPIO_PIN_D_F = (Cpu.Pin)0xDF;

        internal const Cpu.Pin GPIO_PIN_E_0 = (Cpu.Pin)0xE0;
        internal const Cpu.Pin GPIO_PIN_E_1 = (Cpu.Pin)0xE1;
        internal const Cpu.Pin GPIO_PIN_E_2 = (Cpu.Pin)0xE2;
        internal const Cpu.Pin GPIO_PIN_E_3 = (Cpu.Pin)0xE3;
        internal const Cpu.Pin GPIO_PIN_E_4 = (Cpu.Pin)0xE4;
        internal const Cpu.Pin GPIO_PIN_E_5 = (Cpu.Pin)0xE5;
        internal const Cpu.Pin GPIO_PIN_E_6 = (Cpu.Pin)0xE6;
        internal const Cpu.Pin GPIO_PIN_E_7 = (Cpu.Pin)0xE7;
        internal const Cpu.Pin GPIO_PIN_E_8 = (Cpu.Pin)0xE8;
        internal const Cpu.Pin GPIO_PIN_E_9 = (Cpu.Pin)0xE9;
        internal const Cpu.Pin GPIO_PIN_E_A = (Cpu.Pin)0xEA;
        internal const Cpu.Pin GPIO_PIN_E_B = (Cpu.Pin)0xEB;
        internal const Cpu.Pin GPIO_PIN_E_C = (Cpu.Pin)0xEC;
        internal const Cpu.Pin GPIO_PIN_E_D = (Cpu.Pin)0xED;
        internal const Cpu.Pin GPIO_PIN_E_E = (Cpu.Pin)0xEE;
        internal const Cpu.Pin GPIO_PIN_E_F = (Cpu.Pin)0xEF;

        internal const Cpu.Pin GPIO_PIN_F_0 = (Cpu.Pin)0xF0;
        internal const Cpu.Pin GPIO_PIN_F_1 = (Cpu.Pin)0xF1;
        internal const Cpu.Pin GPIO_PIN_F_2 = (Cpu.Pin)0xF2;
        internal const Cpu.Pin GPIO_PIN_F_3 = (Cpu.Pin)0xF3;
        internal const Cpu.Pin GPIO_PIN_F_4 = (Cpu.Pin)0xF4;
        internal const Cpu.Pin GPIO_PIN_F_5 = (Cpu.Pin)0xF5;
        internal const Cpu.Pin GPIO_PIN_F_6 = (Cpu.Pin)0xF6;
        internal const Cpu.Pin GPIO_PIN_F_7 = (Cpu.Pin)0xF7;
        internal const Cpu.Pin GPIO_PIN_F_8 = (Cpu.Pin)0xF8;
        internal const Cpu.Pin GPIO_PIN_F_9 = (Cpu.Pin)0xF9;
        internal const Cpu.Pin GPIO_PIN_F_A = (Cpu.Pin)0xFA;
        internal const Cpu.Pin GPIO_PIN_F_B = (Cpu.Pin)0xFB;
        internal const Cpu.Pin GPIO_PIN_F_C = (Cpu.Pin)0xFC;
        internal const Cpu.Pin GPIO_PIN_F_D = (Cpu.Pin)0xFD;
        internal const Cpu.Pin GPIO_PIN_F_E = (Cpu.Pin)0xFE;
        internal const Cpu.Pin GPIO_PIN_F_F = (Cpu.Pin)0xFF;

        public const Cpu.Pin GPIO_NONE = Cpu.Pin.GPIO_NONE;
        public const Cpu.Pin ONBOARD_LED = GPIO_PIN_F_3;

        // CN5, CN8
        public const Cpu.Pin GPIO_PIN_P00 = GPIO_PIN_0_0;   // TRSTX
        public const Cpu.Pin GPIO_PIN_P01 = GPIO_PIN_0_1;   // TCK
        public const Cpu.Pin GPIO_PIN_P02 = GPIO_PIN_0_2;   // TDI
        public const Cpu.Pin GPIO_PIN_P03 = GPIO_PIN_0_3;   // TMS
        public const Cpu.Pin GPIO_PIN_P04 = GPIO_PIN_0_4;   // TDO
        public const Cpu.Pin GPIO_PIN_P07 = GPIO_PIN_0_7;   // nRESET_OUT

        public const Cpu.Pin GPIO_PIN_P12 = GPIO_PIN_1_2;   //
        public const Cpu.Pin GPIO_PIN_P13 = GPIO_PIN_1_3;   //
        public const Cpu.Pin GPIO_PIN_PC9 = GPIO_PIN_C_9;   //
        public const Cpu.Pin GPIO_PIN_PCA = GPIO_PIN_C_A;   //

        // CN1
        public const Cpu.Pin GPIO_PIN_P14 = GPIO_PIN_1_4;   // MAD00
        public const Cpu.Pin GPIO_PIN_P15 = GPIO_PIN_1_5;   // MAD01
        public const Cpu.Pin GPIO_PIN_P16 = GPIO_PIN_1_6;   // MAD02 
        public const Cpu.Pin GPIO_PIN_P17 = GPIO_PIN_1_7;   // MAD03
        public const Cpu.Pin GPIO_PIN_P18 = GPIO_PIN_1_8;   // MAD04
        public const Cpu.Pin GPIO_PIN_P19 = GPIO_PIN_1_9;   // MAD05
        public const Cpu.Pin GPIO_PIN_P1A = GPIO_PIN_1_A;   // MAD06
        public const Cpu.Pin GPIO_PIN_P1B = GPIO_PIN_1_B;   // MAD07
        public const Cpu.Pin GPIO_PIN_P1C = GPIO_PIN_1_C;   // MAD08
        public const Cpu.Pin GPIO_PIN_P1D = GPIO_PIN_1_D;   // MAD09
        public const Cpu.Pin GPIO_PIN_P1E = GPIO_PIN_1_E;   // MAD10
        public const Cpu.Pin GPIO_PIN_P1F = GPIO_PIN_1_F;   // MAD11
        public const Cpu.Pin GPIO_PIN_P29 = GPIO_PIN_1_F;   // MAD12
        public const Cpu.Pin GPIO_PIN_P28 = GPIO_PIN_1_F;   // MAD13
        public const Cpu.Pin GPIO_PIN_P27 = GPIO_PIN_1_F;   // MAD14
        public const Cpu.Pin GPIO_PIN_P26 = GPIO_PIN_1_F;   // MAD15
        public const Cpu.Pin GPIO_PIN_P25 = GPIO_PIN_1_F;   // MAD16
        public const Cpu.Pin GPIO_PIN_P24 = GPIO_PIN_1_F;   // MAD17
        public const Cpu.Pin GPIO_PIN_P20 = GPIO_PIN_2_0;   // MAD18
        public const Cpu.Pin GPIO_PIN_P90 = GPIO_PIN_9_0;   // MAD19

        public const Cpu.Pin GPIO_PIN_P4A = GPIO_PIN_4_A;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P4B = GPIO_PIN_4_B;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P4C = GPIO_PIN_4_C;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P4D = GPIO_PIN_4_D;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P4E = GPIO_PIN_4_E;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P70 = GPIO_PIN_7_0;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P71 = GPIO_PIN_7_1;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P72 = GPIO_PIN_7_2;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P73 = GPIO_PIN_7_3;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P74 = GPIO_PIN_7_4;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P75 = GPIO_PIN_7_5;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P76 = GPIO_PIN_7_6;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P77 = GPIO_PIN_7_7;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P78 = GPIO_PIN_7_8;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P79 = GPIO_PIN_7_9;   // MDATA00
        public const Cpu.Pin GPIO_PIN_P7A = GPIO_PIN_7_A;   // MDATA00

        public const Cpu.Pin GPIO_PIN_P5A = GPIO_PIN_5_A;   // MCSX0
        public const Cpu.Pin GPIO_PIN_P5B = GPIO_PIN_5_B;   // MCSX1

        // CN2
        public const Cpu.Pin GPIO_PIN_PB0 = GPIO_PIN_B_0;   // AN16
        public const Cpu.Pin GPIO_PIN_PB1 = GPIO_PIN_B_1;   // AN17
        public const Cpu.Pin GPIO_PIN_PB2 = GPIO_PIN_B_2;   // AN18
        public const Cpu.Pin GPIO_PIN_PB3 = GPIO_PIN_B_3;   // AN19
        public const Cpu.Pin GPIO_PIN_PB4 = GPIO_PIN_B_4;   // AN20
        public const Cpu.Pin GPIO_PIN_PB5 = GPIO_PIN_B_5;   // AN21
        public const Cpu.Pin GPIO_PIN_PB6 = GPIO_PIN_B_6;   // AN22
        public const Cpu.Pin GPIO_PIN_PB7 = GPIO_PIN_B_7;   // AN23
        public const Cpu.Pin GPIO_PIN_P05 = GPIO_PIN_0_5;   // SIN4_2
        public const Cpu.Pin GPIO_PIN_P06 = GPIO_PIN_0_6;   // SOT4_2
        public const Cpu.Pin GPIO_PIN_P39 = GPIO_PIN_3_9;   // 
        public const Cpu.Pin GPIO_PIN_P3A = GPIO_PIN_3_A;   // 
        public const Cpu.Pin GPIO_PIN_P21 = GPIO_PIN_2_1;   // SIN0_0
        public const Cpu.Pin GPIO_PIN_P22 = GPIO_PIN_2_2;   // SOT0_0
        public const Cpu.Pin GPIO_PIN_P3C = GPIO_PIN_3_C;   // RTO02_0
        public const Cpu.Pin GPIO_PIN_P51 = GPIO_PIN_5_1;   // MWEX
        public const Cpu.Pin GPIO_PIN_P08 = GPIO_PIN_0_8;   // CTS4_2
        public const Cpu.Pin GPIO_PIN_P52 = GPIO_PIN_5_2;   // MDQM0
        public const Cpu.Pin GPIO_PIN_P53 = GPIO_PIN_5_3;   // MDQM1
        public const Cpu.Pin GPIO_PIN_P50 = GPIO_PIN_5_0;   // MOEX
        public const Cpu.Pin GPIO_PIN_P3B = GPIO_PIN_3_B;   // 
        public const Cpu.Pin GPIO_PIN_P3D = GPIO_PIN_3_D;   // 
        public const Cpu.Pin GPIO_PIN_P09 = GPIO_PIN_0_9;   // RTS4_2
        public const Cpu.Pin GPIO_PIN_P38 = GPIO_PIN_3_8;   // MCLKOUT
        public const Cpu.Pin GPIO_PIN_P7D = GPIO_PIN_7_D;   // INT12_0
        public const Cpu.Pin GPIO_PIN_PF0 = GPIO_PIN_F_0;   // INT13_0
        public const Cpu.Pin GPIO_PIN_PF1 = GPIO_PIN_F_1;   // INT14_0 (MAD20)
        public const Cpu.Pin GPIO_PIN_PF2 = GPIO_PIN_F_2;   // INT15_0 (MAD21)
        public const Cpu.Pin GPIO_PIN_P36 = GPIO_PIN_3_6;   // MCSX2   (MAD23)
        public const Cpu.Pin GPIO_PIN_P37 = GPIO_PIN_3_7;   // MCSX3   (MAD22)
        public const Cpu.Pin GPIO_PIN_P3F = GPIO_PIN_3_F;   // RTO05_1
        public const Cpu.Pin GPIO_PIN_P54 = GPIO_PIN_5_4;   // INT12_0
        public const Cpu.Pin GPIO_PIN_P56 = GPIO_PIN_5_6;   // INT12_0
        public const Cpu.Pin GPIO_PIN_P59 = GPIO_PIN_5_9;   // INT12_0
        public const Cpu.Pin GPIO_PIN_P95 = GPIO_PIN_9_5;   // INT12_0 (MAD24)

        // CN3
        public const Cpu.Pin GPIO_PIN_PC4 = GPIO_PIN_C_4;   // 
        public const Cpu.Pin GPIO_PIN_PC3 = GPIO_PIN_C_3;   // 
        public const Cpu.Pin GPIO_PIN_PC5 = GPIO_PIN_C_5;   // 
        public const Cpu.Pin GPIO_PIN_PD3 = GPIO_PIN_D_3;   // 
        public const Cpu.Pin GPIO_PIN_PD2 = GPIO_PIN_D_3;   // 
        public const Cpu.Pin GPIO_PIN_PD1 = GPIO_PIN_D_1;   // 
        public const Cpu.Pin GPIO_PIN_PC7 = GPIO_PIN_C_7;   // 
        public const Cpu.Pin GPIO_PIN_PC6 = GPIO_PIN_C_6;   // 
        public const Cpu.Pin GPIO_PIN_PC8 = GPIO_PIN_C_8;   // 
        public const Cpu.Pin GPIO_PIN_PC2 = GPIO_PIN_C_2;   // 
        public const Cpu.Pin GPIO_PIN_PC1 = GPIO_PIN_C_1;   // 
        public const Cpu.Pin GPIO_PIN_PC0 = GPIO_PIN_C_0;   // 
        public const Cpu.Pin GPIO_PIN_PCE = GPIO_PIN_C_E;   // 
        public const Cpu.Pin GPIO_PIN_PD0 = GPIO_PIN_D_0;   // 
        public const Cpu.Pin GPIO_PIN_PCF = GPIO_PIN_C_F;   // 
        public const Cpu.Pin GPIO_PIN_PCD = GPIO_PIN_C_D;   // 
        public const Cpu.Pin GPIO_PIN_PCC = GPIO_PIN_C_C;   // 
        public const Cpu.Pin GPIO_PIN_PA0 = GPIO_PIN_A_0;   // 
        public const Cpu.Pin GPIO_PIN_PA1 = GPIO_PIN_A_1;   // 
        public const Cpu.Pin GPIO_PIN_PA2 = GPIO_PIN_A_2;   // 
        public const Cpu.Pin GPIO_PIN_PA3 = GPIO_PIN_A_3;   // 
        public const Cpu.Pin GPIO_PIN_PA4 = GPIO_PIN_A_4;   // 
        public const Cpu.Pin GPIO_PIN_PA5 = GPIO_PIN_A_5;   // 
        public const Cpu.Pin GPIO_PIN_P48 = GPIO_PIN_4_8;   // SIN3_2
        public const Cpu.Pin GPIO_PIN_P49 = GPIO_PIN_4_9;   // SOT3_2
        public const Cpu.Pin GPIO_PIN_P10 = GPIO_PIN_1_0;   // AN00
        public const Cpu.Pin GPIO_PIN_P11 = GPIO_PIN_1_1;   // AN01
        public const Cpu.Pin GPIO_PIN_P30 = GPIO_PIN_3_0;   // MMC_nCS
        public const Cpu.Pin GPIO_PIN_P31 = GPIO_PIN_3_1;   // SPI_CLK
        public const Cpu.Pin GPIO_PIN_P32 = GPIO_PIN_3_2;   // SPI_MOSI
        public const Cpu.Pin GPIO_PIN_P33 = GPIO_PIN_3_3;   // SPI_MISO
        public const Cpu.Pin GPIO_PIN_P34 = GPIO_PIN_3_4;   // 
        public const Cpu.Pin GPIO_PIN_P35 = GPIO_PIN_3_5;   // 

        // CN4
        public const Cpu.Pin GPIO_PIN_P40 = GPIO_PIN_4_0;   // 
        public const Cpu.Pin GPIO_PIN_P41 = GPIO_PIN_4_1;   // 
        public const Cpu.Pin GPIO_PIN_P42 = GPIO_PIN_4_2;   // 
        public const Cpu.Pin GPIO_PIN_P43 = GPIO_PIN_4_3;   // 
        public const Cpu.Pin GPIO_PIN_P44 = GPIO_PIN_4_4;   // 
        public const Cpu.Pin GPIO_PIN_P45 = GPIO_PIN_4_5;   // 
        public const Cpu.Pin GPIO_PIN_PF4 = GPIO_PIN_F_4;   // 
        public const Cpu.Pin GPIO_PIN_PF5 = GPIO_PIN_F_5;   // 
        public const Cpu.Pin GPIO_PIN_P7B = GPIO_PIN_7_B;   // 
        public const Cpu.Pin GPIO_PIN_P7C = GPIO_PIN_7_C;   // 
        public const Cpu.Pin GPIO_PIN_P7E = GPIO_PIN_7_D;   // 
        public const Cpu.Pin GPIO_PIN_P7F = GPIO_PIN_7_E;   // 
    }

    public static class AnalogChannels
    {
        public const Cpu.AnalogChannel ANALOG_PIN_AN00 = (Cpu.AnalogChannel)0;  // P10
        public const Cpu.AnalogChannel ANALOG_PIN_AN01 = (Cpu.AnalogChannel)1;  // P11

        public const Cpu.AnalogChannel ANALOG_PIN_AN16 = (Cpu.AnalogChannel)16; // PB0
        public const Cpu.AnalogChannel ANALOG_PIN_AN17 = (Cpu.AnalogChannel)17; // PB1
        public const Cpu.AnalogChannel ANALOG_PIN_AN18 = (Cpu.AnalogChannel)18; // PB2
        public const Cpu.AnalogChannel ANALOG_PIN_AN19 = (Cpu.AnalogChannel)19; // PB3
        public const Cpu.AnalogChannel ANALOG_PIN_AN20 = (Cpu.AnalogChannel)20; // PB4
        public const Cpu.AnalogChannel ANALOG_PIN_AN21 = (Cpu.AnalogChannel)21; // PB5
        public const Cpu.AnalogChannel ANALOG_PIN_AN22 = (Cpu.AnalogChannel)22; // PB6
        public const Cpu.AnalogChannel ANALOG_PIN_AN23 = (Cpu.AnalogChannel)23; // PB7
    }

    public static class SerialPorts
    {
        public const string COM1 = "COM1";  // CH0
        public const string COM2 = "COM2";  // CH4
        public const string COM3 = "COM3";  // CH3
    }

    public static class BaudRates
    {
        public const BaudRate Baud2400 = BaudRate.Baudrate2400;
        public const BaudRate Baud9600 = BaudRate.Baudrate9600;
        public const BaudRate Baud19200 = BaudRate.Baudrate19200;
        public const BaudRate Baud38400 = BaudRate.Baudrate38400;
        public const BaudRate Baud57600 = BaudRate.Baudrate57600;
        public const BaudRate Baud115200 = BaudRate.Baudrate115200;
        public const BaudRate Baud230400 = BaudRate.Baudrate230400;
    }

    public static class ResistorModes
    {
        public const Port.ResistorMode PullUp = Port.ResistorMode.PullUp;
        public const Port.ResistorMode Disabled = Port.ResistorMode.Disabled;
    }

    public static class InterruptModes
    {
        public const Port.InterruptMode InterruptEdgeLow = Port.InterruptMode.InterruptEdgeLow;
        public const Port.InterruptMode InterruptEdgeHigh = Port.InterruptMode.InterruptEdgeHigh;
        public const Port.InterruptMode InterruptEdgeBoth = Port.InterruptMode.InterruptEdgeBoth;
        public const Port.InterruptMode InterruptEdgeLevelHigh = Port.InterruptMode.InterruptEdgeLevelHigh;
        public const Port.InterruptMode InterruptEdgeLevelLow = Port.InterruptMode.InterruptEdgeLevelLow;
        public const Port.InterruptMode InterruptNone = Port.InterruptMode.InterruptNone;
    }

    public static class SPI_Devices
    {
        public const Microsoft.SPOT.Hardware.SPI.SPI_module SPI1 = Microsoft.SPOT.Hardware.SPI.SPI_module.SPI1;
        public const Microsoft.SPOT.Hardware.SPI.SPI_module SPI2 = Microsoft.SPOT.Hardware.SPI.SPI_module.SPI2;
    }
}
