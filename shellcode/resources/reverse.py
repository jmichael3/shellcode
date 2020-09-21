#!/usr/bin/env python

import sys

asdf = sys.argv[1]
if len(asdf) % 4.0 != 0:
	print("[-]Not divisible by 4\n")
	sys.exit()

asdf = asdf[::-1]
i = 0
while i < len(asdf):
	print("0x" + asdf[i:i+4].encode("hex") + "    ; " + asdf[i:i+4])
	i += 4
