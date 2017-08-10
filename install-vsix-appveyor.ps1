# This PS installs the nanoFramework Visual Studio Extension for VS2015

$vsixPath = "$($env:USERPROFILE)\NetMFVS14.vsix"
(New-Object Net.WebClient).DownloadFile('https://github.com/NETMF/netmf-interpreter/releases/download/v4.4-RTW-20-Oct-2015/NetMFVS14.vsix', $vsixPath)
# "`"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\VSIXInstaller.exe`" /q /a $vsixPath" | out-file ".\install-vsix.cmd" -Encoding ASCII
"`"C:\Program Files (x86)\Microsoft Visual Studio\2015\Community\Common7\IDE\VSIXInstaller.exe`" /q /a $vsixPath" | out-file ".\install-vsix.cmd" -Encoding ASCII
& .\install-vsix.cmd
