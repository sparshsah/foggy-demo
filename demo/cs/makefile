.PHONY: cppc

# following the convention of `javac`, `swiftc`, etc
cppc:
	# e.g. `make cppc f=hello`... MUST explicitly include the `f=` and must NOT append `.cpp`!
	clear  # make it easier to read warnings and errors
	clang++ -std=c++20 -Wall "$f.cpp" -o "$f.exe"

mosp.exe: mosp.cpp
	make cppc f=mosp

mosp: mosp.exe
	./mosp.exe you me all_of_the_people i_dont_know_why_i_cant_take_my_eyes_off_of_you
