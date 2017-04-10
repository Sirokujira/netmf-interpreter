using System;
using System.Runtime.CompilerServices;
using Microsoft.SPOT.Hardware;

namespace CQ.NETMF.SD
{
    public static class StorageDevice
    {
        // Fields
        private static string SdCardPath;

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SDSPI_Mount(string path, uint spi, uint chipSelectPort, uint cardDetectPin);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SDSPI_Unmount();

        // Methods
        static StorageDevice()
        {
            SdCardPath = null;
        }

        public static void MountSD(string path, SPI.SPI_module spi, Cpu.Pin chipSelect, Cpu.Pin cardDetect)
        {
            if (SdCardPath != null)
            {
                throw new NotSupportedException();
            }
            SDSPI_Mount(path, (uint)spi, (uint)chipSelect, (uint)cardDetect);
            SdCardPath = path;
        }

        public static void MountSD(string path, SPI.SPI_module spi, Cpu.Pin chipSelect)
        {
            MountSD(path, spi, chipSelect, Cpu.Pin.GPIO_NONE);
        }

        public static void Unmount(string path)
        {
            if (SdCardPath != path)
            {
                throw new ArgumentException();
            }
            SDSPI_Unmount();
            SdCardPath = null;
        }
    }
}
