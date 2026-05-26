#!/bin/bash
set -e

echo "========================================="
echo "Building Strategy Pattern Demo"
echo "========================================="

# Создаём папку для сборки
mkdir -p build
cd build

# Конфигурируем CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Собираем
make -j$(nproc)

# Запускаем тест
echo ""
echo "Running tests..."
./test_runner

# Создаём DEB пакет
echo ""
echo "Creating DEB package..."
cpack -G DEB

# Копируем в Release
cd ..
mkdir -p Release
cp build/*.deb Release/

echo ""
echo "========================================="
echo "SUCCESS!"
echo "========================================="
ls -lh Release/
