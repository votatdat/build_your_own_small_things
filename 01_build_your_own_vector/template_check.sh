clear

rm -rf build
mkdir -p build

cmake -S . -B build
cmake --build build
./build/vector_tests

cd ..