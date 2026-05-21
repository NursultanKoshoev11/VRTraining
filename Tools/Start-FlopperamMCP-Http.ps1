$ErrorActionPreference = "Stop"

$RepoRoot = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$ServerDir = Join-Path $RepoRoot ".tools\flopperam-unreal-engine-mcp\Python"
$ServerScript = Join-Path $ServerDir "unreal_mcp_server_advanced.py"
$SseBootstrap = Join-Path $ServerDir "run_unreal_mcp_sse.py"

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

logging.getLogger("UnrealMCP_Advanced_SSE").info("Starting UnrealMCP Advanced with SSE transport on http://localhost:8000/sse")

if __name__ == "__main__":
    mcp.run(transport="sse")
'@

Set-Content -Path $SseBootstrap -Value $bootstrapCode -Encoding UTF8

Write-Host "Starting Flopperam Unreal MCP SSE server..."
Write-Host "Local MCP URL: http://localhost:8000/sse"
Write-Host "Keep Unreal Editor open while this server is running."
Write-Host "Keep this PowerShell window open. Press Ctrl+C to stop."

Push-Location $ServerDir
uv run run_unreal_mcp_sse.py
Pop-Location
