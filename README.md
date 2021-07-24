# date-implementation
Date class implementation for Necati Ergin Cpp assignment

## Compile & Run

### With make

* `make all` to build static and shared date libraries, install them under system path. Then build the test binary with it. (`/usr/local/lib` and `/usr/local/include` for the `Date.h` respectively.)
* `make lib` to build shared and static `libddate` libraries.
* `make test` to compile the tet source file under `source/test` and link libddate against it.
* `make install` to install the `Date.h` and `libddate.a` & `libddate.so` under the system path.

### Manually from command line

```
g++ test.cpp Date.cpp -o output -std=c++17 -Wextra -Wall -Werror -pedantic && ./output 
