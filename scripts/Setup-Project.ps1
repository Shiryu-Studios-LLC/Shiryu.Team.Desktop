$ErrorActionPreference = "Stop"

$scriptDir = $PSScriptRoot
$projectRoot = Split-Path $scriptDir -Parent

$os = $PSVersionTable.OS
$arch = $env:PROCESSOR_ARCHITECTURE

if ($os -match "Linux") {
    $premake = "$projectRoot/vendor/bin/premake/Linux/premake5"
} elseif ($os -match "Darwin" -or $os -match "Mac") {
    $premake = "$projectRoot/vendor/bin/premake/MacOS/premake5"
} elseif ($arch -eq "AMD64" -or $arch -eq "x86_64") {
    $premake = "$projectRoot/vendor/bin/premake/Windows/premake5.exe"
} else {
    Write-Error "Unsupported platform"
    exit 1
}

& $premake --file=Build-ShiryuTeam-Project.lua vs2026
