$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot

function Get-Version {
    $cppPath = Join-Path $repoRoot "src\Main.cpp"
    $content = Get-Content $cppPath -Raw
    if ($content -match 'RED4EXT_SEMVER\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)') {
        return "$($Matches[1]).$($Matches[2]).$($Matches[3])"
    }
    throw "Could not find RED4EXT_SEMVER in $cppPath"
}

function Invoke-Build {
    Push-Location $repoRoot
    try {
        cmake --build build --config Release
        if (-not $?) { throw "CMake build failed." }
    }
    finally {
        Pop-Location
    }
}

function Copy-Artifacts {
    param([string]$Version)
    $dist = Join-Path $repoRoot "dist\DateTime-$Version"
    $plugin = Join-Path $dist "red4ext\plugins\DateTime"
    New-Item -ItemType Directory -Force -Path $plugin | Out-Null
    Copy-Item (Join-Path $repoRoot "build\src\Release\DateTime.dll") -Destination $plugin -Force
    Copy-Item (Join-Path $repoRoot "src\DateTime.reds") -Destination $plugin -Force
    return $dist
}

function New-ReleaseZip {
    param([string]$DistPath)
    $zipPath = "$DistPath.zip"
    Compress-Archive -Path "$DistPath\*" -DestinationPath $zipPath -Force
    return $zipPath
}

# --- Main ---
$version = Get-Version
Invoke-Build
$dist = Copy-Artifacts -Version $version
$zipPath = New-ReleaseZip -DistPath $dist
Write-Host "Done. Output: $dist/ and $zipPath"
