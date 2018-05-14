#!/usr/bin/sh

rm -rf ./test/first
rm -rf ./test/third

mkdir -p ./test/first
mkdir -p ./test/first/second
mkdir -p ./test/third

generate_binary_file()
{
    size=$2*1024*1024

    echo "Generating file $1 [$2 Mb] ... "
    dd if=/dev/random of=$1 bs=$size count=1
    echo "Done\n"
}

generate_binary_file ./test/first/first.a.bin 10
generate_binary_file ./test/first/first.b.bin 100
generate_binary_file ./test/first/first.c.bin 4
generate_binary_file ./test/first/first.d.bin 10

generate_binary_file ./test/first/second/second.a.bin 1
generate_binary_file ./test/first/second/second.b.bin 120
generate_binary_file ./test/first/second/second.c.bin 500

generate_binary_file ./test/third/third.a.bin 100
generate_binary_file ./test/third/third.b.bin 10
cp ./test/first/first.b.bin ./test/third/third.c.bin
cp ./test/first/second/second.c.bin ./test/third/third.d.bin
generate_binary_file ./test/third/third.e.bin 120
generate_binary_file ./test/third/third.f.bin 3
cp ./test/first/second/second.c.bin ./test/third/third.g.bin
