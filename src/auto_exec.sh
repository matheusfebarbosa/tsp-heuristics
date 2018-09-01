#!/bin/bash
FILES="att48 berlin52 kroA100 kroA150 kroA200 kroB100 kroB150 kroB200 kroC100 kroD100 kroE100 lin105 pr76 pr107 pr124 pr136 pr144 pr152 rat99 rat195 st70"

for f in $FILES
do
  echo "Processing $f file..."
  ./tp "../input/tests/$f.tsp"
  echo -e "\n"
done