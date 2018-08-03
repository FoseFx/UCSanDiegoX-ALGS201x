#!/bin/bash

for i in $(seq -f "%02g" 1 24)
do
if [ "$(cat tests/$i | ./cmake-build-debug/DataStructures)" = "$(cat tests/$i.a)" ];
then
echo "$i Ok"
else
echo "$i not the same"
fi
done
