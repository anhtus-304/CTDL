param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]] $MakeArgs
)

$ErrorActionPreference = "Stop"

$proj = Split-Path -Parent $PSScriptRoot

$makeExe = "C:\msys64\usr\bin\make.exe"
if (!(Test-Path $makeExe)) {
    Write-Error "Không tìm thấy $makeExe. Cài MSYS2 (https://www.msys2.org) và make: pacman -S --needed make gcc"
    exit 1
}

# Bổ sung PATH để g++ và coreutils khả dụng
$env:Path = "C:\msys64\ucrt64\bin;C:\msys64\usr\bin;" + $env:Path

& $makeExe -C $proj @MakeArgs
exit $LASTEXITCODE
