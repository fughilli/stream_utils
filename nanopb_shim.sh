#!/bin/bash

# This script moves the generated header and source files from
# nanopb_generator.py to the bazel-bin directory to satisfy the genrule()
# export path requirements. Without this shim, Bazel complains about missing
# output artefacts.
#
# The export paths are obtained by parsing a log message printed on stderr by
# the generator script; this will (probably) break in the future.

compile_command=$1
in_proto=$2
out_header=$3
out_source=$4

output=$($compile_command --strip-path \
  --library-include-format='#include "%s"' --extension=".nanopb" $in_proto 2>&1)

intermediate_header=$(echo $output |
  sed -n 's/^Writing\ to\ \(.*\)\ and.*$/\1/p')
intermediate_source=$(echo $output |
  sed -n 's/^Writing\ to\ .*\ and\(.*\)$/\1/p')

mv $intermediate_header $out_header
mv $intermediate_source $out_source
