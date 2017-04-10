using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;

namespace CQ.NETMF.UTIL
{
    public static class EEHeap
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_top();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_size();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_next(UInt32 current);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_prev(UInt32 current);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_last();
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_hb_flags(UInt32 current);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_hb_size(UInt32 current);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern UInt32 EEHeap_get_hb_type(UInt32 current);

        static UInt32 m_top;
        static UInt32 m_size;

        static EEHeap()
        {
            m_top = 0;
            m_size = 0;
        }

        public static UInt32 EEHeapTop()
        {
            m_top = EEHeap_get_top();
            return m_top;
        }

        public static UInt32 EEHeapSize()
        {
            m_size = EEHeap_get_size();
            return m_size;
        }

        public static UInt32 EEHeapNext(UInt32 current)
        {
            return EEHeap_get_next(current);
        }

        public static UInt32 EEHeapPrev(UInt32 current)
        {
            return EEHeap_get_prev(current);
        }

        public static UInt32 EEHeapLast()
        {
            return EEHeap_get_last();
        }

        public static UInt32 EEHeapBlockFlags(UInt32 current)
        {
            return EEHeap_get_hb_flags(current);
        }

        public static UInt32 EEHeapBlockSize(UInt32 current)
        {
            return EEHeap_get_hb_size(current);
        }

        public static UInt32 EEHeapBlockType(UInt32 current)
        {
            return EEHeap_get_hb_type(current);
        }
    }
}
