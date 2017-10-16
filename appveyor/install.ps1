# Sample script to install Python and pip under Windows
# Authors: Olivier Grisel, Jonathan Helmus, Kyle Kastner, and Alex Willmer
# License: CC0 1.0 Universal: http://creativecommons.org/publicdomain/zero/1.0/

$GCC_PRERELEASE_REGEX = @"
(?x)
(?<major>\d+)
\.
(?<minor>\d+)
\.
(?<micro>\d+)
"@


function InstallNETMFSDK()
{
    # NG?
    # Start-FileDownload "https://github.com/NETMF/netmf-interpreter/releases/download/NETMFCryptoLibraries/NetMFCryptoLibs.msi"
    Write-Output "NetMFCryptoLibs.msi : InstallStart"
    # msiexec.exe NetMFCryptoLibs.msi /S /v/norestart /v/qn
    $msipath = "NetMFCryptoLibs.msi"
    
    # http://www.ibm.com/support/knowledgecenter/SS2RWS_2.1.0/com.ibm.zsecure.doc_2.1/visual_client/responseexamples.html?lang=ja
    $install_args = "/S /v/qn /v/norestart"
    RunCommand "schtasks" "/create /tn pclinstall /RL HIGHEST /tr `"$msipath $install_args`" /sc once /st 23:59"
    # Check TaskList
    RunCommand "schtasks" "/query /v"
    RunCommand "sleep" "10"
    RunCommand "schtasks" "/run /tn pclinstall"
    RunCommand "sleep" "30"
    RunCommand "schtasks" "/delete /tn pclinstall /f"
}

function InstallNETMFSDK_44()
{
    Write-Output "MicroFrameworkSDK.MSI : InstallStart"
    msiexec.exe MicroFrameworkSDK.MSI /S /v/norestart /v/qn
}

function InstallGCCCompiler()
{
    # NG?
    # Start-FileDownload "https://launchpad.net/gcc-arm-embedded/5.0/5-2015-q4-major/+download/gcc-arm-none-eabi-5_2-2015q4-20151219-win32.zip"

    # 当スクリプトのディレクトリ
    # $basedir = Convert-Path $(Split-Path -Path $MyInvocation.InvocationName -Parent)
    # Set-Location $basedir

    # ZIPファイル展開(GCC)
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

function InstallGCCCompiler2()
{
    $archivePath = "C:\\projects\\gcc-arm-none-eabi"
    # $zipFilePath = "C:\\projects\\netmf-interpreter\\gcc-arm-none-eabi-5_4-2016q2-20160622-win32.zip"
    # $zipFilePath = "C:\\projects\\netmf-interpreter\\gcc-arm-none-eabi-4_9-2014q4-20141203-win32.zip"
    $zipFilePath = "C:\\projects\\netmf-interpreter\\gcc-arm-none-eabi-4_9-2015q3-20150921-win32.zip"
    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
}

function ParseGCCVersion ($gcc_version) 
{
    if ($gcc_version -match $GCC_PRERELEASE_REGEX) 
    {
        return ([int]$matches.major, [int]$matches.minor, [int]$matches.micro)
    }
    
    # Convert NG
    $version_obj = [version]$gcc_version
    return ($version_obj.major, $version_obj.minor, $version_obj.build, "")
}


function InstallGCCCompiler3($gcc_version, $base_folder, $gcc_compiler_home)
{
    $major, $minor, $micro = ParseGCCVersion $gcc_version

    $archivePath = $gcc_compiler_home
    if ($major -le 4 -and $minor -eq 9)
    {
        # if (micro -eq 3)
        Start-FileDownload "https://launchpad.net/gcc-arm-embedded/4.9/4.9-2015-q3-update/+download/gcc-arm-none-eabi-4_9-2015q3-20150921-win32.zip"

        $zipFilePath = $base_folder + "\\gcc-arm-none-eabi-4_9-2015q3-20150921-win32.zip"
    }
    elseif ($major -le 5 -and $minor -eq 4)
    {
        Start-FileDownload "https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-win32.zip"

        $zipFilePath = $base_folder + "\\gcc-arm-none-eabi-5_4-2016q3-20160926-win32.zip"
    }
    elseif ($major -le 6 -and $minor -eq 0)
    {
        $zipFilePath = $base_folder + "\\gcc-arm-none-eabi-4_9-2015q3-20150921-win32.zip"
    }
    else
    {
        $zipFilePath = $base_folder + "\\gcc-arm-none-eabi-4_9-2015q3-20150921-win32.zip"
    }

    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
}


function InstallBuildTools()
{
    # NG?
    # Start-FileDownload "http://netmf.github.io/downloads/build-tools.zip"

    # ZIPファイル展開(SDK Tools)
    # Appveyor - NG
    # $shell = New-Object -ComObject Shell.Application
    # $archivePath = "C:\\projects"
    # $unzipDirObj = $shell.NameSpace($archivePath)
    # $zipFilePath = "C:\\projects\\netmf-interpreter\\build-tools.zip"
    # $zipPathObj = $sh.NameSpace($zipFilePath)
    # Write-Output "BuildTools : ArchiveDecompressStart $zipPath"
    # $unzipDirObj.CopyHere($zipPathObj.Items())
    
    # $archivePath = "C:\\projects\\build-tools"
    $archivePath = "C:\\projects"
    $zipFilePath = "C:\\projects\\netmf-interpreter\\build-tools.zip"
    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
    
    # FolderMove
    # $moveSrcFolderPath1 = "C:\\projects\\build-tools\bin"
    # $moveDestFolderPath1 = "C:\\projects\\bin"
    # Move-Item $moveSrcFolderPath1 $moveDestFolderPath1
    # $moveSrcFolderPath2 = "C:\\projects\\build-tools\tools"
    # $moveDestFolderPath2 = "C:\\projects\\tools"
    # Move-Item $moveSrcFolderPath2 $moveDestFolderPath2
}

function InstallBuildTools2()
{
    $basePath = "C:\\projects"
    $archivePath = $basePath + "\\netmf-interpreter\\build-tools"
    $zipFilePath = $basePath + "\\netmf-interpreter\\build-tools.zip"
    New-ZipExtract -source $zipFilePath -destination $archivePath -force -verbose
    
    # $moveSrcFolderAllPath = $archivePath
    # $moveDestFolderAllPath = "C:\\projects\\tools"
    # Copy-Item -Path $moveSrcFolderAllPath -Destination $moveDestFolderAllPath
    
    # FolderMove
    $moveSrcFolderPath1 = $archivePath + "\\bin"
    $moveDestFolderPath1 = $basePath + "\\bin"
    # Move-Item $moveSrcFolderPath1 $moveDestFolderPath1
    Copy-Item -Path $moveSrcFolderPath1 -Destination $moveDestFolderPath1 -Recurse
    
    $moveSrcFolderPath2 = $archivePath + "\\tools"
    $moveDestFolderPath2 = $basePath + "\\tools"
    # Move-Item $moveSrcFolderPath2 $moveDestFolderPath2
    Copy-Item -Path $moveSrcFolderPath2 -Destination $moveDestFolderPath2 -Recurse
    
    # $moveSrcFolderPath3 = "C:\\projects\\build-tools"
    # $moveDestFolderPath3 = "C:\\projects\\tools"
    # Copy-Item -Path $moveSrcFolderPath3 -Destination $moveDestFolderPath3 -Recurse
}

function main () 
{
    # Version 4.4
    InstallNETMFSDK
    # ToolChain
    # InstallGCCCompiler
    # InstallGCCCompiler2
    InstallGCCCompiler3 $env:GCC_VERSION $env:APPVEYOR_BUILD_FOLDER $env:GCC_TOOLS
    # Wait Process
    # InstallBuildTools
    InstallBuildTools2
}

main
