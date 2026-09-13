# std::execution — Sender Algorithm Cheat Sheet (C++26)

Verified 13 September 2026 against the C++26 draft clauses ([exec.*]), `NVIDIA/stdexec`
(main), and `bemanproject/execution` (main).

**Namespaces:** standard entities live in `std::execution` (except `sync_wait`,
which is in `std::this_thread`). stdexec puts standard-track entities in
`stdexec::` and extensions in `exec::`. Beman uses `beman::execution::`.

**Column key:** ✓ implemented · (✓) implemented with caveat in footnote · — not available.

---

## Sender factories — start a pipeline

| Algorithm | What it does | stdexec | Beman |
|---|---|---|---|
| `just(vs...)` | Completes immediately with the given values | ✓ | ✓ |
| `just_error(e)` | Completes immediately on the error channel | ✓ | ✓ |
| `just_stopped()` | Completes immediately on the stopped channel | ✓ | ✓ |
| `schedule(sch)` | Completes (with nothing) on the scheduler's execution context — the root of most pipelines | ✓ | ✓ |
| `read_env(query)` | Completes with a value read from the receiver's environment (e.g. `get_stop_token`) | ✓ | ✓ |

## Sender adaptors — transform and compose

| Algorithm | What it does | stdexec | Beman |
|---|---|---|---|
| `then(sndr, f)` | Transform the value(s) with an ordinary function | ✓ | ✓ |
| `upon_error(sndr, f)` | Transform an error into a value (recovery) | ✓ | ✓ |
| `upon_stopped(sndr, f)` | Turn cancellation into a value | ✓ | ✓ |
| `let_value(sndr, f)` | `f` returns a **sender**; chains a dependent async step | ✓ | ✓ |
| `let_error(sndr, f)` | Async recovery: error → new sender | ✓ | ✓ |
| `let_stopped(sndr, f)` | Async fallback on cancellation | ✓ | ✓ |
| `starts_on(sch, sndr)` | Run the whole sender on `sch` | ✓ | ✓ |
| `continues_on(sndr, sch)` | Resume everything downstream on `sch` | ✓ | ✓ |
| `on(sch, sndr)` | Round trip: run `sndr` on `sch`, then return to the original scheduler (P3175) | ✓ | ✓ |
| `schedule_from(sch, sndr)` | Customization point underlying `continues_on`; rarely called directly | ✓ | ✓ |
| `when_all(sndrs...)` | Run concurrently; join into one completion. First error/stop cancels the rest | ✓ | ✓ |
| `when_all_with_variant(...)` | `when_all` over senders with multiple value signatures | ✓ | ✓ |
| `into_variant(sndr)` | Collapse multiple value signatures into one `variant<tuple<...>...>` value | ✓ | ✓ |
| `stopped_as_optional(sndr)` | Stopped → value channel as empty `optional` | ✓ | ✓ |
| `stopped_as_error(sndr, e)` | Stopped → error channel with your error | ✓ | ✓ |
| `bulk(sndr, pol, shape, f)` | Parallel loop over `[0, shape)` under an execution policy | (✓)¹ | ✓ |
| `bulk_chunked` / `bulk_unchunked` | `bulk` variants with explicit chunking control (P3481) | — | ✓ |
| `write_env(sndr, env)` | Run child with additional environment entries | ✓ | ✓ |
| `unstoppable(sndr)` | Hide stop requests from the child — a cancellation firewall | ✓ | ✓ |
| `stop_when(sndr, token)` | Also request stop when an external token fires | ✓ | ✓ |
| `affine` | Scheduler-affinity adaptor used by `task` to return to its scheduler. Redesigned and made unary by P3941R4; renamed from `affine_on` by P4151R1 | ✓ | ✓ |

## Sender consumers — leave sender-land

| Algorithm | What it does | stdexec | Beman |
|---|---|---|---|
| `this_thread::sync_wait(sndr)` | Block until done; `optional<tuple<Vs...>>` (empty = stopped, errors rethrow). Requires exactly one value signature | ✓ | ✓ |
| `this_thread::sync_wait_with_variant(sndr)` | Same, for senders with multiple value signatures | ✓ | ✓ |

## Structured concurrency scopes (P3149)

| Facility | What it does | stdexec | Beman |
|---|---|---|---|
| `counting_scope` | Tracks spawned work; join it before the scope dies | ✓ | ✓ |
| `simple_counting_scope` | Same, minus stop-request support | ✓ | ✓ |
| `spawn(sndr, tok)` | Fire-and-forget into a scope (this is where allocation is opt-in) | ✓ | ✓ |
| `spawn_future(sndr, tok)` | Spawn eagerly, get a sender for the result | ✓ | ✓ |
| `associate(sndr, tok)` | Tie a sender's lifetime to a scope without starting it | ✓ | ✓ |

## Coroutine integration (P2300 + P3552)

| Facility | What it does | stdexec | Beman |
|---|---|---|---|
| `task<T, Env>` | Standard coroutine task type; `co_await` senders inside | ✓ | ✓ |
| `task_scheduler` | Type-erased scheduler for `task` environments | ✓ | ✓ |
| `as_awaitable(sndr)` | Make any sender awaitable in a coroutine | ✓ | ✓ |
| `with_awaitable_senders<P>` | Promise-base that lets a coroutine await senders | ✓ | ✓ |

## Schedulers & contexts in the standard

| Facility | What it does | stdexec | Beman |
|---|---|---|---|
| `run_loop` | Single-threaded manually-driven context (what `sync_wait` uses) | ✓ | ✓ |
| `parallel_scheduler` / `get_parallel_scheduler()` | The standard system-provided parallel context (P2079) | ✓ | ✓ |

---

## Renamed or removed on the way to C++26

| Old (pre-R10 / early drafts) | C++26 | Notes |
|---|---|---|
| `transfer` | `continues_on` | stdexec's older releases spell it `transfer` |
| `on` (old meaning) | `starts_on` | `on` now names the P3175 round-trip adaptor |
| `read` | `read_env` | |
| `tag_invoke` customization | member functions | changed in P2300R10, the adopted revision |
| `sender_t` / `receiver_t` / `scheduler_t` / `operation_state_t` | `sender_tag` / `receiver_tag` / `scheduler_tag` / `operation_state_tag` | renamed by P4154R0, Croydon 2026-03. stdexec keeps the `_t` spellings as backwards-compatibility aliases |
| `ensure_started` | *removed* | use `counting_scope` + `spawn_future`; survives as `exec::ensure_started` |
| `start_detached` | *removed* | use `spawn`; survives as `exec::start_detached` |
| `execute` | *removed* | |
| `split` | *removed* | P3682R0, adopted at Sofia 2025-06. Survives as `exec::split` in stdexec |
| `bulk(sndr, shape, f)` | `bulk(sndr, pol, shape, f)` | execution policy added by P3481 |

## Notable stdexec-only extensions (`exec::`, no standard equivalent)

| Facility | What it does |
|---|---|
| `async_scope` | Pre-standard ancestor of `counting_scope` (the deck's examples use it) |
| `when_any(sndrs...)` | First completion wins; the rest are cancelled |
| `repeat` / `repeat_until` / `repeat_n` | Looping combinators. `repeat_effect` / `repeat_effect_until` are deprecated aliases; `<exec/repeat_effect_until.hpp>` warns and forwards to `<exec/repeat_until.hpp>`. Needs the child sender to be copyable **or** lvalue-connectable — type-erased senders are neither, so erase a sender *factory* instead |
| `finally(sndr, cleanup)` | Unconditional async cleanup (async RAII)² |
| `any_sender_of<Sigs...>` | Type-erased sender (this is an allocation point) |
| `sequence(sndrs...)` | Run senders one after another — serial composition, the basis of P4320. **Not** a stream abstraction |
| `sequence_senders` | The actual stream abstraction: `set_next`, plus `iterate` / `transform_each` / `ignore_all_values` / `merge_each` / `any_sequence_of` under `exec/sequence/`. Very experimental; open stop-propagation issues through type-erased sequences. No standards paper |
| `into_tuple(sndr)` | Pack all values into one tuple value |
| `create(fn)` | Build a sender from a callback-style initiation function — handy for wrapping |
| `static_thread_pool` | Concrete fixed-size thread-pool scheduler |
| `io_uring_context` | Linux io_uring run context — timers/scheduling only, no read/write ops |
| `libdispatch_queue` | Apple Grand Central Dispatch scheduler |
| `single_thread_context`, `timed_thread_scheduler`, `trampoline_scheduler` | Assorted single-thread / timed / stack-safe contexts |

---

**Footnotes**

1. stdexec's `bulk` still has the pre-P3481 shape (no policy parameter, no
   chunked variants).
2. `finally` appears in stdexec's standard-track namespace but is **not** in
   C++26. It was proposed alongside `write_env` and `unstoppable` in P3284R0/R1,
   then cut: from R2 the paper is titled for the other two only, and R4 — the
   adopted revision — carries just `write_env` and `unstoppable`.

**Attribution.** Some material adapted from P4014R2, "The Sender Sub-Language For
Beginners" (Vinnie Falco, Mungo Gill, 2026), dedicated to the public domain under
CC0 1.0 — <https://wg21.link/P4014>. That paper covers all thirty C++26 sender
algorithms with a worked example and a plain-C++ equivalent for each; §2.4 maps
each algorithm to its theoretical origin. Recommended for depth, with the note
that its authors also advocate a coroutine-native alternative.

**Caveats.** Beman self-reports "under development, not ready for production";
its status doc shows a few items (bulk, sync_wait, task, scopes, spawn) as
implemented and tested but with review/documentation still catching up. stdexec
remains experimental with ongoing API churn. Verify against each repo before
relying on a specific spelling — this sheet reflects August 2026.
