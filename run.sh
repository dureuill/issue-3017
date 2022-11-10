#!/bin/bash

rm -rf tmp_env_*
for i in {0..1000};
do
    mkdir tmp_env_$i 
done
gcc main.c ../liblmdb.a -lpthread -o repro && ./repro
