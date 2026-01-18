#!/bin/bash
set -e

# FBNeo Vendoring Script for CPS1/CPS2/CPS3
# Vendors only the minimal required components for Capcom arcade systems

# Check arguments
if [ $# -ne 3 ]; then
    echo "Error: Missing required arguments"
    echo ""
    echo "Usage: $0 <repo-root-dir> <fbneo-commit> <temp-dir>"
    echo ""
    echo "Arguments:"
    echo "  repo-root-dir  : Root directory of emu-ex-plus-alpha repository"
    echo "  fbneo-commit   : FBNeo commit hash to vendor"
    echo "  temp-dir       : Temporary directory for cloning FBNeo"
    echo ""
    echo "Example:"
    echo "  $0 /path/to/emu-ex-plus-alpha e6d13dfa0259bb270b6e86545a6e1d09de928d15 /tmp"
    exit 1
fi

REPO_ROOT="$1"
FBNEO_COMMIT="$2"
TEMP_DIR="$3"

# Validate arguments
if [ ! -d "$REPO_ROOT" ]; then
    echo "Error: Repository root directory does not exist: $REPO_ROOT"
    exit 1
fi

if [ ! -d "$TEMP_DIR" ]; then
    echo "Error: Temporary directory does not exist: $TEMP_DIR"
    exit 1
fi

if [ -z "$FBNEO_COMMIT" ]; then
    echo "Error: FBNeo commit hash is empty"
    exit 1
fi

echo "=========================================="
echo "FBNeo CPS1/CPS2/CPS3 Vendoring Script"
echo "=========================================="
echo "Repository root: $REPO_ROOT"
echo "FBNeo commit:    $FBNEO_COMMIT"
echo "Temp directory:  $TEMP_DIR"
echo ""

# 1. Clone FBNeo to temporary location
echo "[1/11] Cloning FBNeo..."
cd "$TEMP_DIR"
rm -rf FBNeo
git clone --depth 1 https://github.com/finalburnneo/FBNeo.git
cd FBNeo
git fetch --depth 1 origin "$FBNEO_COMMIT"
git checkout "$FBNEO_COMMIT"
echo "✓ Cloned and checked out commit $FBNEO_COMMIT"
echo ""

# 2. Create directory structure
echo "[2/11] Creating directory structure..."
cd "$REPO_ROOT"
mkdir -p FBNeo.emu/src/fbneo/burn/{drv,snd,devices}
mkdir -p FBNeo.emu/src/fbneo/cpu
echo "✓ Directory structure created"
echo ""

# 3. Copy Capcom drivers (CPS1/2/3)
echo "[3/11] Copying Capcom drivers..."
cp -r "$TEMP_DIR/FBNeo/src/burn/drv/capcom" FBNeo.emu/src/fbneo/burn/drv/
FILE_COUNT=$(find FBNeo.emu/src/fbneo/burn/drv/capcom -type f | wc -l)
echo "✓ Copied $FILE_COUNT files from Capcom drivers"
echo ""

# 4. Copy burn core files
echo "[4/11] Copying burn core files..."
cp "$TEMP_DIR/FBNeo/src/burn"/*.h FBNeo.emu/src/fbneo/burn/ 2>/dev/null || true
cp "$TEMP_DIR/FBNeo/src/burn"/*.cpp FBNeo.emu/src/fbneo/burn/ 2>/dev/null || true
FILE_COUNT=$(find FBNeo.emu/src/fbneo/burn -maxdepth 1 -type f | wc -l)
echo "✓ Copied burn core files ($FILE_COUNT files)"
echo ""

# 5. Copy sound chips (YM2151, MSM6295)
echo "[5/11] Copying sound chips..."
cd "$TEMP_DIR/FBNeo/src/burn/snd"
cp burn_ym2151.* msm6295.* ym2151.* \
   "$REPO_ROOT/FBNeo.emu/src/fbneo/burn/snd/" 2>/dev/null || true
FILE_COUNT=$(find "$REPO_ROOT/FBNeo.emu/src/fbneo/burn/snd" -type f 2>/dev/null | wc -l)
echo "✓ Copied sound chip files ($FILE_COUNT files)"
echo ""

# 6. Copy devices (EEPROM, Timer, etc.)
echo "[6/11] Copying devices..."
cd "$TEMP_DIR/FBNeo/src/burn/devices"
cp eeprom.* timekpr.* timer.* samples.* \
   "$REPO_ROOT/FBNeo.emu/src/fbneo/burn/devices/" 2>/dev/null || true
FILE_COUNT=$(find "$REPO_ROOT/FBNeo.emu/src/fbneo/burn/devices" -type f 2>/dev/null | wc -l)
echo "✓ Copied device files ($FILE_COUNT files)"
echo ""

# 7. Copy CPU cores (68000, Z80)
echo "[7/11] Copying CPU cores..."
cp -r "$TEMP_DIR/FBNeo/src/cpu/m68k" "$REPO_ROOT/FBNeo.emu/src/fbneo/cpu/"
cp -r "$TEMP_DIR/FBNeo/src/cpu/z80" "$REPO_ROOT/FBNeo.emu/src/fbneo/cpu/"
M68K_COUNT=$(find "$REPO_ROOT/FBNeo.emu/src/fbneo/cpu/m68k" -type f | wc -l)
Z80_COUNT=$(find "$REPO_ROOT/FBNeo.emu/src/fbneo/cpu/z80" -type f | wc -l)
echo "✓ Copied M68K core ($M68K_COUNT files)"
echo "✓ Copied Z80 core ($Z80_COUNT files)"
echo ""

# 8. Copy dependencies (if needed)
echo "[8/11] Copying dependencies..."
mkdir -p "$REPO_ROOT/FBNeo.emu/src/fbneo/dep"
if [ -d "$TEMP_DIR/FBNeo/src/dep/libs7zip" ]; then
    cp -r "$TEMP_DIR/FBNeo/src/dep/libs7zip" "$REPO_ROOT/FBNeo.emu/src/fbneo/dep/" 2>/dev/null || true
    echo "✓ Copied libs7zip dependency"
else
    echo "⚠ libs7zip not found, skipping"
fi
echo ""

# 9. Copy license
echo "[9/11] Copying license..."
cp "$TEMP_DIR/FBNeo/src/license.txt" "$REPO_ROOT/FBNeo.emu/src/fbneo/"
echo "✓ Copied FBNeo license"
echo ""

# 10. Record vendored version
echo "[10/11] Recording version info..."
cat > "$REPO_ROOT/FBNeo.emu/FBNEO_VERSION.txt" <<EOF
FBNeo Vendored Source Information
==================================
Commit: $FBNEO_COMMIT
Source: https://github.com/finalburnneo/FBNeo
Date: $(date -u +"%Y-%m-%d %H:%M:%S UTC")
Scope: CPS1/CPS2/CPS3 only (Capcom arcade systems)

Components Vendored:
- Capcom drivers (CPS1/CPS2/CPS3) from src/burn/drv/capcom/
- M68000 CPU core from src/cpu/m68k/
- Z80 CPU core from src/cpu/z80/
- YM2151 sound chip from src/burn/snd/
- MSM6295 ADPCM from src/burn/snd/
- Burn core framework from src/burn/
- Required devices (EEPROM, Timer) from src/burn/devices/
- Dependencies (libs7zip if present) from src/dep/

Note: This is a minimal vendor containing only CPS support.
To add other arcade systems, re-run this script and vendor
additional drivers from src/burn/drv/.
EOF
echo "✓ Version information recorded"
echo ""

# 11. Clean up
echo "[11/11] Cleaning up..."
rm -rf "$TEMP_DIR/FBNeo"
echo "✓ Temporary files removed"
echo ""

# Summary
echo "=========================================="
echo "✅ FBNeo vendored successfully!"
echo "=========================================="
echo "Location: $REPO_ROOT/FBNeo.emu/src/fbneo/"
echo "Version file: $REPO_ROOT/FBNeo.emu/FBNEO_VERSION.txt"
echo ""
TOTAL_SIZE=$(du -sh "$REPO_ROOT/FBNeo.emu/src/fbneo" | cut -f1)
echo "Total size: $TOTAL_SIZE"
echo ""
