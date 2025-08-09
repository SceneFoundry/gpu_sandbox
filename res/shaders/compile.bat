@echo off
setlocal enabledelayedexpansion

::――――――――――――――――――――――――――――
:: This script must live in your res\shaders folder.
:: It will compile *.vert and *.frag in this folder into ./spirV.

:: Path to this script’s directory (ends with a backslash)
set "SRC_DIR=%~dp0"

:: Path to glslangValidator; adjust if yours lives elsewhere
set "GLSLANG=C:/LocalVendor/glSlang/bin/glslangValidator.exe"

:: Output subfolder
set "OUT_DIR=%SRC_DIR%spirV"

:: Vulkan target
set "GLSL_FLAGS=-V --target-env vulkan1.3"

:: Make sure OUT_DIR exists
if not exist "%OUT_DIR%" (
    echo Creating output directory "%OUT_DIR%"...
    mkdir "%OUT_DIR%"
) else (
    echo Cleaning old SPV files in "%OUT_DIR%"...
    del /Q "%OUT_DIR%\*.spv" 2>nul
)

:: Compile both vertex and fragment
pushd "%SRC_DIR%"
for %%F in (*.vert *.frag) do (
    echo Compiling %%F...
    "%GLSLANG%" %GLSL_FLAGS% "%%F" -o "%OUT_DIR%\%%~nF.spv"
    if errorlevel 1 (
        echo.
        echo *** ERROR: Failed to compile %%F ***
        popd
        pause
        exit /b 1
    )
)
popd

echo.
echo All shaders compiled successfully!
pause
