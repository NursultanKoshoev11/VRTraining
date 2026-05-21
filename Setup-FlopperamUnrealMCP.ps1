$ErrorActionPreference = "Stop"

$RepoRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Join-Path $RepoRoot "Default"
$UProjectPath = Join-Path $ProjectRoot "Default.uproject"
$ToolsRoot = Join-Path $RepoRoot ".tools"
$FlopperamRoot = Join-Path $ToolsRoot "flopperam-unreal-engine-mcp"
$PluginSource = Join-Path $FlopperamRoot "UnrealMCP"
$PluginDestRoot = Join-Path $ProjectRoot "Plugins"
$PluginDest = Join-Path $PluginDestRoot "UnrealMCP"

function Assert-CommandExists {
    param([string]$Name)
    if (-not (Get-Command $Name -ErrorAction SilentlyContinue)) {
        throw "Required command '$Name' was not found in PATH. Please install it and run this script again."
    }
}

if (-not (Test-Path $UProjectPath)) {
    throw "Default.uproject was not found at: $UProjectPath"
}

Assert-CommandExists git

New-Item -ItemType Directory -Force -Path $ToolsRoot | Out-Null
New-Item -ItemType Directory -Force -Path $PluginDestRoot | Out-Null

if (-not (Test-Path $FlopperamRoot)) {
    Write-Host "Cloning Flopperam Unreal Engine MCP..."
    git clone https://github.com/flopperam/unreal-engine-mcp.git $FlopperamRoot
} else {
    Write-Host "Updating Flopperam Unreal Engine MCP..."
    Push-Location $FlopperamRoot
    git fetch origin main
    git reset --hard origin/main
    Pop-Location
}

if (-not (Test-Path $PluginSource)) {
    throw "UnrealMCP plugin folder was not found in: $PluginSource"
}

if (Test-Path $PluginDest) {
    Write-Host "Removing old UnrealMCP plugin copy..."
    Remove-Item -Recurse -Force $PluginDest
}

Write-Host "Copying UnrealMCP plugin into the Unreal project..."
Copy-Item -Recurse -Force $PluginSource $PluginDest

Write-Host "Enabling UnrealMCP and EditorScriptingUtilities in Default.uproject..."
$projectJson = Get-Content $UProjectPath -Raw | ConvertFrom-Json

if (-not $projectJson.PSObject.Properties.Name.Contains("Plugins") -or $null -eq $projectJson.Plugins) {
    $projectJson | Add-Member -MemberType NoteProperty -Name Plugins -Value @()
}

function Enable-Plugin {
    param(
        [Parameter(Mandatory=$true)] $Json,
        [Parameter(Mandatory=$true)] [string] $PluginName,
        [string[]] $TargetAllowList = $null
    )

    $existing = @($Json.Plugins | Where-Object { $_.Name -eq $PluginName })
    if ($existing.Count -gt 0) {
        $existing[0].Enabled = $true
        if ($TargetAllowList) {
            if ($existing[0].PSObject.Properties.Name.Contains("TargetAllowList")) {
                $existing[0].TargetAllowList = $TargetAllowList
            } else {
                $existing[0] | Add-Member -MemberType NoteProperty -Name TargetAllowList -Value $TargetAllowList
            }
        }
        return
    }

    $plugin = [ordered]@{
        Name = $PluginName
        Enabled = $true
    }
    if ($TargetAllowList) {
        $plugin.TargetAllowList = $TargetAllowList
    }

    $Json.Plugins += [pscustomobject]$plugin
}

Enable-Plugin -Json $projectJson -PluginName "EditorScriptingUtilities" -TargetAllowList @("Editor")
Enable-Plugin -Json $projectJson -PluginName "UnrealMCP" -TargetAllowList @("Editor")

$projectJson | ConvertTo-Json -Depth 100 | Set-Content -Path $UProjectPath -Encoding UTF8

Write-Host "Done. UnrealMCP has been installed into: $PluginDest"
Write-Host "Next steps:"
Write-Host "1) Open Default/Default.uproject in Unreal Engine 5.6."
Write-Host "2) If Unreal asks to rebuild the plugin, click Yes."
Write-Host "3) After the editor opens, run Tools/Start-FlopperamMCP.ps1 from PowerShell."
