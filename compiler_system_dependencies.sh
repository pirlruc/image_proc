LLVM_VERSION=13
CMAKE_VERSION=3.21
CMAKE_BUILD=4

HOME_DIRECTORY=$(pwd)

# LLVM - Clang
mkdir llvm_dir
cd llvm_dir

wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh $LLVM_VERSION

cd "$HOME_DIRECTORY"
rm -r llvm_dir

# CMake
sudo apt -y update
sudo apt -y install build-essential libtool autoconf unzip wget

sudo apt -y remove --purge --auto-remove cmake

mkdir cmake_dir
cd cmake_dir
wget https://cmake.org/files/v$CMAKE_VERSION/cmake-$CMAKE_VERSION.$CMAKE_BUILD.tar.gz
tar -xzvf cmake-$CMAKE_VERSION.$CMAKE_BUILD.tar.gz
cd cmake-$CMAKE_VERSION.$CMAKE_BUILD/

./bootstrap
make -j$(nproc)
sudo make install

cd "$HOME_DIRECTORY"
rm -rf cmake_dir