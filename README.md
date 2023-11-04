# bane
[ncurses](https://www.gnu.org/software/ncurses/) based terminal GUI library

State: **early development - incomplete**

# Build
## Natively (tested on Ubuntu 22.04)
### Requirements

- [Conan package manager](https://conan.io)
- Ubuntu package libncurses-dev

$ conan install . --output-folder=build --build=missing
$ cd build
$ cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
$ cmake --build .


## Development

# Monitoring log file

```bash
cd build
tail -F bane.log
```

## Known issues

# CMake version
CMake 3.5.1 does not find pthread library.
