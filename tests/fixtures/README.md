# Brotli regression input

`invalid-block-switch.hex` contains the 22-byte malformed Brotli stream used by the public CVE-2026-111497 reproduction at <https://github.com/hypnguyen1209/CVE-2026-111497/blob/main/exploit/poc.py>. The fixture is only the bounded compressed input; the HTTP server and exploit wrapper are not included. `brotli-stream-probe.c` sends it directly to the installed streaming decoder once, records the decoder result, then verifies a normal encode/decode round trip. Run only in the project's disposable test environment.
