#!/usr/bin/env bash
set -euo pipefail
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cd "$work"
printf '%s\n' 'GetPatched Brotli round trip' > payload
brotli -o payload.br payload
brotli -d -o restored payload.br
cmp payload restored
