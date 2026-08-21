param(
    [Parameter(Mandatory = $true)]
    [string]$SourceDir,

    [Parameter(Mandatory = $true)]
    [string]$CurrentName
)

$sources = Get-ChildItem -LiteralPath $SourceDir -Filter '*.c' -File
if ($sources.Count -eq 0) {
    throw "目录中没有找到 .c 文件: $SourceDir"
}

$currentSource = Join-Path $SourceDir $CurrentName
if (-not (Test-Path -LiteralPath $currentSource -PathType Leaf)) {
    throw "当前 C 文件不存在: $CurrentName"
}

$debugOutput = Join-Path ([System.IO.Path]::GetDirectoryName($currentSource)) 'current.exe'
$statePath = Join-Path $PSScriptRoot 'current.build.json'
$sourceHash = (Get-FileHash -LiteralPath $currentSource -Algorithm SHA256).Hash
$sourceRoot = (Resolve-Path $SourceDir).Path.TrimEnd('\')
$sourcePath = (Resolve-Path $currentSource).Path
$relativeSource = $sourcePath.Substring($sourceRoot.Length).TrimStart([char[]]@('\', '/'))
$needsBuild = -not (Test-Path -LiteralPath $debugOutput -PathType Leaf)

if (Test-Path -LiteralPath $statePath -PathType Leaf) {
    $state = Get-Content -LiteralPath $statePath -Raw | ConvertFrom-Json
    $needsBuild = $needsBuild -or $state.Source -ne $relativeSource -or $state.Hash -ne $sourceHash
}
else {
    $needsBuild = $true
}

if ($needsBuild) {
    Write-Host "编译 $CurrentName -> current.exe"
    & gcc -g -Wall -Wextra $currentSource -o $debugOutput
    if ($LASTEXITCODE -ne 0) {
        throw "编译失败: $CurrentName"
    }

    [ordered]@{
        Source = $relativeSource
        Hash = $sourceHash
    } | ConvertTo-Json | Set-Content -LiteralPath $statePath -Encoding UTF8
}
else {
    Write-Host "文件未变化，跳过编译: $CurrentName"
}
