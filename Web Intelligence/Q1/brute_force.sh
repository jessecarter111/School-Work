#!/bin/bash

files=$(find ./data)

for file in ${files[@]}
do
  grep "\\\\n" $file
done
