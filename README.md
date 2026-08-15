# RATS.EXE reconstruction

This repository is a minimal base for reconstructing `RATS.EXE`, the original
Windows version of [*Rats!*](https://www.windowsgames.co.uk/rats.html) by Sean
O'Connor. It builds a Win32 executable with Microsoft Visual C++ 4.20 under
[wibo](https://github.com/neuromancer/wibo), and runs it in
[DREAMM](https://dreamm.aarongiles.com/).

The original executable appears to have been built with Visual C++ 4.1. The
4.20 toolchain is a deliberate starting approximation; compiler flags and
source structure will be refined from binary comparisons as reconstruction
progresses.

## Setup

Clone with submodules, or initialise them after cloning:

```sh
git submodule update --init --recursive
```

The original executable is not included. Download the free Windows version
from the [official *Rats!* page](https://www.windowsgames.co.uk/rats.html) and
place its `RATS.EXE` in the repository root to use the original-executable and
binary-comparison targets.

The host needs CMake, Ninja, `curl`, and a C/C++ compiler to build wibo. On
macOS, the DREAMM smoke target also uses GNU `gtimeout` from `coreutils`:

```sh
brew install cmake ninja coreutils
```

## Commands

```sh
make                 # build out/RATS_RE.EXE, .map, .obj, and .asm
make run             # launch the rebuilt executable in DREAMM
make run-original    # launch the preserved original RATS.EXE
make test            # bounded DREAMM smoke test of the rebuilt executable
make test-original   # bounded DREAMM smoke test of the original executable
make debug           # start the rebuilt executable in DREAMM's debugger
make compare-func FUNC=SaveHighScores ADDR=00409092
```

wibo's compatible `msvcrt40.dll` and DREAMM `4.0x21` are downloaded on demand.
They remain local build dependencies and are not committed. A locally supplied
`RATS.EXE` is never overwritten; rebuilt programs are placed under `out/`.

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

## Acknowledgements

Special thanks to:

- [Sean O'Connor](https://www.windowsgames.co.uk/) for creating *Rats!* and
  continuing to make its original Windows release available from the
  [official game page](https://www.windowsgames.co.uk/rats.html).
