#!/bin/bash
make clean
make
./boolcalc -isfull tests/funs01.in output.txt && cmp output.txt tests/funs01.out
./boolcalc -isfull tests/funs02.in output.txt && cmp output.txt tests/funs02.out
./boolcalc -isfull tests/funs03.in output.txt && cmp output.txt tests/funs03.out
./boolcalc -isfull tests/funs04.in output.txt && cmp output.txt tests/funs04.out
./boolcalc -isfull tests/funs05.in output.txt && cmp output.txt tests/funs05.out
./boolcalc -isfull tests/funs06.in output.txt && cmp output.txt tests/funs06.out
./boolcalc -isfull tests/funs07.in output.txt && cmp output.txt tests/funs07.out
./boolcalc -isfull tests/funs08.in output.txt && cmp output.txt tests/funs08.out
./boolcalc -isfull tests/funs09.in output.txt && cmp output.txt tests/funs09.out
./boolcalc -isfull tests/funs10.in output.txt && cmp output.txt tests/funs10.out
