# Step 1: Define destination
$installPath = "C:\Program Files\cppkm\bin"
$exeUrl = "https://github.com/Arshal-Agarwal/CPPKM_CLI/releases/download/test/cppkm.exe"
$exeName = "cppkm.exe"
$exeFullPath = Join-Path $installPath $exeName

# Step 2: Create install directory if not exists
if (!(Test-Path $installPath)) {
    New-Item -ItemType Directory -Force -Path $installPath
}

# Step 3: Download exe
Invoke-WebRequest -Uri $exeUrl -OutFile $exeFullPath

# Step 4: Add to system PATH if not already added
$sysPath = [Environment]::GetEnvironmentVariable("Path", [EnvironmentVariableTarget]::Machine)
if ($sysPath -notlike "*$installPath*") {
    [Environment]::SetEnvironmentVariable("Path", "$sysPath;$installPath", [EnvironmentVariableTarget]::Machine)
    Write-Output "System PATH updated."
} else {
    Write-Output "Path already present in system PATH."
}

# Step 5: Verify install
Write-Output "`nInstalled cppkm to: $exeFullPath"
Write-Output "`nYou may need to restart your terminal or log out and back in to use 'cppkm' globally."
