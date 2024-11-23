#!/bin/bash

file=$1

/usr/local/LinkServer/LinkServer flash MCXN947 load --erase-all $file
