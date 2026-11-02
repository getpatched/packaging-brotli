# GetPatched recipe: Brotli

GetPatched maintains selected security backports for distribution packages whose normal security support has ended. This repository contains a target-specific build recipe, patch and regression probe; it does not fork or vendor a second complete copy of Brotli. Builds fetch the exact public Ubuntu source package and keep Ubuntu's packaging and existing patches.

## Current target

| Field | Value |
|---|---|
| Target | Ubuntu 20.04 LTS (Focal), amd64 |
| Source | `brotli` `1.0.7-6ubuntu0.1`, public updates pocket |
| GetPatched version | `1.0.7-6ubuntu0.1+getpatched1` |
| Runtime packages | `libbrotli1`, `python3-brotli`, `brotli` |
| Access | Sponsor first for 168 hours, then public after release checks |
| State | Development candidate; no release binary is published |

Ubuntu's current advisory rates CVE-2026-111497 critical and lists Focal fixed only through ESM. GetPatched builds from the public non-ESM source above; it does not use ESM source or binaries. The signed Focal source indexes and all pinned file hashes have been checked. The source descriptor's separate uploader signature has not been verified. No package build, installed regression, scanner comparison or APT install is claimed yet.

## Structure and patch

`package-manifest.json` indexes target-specific recipe files. `targets/ubuntu/focal-amd64.json` pins the public source publication and archive files, their SHA-256 hashes, supported source version, output version and release policy. `patches/metadata.json` records the target-scoped backport, upstream commit, patch hash and regression expectations. `patches/CVE-2026-111497-focal.patch` backports upstream commit [`50a9b70`](https://github.com/google/brotli/commit/50a9b70a4d5e1443fc40927952276b68fffa83a0), applied after Ubuntu's existing quilt series.

The small hex fixture is a malformed block-switch stream from a public CVE reproduction. The checked-in probe passes only that 22-byte input to the installed streaming decoder, records its result, and checks a separate normal compression round trip. It does not include the reproduction's HTTP service or wrapper. Run it only in the project's disposable test environment.

## Sponsorship and licenses

All recipe source and patches are public from day one. For the official binary only, every active individual GitHub Sponsors tier gets access during the first seven days. Early binaries may be used privately and commercially; redistribution is prohibited until public promotion. Access ends when GitHub reports sponsorship inactive. GetPatched-authored material is MIT-licensed; the Brotli and Ubuntu source notices remain in force. See `LICENSES/GETPATCHED-EARLY-ACCESS-1.2.md` and `LICENSES/ubuntu-source-copyright`.

Target support is specific to Ubuntu release and architecture. Adding another release or arm64 requires its own exact source pin, patch applicability check, build, installed regression, scan and APT test.
