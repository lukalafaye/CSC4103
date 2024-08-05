#!/bin/bash
base_dir="$PWD"

tmp_dir=$(mktemp -d)

cd $tmp_dir || exit 1
wget https://cmocka.org/files/1.1/cmocka-1.1.1.tar.xz || exit 1
tar -xJf cmocka-1.1.1.tar.xz || exit 1


src_dir=cmocka-1.1.1
build_dir=build
install_dir=install

mkdir -p "$build_dir" || exit 1
mkdir -p "$install_dir" || exit 1

cmake -DCMAKE_INSTALL_PREFIX="$install_dir" -DWITH_STATIC_LIB=1 -DCMAKE_BUILD_TYPE=Debug "$src_dir" || exit 1
make -j4 || exit 1
make install || exit 1

echo "installation du fichier libcmocka.a..."
cp "${install_dir}/lib/libcmocka.a" "${base_dir}" || exit 1
echo -e "\tOK !"

echo "installation du fichier cmocka.h..."
cp ${install_dir}/include/cmocka*.h "${base_dir}" || exit 1
echo -e "\tOK !"

cd "$base_dir"
rm -rf "$tmp_dir"
