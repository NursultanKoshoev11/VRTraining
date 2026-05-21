$ErrorActionPreference = "Stop"

$RepoRoot = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$SmokeDir = Join-Path $RepoRoot ".tools\mcp-smoke-test"
$SmokeFile = Join-Path $SmokeDir "smoke_mcp.py"

function Assert-CommandExists {
    param([string]$Name)
    if (-not (Get-Command $Name -ErrorAction SilentlyContinue)) {
        throw "Required command '$Name' was not found in PATH."
    }
}

Assert-CommandExists uv
New-Item -ItemType Directory -Force -Path $SmokeDir | Out-Null

$smokeCode = @'
from mcp.server.fastmcp import FastMCP

mcp = FastMCP("VRTraining MCP Smoke Test", json_response=True)

@mcp.tool()
def ping() -> str:
    """Return a simple health-check response."""
    return "pong from VRTraining smoke test"

@mcp.tool()
def unreal_status() -> str:
    """Return a placeholder status for the Unreal MCP connector smoke test."""
    return "MCP connector is reachable. Unreal tools are not loaded in this smoke test."

if __name__ == "__main__":
    mcp.run(transport="streamable-http")
'@

Set-Content -Path $SmokeFile -Value $smokeCode -Encoding UTF8

Write-Host "Starting minimal MCP smoke-test server..."
Write-Host "Local MCP URL: http://localhost:8000/mcp"
Write-Host "This server only has ping/unreal_status tools. Use it to test ChatGPT connector creation."

Push-Location $SmokeDir
uv run --with "mcp[cli]>=1.20.0" smoke_mcp.py
Pop-Location
