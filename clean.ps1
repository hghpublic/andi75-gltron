$BuildDir = "build"
if (Test-Path -Path $BuildDir) {
    Remove-Item -Recurse -Force $BuildDir
}
$DepsDir = "_deps"
if (Test-Path -Path $DepsDir) {
    Remove-Item -Recurse -Force $DepsDir
}
