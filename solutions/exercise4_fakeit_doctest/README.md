# To build and Run

From project root:
```
$ meson builddir && cd builddir
$ meson test
```
If you want to see the full gtest output then add the `-v` option, e.g.:
```
$ meson test -v
```

## Valgrind
If valgrind is installed, then the tests can be run wrapped in valgrind, e.g.
```
$ meson test --wrap=valgrind -v
```
