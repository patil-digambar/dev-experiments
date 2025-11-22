#!/bin/bash
set -euo pipefail

# --- Configuration ---
VCPKG_ROOT_DIR=/home/digambar/dev-experiments/SkillForge-Project/tools/vcpkg
TOOLCHAIN_FILE="$VCPKG_ROOT_DIR/scripts/buildsystems/vcpkg.cmake"

# --- Build Steps ---

# 1. Install system dependencies (pkg-config, build tools)
sudo apt update
sudo apt install -y pkg-config build-essential cmake

# 2. Ensure vcpkg is executable
chmod +x "$VCPKG_ROOT_DIR/vcpkg"

# 3. Install project dependencies from manifest
echo "Installing dependencies via vcpkg..."
"$VCPKG_ROOT_DIR/vcpkg" install

# 4. Create and enter the build directory
rm -rf build
mkdir -p build
cd build

# 5. Configure CMake with vcpkg toolchain
echo "Running CMake configuration with vcpkg toolchain..."
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"

# 6. Build the project
echo "Starting build..."
cmake --build . -- -j$(nproc)

echo "Build finished successfully! All libraries are provided via vcpkg."
