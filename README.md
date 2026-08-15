# RATS.EXE reconstruction

This repository is a minimal base for reconstructing `RATS.EXE`, the original
Windows version of [*Rats!*](https://www.windowsgames.co.uk/rats.html) by Sean
O'Connor. It builds a Win32 executable with Microsoft Visual C++ 4.1 under
[wibo](https://github.com/neuromancer/wibo), and runs it in
[DREAMM](https://dreamm.aarongiles.com/).

The original executable appears to have been built with Visual C++ 4.1. The
reconstruction now uses that compiler directly: C/C++ compiler version
10.10.6038 and linker version 3.10.6038.

## Setup

Clone with submodules, or initialise them after cloning:

```sh
git submodule update --init --recursive
```

The original executable is not included. Download the free Windows version
from the [official *Rats!* page](https://www.windowsgames.co.uk/rats.html) and
place its `RATS.EXE` in the repository root to use the original-executable and
binary-comparison targets.

The host needs CMake, Ninja, `curl`, `tar`, and a C/C++ compiler to build wibo.
On macOS, the DREAMM smoke target also uses GNU `gtimeout` from `coreutils`:

```sh
brew install cmake ninja coreutils
```

## Commands

```sh
make                 # build out/RATS_RE.EXE, .map, .obj, and .asm
make toolchain       # download, extract, and verify Microsoft Visual C++ 4.1
make run             # launch the rebuilt executable in DREAMM
make run-original    # launch the preserved original RATS.EXE
make test            # bounded DREAMM smoke test of the rebuilt executable
make test-original   # bounded DREAMM smoke test of the original executable
make debug           # start the rebuilt executable in DREAMM's debugger
make compare-func FUNC=SaveHighScores ADDR=00409092
```

The checksum-pinned
[MSVC 4.1 archive](https://github.com/decompme/compilers/releases/download/compilers/msvc4.1.tar.gz),
the required MSVC 4.1 libraries, wibo's compatible `msvcrt40.dll`, and DREAMM
`4.0x21` are downloaded on demand. They remain ignored local build dependencies
and are not committed. A locally supplied `RATS.EXE` is never overwritten;
rebuilt programs are placed under `out/`.

## Function reconstruction

The checked-in `ghidra/` directory contains assembly and decompiler exports for
all 177 internal functions discovered in the executable. Assembly is the
comparison authority; decompiler output is supplied to weaker local models as a
semantic hint.

Install [`binary-recons`](https://github.com/gg-sl-oss/binary-recons) once, then
it can be run from this or any other directory:

```sh
python3 -m pip install -e /path/to/binary-recons
binary-recons --project-root /path/to/rats-re --address 0x409092 --dry-run-prompt
```

`binary-recons.toml` selects the shared `c89` and `msvc4-od` rule profiles and
connects the model loop to the project's `binary-comp` target. It also
allowlists the shared type and global files, so a model can return any required
declarations and definitions as part of the same compiled, rollback-safe change
set as the function and prototype. No local model is needed for prompt
inspection or for the package's CI tests.

Measured local-model runs are recorded in [docs/MODEL_RESULTS.md](docs/MODEL_RESULTS.md).

<details>
<summary>Current function similarity and reconstruction timings (25 retained, 8 deferred)</summary>

The retained candidates were produced with Unsloth's
[Qwen3.8 27B GGUF](https://unsloth.ai/docs/models/qwen3.8) in BF16
(`Qwen3.8-27B-BF16`, served as `qwen3.8-27b-bf16`) through llama.cpp with a
32,768-token context and the `qwen` model preset. Gemma 4 31B IT BF16 was also
benchmarked, but no Gemma-generated candidate is retained in the source tree.

Similarity was remeasured from the current MSVC 4.1 source tree with
`binary-comp` on 2026-08-15. Logged time is the complete elapsed time of the
successful retained run, including managed-server startup, generation, any
compile repair, build, and comparison. It excludes earlier unsuccessful
exploratory runs.

| Address | Function | Current similarity | Logged time |
| --- | --- | ---: | ---: |
| `0x0040215C` | `IsLevelIndexInRange` | 43.18% | 46.9 s |
| `0x00402BF3` | `AddLevelToTable` | 73.85% | 4m 04.6s |
| `0x00402DC6` | `UpdateGameDisplay` | 78.18% | 1m 36.4s |
| `0x00402EE7` | `GetLevelDisplayInfo` | 71.70% | 2m 15.9s |
| `0x00403607` | `PlaceLevel` | 80.00% | 2m 32.6s |
| `0x00404D6E` | `DrawBitmapPair` | 98.67% | 1m 04.6s |
| `0x00404E3B` | `RenderBitmapToWindow` | 94.74% | 26.4 s |
| `0x00404ECE` | `DrawBitmapToWindow` | 95.59% | 59.3 s |
| `0x00404F8B` | `DrawScore` | 96.20% | 1m 32.4s |
| `0x0040507F` | `DrawScorePanel` | 97.97% | 2m 45.0s |
| `0x0040525D` | `DrawScoreDigits` | 94.20% | 2m 13.7s |
| `0x00405343` | `RenderScoreOverlay` | 76.77% | 1m 28.1s |
| `0x0040546B` | `DrawFrameBorder` | 86.30% | 37.0 s |
| `0x0040552E` | `ExplodeBomb` | 64.71% | 1m 50.9s |
| `0x0040560E` | `RenderExplosionWave` | 85.07% | 5m 40.0s |
| `0x0040591A` | `DrawBombExplosion` | 89.31% | 1m 45.8s |
| `0x00405AF5` | `DrawPausedOverlay` | 96.21% | 1m 05.1s |
| `0x00405DB8` | `ScorePanelDialogProc` | 50.34% | 1m 53.1s |
| `0x00405F72` | `DemoVersionDialogProc` | 46.31% | 4m 18.5s |
| `0x00408854` | `DrawStartButton` | 70.80% | 1m 35.6s |
| `0x00408A51` | `UpdateMainMenuState` | 97.56% | 28.9 s |
| `0x00408E6A` | `LoadLevelData` | 77.50% | 52.5 s |
| `0x00408F02` | `LoadHighScores` | 79.61% | 1m 15.0s |
| `0x00409092` | `SaveHighScores` | 94.12% | 1m 25.9s |
| `0x00409DB6` | `IsRatsHelpFile` | 91.67% | 41.5 s |

The following addresses exhausted their bounded attempts without leaving a
source implementation. Time spent is cumulative across all logged attempts.

| Deferred address | Time spent | Outcome |
| --- | ---: | --- |
| `0x00402205` | 3m 04.0s | Model request timed out |
| `0x0040250C` | 4m 36.6s | No compilable candidate after repair |
| `0x004026D0` | 3m 04.1s | Model request timed out |
| `0x00402FD5` | 3m 03.7s | Model request timed out |
| `0x00403430` | 4m 48.4s | Compile-repair request timed out |
| `0x00405C52` | 4m 54.5s | No compilable candidate after two runs |
| `0x004061D3` | 3m 04.2s | Model request timed out |
| `0x00408AD3` | 3m 03.8s | Model request timed out |

`WinMain` at `0x00401000` remains a minimal manual scaffold. Its current 1.13%
similarity is not counted as an LLM reconstruction.

</details>

## Acknowledgements

Special thanks to:

- [Sean O'Connor](https://www.windowsgames.co.uk/) for creating *Rats!* and
  continuing to make its original Windows release available from the
  [official game page](https://www.windowsgames.co.uk/rats.html).
