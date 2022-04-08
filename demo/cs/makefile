# author: sparshsah

.PHONY: cc cppc mosp

# following the convention of `javac`, `swiftc`, etc
cc:
	# e.g. `make cc f=hello`... MUST explicitly include the `f=` and must NOT append `.c`!
	clear  # make it easier to read warnings and errors
	clang -Wall "$f.c" -o "$f.exe"

cppc:
	# e.g. `make cppc f=hello`... MUST explicitly include the `f=` and must NOT append `.cpp`!
	clear  # make it easier to read warnings and errors
	clang++ -std=c++20 -Wall "$f.cpp" -o "$f.exe"

mosp.exe: mosp.c
	make cc f=mosp

mosp: mosp.exe
	./mosp.exe
