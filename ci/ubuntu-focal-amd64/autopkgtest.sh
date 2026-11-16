#!/usr/bin/env bash
set -euo pipefail
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
descriptors=(/originals/*.dsc)
test "${#descriptors[@]}" -eq 1
dpkg-source -x "${descriptors[0]}" "$work/source"

# Run outside the source tree so Python imports the installed Brotli binding.
cd "$work"
test -n "$(py3versions -r 2>/dev/null)"
sh -eu "$work/source/debian/tests/python3"
printf 'python3 PASS\n' > /reports/autopkgtest-summary.txt
