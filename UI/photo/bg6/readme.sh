#!/usr/bin/bash
for i in {0..120}
do
	mv bg_$i.png bg_$[i-1].png
done
