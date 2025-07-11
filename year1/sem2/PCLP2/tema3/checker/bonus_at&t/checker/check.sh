#!/bin/bash

INPUTS="tests/in/"
OUTPUTS="tests/out/"
REFS="tests/ref/"

IN_EXT=".in"
OUT_EXT=".out"
REF_EXT=".ref"

TASK_SCORE=$(echo "scale=3; 10 / 3" | bc)
MAX_SCORE=10
TOTAL=0

make > /dev/null 2>&1

echo "================== AT&T bonus task =================="

for i in 1 2 3 ; do
	./checker < "${INPUTS}${i}${IN_EXT}" > "${OUTPUTS}${i}${OUT_EXT}"
	diff "${OUTPUTS}${i}${OUT_EXT}" "${REFS}${i}${REF_EXT}" > /tmp/diff_out
	if [ "$?" == "0" ]; then
		echo "Test $i					  ${TASK_SCORE::-1}p/${TASK_SCORE::-1}p"
		TOTAL=$(echo "scale=3; $TOTAL + $TASK_SCORE" | bc)
	else
		echo "Test $i					  0.00p/${TASK_SCORE::-1}p"
		cat /tmp/diff_out
	fi
done

echo
printf "Total score:				%5.2fp/%5.2fp\n" ${TOTAL} ${MAX_SCORE}

make clean > /dev/null 2>&1

echo "bonus_at&t:${TOTAL}" >> ../../.results
