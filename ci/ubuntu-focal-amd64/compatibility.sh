#!/usr/bin/env bash
set -euo pipefail

work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
cd "$work"
printf 'Brotli CLI and Python interoperability\n' > payload
brotli -o from-cli.br payload
python3 - <<'PY'
from pathlib import Path

import brotli

payload = Path("payload").read_bytes()
assert brotli.decompress(Path("from-cli.br").read_bytes()) == payload
Path("from-python.br").write_bytes(brotli.compress(payload))
PY
brotli -d -o restored from-python.br
cmp payload restored
