#!/bin/bash
set -e

echo "=== Building ==="

# Создаём папку для сборки
mkdir -p build
cd build

# Конфигурируем и собираем
cmake ..
make -j$(nproc)

# Запускаем тесты
ctest --output-on-failure

# Создаём DEB пакет
cpack -G DEB

# Создаём папку Release и копируем туда DEB
mkdir -p ../Release
cp *.deb ../Release/

echo "=== Done ==="
ls -lh ../Release/
