#!/usr/bin/env sh
set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
CXX=${CXX:-clang++}
STD=${CXX_STD:-c++17}

set -- "$ROOT_DIR"/tools/gdiplus_usage/*.cpp

if [ "$1" = "$ROOT_DIR/tools/gdiplus_usage/*.cpp" ]; then
  echo "No GDI+ C++ usage sources found under tools/gdiplus_usage" >&2
  exit 1
fi

for SRC_FILE in "$@"; do
  if [ ! -f "$SRC_FILE" ]; then
    echo "Missing smoke source: $SRC_FILE" >&2
    exit 1
  fi

  "$CXX" \
    -fsyntax-only \
    -x c++ \
    -std="$STD" \
    -D_M_ARM=7 \
    -D_WCHAR_T_DEFINED \
    -I"$ROOT_DIR" \
    -I"$ROOT_DIR/lib/include" \
    -I"$ROOT_DIR/lib/include/win32" \
    -I"$ROOT_DIR/lib/include/gdiplus" \
    "$SRC_FILE"
done

echo "GDI+ C++ syntax check passed"
