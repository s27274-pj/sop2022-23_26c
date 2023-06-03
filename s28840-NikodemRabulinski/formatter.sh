#!/usr/bin/env bash

cd "${MESON_SOURCE_ROOT}"
clang-format -style=llvm --Werror -i *.c
