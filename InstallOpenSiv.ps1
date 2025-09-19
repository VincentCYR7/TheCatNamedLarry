$OpenSivDownloadUrl = "https://siv3d.jp/downloads/Siv3D/manual/0.6.14/OpenSiv3D_SDK_0.6.14.zip"
Invoke-WebRequest $OpenSivDownloadUrl -OutFile "$($PSScriptRoot)\OpenSiv3D.zip"
Expand-Archive -Path "$($PSScriptRoot)\OpenSiv3D.zip" -DestinationPath $PSScriptRoot
<#
Template Download:
	https://siv3d.jp/downloads/Siv3D/manual/0.6.6/OpenSiv3D_0.6.6.zip
#>
return 0