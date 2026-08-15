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
