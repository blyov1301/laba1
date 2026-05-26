#!/bin/bash

# Сборка
mkdir -p build
cd build
cmake ..
make

# Запуск тестов
echo "Running tests..."
./run_tests
if [ $? -eq 0 ]; then
    echo "Tests passed!"
else
    echo "Tests failed!"
    exit 1
fi

# Создание deb пакета
mkdir -p deb_package/usr/local/bin
cp text_restricter deb_package/usr/local/bin/

mkdir -p deb_package/DEBIAN
cat > deb_package/DEBIAN/control << EOF
Package: text-restricter
Version: 1.0
Section: utils
Priority: optional
Architecture: amd64
Maintainer: User <user@example.com>
Description: Simple text restriction tool
EOF

dpkg-deb --build deb_package text-restricter_1.0_amd64.deb

# Создание Release директории
mkdir -p ../Release
mv text-restricter_1.0_amd64.deb ../Release/

echo "Done! Deb package in Release/ directory"
