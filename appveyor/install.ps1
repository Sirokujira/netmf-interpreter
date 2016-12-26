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

    # ���X�N���v�g�̃f�B���N�g��
    # $basedir = Convert-Path $(Split-Path -Path $MyInvocation.InvocationName -Parent)
    # Set-Location $basedir

    # ZIP�t�@�C���W�J(GCC)
    # $shell = New-Object -ComObject Shell.Application
    # $archivePath = "C:\\projects\\netmf-interpreter"
    # $unzipDirObj = $sh.NameSpace($archivePath)
    # $zipFilePath = "C:\\projects\\netmf-interpreter\\gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip"
    # $zipPathObj = $sh.NameSpace($zipFilePath)
    # Write-Output "GCCCompiler : ArchiverDecompressStart $zipPath"
    # $unzipDirObj.CopyHere($zipPathObj.Items())
    
    $archivePath = "C:\\projects\\gcc-arm-none-eabi"
    $zipFilePath = "C:\\projects\\netmf-interpreter\\gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip"
    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
}

function InstallBuildTools()
{
    # NG?
    # Start-FileDownload "http://netmf.github.io/downloads/build-tools.zip"

    # ZIP�t�@�C���W�J(SDK Tools)
    # Appveyor - NG
    # $shell = New-Object -ComObject Shell.Application
    # $archivePath = "C:\\projects"
    # $unzipDirObj = $shell.NameSpace($archivePath)
    # $zipFilePath = "C:\\projects\\netmf-interpreter\\build-tools.zip"
    # $zipPathObj = $sh.NameSpace($zipFilePath)
    # Write-Output "BuildTools : ArchiveDecompressStart $zipPath"
    # $unzipDirObj.CopyHere($zipPathObj.Items())
    
    # $archivePath = "C:\\projects\\build-tools"
    $archivePath = "C:\\projects\\build-tools"
    $zipFilePath = "C:\\projects\\netmf-interpreter\\build-tools.zip"
    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
    
    # FolderMove
    $moveSrcFolderPath1 = "C:\\projects\\build-tools\bin"
    $moveDestFolderPath1 = "C:\\projects\\bin"
    Move-Item $moveSrcFolderPath1 $moveDestFolderPath1
    $moveSrcFolderPath2 = "C:\\projects\\build-tools\tools"
    $moveDestFolderPath2 = "C:\\projects\\tools"
    Move-Item $moveSrcFolderPath2 $moveDestFolderPath2
}

function InstallBuildTools2()
{
    $archivePath = "C:\\projects\\build-tools"
    $basePath = "C:\\projects\\netmf-interpreter\\"
    $zipFilePath = $basePath + "\\build-tools.zip"
    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
    
    $moveSrcFolderAllPath = $archivePath
    $moveDestFolderAllPath = "C:\\projects"
    Copy-Item -Path $moveSrcFolderAllPath -Destination $moveDestFolderAllPath
    
    # FolderMove
    $moveSrcFolderPath1 = $archivePath + "\\bin"
    $moveDestFolderPath1 = $basePath + "\\bin"
    # Move-Item $moveSrcFolderPath1 $moveDestFolderPath1
    Copy-Item -Path $moveSrcFolderPath1 -Destination $moveDestFolderPath1
    
    $moveSrcFolderPath2 = $archivePath + "\\tools"
    $moveDestFolderPath2 = $basePath + "\\tools"
    # Move-Item $moveSrcFolderPath2 $moveDestFolderPath2
    Move-Item -Path $moveSrcFolderPath2 -Destination $moveDestFolderPath2
}

function main () 
{
    # Version 4.4
    InstallNETMFSDK
    InstallGCCCompiler
    # InstallBuildTools
    InstallBuildTools2
}

main