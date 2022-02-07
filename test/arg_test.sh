#!/bin/bash

function ASSERT() {
	if [ "$1" = "$2" ]
	then
		echo "test ok     : $1 $2"
	else
		echo "test failed : $1 $2" 1>&2
		exit 1
	fi
}

cur_path=$(pwd)
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test1.txt"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test1.txt 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test2.file"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test2.file 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test3"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test3 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test4.fd"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test4.fd 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test5.fdff"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test5.fdff 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test6.fdff"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test6.fdff 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test7.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test7.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test8.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test8.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test9.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test9.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test10.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test10.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test11.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test11.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test12.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test12.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test13.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test13.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test14.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test14.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test15.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test15.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test16.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test16.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test17.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test17.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test18.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test18.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test19.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test19.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test20.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test20.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
echo "test : ${cur_path}/../fdf ${cur_path}/test_map/test21.fdf"
leak_block=$(${cur_path}/../fdf ${cur_path}/test_map/test21.fdf 2>&1 | grep "total leaked bytes" | awk '{print $3}')
ASSERT $leak_block 0
