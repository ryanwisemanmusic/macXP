#!/usr/bin/env sh
set -eu

mode="${1:-all}"
cc="${CC:-clang}"
cxx="${CXX:-clang++}"

common_includes="
  -I.
  -Ilib/include
  -Ilib/include/win32
  -Ilib/include/gdiplus
  -Ithird_party/SDL3/include
  -Ilibce/include
"

check_c_file() {
  "$cc" -fsyntax-only -Wno-ignored-attributes -std=c11 \
    $common_includes "$1"
}

check_cpp_file() {
  "$cxx" -fsyntax-only -Wno-ignored-attributes -std=c++20 \
    -D_M_ARM=7 -D_WCHAR_T_DEFINED \
    $common_includes "$1"
}

run_list() {
  list_file="$1"
  kind="$2"

  while IFS= read -r src; do
    [ -n "$src" ] || continue
    case "$kind" in
      c)
        check_c_file "$src"
        ;;
      cpp)
        check_cpp_file "$src"
        ;;
      mixed)
        case "$src" in
          *.cpp) check_cpp_file "$src" ;;
          *.c) check_c_file "$src" ;;
        esac
        ;;
    esac
  done < "$list_file"
}

check_tools() {
  list_file="$(mktemp)"
  trap 'rm -f "$list_file"' EXIT HUP INT TERM
  rg --files tools -g '*.c' -g '*.cpp' | sort > "$list_file"
  run_list "$list_file" mixed
  rm -f "$list_file"
  trap - EXIT HUP INT TERM
}

check_lib() {
  list_file="$(mktemp)"
  trap 'rm -f "$list_file"' EXIT HUP INT TERM
  rg --files lib -g '*.c' | rg -v '(^|/)test\.c$' | sort > "$list_file"
  run_list "$list_file" c
  rm -f "$list_file"
  trap - EXIT HUP INT TERM
}

check_libce() {
  list_file="$(mktemp)"
  trap 'rm -f "$list_file"' EXIT HUP INT TERM
  rg --files libce -g '*.c' | rg -v '(^|/)test\.c$' | sort > "$list_file"
  run_list "$list_file" c
  rm -f "$list_file"
  trap - EXIT HUP INT TERM
}

case "$mode" in
  tools)
    check_tools
    ;;
  lib)
    check_lib
    ;;
  libce)
    check_libce
    ;;
  all)
    check_tools
    check_lib
    check_libce
    ;;
  *)
    echo "usage: $0 [tools|lib|libce|all]" >&2
    exit 2
    ;;
esac

echo "Repository compile check passed ($mode)"
