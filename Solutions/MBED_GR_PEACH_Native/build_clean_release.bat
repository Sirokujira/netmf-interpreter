@rem msbuild.exe dotNetMF.proj /v:d /t:clean /p:flavor=release;memory=flash;platform=MBED_GR_PEACH 2>&1 | tee build_clean_release.txt
msbuild.exe dotNetMF.proj /v:d /t:clean /p:flavor=release;memory=flash;platform=MBED_GR_PEACH
