@rem msbuild.exe dotNetMF.proj /v:d /t:build /p:flavor=debug;memory=flash;platform=MBED_GR_PEACH 2>&1 | tee build_flash_debug.txt
msbuild.exe dotNetMF.proj /t:build /p:flavor=debug;memory=flash /fl /flp:logfile=build_flash_debug.txt;
