using System;
using Microsoft.SPOT;
using Microsoft.SPOT.Hardware;
using System.Runtime.CompilerServices;

namespace CQ.NETMF.CQ_FRK_FM3.Hardware
{
    public class FM3_I2CDevice : I2CDevice
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void I2CDevice_SetChannel(UInt32 ch);

        I2CDevice fm3_i2c = null;

        public const UInt32 I2C1 = 5;
        public const UInt32 I2C2 = 1;
        public const UInt32 I2C3 = 7;
        private UInt32 fm3_i2c_ch = I2C1;

        public FM3_I2CDevice(I2CDevice.Configuration conf) : base(conf)
        {
            SetChannel(I2C1);
            fm3_i2c = new I2CDevice(conf);
        }

        public FM3_I2CDevice(UInt32 ch, I2CDevice.Configuration conf) : base(conf)
        {
            SetChannel(ch);
            fm3_i2c = new I2CDevice(conf);
        }

        ~FM3_I2CDevice()
        {
            Dispose();
        }

        public new void Dispose()
        {
            fm3_i2c.Dispose();
        }

        public void SetChannel(UInt32 ch)
        {
            fm3_i2c_ch = ch;
            I2CDevice_SetChannel(fm3_i2c_ch);
        }

        public new I2CReadTransaction CreateReadTransaction(byte[] buffer)
        {
            SetChannel(fm3_i2c_ch);
            return I2CDevice.CreateReadTransaction(buffer);
        }

        public new I2CWriteTransaction CreateWriteTransaction(byte[] buffer)
        {
            SetChannel(fm3_i2c_ch);
            return I2CDevice.CreateWriteTransaction(buffer);
        }

        public new int Execute(I2CDevice.I2CTransaction[] xActions, int timeout)
        {
            SetChannel(fm3_i2c_ch);
            return fm3_i2c.Execute(xActions, timeout);
        }
    }
}
