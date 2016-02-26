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
    # NG?
    # Start-FileDownload "https://github.com/NETMF/netmf-interpreter/releases/download/NETMFCryptoLibraries/NetMFCryptoLibs.msi"
    Write-Output "NetMFCryptoLibs.msi : InstallStart"
    msiexec.exe NetMFCryptoLibs.msi /S /v/norestart /v/qn
}

function InstallGCCCompiler()
{
    # NG?
    # Start-FileDownload "https://launchpad.net/gcc-arm-embedded/5.0/5-2015-q4-major/+download/gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip"

    # 当スクリプトのディレクトリ
    # $basedir = Convert-Path $(Split-Path -Path $MyInvocation.InvocationName -Parent)
    # Set-Location $basedir

    # ZIPファイル展開(GCC)
    $shell = New-Object -ComObject Shell.Application
    $archivePath = "C:\\projects\\netmf-interpreter"
    $unzipDirObj = $sh.NameSpace($archivePath)
    $zipFilePath = "C:\\projects\\netmf-interpreter\\gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip"
    $zipPathObj = $sh.NameSpace()
    Write-Output "GCCCompiler : ArchiverDecompressStart $zipPath"
    $unzipDirObj.CopyHere($zipPathObj.Items())
}

function InstallBuildTools()
{
    # NG?
    # Start-FileDownload "http://netmf.github.io/downloads/build-tools.zip"

    # ZIPファイル展開(SDK Tools)
    $shell = New-Object -ComObject Shell.Application
    $archivePath = "C:\\projects"
    $unzipDirObj = $shell.NameSpace($archivePath)
    $zipFilePath = "C:\\projects\\netmf-interpreter\\build_tools.zip"
    $zipPathObj = $sh.NameSpace(zipFilePath)
    Write-Output "BuildTools : ArchiveDecompressStart $zipPath"
    $unzipDirObj.CopyHere($zipPathObj.Items())
}

function main () 
{
    # Version 4.4
    InstallNETMFSDK
    InstallGCCCompiler
    InstallBuildTools
}

main
