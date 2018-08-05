#!/bin/bash

for i in $(seq -f "%02g" 1 22)
do
if [ "$(cat tests/$i | ./cmake-build-debug/ProcessPackages)" = "$(cat tests/$i.a)" ];
then
echo "$i Ok"
else
echo "$i not the same"
fi
done
