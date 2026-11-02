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
| State | Hosted verification passed; sponsor flow pending; no release binary published |

Ubuntu currently rates CVE-2026-111497 High priority with CVSS 9.8 and lists the Focal fix through ESM. GetPatched builds from the public non-ESM source above; it does not use ESM source or binaries. The signed Focal source indexes and all pinned file hashes have been checked. The source descriptor's separate uploader signature has not been verified. The hosted run passed the package suite, installed decoder regression and consumer check, removed the target CVE findings from the package-aware scan, and passed the signed APT-client check: [run 41492184315](https://github.com/getpatched/platform/actions/runs/41492184315). This verified candidate is not release-eligible while sponsor entitlement, revocation and promotion flow remain unverified; no production binary is published.

## Structure and patch

`package-manifest.json` indexes target-specific recipe files. `targets/ubuntu/focal-amd64.json` pins the public source publication and archive files, their SHA-256 hashes, supported source version, output version and release policy. `patches/metadata.json` records the target-scoped backport, upstream commit, patch hash and regression expectations. `patches/CVE-2026-111497-focal.patch` backports upstream commit [`50a9b70`](https://github.com/google/brotli/commit/50a9b70a4d5e1443fc40927952276b68fffa83a0), applied after Ubuntu's existing quilt series.

The small hex fixture is a malformed block-switch stream from a public CVE reproduction. The checked-in probe feeds that 22-byte input to the installed streaming decoder in bounded 4 KiB output chunks, stopping at a terminal decoder result or after at most 32 MiB/8,192 calls. The baseline oracle expects decoder error -9 after 16 MiB/4,096 calls; the patched oracle expects decoder error -17 within the same hard bounds. The probe also checks a separate normal compression round trip. It does not include the reproduction's HTTP service or wrapper. Run it only in the project's disposable test environment.

## Sponsorship and licenses

All recipe source and patches are public from day one. For the official binary only, every active individual GitHub Sponsors tier gets access during the first seven days. Early binaries may be used privately and commercially; redistribution is prohibited until public promotion. Access ends when GitHub reports sponsorship inactive. GetPatched-authored material is MIT-licensed; the Brotli and Ubuntu source notices remain in force. See `LICENSES/GETPATCHED-EARLY-ACCESS-1.2.md` and `LICENSES/ubuntu-source-copyright`.

Target support is specific to Ubuntu release and architecture. Adding another release or arm64 requires its own exact source pin, patch applicability check, build, installed regression, scan and APT test.
