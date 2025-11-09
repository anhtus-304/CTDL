$ErrorActionPreference = "Stop"
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

$proj = Split-Path -Parent $PSScriptRoot
$exe = Join-Path $proj "build\main.exe"

# Bổ sung PATH để runtime tìm thấy DLL nếu cần
$env:Path = "C:\msys64\ucrt64\bin;C:\msys64\usr\bin;" + $env:Path

if (!(Test-Path $exe)) {
    Write-Host "Chưa có build. Đang build..."
    & (Join-Path $PSScriptRoot "build.ps1")
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}

Set-Location $proj
& .\build\main.exe
exit $LASTEXITCODE
