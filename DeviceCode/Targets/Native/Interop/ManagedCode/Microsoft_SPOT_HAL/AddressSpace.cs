using System;
using Microsoft.SPOT;
using System.Runtime.CompilerServices;

namespace Microsoft.SPOT.Hardware
{
    /// <summary>Base class for access to a memory address space</summary>
    /// <remarks>
    /// An Address space consists of a base address, bit width and length
    /// for some Memory or I/O Mapped region. Derived classes provide
    /// access to the memory with type safe accessors that overload the
    /// index (this[]) operator.
    /// </remarks>
    public class AddressSpace
    {
        /// <summary>Per instance Address Space ID stored by Native code</summary>
        protected UIntPtr ASID;
        /// <summary>Creates a new AddressSpace instance</summary>
        /// <param name="Name">Name of the address space</param>
        /// <param name="Width">Expected bit width of the address space</param>
        /// <remarks>
        /// The HAL defines the address space
        /// </remarks>
        [MethodImpl(MethodImplOptions.InternalCall)]
        protected extern AddressSpace(string Name, int Width);
        /// <summary>Bit width for the address space</summary>
        /// <value>number of bits per word for the address space</value>
        /// <remarks>
        /// The number of bits is determined by the HAL and cannot
        /// be changed from managed code. 
        /// </remarks>
        public extern int BitWdith
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
        /// <summary>Word Length for the address space</summary>
        /// <value>Number of address space words (BitWidth Wide) in the address space</value>
        /// <remarks>
        /// The length is a word length and not a byte length. This is done to support
        /// indexing in derived classes like an array. The byte length can be computed
        /// as follows: int byteLength = ( this.Length * this.BitWidth ) / 8;
        /// </remarks>
        public extern UInt32 Length
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
    }
    /// <summary>8 bit wide address space</summary>
    public class AddressSpaceUInt8 : AddressSpace
    {
        public AddressSpaceUInt8(string Name)
            : base(Name, 8)
        {
        }
        /// <summary>Accesses a byte in the address space</summary>
        /// <param name="Offset">byte offset from the base of the address space (e.g. 0 based index)</param>
        /// <value>New Value for the byte at the specified offset</value>
        /// <returns>Value of the byte at the offset</returns>
        public extern byte this[UInt32 Offset]
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
    /// <summary>16 bit address space</summary>
    public class AddressSpaceUInt16 : AddressSpace
    {
        public AddressSpaceUInt16(string Name)
            : base(Name, 16)
        {
        }
        /// <summary>Accesses a 16 bit value in the address space</summary>
        /// <param name="Offset">16 bit word offset from the base of the address space (e.g. 0 based index)</param>
        /// <value>New Value for word at the specified offset</value>
        /// <returns>Value of the word at the specified offset</returns>
        public extern UInt16 this[UInt32 Offset]
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
    /// <summary>32 bit address space</summary>
    public class AddressSpaceUInt32 : AddressSpace
    {
        public AddressSpaceUInt32(string Name)
            : base(Name, 32)
        {
        }
        /// <summary>Accesses a 32 bit value in the address space</summary>
        /// <param name="Offset">32 bit word offset from the base of the address space (e.g. 0 based index)</param>
        /// <value>New Value for word at the specified offset</value>
        /// <returns>Value of the word at the specified offset</returns>
        public extern UInt32 this[UInt32 Offset]
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
