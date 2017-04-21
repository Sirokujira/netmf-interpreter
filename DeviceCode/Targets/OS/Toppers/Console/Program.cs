//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2013 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: Program.cs 149 2013-05-13 11:14:39Z nagasima $
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;

namespace Console
{
	class Program
	{
		IUnitSim m_Sample1;
		Thread m_Thread;
		AutoResetEvent m_Event;
		bool m_Terminated;
		FileStream m_TraceLog;

		static void Main(string[] args)
		{
			Program Program = new Program();

			Program.Init();

			Program.Start();

			for (; ; )
			{
				if (System.Console.KeyAvailable)
				{
					ConsoleKeyInfo info = System.Console.ReadKey();

					if (Program.m_Terminated)
						break;

					Program.m_Sample1.Input(0, new byte[] { (byte)info.KeyChar });
				}

				Thread.Sleep(0);
			}

			Program.Terminate();
		}

		public Program()
		{
			m_Thread = new Thread(new ThreadStart(TimerProc));
			m_Thread.Name = "TimerProc";
			m_Event = new AutoResetEvent(false);
		}

		public void Init()
		{
			try
			{
				m_TraceLog = new FileStream("trace" + DateTime.Now.ToString("yyyyMMddhhmmss") + ".log", FileMode.CreateNew);
			}
			catch (Exception)
			{
				m_TraceLog = null;
			}

			m_Sample1 = new Sample1();
			m_Sample1.UnitExit += new UnitEventHandler(UnitSim_UnitExit);
			m_Sample1.UnitOutput += new UnitOutputEventHandler(UnitSim_Log);
			m_Sample1.UnitSetEvent += new UnitEventHandler(Unit_UnitSetEvent);
			m_Sample1.UnitGetSystemTime += new UnitGetSystemTimeEventHandler(Sample1_UnitGetSystemTime);

			m_Thread.Start();
		}

		public void Start()
		{
			m_Sample1.Start();
		}

		public void Terminate()
		{
			if (m_TraceLog != null)
			{
				m_TraceLog.Close();
				m_TraceLog.Dispose();
				m_TraceLog = null;
			}
			//m_Sample1.Exit();
		}

		public void UnitSim_UnitExit(IUnitSim sender)
		{
			if (m_Sample1 == sender)
			{
				m_Sample1 = null;
				m_Terminated = true;

				// DLLアンロードは少し遅らせて実行
				UnitEventHandler handler = new UnitEventHandler(delegate(IUnitSim unit)
				{
					IDisposable dsp = unit as IDisposable;
					if (dsp != null)
						dsp.Dispose();
				});
				handler.BeginInvoke(sender, null, this);
			}
		}

		public void UnitSim_Log(IUnitSim sender, int Kind, byte[] Data)
		{
			switch (Kind)
			{
				case 1:
					m_TraceLog.Write(Data, 0, Data.Length);
					break;
			}
		}

		void TimerProc()
		{
			long prev, now, frequency, sim;

			frequency = 10000000/*[100nsec]=1[sec]*/;
			now = DateTime.Now.Ticks;
			sim = now;

			while (!m_Terminated)
			{
				//タイムアウト処理があればを実行する
				m_Sample1.CallTimeOut(frequency);

				// タイマーの最小値を取得
				long timer = m_Sample1.GetTimer();
				bool signal = false;

				if (timer >= 0)
				{
					bool taskSwitch = timer == 0;
					// タイムアウト後の時刻から、タイマー時間を計算
					long target = sim + timer;
					long temp = DateTime.Now.Ticks;
					long diff = target - temp;
					if (diff < 0)
						diff = 0;

					if ((diff > 0) || taskSwitch)
						signal = m_Event.WaitOne(new TimeSpan(diff));
				}
				else
					signal = m_Event.WaitOne();

				prev = now;
				now = DateTime.Now.Ticks;

				// 経過時間の計算、シグナルで起こされた場合、測定値を使用
				long interval = signal ? (now - prev) : timer;

				sim += interval;

				// 時間が進んだことをメッセージ処理に知らせる
				m_Sample1.Progress(interval);

				// イベントを処理する（ここでm_Terminatedがtrueになることがある）
				m_Sample1.ProcessEvent();
			}
		}

		void Unit_UnitSetEvent(IUnitSim sender)
		{
			m_Event.Set();
		}

		static long m_Start = (new DateTime(1970, 1, 1)).Ticks;

		void Sample1_UnitGetSystemTime(IUnitSim sender, ref long now, ref long frequency)
		{
			now = DateTime.Now.Ticks - m_Start;
			frequency = 10000000/*[100nsec]=1[sec]*/;
		}
	}
}
