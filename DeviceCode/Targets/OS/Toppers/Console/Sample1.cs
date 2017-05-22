//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2013 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: Sample1.cs 116 2013-02-11 09:48:20Z nagasima $
using System;
using System.Collections.Generic;
using System.Text;

namespace Console
{
    /// <summary>
    /// STM32 用
    /// </summary>
	public class Sample1 : DllUnitSim
	{
		List<IUnitInterface> m_Interfaces = new List<IUnitInterface>();

		public Sample1()
			: base("Sample1")
		{
		}

		public override void Dispose()
		{
			ClearInterfaces();
			base.Dispose();
		}

		protected override void Push(int kind, byte[] Data)
		{
			string str = Encoding.Default.GetString(Data);
			System.Console.Write(str);
		}

		public override IList<IUnitInterface> Interfaces
		{
			get { return m_Interfaces.AsReadOnly(); }
		}

		private void ClearInterfaces()
		{
			while (m_Interfaces.Count > 0)
			{
				IUnitInterface unitInterface = m_Interfaces[0];
				DoRemoveInterface(unitInterface);
				m_Interfaces.RemoveAt(0);
			}
		}
	}
}
