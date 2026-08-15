# Local model results

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
