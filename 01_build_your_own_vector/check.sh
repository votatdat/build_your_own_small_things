clear

rm -rf build
mkdir -p build
cd build

cmake ..
cmake --build .
./vector_tests

cd ..