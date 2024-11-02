
$BuildDir = "build"
if (Test-Path -Path $BuildDir) {
    Remove-Item -Recurse -Force $BuildDir
}
$DepsDir = "_deps"
if (Test-Path -Path $DepsDir) {
    Remove-Item -Recurse -Force $DepsDir
}


New-Item $BuildDir -ItemType Directory
cd $BuildDir


cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=D:\hgh\bin\vcpkg\scripts\buildsystems\vcpkg.cmake ..

$msbuild = C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe
