#!/bin/bash

valgrind	--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind-out.txt ./minirt_parse

#leak-check=full: each individual leak will be shown in details
#--show-leak-kinds=all: shows all leaks kinds in full report
#--track=origins=yes: favors useful output over speed, tracks origis of uninitialized values
#--verbose: can tell about unusual behavior in the program
#--log-file: wirtes to a file (useful when output exceeds terminal space)
