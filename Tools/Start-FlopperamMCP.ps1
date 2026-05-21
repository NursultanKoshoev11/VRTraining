$ErrorActionPreference = "Stop"

$RepoRoot = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$ServerDir = Join-Path $RepoRoot ".tools\flopperam-unreal-engine-mcp\Python"
$ServerScript = Join-Path $ServerDir "unreal_mcp_server_advanced.py"

function Assert-CommandExists {
    param([string]$Name)
    if (-not (Get-Command $Name -ErrorAction SilentlyContinue)) {
        throw "Required command '$Name' was not found in PATH."
    }
}

if (-not (Test-Path $ServerScript)) {
    throw "MCP server script was not found. Run Setup-FlopperamUnrealMCP.ps1 first. Expected: $ServerScript"
}

Assert-CommandExists uv

Write-Host "Starting Flopperam Unreal MCP local server..."
Write-Host "Server directory: $ServerDir"
Write-Host "Keep Unreal Editor open while this server is running."
Write-Host "Press Ctrl+C to stop."

Push-Location $ServerDir
uv run unreal_mcp_server_advanced.py
Pop-Location
