#!/usr/bin/bash
for i in {1..10}
do
	mv buff_$i.png buff_$[i-1].png
done
