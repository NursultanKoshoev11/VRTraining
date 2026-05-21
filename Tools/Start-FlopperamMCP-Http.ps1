$ErrorActionPreference = "Stop"

$RepoRoot = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$ServerDir = Join-Path $RepoRoot ".tools\flopperam-unreal-engine-mcp\Python"
$ServerScript = Join-Path $ServerDir "unreal_mcp_server_advanced.py"
$HttpBootstrap = Join-Path $ServerDir "run_unreal_mcp_streamable_http.py"

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

$bootstrapCode = @'
import logging
from unreal_mcp_server_advanced import mcp

logging.getLogger("UnrealMCP_Advanced_HTTP").info("Starting UnrealMCP Advanced with Streamable HTTP transport on http://localhost:8000/mcp")

if __name__ == "__main__":
    mcp.run(transport="streamable-http")
'@

Set-Content -Path $HttpBootstrap -Value $bootstrapCode -Encoding UTF8

Write-Host "Updating MCP SDK so streamable-http transport is available..."
Push-Location $ServerDir
uv add "mcp[cli]>=1.20.0"

Write-Host "Starting Flopperam Unreal MCP Streamable HTTP server..."
Write-Host "Local MCP URL: http://localhost:8000/mcp"
Write-Host "Keep Unreal Editor open while this server is running."
Write-Host "Keep this PowerShell window open. Press Ctrl+C to stop."
uv run run_unreal_mcp_streamable_http.py
Pop-Location
