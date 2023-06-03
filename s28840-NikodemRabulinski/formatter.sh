#!/usr/bin/env bash
shopt -s globstar
cd "${MESON_SOURCE_ROOT}"
clang-format -style=llvm --Werror -i **/*.c
