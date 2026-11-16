#!/usr/bin/env bash
set -euo pipefail
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
descriptors=(/originals/*.dsc)
test "${#descriptors[@]}" -eq 1
dpkg-source -x "${descriptors[0]}" "$work/source"

# Run outside the source tree so Python imports the installed Brotli binding.
cd "$work"
# Focal's py3versions needs debian/control to enumerate requested interpreters.
mkdir debian
ln -s "$work/source/debian/control" debian/control
interpreters=$(py3versions -r)
test -n "$interpreters"
sh -eu "$work/source/debian/tests/python3"
printf 'python3 PASS\n' > /reports/autopkgtest-summary.txt
