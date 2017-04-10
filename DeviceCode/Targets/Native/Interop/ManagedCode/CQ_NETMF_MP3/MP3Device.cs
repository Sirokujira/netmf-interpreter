using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;

namespace CQ.NETMF.MP3
{
    public static class MP3Device
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void MP3Device_MP3_Initialize();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void MP3Device_MP3_Play(string s);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void MP3Device_MP3_Stop(string s);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void MP3Device_MP3_Pause(string s);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void MP3Device_MP3_Uninitialize();

        public static void Initialize()
        {
            MP3Device_MP3_Initialize();
        }

        public static void Start(String s)
        {
            MP3Device_MP3_Play(s);
        }

        public static void Stop(String s)
        {
            MP3Device_MP3_Stop(s);
        }

        public static void Pause(String s)
        {
            MP3Device_MP3_Pause(s);
        }

        public static void Uninitialize()
        {
            MP3Device_MP3_Uninitialize();
        }
    }
}
