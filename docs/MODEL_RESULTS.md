# Local model results

## WinMain size-limit POC

`WinMain` at `0x00401000` was used to compare a Pcode-first pipeline with a
compiler-led Qwen cleanup pass. AutoDecompiler reached its 6,000-token output
limit after 185.8 seconds without completing the function, so its draft was
discarded. Qwen produced a useful signature-only repair in 62.1 seconds, but a
broad follow-up containing project declarations and string evidence timed out
after 360 seconds without returning a response. A reduced first-error-cluster
request completed model inference in 21.8 seconds, but the experiment was
stopped before applying its output because the full function would still
require too many serial repair clusters.

No generated `WinMain` source was retained. The original 1.13% manual scaffold
remains in place, and the function is deferred as too large for the current
bounded first-pass workflow.

## Pcode draft-assisted hard-function POC

Two functions that previously timed out under Qwen-only reconstruction were
retried with a first-pass Pcode draft from
[`AutoDecompiler-30B-pscode`](https://huggingface.co/AutoDecompiler/AutoDecompiler-30B-pscode)
BF16. The raw draft was treated as an untrusted hint; Qwen3.8 27B BF16 still
received the original assembly, Ghidra decompilation, project declarations, and
rules, and produced the only candidate eligible for compilation and retention.
The historical Qwen-only runs were not repeated.

| Address | Pcode draft | Qwen candidate | Focused resume | Outcome |
| --- | ---: | ---: | ---: | --- |
| `0x004026D0` | 36.0 s | 5m 50.7s | 2m 30.9s | `RenderScoreboard`, 95.40%, retained |
| `0x004061D3` | 34.2 s | 4m 27.2s | 3m 13.3s | Did not compile; rolled back |

Both first Qwen candidates reused an existing function name. This exposed that
the name-only repair consumed the compiler-repair allowance. `binary-recons`
now keeps those budgets separate and can resume a logged candidate directly,
avoiding another full reconstruction request. The resumed scoreboard candidate
needed only a C89 declaration repair and then exceeded the 90% stopping
threshold. The second candidate still retained an invalid WinHelp constant
after its single focused repair, so the function remains deferred.

## Function 0x00409092

Both models received the same committed empty-function baseline, Ghidra
assembly and decompilation, referenced strings, central declarations, shared
`c89` and `msvc4-od` profiles, and compiler comparison feedback.

| Model | Baseline | Retained score | Attempts | Startup | Total |
| --- | ---: | ---: | ---: | ---: | ---: |
| Gemma 4 31B IT BF16 | 29.41% | 94.12% | 2 | 23.959 s | 151.169 s |
| Qwen3.8 27B BF16 | 29.41% | 94.12% | 2 | 25.989 s | 85.905 s |

The bounded settings were one iteration, three requested candidates, one
compile-repair attempt, 1,600 maximum response tokens, disabled thinking,
32,768 context, and an 80% early-stop threshold. In both runs, candidate one
needed the single compiler-repair pass and then exceeded 90%, so later
candidates were not compiled. The repaired candidates produced the same
remaining assembly mismatch. Qwen's result was retained because it reached the
same score substantially faster and used the project's platform type aliases.

The runs used llama.cpp build 10360 (`48d22e295`). Managed serving stopped each
owned model process before the other model was loaded.

## Model-inferred contract batch

Six additional functions were started without source stubs or declarations.
The target contract contained only the address: Qwen selected each function
name, prototype, and implementation from the assembly, decompiler hint,
referenced strings, and mechanically matched global declarations.

| Address | Model-selected name | Final similarity |
| --- | --- | ---: |
| `0x00404D6E` | `DrawBitmapPair` | 98.67% |
| `0x00404E3B` | `RenderBitmapToWindow` | 94.74% |
| `0x0040546B` | `DrawFrameBorder` | 86.30% |
| `0x00408A51` | `UpdateMainMenuState` | 97.56% |
| `0x00408E6A` | `LoadLevelData` | 77.50% |
| `0x00409DB6` | `IsRatsHelpFile` | 91.67% |

The final scores above were re-measured together from the retained tree. Five
of the six fresh functions exceed 80%. Each first pass requested one candidate
and allowed one compiler repair; only `0x00404D6E` needed a second generation
iteration to clear a name collision, and `0x00408E6A` received one follow-up
iteration that did not improve its retained score.

The live batch led to two general driver improvements. Python now supplies an
omitted address marker mechanically, and prompts expose existing function names
as a reserved-name list without revealing their interfaces. These changes do
not influence the model's proposed contract or C implementation.

## Restricted multi-file workflow validation

The transactional change-set workflow was validated on a disposable copy of
the project with the unimplemented function at `0x00404ECE`. Qwen received one
structured request with no agentic tools. Its first candidate selected the name
and interface, supplied matching declarations and definitions for three
previously undeclared globals, compiled, and reached 95.59% similarity. No
repair call was needed. The managed llama.cpp process stopped normally, and the
disposable candidate was not copied into the retained source tree.
