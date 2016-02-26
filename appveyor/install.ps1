# Sample script to install Python and pip under Windows
# Authors: Olivier Grisel, Jonathan Helmus, Kyle Kastner, and Alex Willmer
# License: CC0 1.0 Universal: http://creativecommons.org/publicdomain/zero/1.0/

$WINSDK_URL = "https://www.python.org/ftp/python/"
$GCCCOMPILER_URL = "https://www.python.org/ftp/python/"

$PYTHON_PRERELEASE_REGEX = @"
(?x)
(?<major>\d+)
\.
(?<minor>\d+)
\.
(?<micro>\d+)
(?<prerelease>[a-z]{1,2}\d+)
"@

function InstallNETMFSDK()
{
    Start-FileDownload "https://github.com/NETMF/netmf-interpreter/releases/download/NETMFCryptoLibraries/NetMFCryptoLibs.msi"
    msiexec.exe NetMFCryptoLibs.msi /S /v/norestart /v/qn
}

function InstallGCCCompiler()
{
    Start-FileDownload "https://launchpad.net/gcc-arm-embedded/5.0/5-2015-q4-major/+download/gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip"

    # ZIPファイル展開(GCC)
    $sh = New-Object -ComObject Shell.Application
    $unzipDirObj = $sh.NameSpace("C:\projects\netmf-interpreter")
    $zipPathObj = $sh.NameSpace("C:\projects\netmf-interpreter\gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip")
    Write-Output "ArchiveDecompressStart $zipPath"
    $unzipDirObj.CopyHere($zipPathObj.Items())
}

function InstallWinSDK()
{
	Start-FileDownload "http://netmf.github.io/downloads/build-tools.zip"

    # ZIPファイル展開(SDK Tools)
    $sh = New-Object -ComObject Shell.Application
    $unzipDirObj = $sh.NameSpace("C:\projects")
    $zipPathObj = $sh.NameSpace("C:\projects\netmf-interpreter\build_tools.zip")
    Write-Output "ArchiveDecompressStart $zipPath"
    $unzipDirObj.CopyHere($zipPathObj.Items())
}

function main () 
{
    # Version 4.4
    InstallNETMFSDK
    InstallGCCCompiler
    InstallWinSDK
}

main
