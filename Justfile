set dotenv-filename := ".envrc"

cxx_compiler := "${CXX}"
c_compiler := "${CC}"
cmake_build_type := "${BUILD_TYPE}"
cmake_generator := "${GENERATOR}"
build_dir := "builddir/" + cxx_compiler
target_output_dir := "artifacts"
ncores := `nproc`

default:
  @just --list

setup: clean init build install

init cxx=cxx_compiler:
  git submodule update --init
  cd data && unzip -uq \*.zip
  mkdir -p {{build_dir}}
  CXX={{cxx}} cmake \
    -B {{build_dir}} \
    -S . \
    -G "{{cmake_generator}}" \
    -DCMAKE_BUILD_TYPE={{cmake_build_type}} \
    -DWITH_UNIT_TESTS=on \
    -DWITH_COMPLIANCE_TESTS=on \
    -DWITH_EXAMPLES=on
  ln -fs {{build_dir}}/compile_commands.json compile_commands.json

build: 
  cmake --build {{build_dir}} --parallel {{ncores}}

install:
  sudo cmake --install {{build_dir}}

run_unit_tests:
  ./artifacts/bin/unit-tests

run_compliance_tests duration_seconds jobs=ncores: 
  python3 scripts/run_compliance_tests.py \
    --target artifacts/bin/compliance-tests \
    --edition 2013 2014 2017 \
    --duration {{duration_seconds}} \
    --jobs {{jobs}}

clean: 
  rm -rf {{build_dir}}
  rm -rf {{target_output_dir}}

fmt: 
  find src -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
  find include  -not -path '**/mdspan/**'  -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
