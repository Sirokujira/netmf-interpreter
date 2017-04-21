//------------------------------------------------------------------------------
//  TOPPERS/ASP Windows Debug Environment
//  Copyright (C) 2010-2013 Cores Co., Ltd. Japan
//------------------------------------------------------------------------------
// $Id: UnitSim.cs 116 2013-02-11 09:48:20Z nagasima $
using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Threading;
using System.Runtime.InteropServices;
using System.CodeDom;
using System.CodeDom.Compiler;
using Microsoft.CSharp;
using System.IO;

namespace Console
{
	public interface IUnitInterface
	{
		string InterfaceName { get; }
		IUnitSim UnitSim { get; }
	}

	public interface IInterfaceHub
	{
		bool Send(IUnitInterface sender, object message);
	}

	public delegate void UnitEventHandler(IUnitSim sender);
	public delegate void UnitInterfaceEventHandler(IUnitSim sender, IUnitInterface item);
	public delegate void UnitOutputEventHandler(IUnitSim sender, int kind, byte[] data);
	public delegate void UnitGetSystemTimeEventHandler(IUnitSim sender, ref long now, ref long frequency);

	public interface IUnitSim
	{
		void Start();
		void Exit();
		void Interrupt(int IntNo);
		int ReadAddr(uint addr, byte[] dst);
		int WriteAddr(uint addr, byte[] src);
		void SetBit(uint addr, int bit, bool value);
		bool GetBit(uint addr, int bit);
		void Input(int kind, byte[] Data);
		long GetTimer();
		void Progress(long timer);
		void CallTimeOut(long frequency);
		bool ProcessEvent();
		string UnitName { get; set; }
		event UnitEventHandler UnitSetEvent;
		event UnitEventHandler UnitStart;
		event UnitEventHandler UnitExit;
		event UnitEventHandler UnitIdle;
		event UnitOutputEventHandler UnitOutput;
		event UnitGetSystemTimeEventHandler UnitGetSystemTime;
		IList<IUnitInterface> Interfaces { get; }
		event UnitInterfaceEventHandler AddInterface;
		event UnitInterfaceEventHandler RemoveInterface;
		event UnitInterfaceEventHandler UpdateInterface;
	}

	public abstract class DllUnitSim : IDisposable, IUnitSim
	{
		[DllImport("kernel32", CharSet = CharSet.Unicode)]
		private extern static IntPtr LoadLibrary(string lpFileName);

		[DllImport("kernel32")]
		private extern static bool FreeLibrary(IntPtr hModule);

		[DllImport("kernel32", CharSet = CharSet.Ansi)]
		private extern static IntPtr GetProcAddress(IntPtr hModule, string lpProcName);

		[DllImport("kernel32", CharSet = CharSet.Unicode)]
		private extern static IntPtr FindResource(IntPtr hModule, int lpName, string lpType);

		[DllImport("kernel32", CharSet = CharSet.Unicode)]
		private extern static int SizeofResource(IntPtr hModule, IntPtr hResInfo);

		[DllImport("kernel32", CharSet = CharSet.Unicode)]
		private extern static IntPtr LoadResource(IntPtr hModule, IntPtr hResInfo);

		[DllImport("kernel32", CharSet = CharSet.Unicode)]
		private extern static IntPtr LockResource(IntPtr hResData);

		[UnmanagedFunctionPointer(CallingConvention.StdCall)]
		private delegate void TKernelEvent(IntPtr Obj);
		[UnmanagedFunctionPointer(CallingConvention.StdCall)]
		private delegate void TOutputEvent(IntPtr Obj, int Kind, IntPtr Data, int Size);
		[UnmanagedFunctionPointer(CallingConvention.StdCall)]
		private delegate void TGetSystemTimeEvent(IntPtr Obj, ref long Now, ref long Frequency);

		private string m_DllName;
		private IntPtr m_Object;
		private IntPtr m_Module;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TStart();
		private TStart m_Start;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TExit();
		private TExit m_Exit;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TInterrupt(int IntNo);
		private TInterrupt m_Interrupt;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TGetUnitName(IntPtr value, int size);
		private TGetUnitName m_GetUnitName;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TSetUnitName(IntPtr value);
		private TSetUnitName m_SetUnitName;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TAssignOnSetEvent(TKernelEvent OnSetEvent, IntPtr ObjOfOnSetEvent);
		private TAssignOnSetEvent m_AssignOnSetEvent;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TAssignOnStart(TKernelEvent OnStart, IntPtr ObjOfOnStart);
		private TAssignOnStart m_AssignOnStart;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TAssignOnTerminate(TKernelEvent OnTerminate, IntPtr ObjOfOnTerminate);
		private TAssignOnTerminate m_AssignOnTerminate;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TAssignOnIdle(TKernelEvent OnIdle, IntPtr ObjOfOnIdle);
		private TAssignOnIdle m_AssignOnIdle;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TAssignOnOutput(TOutputEvent OnLog, IntPtr ObjOfOnLog);
		private TAssignOnOutput m_AssignOnOutput;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TAssignOnGetSystemTime(TGetSystemTimeEvent OnGetSystemTime, IntPtr ObjOfOnGetSystemTime);
		private TAssignOnGetSystemTime m_AssignOnGetSystemTime;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate int TReadAddr(uint Addr, IntPtr buffer, int count);
		private TReadAddr m_ReadAddr;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate int TWriteAddr(uint Addr, IntPtr buffer, int count);
		private TWriteAddr m_WriteAddr;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate bool TGetBit(uint Addr, int bit);
		private TGetBit m_GetBit;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TSetBit(uint Addr, int bit, bool value);
		private TSetBit m_SetBit;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate bool TProcessEvent();
		private TProcessEvent m_ProcessEvent;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TInput(int Kind, IntPtr Data, int Size);
		private TInput m_Input;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate long TGetTimer();
		private TGetTimer m_GetTimer;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TProgress(long Timer);
		private TProgress m_Progress;
		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate void TCallTimeOut(long Frequency);
		private TCallTimeOut m_CallTimeOut;

		private TKernelEvent m_UnitOnSetEvent;
		private TKernelEvent m_UnitOnStart;
		private TKernelEvent m_UnitOnTerminate;
		private TKernelEvent m_UnitOnIdle;
		private TOutputEvent m_UnitOnOutput;
		private TGetSystemTimeEvent m_UnitOnGetSystemTime;

		private string m_TraceLogResource;

		public DllUnitSim(string dllName)
		{
			m_DllName = dllName;
			m_Module = LoadLibrary(dllName);

			if (m_Module == IntPtr.Zero)
				throw new DllNotFoundException(dllName + ".dll");

			m_Start = (TStart)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "Start"), typeof(TStart));
			m_Exit = (TExit)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "Exit"), typeof(TExit));
			m_Interrupt = (TInterrupt)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "Interrupt"), typeof(TInterrupt));
			m_GetUnitName = (TGetUnitName)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "GetUnitName"), typeof(TGetUnitName));
			m_SetUnitName = (TSetUnitName)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "SetUnitName"), typeof(TSetUnitName));
			m_AssignOnSetEvent = (TAssignOnSetEvent)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "AssignOnSetEvent"), typeof(TAssignOnSetEvent));
			m_AssignOnStart = (TAssignOnStart)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "AssignOnStart"), typeof(TAssignOnStart));
			m_AssignOnTerminate = (TAssignOnTerminate)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "AssignOnTerminate"), typeof(TAssignOnTerminate));
			m_AssignOnIdle = (TAssignOnIdle)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "AssignOnIdle"), typeof(TAssignOnIdle));
			m_AssignOnOutput = (TAssignOnOutput)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "AssignOnOutput"), typeof(TAssignOnOutput));
			m_AssignOnGetSystemTime = (TAssignOnGetSystemTime)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "AssignOnGetSystemTime"), typeof(TAssignOnGetSystemTime));
			m_ReadAddr = (TReadAddr)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "ReadAddr"), typeof(TReadAddr));
			m_WriteAddr = (TWriteAddr)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "WriteAddr"), typeof(TWriteAddr));
			m_GetBit = (TGetBit)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "GetBit"), typeof(TGetBit));
			m_SetBit = (TSetBit)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "SetBit"), typeof(TSetBit));
			m_ProcessEvent = (TProcessEvent)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "ProcessEvent"), typeof(TProcessEvent));
			m_Input = (TInput)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "Input"), typeof(TInput));
			m_GetTimer = (TGetTimer)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "GetTimer"), typeof(TGetTimer));
			m_Progress = (TProgress)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "Progress"), typeof(TProgress));
			m_CallTimeOut = (TCallTimeOut)Marshal.GetDelegateForFunctionPointer(GetProcAddress(m_Module, "CallTimeOut"), typeof(TCallTimeOut));

			m_Object = Marshal.GetIUnknownForObject(this);

			m_UnitOnSetEvent = new TKernelEvent(UnitOnSetEvent);
			m_AssignOnSetEvent(m_UnitOnSetEvent, m_Object);
			m_UnitOnStart = new TKernelEvent(UnitOnStart);
			m_AssignOnStart(m_UnitOnStart, m_Object);
			m_UnitOnTerminate = new TKernelEvent(UnitOnTerminate);
			m_AssignOnTerminate(m_UnitOnTerminate, m_Object);
			m_UnitOnIdle = new TKernelEvent(UnitOnIdle);
			m_AssignOnIdle(m_UnitOnIdle, m_Object);
			m_UnitOnOutput = new TOutputEvent(UnitOnOutput);
			m_AssignOnOutput(m_UnitOnOutput, m_Object);
			m_UnitOnGetSystemTime = new TGetSystemTimeEvent(UnitOnGetSystemTime);
			m_AssignOnGetSystemTime(m_UnitOnGetSystemTime, m_Object);

			IntPtr hResInfo = FindResource(m_Module, 1, "TRACELOG_RESOURCE");
			if (hResInfo == IntPtr.Zero)
				return;

			int size = SizeofResource(m_Module, hResInfo);
			IntPtr hGlobal = LoadResource(m_Module, hResInfo);

			byte[] buf = new byte[size];
			Marshal.Copy(LockResource(hGlobal), buf, 0, buf.Length);

			m_TraceLogResource = Encoding.Default.GetString(buf);
		}

		public virtual void Dispose()
		{
			m_Start = null;
			m_Exit = null;
			m_Interrupt = null;
			m_GetUnitName = null;
			m_SetUnitName = null;
			m_AssignOnStart = null;
			m_AssignOnTerminate = null;
			m_AssignOnIdle = null;
			m_AssignOnOutput = null;
			m_UnitOnGetSystemTime = null;
			m_ReadAddr = null;
			m_WriteAddr = null;
			m_GetBit = null;
			m_SetBit = null;
			m_ProcessEvent = null;
			m_Input = null;
			m_GetTimer = null;
			m_Progress = null;
			m_CallTimeOut = null;

			Marshal.Release(m_Object);
			m_Object = IntPtr.Zero;
			if (m_Module != null)
			{
				if (FreeLibrary(m_Module))
				{
					m_Module = IntPtr.Zero;
				}
			}
		}

		public event UnitEventHandler UnitSetEvent;
		public event UnitEventHandler UnitStart;
		public event UnitEventHandler UnitExit;
		public event UnitEventHandler UnitIdle;
		public event UnitOutputEventHandler UnitOutput;
		public event UnitGetSystemTimeEventHandler UnitGetSystemTime;

		private static void UnitOnSetEvent(IntPtr Obj)
		{
			DllUnitSim u = (DllUnitSim)Marshal.GetObjectForIUnknown(Obj);

			if (u.UnitSetEvent == null)
				return;

			u.UnitSetEvent(u);
		}

		private static void UnitOnStart(IntPtr Obj)
		{
			DllUnitSim u = (DllUnitSim)Marshal.GetObjectForIUnknown(Obj);

			if (u.UnitStart == null)
				return;

			u.UnitStart(u);
		}

		private static void UnitOnTerminate(IntPtr Obj)
		{
			DllUnitSim u = (DllUnitSim)Marshal.GetObjectForIUnknown(Obj);

			if (u.UnitExit == null)
				return;

			u.UnitExit(u);
		}

		private static void UnitOnIdle(IntPtr Obj)
		{
			DllUnitSim u = (DllUnitSim)Marshal.GetObjectForIUnknown(Obj);

			if (u.UnitIdle == null)
				return;

			u.UnitIdle(u);
		}

		private static void UnitOnOutput(IntPtr Obj, int Kind, IntPtr Data, int Size)
		{
			DllUnitSim u = (DllUnitSim)Marshal.GetObjectForIUnknown(Obj);

			byte[] data = new byte[Size];

			Marshal.Copy(Data, data, 0, Size);

			if (Kind == 0)
			{
				System.Diagnostics.Debug.WriteLine(u.UnitName + " : " + Encoding.Unicode.GetString(data));
			}
			else if (Kind < 0)
			{
				u.Push(-Kind, data);
			}
			else if (u.UnitOutput != null)
			{
				u.UnitOutput(u, Kind, data);
			}
		}

		private static void UnitOnGetSystemTime(IntPtr Obj, ref long now, ref long frequency)
		{
			DllUnitSim u = (DllUnitSim)Marshal.GetObjectForIUnknown(Obj);

			if (u.UnitGetSystemTime == null)
				return;

			u.UnitGetSystemTime(u, ref now, ref frequency);
		}

		public void Start()
		{
			m_Start();
		}

		public void Exit()
		{
			m_Exit();
		}

		public void Interrupt(int IntNo)
		{
			m_Interrupt(IntNo);
		}

		public int ReadAddr(uint Addr, byte[] dst)
		{
			int result;

			GCHandle hResult = GCHandle.Alloc(dst, GCHandleType.Pinned);
			try
			{
				IntPtr buffer = Marshal.UnsafeAddrOfPinnedArrayElement(dst, 0);

				result = m_ReadAddr(Addr, buffer, dst.Length);
			}
			finally
			{
				hResult.Free();
			}

			return result;
		}

		public int WriteAddr(uint Addr, byte[] src)
		{
			int result;

			GCHandle hResult = GCHandle.Alloc(src, GCHandleType.Pinned);
			try
			{
				IntPtr buffer = Marshal.UnsafeAddrOfPinnedArrayElement(src, 0);

				result = m_WriteAddr(Addr, buffer, src.Length);
			}
			finally
			{
				hResult.Free();
			}

			return result;
		}

		public void SetBit(uint addr, int bit, bool value)
		{
			m_SetBit(addr, bit, value);
		}

		public bool GetBit(uint addr, int bit)
		{
			return m_GetBit(addr, bit);
		}

		public void Input(int Kind, byte[] Data)
		{
			GCHandle hResult = GCHandle.Alloc(Data, GCHandleType.Pinned);
			try
			{
				IntPtr buffer = Marshal.UnsafeAddrOfPinnedArrayElement(Data, 0);

				m_Input(Kind, buffer, Data.Length);
			}
			finally
			{
				hResult.Free();
			}
		}

		public long GetTimer()
		{
			return m_GetTimer();
		}

		public void Progress(long timer)
		{
			m_Progress(timer);
		}

		public void CallTimeOut(long frequency)
		{
			m_CallTimeOut(frequency);
		}

		public string UnitName
		{
			get
			{
				char[] result = new char[256];
				GCHandle hResult = GCHandle.Alloc(result, GCHandleType.Pinned);
				try
				{
					IntPtr buffer = Marshal.UnsafeAddrOfPinnedArrayElement(result, 0);

					m_GetUnitName(buffer, result.Length);
				}
				finally
				{
					hResult.Free();
				}
				int last = Array.IndexOf<char>(result, '\0');
				if (last < 0)
					last = result.Length;
				return new String(result, 0, last);
			}
			set
			{
				char[] result = value.ToCharArray();
				GCHandle hResult = GCHandle.Alloc(result, GCHandleType.Pinned);
				try
				{
					IntPtr buffer = Marshal.UnsafeAddrOfPinnedArrayElement(result, 0);

					m_SetUnitName(buffer);
				}
				finally
				{
					hResult.Free();
				}
			}
		}

		public bool ProcessEvent()
		{
			if (m_ProcessEvent != null)
				return m_ProcessEvent();
			return false;
		}

		protected abstract void Push(int kind, byte[] Data);

		public abstract IList<IUnitInterface> Interfaces { get; }

		public event UnitInterfaceEventHandler AddInterface;
		public event UnitInterfaceEventHandler RemoveInterface;
		public event UnitInterfaceEventHandler UpdateInterface;

		protected void DoAddInterface(IUnitInterface item)
		{
			if (AddInterface != null)
				AddInterface(this, item);
		}

		protected void DoRemoveInterface(IUnitInterface item)
		{
			if (RemoveInterface != null)
				RemoveInterface(this, item);
		}

		protected void DoUpdateInterface(IUnitInterface item)
		{
			if (UpdateInterface != null)
				UpdateInterface(this, item);
		}

		protected void CallLog(int kind, byte[] data)
		{
			if (UnitOutput != null)
				UnitOutput(this, kind, data);
		}
	}

	public interface IUnitSimAdpt
	{
		IUnitSim Target { get; }
		void Restart();
	}

	public delegate IUnitInterface GetInterfaceCallback(IUnitSim owner, IUnitInterface item);

	public class UnitSimAdpt<T> : IDisposable, IUnitSim, IUnitSimAdpt
		where T : class, IUnitSim
	{
		Type m_Type;
		protected T m_UnitSim;
		IInterfaceHub m_InterfaceHub;
		List<IUnitInterface> m_Interfaces = new List<IUnitInterface>();
		string m_UnitName;

		public UnitSimAdpt(T unitSim, IInterfaceHub hub)
		{
			m_Type = unitSim.GetType();
			m_UnitSim = unitSim;
			Init(hub);
		}

		public UnitSimAdpt(IInterfaceHub hub)
		{
			m_Type = typeof(T);
			Create(hub);
		}

		protected Type Type
		{
			get { return m_Type; }
		}

		protected virtual void Create(IInterfaceHub hub)
		{
			ConstructorInfo ctor = m_Type.GetConstructor(new Type[] { typeof(IInterfaceHub) });
			m_UnitSim = (T)ctor.Invoke(new object[] { hub });
			Init(hub);
		}

		public void Dispose()
		{
			foreach (IUnitInterface item1 in m_Interfaces)
			{
				UnitInterfaceAdpt item2 = (UnitInterfaceAdpt)item1;
				item2.Target = null;
			}

			IDisposable dis = m_UnitSim as IDisposable;
			m_UnitSim = default(T);
			if (dis != null)
				dis.Dispose();
		}

		public void Restart()
		{
			Dispose();

			Create(m_InterfaceHub);
		}

		protected void Init(IInterfaceHub hub)
		{
			m_InterfaceHub = hub;
			m_UnitName = m_UnitSim.UnitName;
			m_UnitSim.UnitSetEvent += new UnitEventHandler(UnitSim_UnitSetEvent);
			m_UnitSim.UnitStart += new UnitEventHandler(UnitSim_UnitStart);
			m_UnitSim.UnitExit += new UnitEventHandler(UnitSim_UnitExit);
			m_UnitSim.UnitIdle += new UnitEventHandler(UnitSim_UnitIdle);
			m_UnitSim.UnitOutput += new UnitOutputEventHandler(UnitSim_Log);
			m_UnitSim.UnitGetSystemTime += new UnitGetSystemTimeEventHandler(UnitSim_UnitGetSystemTime);
			m_UnitSim.AddInterface += new UnitInterfaceEventHandler(UnitSim_AddInterface);
			m_UnitSim.RemoveInterface += new UnitInterfaceEventHandler(UnitSim_RemoveInterface);
			m_UnitSim.UpdateInterface += new UnitInterfaceEventHandler(UnitSim_UpdateInterface);
			foreach (IUnitInterface item in m_UnitSim.Interfaces)
			{
				UnitInterfaceAdpt oldItem = (UnitInterfaceAdpt)m_Interfaces.Find(
					delegate(IUnitInterface item1)
					{
						return ((UnitInterfaceAdpt)item1).InterfaceName == item.InterfaceName;
					});

				if (oldItem != null)
				{
					oldItem.Target = item;
					continue;
				}

				IUnitInterface adpt = GetOrGenerateInterface(item);
				m_Interfaces.Add(adpt);
			}
		}

		public IUnitInterface FindInterface(string name)
		{
			return m_Interfaces.Find(delegate(IUnitInterface cmp)
			{
				return cmp.InterfaceName == name;
			});
		}

		public static GetInterfaceCallback GetInterface;

		private IUnitInterface GetOrGenerateInterface(IUnitInterface item)
		{
			IUnitInterface uif = null;

			if (GetInterface != null)
				uif = GetInterface(this, item);

			if (uif == null)
				uif = GenerateInterface(item);

			return uif;
		}

		/// <summary>
		/// デフォルト値の式を返す
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		private CodeExpression GetDefaultValue(Type type)
		{
			if (type == typeof(string))
				return new CodePrimitiveExpression("");
			else if (type == typeof(bool))
				return new CodePrimitiveExpression(false);
			else if (type.IsPrimitive)
				return new CodePrimitiveExpression(0);
			else if (type.IsEnum)
				return new CodeCastExpression(type, new CodePrimitiveExpression(0));
			else if (type.IsValueType)
			{
				CodeObjectCreateExpression ret = new CodeObjectCreateExpression();
				ret.CreateType = new CodeTypeReference(type);
				return ret;
			}
			else
				return new CodePrimitiveExpression(null);
		}

		static Dictionary<Type, Type> m_AdapterTypes = new Dictionary<Type, Type>();

		/// <summary>
		/// 動的にアダプタークラスを作成する
		/// </summary>
		/// <param name="item"></param>
		/// <returns></returns>
		private IUnitInterface GenerateInterface(IUnitInterface item)
		{
			Type itemType = item.GetType();
			Type[] itemInterfaces = itemType.GetInterfaces();
			Type adptType;

			if (!m_AdapterTypes.TryGetValue(itemType, out adptType))
			{
				List<string> assembles = new List<string>();
				Assembly execAssembly = Assembly.GetExecutingAssembly();
				assembles.Add(execAssembly.Location);

				CodePrimitiveExpression nullExp = new CodePrimitiveExpression(null);

				// 名前空間
				CodeNamespace nameSpace = new CodeNamespace("Console");

				// クラス
				string className = "UnitIFAdapter" + (m_AdapterTypes.Count + 1).ToString();
				CodeTypeDeclaration newType = new CodeTypeDeclaration(className);
				nameSpace.Types.Add(newType);

				newType.BaseTypes.Add(new CodeTypeReference(typeof(UnitInterfaceAdpt)));

				// コンストラクタ
				{
					CodeConstructor ctor = new CodeConstructor();
					newType.Members.Add(ctor);

					ctor.Attributes = MemberAttributes.Public;

					CodeParameterDeclarationExpression param1 = new CodeParameterDeclarationExpression();
					param1.Type = new CodeTypeReference(itemType);
					param1.Name = "unitIf";
					ctor.Parameters.Add(param1);

					CodeParameterDeclarationExpression param2 = new CodeParameterDeclarationExpression();
					param2.Type = new CodeTypeReference(typeof(IUnitSim));
					param2.Name = "unitSim";
					ctor.Parameters.Add(param2);

					ctor.BaseConstructorArgs.Add(new CodeArgumentReferenceExpression("unitIf"));
					ctor.BaseConstructorArgs.Add(new CodeArgumentReferenceExpression("unitSim"));
				}

				CodeFieldReferenceExpression this_Target = new CodeFieldReferenceExpression();
				this_Target.TargetObject = new CodeThisReferenceExpression();
				this_Target.FieldName = "Target";

				// インターフェイスを実装
				foreach (Type ifType in itemInterfaces)
				{
					if ((ifType == typeof(IUnitInterface) || (ifType == typeof(IUnitInterfaceAdpt))))
						continue;

					string assemblyLocation = Assembly.GetAssembly(ifType).Location;
					if (!assembles.Contains(assemblyLocation))
						assembles.Add(assemblyLocation);

					newType.BaseTypes.Add(new CodeTypeReference(ifType));

					CodeCastExpression if_Target = new CodeCastExpression();
					if_Target.Expression = this_Target;
					if_Target.TargetType = new CodeTypeReference(ifType);

					// ラッパープロパティの実装
					foreach (PropertyInfo pInfo in ifType.GetProperties())
					{
						CodeMemberProperty prop = new CodeMemberProperty();
						newType.Members.Add(prop);

						prop.PrivateImplementationType = new CodeTypeReference(ifType);
						prop.Attributes = (MemberAttributes)0;
						prop.Name = pInfo.Name;
						prop.Type = new CodeTypeReference(pInfo.PropertyType);

						assemblyLocation = Assembly.GetAssembly(pInfo.PropertyType).Location;
						if (!assembles.Contains(assemblyLocation))
							assembles.Add(assemblyLocation);

						List<CodeExpression> indexes = new List<CodeExpression>();

						ParameterInfo[] paramInfos = pInfo.GetIndexParameters();
						foreach (ParameterInfo paramInfo in paramInfos)
						{
							CodeParameterDeclarationExpression param = new CodeParameterDeclarationExpression();
							prop.Parameters.Add(param);

							FieldDirection dir = (FieldDirection)0;
							if (paramInfo.IsIn)
								dir |= FieldDirection.In;
							if (paramInfo.IsOut)
								dir |= FieldDirection.Out;
							if (paramInfo.IsRetval)
								dir |= FieldDirection.Ref;
							param.Direction = dir;
							param.Type = new CodeTypeReference(paramInfo.ParameterType);
							param.Name = paramInfo.Name;

							assemblyLocation = Assembly.GetAssembly(paramInfo.ParameterType).Location;
							if (!assembles.Contains(assemblyLocation))
								assembles.Add(assemblyLocation);

							indexes.Add(new CodeArgumentReferenceExpression(paramInfo.Name));
						}

						prop.HasGet = pInfo.GetGetMethod() != null;
						if (prop.HasGet)
						{
							CodeConditionStatement ifState = new CodeConditionStatement();
							prop.GetStatements.Add(ifState);

							CodeBinaryOperatorExpression ifStateCondition = new CodeBinaryOperatorExpression();
							ifStateCondition.Operator = CodeBinaryOperatorType.IdentityEquality;
							ifStateCondition.Left = this_Target;
							ifStateCondition.Right = nullExp;
							ifState.Condition = ifStateCondition;

							CodeMethodReturnStatement trueRetState = new CodeMethodReturnStatement();
							ifState.TrueStatements.Add(trueRetState);
							trueRetState.Expression = GetDefaultValue(pInfo.PropertyType);

							CodeMethodReturnStatement falseRetState = new CodeMethodReturnStatement();
							ifState.FalseStatements.Add(falseRetState);
							if (paramInfos.Length > 0)
							{
								falseRetState.Expression = new CodeArrayIndexerExpression(if_Target, indexes.ToArray());
							}
							else
								falseRetState.Expression = new CodeFieldReferenceExpression(if_Target, pInfo.Name);
						}
						prop.HasSet = pInfo.GetSetMethod() != null;
						if (prop.HasSet)
						{
							CodeConditionStatement ifState = new CodeConditionStatement();
							prop.SetStatements.Add(ifState);

							CodeBinaryOperatorExpression ifStateCondition = new CodeBinaryOperatorExpression();
							ifStateCondition.Operator = CodeBinaryOperatorType.IdentityInequality;
							ifStateCondition.Left = this_Target;
							ifStateCondition.Right = nullExp;
							ifState.Condition = ifStateCondition;

							CodeAssignStatement trueRetState = new CodeAssignStatement();
							ifState.TrueStatements.Add(trueRetState);
							if (paramInfos.Length > 0)
							{
								trueRetState.Left = new CodeArrayIndexerExpression(if_Target, indexes.ToArray());
							}
							else
								trueRetState.Left = new CodeFieldReferenceExpression(if_Target, pInfo.Name);
							trueRetState.Right = new CodePropertySetValueReferenceExpression();
						}
					}

					// ラッパーメソッドの実装
					foreach (MethodInfo mInfo in ifType.GetMethods())
					{
						if (mInfo.IsSpecialName)
							continue;

						CodeMemberMethod method = new CodeMemberMethod();
						newType.Members.Add(method);

						method.PrivateImplementationType = new CodeTypeReference(ifType);
						method.Attributes = (MemberAttributes)0;
						method.Name = mInfo.Name;
						method.ReturnType = new CodeTypeReference(mInfo.ReturnType);

						assemblyLocation = Assembly.GetAssembly(mInfo.ReturnType).Location;
						if (!assembles.Contains(assemblyLocation))
							assembles.Add(assemblyLocation);

						List<CodeExpression> prms = new List<CodeExpression>();

						ParameterInfo[] paramInfos = mInfo.GetParameters();
						foreach (ParameterInfo paramInfo in paramInfos)
						{
							CodeParameterDeclarationExpression param = new CodeParameterDeclarationExpression();
							method.Parameters.Add(param);

							FieldDirection dir = (FieldDirection)0;
							if (paramInfo.IsIn)
								dir |= FieldDirection.In;
							if (paramInfo.IsOut)
								dir |= FieldDirection.Out;
							if (paramInfo.IsRetval)
								dir |= FieldDirection.Ref;
							param.Direction = dir;
							param.Type = new CodeTypeReference(paramInfo.ParameterType);
							param.Name = paramInfo.Name;

							assemblyLocation = Assembly.GetAssembly(paramInfo.ParameterType).Location;
							if (!assembles.Contains(assemblyLocation))
								assembles.Add(assemblyLocation);

							CodeArgumentReferenceExpression prm = new CodeArgumentReferenceExpression(paramInfo.Name);
							if (dir != (FieldDirection)0)
								prms.Add(new CodeDirectionExpression(dir, prm));
							else
								prms.Add(prm);
						}

						CodeMethodReferenceExpression cmre = new CodeMethodReferenceExpression(if_Target, method.Name);
						if (mInfo.ReturnType == typeof(void))
						{
							CodeConditionStatement ifState = new CodeConditionStatement();
							method.Statements.Add(ifState);

							CodeBinaryOperatorExpression ifStateCondition = new CodeBinaryOperatorExpression();
							ifStateCondition.Operator = CodeBinaryOperatorType.IdentityInequality;
							ifStateCondition.Left = this_Target;
							ifStateCondition.Right = nullExp;
							ifState.Condition = ifStateCondition;

							ifState.TrueStatements.Add(new CodeMethodInvokeExpression(cmre, prms.ToArray()));
						}
						else
						{
							CodeConditionStatement ifState = new CodeConditionStatement();
							method.Statements.Add(ifState);

							CodeBinaryOperatorExpression ifStateCondition = new CodeBinaryOperatorExpression();
							ifStateCondition.Operator = CodeBinaryOperatorType.IdentityEquality;
							ifStateCondition.Left = this_Target;
							ifStateCondition.Right = nullExp;
							ifState.Condition = ifStateCondition;

							CodeMethodReturnStatement trueRetState = new CodeMethodReturnStatement();
							ifState.TrueStatements.Add(trueRetState);
							trueRetState.Expression = GetDefaultValue(mInfo.ReturnType);

							CodeMethodReturnStatement falseRetState = new CodeMethodReturnStatement();
							ifState.FalseStatements.Add(falseRetState);
							falseRetState.Expression = new CodeMethodInvokeExpression(cmre, prms.ToArray());
						}
					}
				}

				CodeCompileUnit compileUnit = new CodeCompileUnit();
				compileUnit.Namespaces.Add(nameSpace);

				compileUnit.ReferencedAssemblies.AddRange(assembles.ToArray());

				CSharpCodeProvider provider = new CSharpCodeProvider();

				CompilerParameters cplparam = new CompilerParameters();
				cplparam.GenerateInMemory = true;

				CodeCompileUnit[] units = { compileUnit };
				CompilerResults result = provider.CompileAssemblyFromDom(cplparam, units);

				if (result.Errors.Count > 0)
				{
					CodeGeneratorOptions option = new CodeGeneratorOptions();
					StringBuilder sb = new StringBuilder();
					TextWriter tw = new StringWriter(sb);

					provider.GenerateCodeFromCompileUnit(compileUnit, tw, option);

					tw.Close();

					System.Diagnostics.Debug.WriteLine(sb);
					foreach (CompilerError text in result.Errors)
						System.Diagnostics.Debug.WriteLine(text.ErrorText);

					return new UnitInterfaceAdpt(item, this);
				}

				Assembly assembly = result.CompiledAssembly;

				adptType = assembly.GetType("Console." + className);

				m_AdapterTypes.Add(itemType, adptType);
			}

			ConstructorInfo ctorInfo = adptType.GetConstructor(new Type[] { itemType, typeof(IUnitSim) });
			return (IUnitInterface)ctorInfo.Invoke(new object[] { item, this });
		}

		public T Target
		{
			get { return m_UnitSim; }
		}

		IUnitSim IUnitSimAdpt.Target
		{
			get { return m_UnitSim; }
		}

		public static T GetTarget(IUnitSim unit)
		{
			IUnitSimAdpt adpt = unit as IUnitSimAdpt;
			if (adpt == null)
			{
				T bare = unit as T;
				if (bare != null)
					return bare;
				return null;
			}

			return adpt.Target as T;
		}

		void UnitSim_UnitSetEvent(IUnitSim sender)
		{
			if (UnitSetEvent != null)
				UnitSetEvent(this);
		}

		void UnitSim_UnitStart(IUnitSim sender)
		{
			if (UnitStart != null)
				UnitStart(this);
		}

		void UnitSim_UnitExit(IUnitSim sender)
		{
			if (UnitExit != null)
				UnitExit(this);
		}

		void UnitSim_UnitIdle(IUnitSim sender)
		{
			if (UnitIdle != null)
				UnitIdle(this);
		}

		void UnitSim_Log(IUnitSim sender, int Kind, byte[] Data)
		{
			if (UnitOutput != null)
				UnitOutput(this, Kind, Data);
		}

		void UnitSim_UnitGetSystemTime(IUnitSim sender, ref long now, ref long frequency)
		{
			if (UnitGetSystemTime != null)
				UnitGetSystemTime(this, ref now, ref frequency);
		}

		void UnitSim_AddInterface(IUnitSim sender, IUnitInterface item)
		{
			IUnitInterface adpt = GetOrGenerateInterface(item);
			m_Interfaces.Add(adpt);
			if (AddInterface != null)
				AddInterface(this, adpt);
		}

		void UnitSim_RemoveInterface(IUnitSim sender, IUnitInterface item)
		{
			foreach (IUnitInterface item1 in m_Interfaces)
			{
				UnitInterfaceAdpt item2 = (UnitInterfaceAdpt)item1;
				if (item2.Target == item)
				{
					item2.Target = null;
					break;
				}
			}
		}

		void UnitSim_UpdateInterface(IUnitSim sender, IUnitInterface item)
		{
			if (UpdateInterface != null)
			{
				foreach (IUnitInterface item1 in m_Interfaces)
				{
					UnitInterfaceAdpt item2 = (UnitInterfaceAdpt)item1;
					if (item2.Target == item)
					{
						UpdateInterface(this, item2);
						break;
					}
				}
			}
		}

		#region IUnitSim メンバ

		public string UnitName
		{
			get { if (m_UnitSim != null) m_UnitName = m_UnitSim.UnitName; return m_UnitName; }
			set { m_UnitName = value; if (m_UnitSim != null) m_UnitSim.UnitName = value; }
		}

		public event UnitEventHandler UnitSetEvent;

		public event UnitEventHandler UnitStart;

		public event UnitEventHandler UnitExit;

		public event UnitEventHandler UnitIdle;

		public event UnitOutputEventHandler UnitOutput;

		public event UnitGetSystemTimeEventHandler UnitGetSystemTime;

		public event UnitInterfaceEventHandler AddInterface;

		public event UnitInterfaceEventHandler RemoveInterface;

		public event UnitInterfaceEventHandler UpdateInterface;

		public void Start()
		{
			if (m_UnitSim != null)
				m_UnitSim.Start();
		}

		public void Exit()
		{
			if (m_UnitSim != null)
				m_UnitSim.Exit();
		}

		public IList<IUnitInterface> Interfaces
		{
			get { return m_Interfaces.AsReadOnly(); }
		}

		public void Interrupt(int IntNo)
		{
			if (m_UnitSim != null)
				m_UnitSim.Interrupt(IntNo);
		}

		public void Input(int kind, byte[] Data)
		{
			if (m_UnitSim != null)
				m_UnitSim.Input(kind, Data);
		}

		public int ReadAddr(uint addr, byte[] dst)
		{
			if (m_UnitSim != null)
				return m_UnitSim.ReadAddr(addr, dst);
			return 0;
		}

		public int WriteAddr(uint addr, byte[] src)
		{
			if (m_UnitSim != null)
				return m_UnitSim.WriteAddr(addr, src);
			return 0;
		}

		public bool GetBit(uint addr, int bit)
		{
			if (m_UnitSim != null)
				return m_UnitSim.GetBit(addr, bit);
			return false;
		}

		public void SetBit(uint addr, int bit, bool value)
		{
			if (m_UnitSim != null)
				m_UnitSim.SetBit(addr, bit, value);
		}

		public long GetTimer()
		{
			if (m_UnitSim != null)
				return m_UnitSim.GetTimer();
			return -1;
		}

		public void Progress(long timer)
		{
			if (m_UnitSim != null)
				m_UnitSim.Progress(timer);
		}

		public void CallTimeOut(long frequency)
		{
			if (m_UnitSim != null)
				m_UnitSim.CallTimeOut(frequency);
		}

		public bool ProcessEvent()
		{
			if (m_UnitSim != null)
				return m_UnitSim.ProcessEvent();
			return false;
		}

		#endregion
	}

	public interface IUnitInterfaceAdpt
	{
		IUnitInterface Target { get; set; }
	}

	public class UnitInterfaceAdpt : IUnitInterface, IUnitInterfaceAdpt
	{
		IUnitInterface m_UnitInterface;
		IUnitSim m_UnitSim;
		string m_InterfaceName;

		public UnitInterfaceAdpt(IUnitInterface unitInterface, IUnitSim unitSim)
		{
			m_UnitInterface = unitInterface;
			m_InterfaceName = unitInterface.InterfaceName;
			m_UnitSim = unitSim;
		}

		public IUnitInterface Target
		{
			get { return m_UnitInterface; }
			set { m_UnitInterface = value; }
		}

		#region IUnitInterface メンバ

		public string InterfaceName
		{
			get { return m_InterfaceName; }
		}

		public IUnitSim UnitSim
		{
			get { return m_UnitSim; }
		}

		#endregion

		public static bool Is<C>(IUnitInterface item) where C : class
		{
			C cast = item as C;
			if (cast == null)
			{
				IUnitInterfaceAdpt adpt = item as IUnitInterfaceAdpt;
				cast = adpt.Target as C;
			}

			return cast != null;
		}

		public static C As<C>(IUnitInterface item) where C : class
		{
			C cast = item as C;
			if (cast == null)
			{
				IUnitInterfaceAdpt adpt = item as IUnitInterfaceAdpt;
				cast = adpt.Target as C;
			}

			return cast;
		}
	}
}
