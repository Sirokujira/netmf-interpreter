@echo off

set FORCEDAT=
set FLAVOR=

if /I "%2"==""        set FLAVOR=debug
if /I "%2"=="?"       GOTO :HELP
if /I "%2"=="/?"      GOTO :HELP
if /I "%2"=="HELP"    GOTO :HELP

if /I "%2"=="D"       set FLAVOR=debug
if /I "%2"=="debug"   set FLAVOR=debug
if /I "%2"=="checked" set FLAVOR=debug

if /I "%2"=="R"       set FLAVOR=release
if /I "%2"=="release" set FLAVOR=release
if /I "%2"=="RTM"     set FLAVOR=release
if /I "%2"=="Free"    set FLAVOR=release

if /I "%FLAVOR%"==""  GOTO :HELP

if /I "%1"==""     GOTO :HELP
if /I "%1"=="?"    GOTO :HELP
if /I "%1"=="/?"   GOTO :HELP
if /I "%1"=="H"    GOTO :HELP
if /I "%1"=="HELP" GOTO :HELP

if /I "%1"=="N"                GOTO :NATIVESAMPLE
if /I "%1"=="Native"           GOTO :NATIVESAMPLE
if /I "%1"=="NativeSample"     GOTO :NATIVESAMPLE
if /I "%1"=="P"                GOTO :PORTBOOTER
if /I "%1"=="Port"             GOTO :PORTBOOTER
if /I "%1"=="PortBooter"       GOTO :PORTBOOTER
if /I "%1"=="L"                GOTO :PORTBOOTERLOADER
if /I "%1"=="Loader"           GOTO :PORTBOOTERLOADER
if /I "%1"=="PortBooterLoader" GOTO :PORTBOOTERLOADER
if /I "%1"=="Tiny"             GOTO :TINYBOOTER
if /I "%1"=="TinyBooter"       GOTO :TINYBOOTER
if /I "%1"=="B"                GOTO :TINYBOOTER
if /I "%1"=="Booter"           GOTO :TINYBOOTER
if /I "%1"=="D"                GOTO :TINYBOOTERDECOMPOSER
if /I "%1"=="DECOMPOSER"       GOTO :TINYBOOTERDECOMPOSER
if /I "%1"=="C"                GOTO :TINYCLR
if /I "%1"=="CLR"              GOTO :TINYCLR
if /I "%1"=="TINYCLR"          GOTO :TINYCLR

if /I "%1"=="HELLO"            GOTO :HELLO
if /I "%1"=="HELLOWORLD"       GOTO :HELLO
if /I "%1"=="NET"              GOTO :NET
if /I "%1"=="NETWORK"          GOTO :NET
if /I "%1"=="CLIENT"           GOTO :CLIENT
if /I "%1"=="SOCKETCLIENT"     GOTO :CLIENT
if /I "%1"=="SERVER"           GOTO :SERVER
if /I "%1"=="SOCKETSERVER"     GOTO :SERVER

if /I "%1"=="ALL"            ( GOTO :ALL
) else (                       GOTO :HELP )

:HELP
@echo.
@echo [[ Build Usage ]]
@echo.
@echo Build NativeSample     [Debug^|Release]
@echo Build PortBooter       [Debug^|Release]
@echo Build PortBooterLoader [Debug^|Release]
@echo Build TinyBooter       [Debug^|Release]
@echo Build Decomposer       [Debug^|Release]
@echo Build TinyCLR          [Debug^|Release]
@echo. 
@echo Build HelloWorld       [Debug^|Release]
@echo Build Network          [Debug^|Release]
@echo Build SocketClient     [Debug^|Release]
@echo Build SocketServer     [Debug^|Release]
@echo.
@echo Build All              [Debug^|Release]

GOTO :EOF


:NATIVESAMPLE
@echo NativeSample... %FLAVOR%
@echo MSbuild NativeSample\NativeSample.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
MSbuild NativeSample\NativeSample.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
GOTO :EOF

:PORTBOOTER
@echo PortBooter... %FLAVOR%
@echo MSbuild PortBooter\PortBooter.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
GOTO :EOF

:PORTBOOTERLOADER
@echo PortBooterLoader... %FLAVOR%
@echo MSbuild PortBooter\PortBooterLoader.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
GOTO :EOF

:TINYBOOTER
@echo TinyBooter... %FLAVOR%
@echo MSbuild TinyBooter\TinyBooter.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
GOTO :EOF

:TINYBOOTERDECOMPOSER
@echo TinyBooterDecomposer... %FLAVOR%
@echo MSbuild TinyBooter\TinyBooterDecomposer.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
GOTO :EOF

:TINYCLR
set FORCEDAT=
@echo TinyCLR... %FLAVOR%
@echo MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash
GOTO :EOF


:HELLO
set FORCEDAT=HelloWorld_Microsoft
@echo TinyCLR /w Hello... %FLAVOR%
@echo MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
GOTO :EOF

:NET
set FORCEDAT=network
@echo TinyCLR /w Network... %FLAVOR%
@echo MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
GOTO :EOF

:CLIENT
set FORCEDAT=SocketClient
@echo TinyCLR /w SocketClient... %FLAVOR%
@echo MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
GOTO :EOF

:SERVER
set FORCEDAT=SocketServer
@echo TinyCLR /w SocketServer... %FLAVOR%
@echo MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
MSbuild TinyCLR\TinyCLR.proj /t:rebuild /p:flavor=%FLAVOR%;memory=flash;forcedat=%FORCEDAT%
GOTO :EOF

:ALL
@echo AllProject.... %FLAVOR%
@echo MSbuild NativeSample\NativeSample.proj /p:flavor=%FLAVOR%;memory=flash
MSbuild NativeSample\NativeSample.proj /p:flavor=%FLAVOR%;memory=flash
@echo MSbuild TinyCLR\TinyCLR.proj /p:flavor=%FLAVOR%;memory=flash
MSbuild TinyCLR\TinyCLR.proj /p:flavor=%FLAVOR%;memory=flash

GOTO :EOF

:EOF
