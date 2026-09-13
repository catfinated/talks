# WG21 papers cited in the deck

`wg21.link/PXXXX` without a revision suffix redirects to the **latest revision**, so these
links stay current as papers are revised. Where a specific revision is known, it's noted.

## Adopted into C++26

| Paper | What it is | Latest known | Link |
|---|---|---|---|
| P2300 | `std::execution` — the whole model | R10, adopted St. Louis Jun 2024 | https://wg21.link/P2300 |
| P3149 | `counting_scope` / `simple_counting_scope`, `spawn`, `spawn_future`, `associate` | R11 | https://wg21.link/P3149 |
| P2079 | `parallel_scheduler` / system execution context | R10 | https://wg21.link/P2079 |
| P3552 | `std::execution::task` coroutine type | R3 | https://wg21.link/P3552 |
| P3481 | `bulk` issues — `bulk_chunked`, `bulk_unchunked`, execution policy | — | https://wg21.link/P3481 |
| P3284 | `write_env` and `unstoppable` sender adaptors | R4 | https://wg21.link/P3284 |
| P3682 | **Removes** `std::execution::split` (Leahy) | R0, Sofia 2025-06 | https://wg21.link/P3682 |
| P4154 | "Renaming various execution things" — `sender_t`→`sender_tag`, `receiver_t`→`receiver_tag`, `scheduler_t`→`scheduler_tag`, `operation_state_t`→`operation_state_tag` | R0, Croydon 2026-03 | https://wg21.link/P4154 |

**Note on P3284:** R0 and R1 were titled "`finally`, `write_env`, and `unstoppable`". `finally`
was cut from R2 onward; only `write_env` and `unstoppable` were adopted. `finally` survives as
`exec::finally` in stdexec.

## Proposed — sender-side

| Paper | What it is | Status | Link |
|---|---|---|---|
| P2762 | Sender/receiver interface for networking (Kühl) | C++29 target | https://wg21.link/P2762 |
| P3482 | "Design for C++ networking based on IETF TAPS" (Rodgers, Kühl, 2024) — the API *shape*: describe the connection you need, not the socket. SG4's Tokyo 2024 direction. Cited by both camps | R1 | https://wg21.link/P3482 |
| P3955 | "It's Scopes All the Way Down" — async RAII, async construction/destruction (Leahy) | **R1 has wording.** SG1 saw R0 at Brno, liked it, asked for wording | https://wg21.link/P3955 |
| P4320 | `std::execution::sequence` — serial composition of senders (Leahy) | R1, 2026-08-22 (wording bug fix) | https://wg21.link/P4320 |
| P2849 | `async_object` — async constructor and destructor concept (Shoop) | Predecessor to P3955 | https://wg21.link/P2849 |

## Proposed — coroutine-first alternative (C++ Alliance)

| Paper | What it is | Status | Link |
|---|---|---|---|
| P4100 | "Coroutine-Native I/O for C++29 (The Network Endeavor)" (Falco, Gerbino, Vandeberg, Gill, Nejati) — **Intent: Inform.** Umbrella paper for the whole series; named on the ecosystem slide | R1, 2026-05-01 (pre-Brno mailing) | https://wg21.link/P4100 |
| P4003 | "A Minimal Coroutine Execution Model" (Falco, Gerbino, Gill) — **Intent: Ask.** The IoAwaitable protocol: executor affinity, stop-token propagation, frame-allocator delivery | R3, 2026-05-01 | https://wg21.link/P4003 |
| P4007 | "Open Issues in `std::execution::task`" (Falco, Gill) — **informational**, "asks for nothing" | R3, 2026-05-01 | https://wg21.link/P4007 |
| P4014 | "The Sender Sub-Language For Beginners" (Falco, Gill) — all 30 C++26 algorithms with plain-C++ equivalents. **CC0 public domain.** Informational | R2, 2026-05-01 | https://wg21.link/P4014 |
| P4041 | "Is `std::execution` a Universal Async Model?" (Falco) | R0, ~May 2026 | https://wg21.link/P4041 |

**The incompatibility is deliberate, and worth knowing precisely.** `IoAwaitable` requires a
*two-argument* `await_suspend(h, io_env const*)`, injected by the caller's `await_transform`.
`std::execution::task` doesn't inject it, so you cannot `co_await` an `IoAwaitable` from a
`task`. P4003 states this is intentional — both sides of every suspension point are statically
verified, and awaiting across model boundaries should fail to compile. So "complementary" holds
between subsystems but not within a single coroutine.

**Framing note.** Only P4003 is a proposal; P4007 is an informational classification of open
issues in the C++26 `task` type. Falco's stated position is that coroutine-native I/O and
`std::execution` are *complementary*, each suited to different domains — not that one replaces
the other. Don't present this line of work as a competing bid to replace senders.

**On P4014.** The most complete sender tutorial available, and CC0 — explicitly dedicated for
reuse as teaching material, so you can lift from it for the cheatsheet. §2.4 maps every algorithm
to its theoretical origin; §13 is a sensor-fusion / collision-detection / actuator-braking
example. Caveat: the register turns ironic, §14.1 contrasts a recursive backtracker with a
ten-line plain equivalent, and the conclusion points at the author's own Corosio. Recommend it
for coverage; say the author is making a case.

**Algorithms P4014 covers that the deck never mentions:** `affine` (renamed from `affine_on` by
P4151R1, made unary by P3941R4), `schedule_from`, `read_env`, `into_variant`,
`stopped_as_optional`, `stopped_as_error`, `when_all_with_variant`, `just_error`,
`just_stopped`, `associate`. Worth a skim in case one of them answers a Q&A question better
than improvising.

**P4007's four "not fixable post-ship" issues**, if you need specifics: Allocator Timing,
Allocator Propagation, Error Return (`co_yield with_error` is locked in because `return_value`
and `return_void` are mutually exclusive), and Symmetric Transfer (completion functions return
`void`, so a synchronously-completing sender resumes on the caller's stack with no bound on
frame growth — Müller called it a potential security vulnerability, and a production crash was
reported against stdexec in April 2026). Treat as one party's analysis, but it is sourced to NB
ballot comments and LWG issues.

P4041 isn't cited on any slide, but it now backs the "too hard to use" concession in slide 3's
speaker notes: Sean Baxter's 5,500-line error that triggered an ICE, Rainer Grimm abandoning
his C++26 library coverage, and Ben FrantzDale's "sea of underscores" remark. Cite it as a collection of criticism,
not a neutral assessment — the author is proposing an alternative model.

### Papers referenced *by* P4007, if you want the trail

P3552R3 (the `task` type itself), P3796R1 "Coroutine Task Issues" (Kühl), P3801R0 "Concerns
about the design of `std::execution::task`" (Müller), P3980R1 "Task's Allocator Use" (Kühl),
P3941R4 "Scheduler Affinity" (Kühl), P4151R1 "Rename `affine_on`" (Leahy), P3927R2
"`task_scheduler` Bulk Execution" (Niebler), P2583R4 "Symmetric Transfer and Sender
Composition" (Gill, Falco), P3950R0 "`return_value` & `return_void` Are Not Mutually Exclusive"
(Leahy), P1713R0 (Baker, 2019).

## Historical / referenced in passing

| Paper | What it is | Link |
|---|---|---|
| N2175 | Kohlhoff's networking proposal, 2007 | https://wg21.link/N2175 |
| N3721 | "Improvements to `std::future<T>`" — `.then()`, 2013 | https://wg21.link/N3721 |
| P0443 | A Unified Executors Proposal — the executor wars | https://wg21.link/P0443 |
| P1662 | "Adding async RAII support to coroutines" (Baker, 2019) — never adopted | https://wg21.link/P1662 |
| P3175 | Reconsidering `on` — source of the `transfer` → `continues_on` rename | https://wg21.link/P3175 |
| P2444 | Referenced in speaker notes | https://wg21.link/P2444 |
| P2464 | Referenced in speaker notes | https://wg21.link/P2464 |

## Cited in the speaker notes

| Paper | Why it matters | Link |
|---|---|---|
| P4172 | Falco, companion to P4003 (2026). Argues senders suit DAG-shaped work while byte-oriented I/O is chain-shaped — the source of the graph/chain test on the adoption slide | https://wg21.link/P4172 |
| P4029 | Wong, "The SG14 Priority List for C++29/32" (Feb 2026). SG14 advises networking should **not** be built on P2300 — allocation patterns incompatible with low-latency requirements — and recommends P4003 "Direct Style" I/O as the C++29 networking model instead. Answered in the adoption slide's notes | https://wg21.link/P4029 |

## Not cited but relevant

| Paper | Why it matters | Link |
|---|---|---|
| P3300 | Lelbach, "C++ Asynchronous Parallel Algorithms" — §6.1 is the source of the "dynamic asynchrony" concern P4320 cites against `let_value` | https://wg21.link/P3300 |

**Capy / Corosio, if the graph-vs-chain line comes up.** Capy (cppalliance/capy) is the library
P4003 is drawn from: coroutine task type, byte streams, type-erased streams, and concurrency
facilities including `when_all`, `when_any`, executors, strands and thread pools, with executor
affinity propagated through every `co_await`. CERN's traccc uses it for GPU reconstruction
pipelines. Corosio is the networking layer built on it. So coroutine libraries do fan out across
contexts, and they are on GPUs — don't claim graph-shaped work is sender-only.

**Primary sources beat citations.** P4041 reproduces Sutter's Citadel production quote but omits
the following sentence — that it was possible because they ran their own in-house implementation
for years. Original: herbsutter.com, 23 April 2025, "Living in the future: Using C++26 at work".

---

## Where each appears in the deck

- **On slides:** P2300, P2762, P2849, P3149, P3284, P3481, P3482, P3552, P3682, P3955, P4003,
  P4007, P4014, P4100, P4154, P4320, P2079, N2175, N3721, P0443
- **Speaker notes only:** P1662, P3175, P2444, P2464, P4029, P4041, P4172
