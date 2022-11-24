cmd_twod_matrix/built-in.a := rm -f twod_matrix/built-in.a; echo twod_matrix.o | sed -E 's:([^ ]+):twod_matrix/\1:g' | xargs ar cDPrST twod_matrix/built-in.a
