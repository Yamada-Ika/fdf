#!/bin/bash

cur_path=$(pwd)
${cur_path}/../fdf ${cur_path}/test_map/test1.txt
echo $?
${cur_path}/../fdf ${cur_path}/test_map/test2.file
echo $?
${cur_path}/../fdf ${cur_path}/test_map/test3
echo $?
${cur_path}/../fdf ${cur_path}/test_map/test4.fd
echo $?
${cur_path}/../fdf ${cur_path}/test_map/test5.fdff
echo $?
