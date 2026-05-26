#!/bin/bash
set -e

echo "🔨 Building..."
mkdir -p build && cd build
cmake ..
make -j$(nproc)

echo "🧪 Running tests..."
ctest --output-on-failure

echo "📦 Creating DEB package..."
cpack -G DEB

echo "📁 Copying to Release..."
mkdir -p ../Release
cp *.deb ../Release/

echo "✅ Done! Package in Release/"
ls -lh ../Release/
