## Visual Studio for NETMF Native Development

This guide describes steps needed to setup NETMF native code development from
within Visual Studio IDE, using GCC toolchain and OpenOCD debugger on GR-PEACH board.

### Prerequisites

1. [Visual Studio 2015 Community](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx) or higher edition,
2. [Visual C++ for IoT Development](https://visualstudiogallery.msdn.microsoft.com/35dbae07-8c1a-4f9d-94b7-bac16cad9c01) extension,
3. [GNU ARM Embedded Toolchain](https://launchpad.net/gcc-arm-embedded) (4.9.3 at the time of writing),
4. OpenOCD debugger - prebuilt binaries with GR-PEACH support available at GNU ARM Eclipse [OpenOCD dev](https://github.com/gnuarmeclipse/openocd/releases/tag/gae-0.10.0-20160110)

### Build

1. Navigate to `Solutions\MBED_GR_PEACH\VS` folder,
2. To customize toolchain environment and msbuild options copy `build.props.user-example` to `build.props.user` and change the values of the respective properties,
3. Open `MBED_GR_PEACH.sln` solution in Visual Studio,
4. Select the **Release** configuration for **ARM** platform,
5. Build

>_Note: In order to have full debugging information (such as local variable names)
available during debugging, you can either select the **Debug** configuration
or increase the amount of debugging information generated for the **Release**
configuration in GCC .targets file. In either case, make sure the generated
binary fits into the flash memory region._

### Debugging

1. In Visual Studio select **Debugging** in the Project Properties and set the options for **OCD GDB Debugger**
    * _OCD Debugger Executable_ to `<GCC root>\bin\arm-none-eabi-gdb.exe`
    * _OCD Debugger Server Address_ leave `localhost:3333`
    * _OCD Debug Binary_ browse for `tinyclr.bin`, e.g. `<NETMF root>BuildOutput\RZA1\GCC4.9\le\FLASH\release\MBED_GR_PEACH\bin\tinyclr.bin`,
2. Open command prompt in OpenOCD root folder and launch

    `bin\openocd.exe -f <NETMF root>\Solutions\MBED_GR_PEACH\vs\renesas_rza1h_swd.cfg`

3. Switch back to Visual Studio and launch **OCD GDB Debugger** command (on the toolbar)

If the connection is successfully established, OpenOCD output should be similar to
```
...
Info : ?????
Info : ?????
Info : ?????
Info : ?????
```
