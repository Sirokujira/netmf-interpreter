@echo off
cd /D E:\ToppersASP_WindowsSimulator\netmf-interpreter
REM VS2013
set VS140COMNTOOLS=%VS120COMNTOOLS%
REM VS2017
REM set VS140COMNTOOLS=%VS141COMNTOOLS%
setenv_gcc 4.9.3 E:\gcc-arm-none-eabi-4_9-2015q3-20150921-win32

