@echo off

if NOT "%1"=="" GOTO :ARGSOK
if NOT "%2"=="" GOTO :ARGSOK

@echo.
@echo Error: Invalid Arguments!
@echo.
@echo Usage: build SPOCLIENT SolutionName [msbuild args]
@echo.
GOTO :EOF

:ARGSOK

if NOT "%NETMFVS_SETENV%"=="" GOTO :VARSOK

@echo.
@echo NETMFVS_SETENV variable is not set.
@echo.
GOTO :EOF

:VARSOK

setlocal
cd /d %1
call %NETMFVS_SETENV%
cd %1\Solutions\%2
@msbuild dotnetmf.proj %~3 %NETMFVS_MSBUILD%
MSbuild dotnetmf.proj /t:rebuild /p:flavor=release;memory=flash /filelogger
endlocal&&exit /B %ERRORLEVEL%