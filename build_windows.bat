@echo off
chcp 65001
echo Building Library Management System...

if not exist "build" mkdir build

g++ -std=c++17 -Isrc -Isrc\managers -Isrc\menu -Isrc\models -Isrc\utils ^
src\main.cpp ^
src\managers\*.cpp ^
src\menu\*.cpp ^
src\models\*.cpp ^
src\utils\*.cpp ^
-o build\main.exe

if %errorlevel% equ 0 (
    echo Build successful!
    echo.
    build\main.exe
) else (
    echo Build failed!
    pause
)