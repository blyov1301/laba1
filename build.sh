#!/bin/bash

# Установка GTest
sudo apt-get install -y libgtest-dev cmake
cd /usr/src/gtest && sudo cmake . && sudo make && sudo cp *.a /usr/lib

# Сборка
cd $GITHUB_WORKSPACE
mkdir -p build && cd build
cmake .. && make

# Тест
./run_tests

# Deb пакет
mkdir -p pkg/usr/local/bin
cp text_restricter pkg/usr/local/bin/
mkdir -p pkg/DEBIAN
echo "Package: test" > pkg/DEBIAN/control
echo "Version: 1.0" >> pkg/DEBIAN/control
echo "Architecture: amd64" >> pkg/DEBIAN/control
dpkg-deb --build pkg text-restricter.deb

mkdir -p ../Release
mv text-restricter.deb ../Release/
