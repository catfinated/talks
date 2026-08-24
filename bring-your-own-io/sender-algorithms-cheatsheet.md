# std::execution — Sender Algorithm Cheat Sheet (C++26)

Verified August 2026 against the C++26 draft clauses ([exec.*]), `NVIDIA/stdexec`
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
| `split(sndr)` | Single-shot → multi-shot: many consumers, work runs once | (✓)¹ | ✓ |
| `bulk(sndr, pol, shape, f)` | Parallel loop over `[0, shape)` under an execution policy | (✓)² | ✓ |
| `bulk_chunked` / `bulk_unchunked` | `bulk` variants with explicit chunking control (P3481) | — | ✓ |
| `write_env(sndr, env)` | Run child with additional environment entries | ✓ | ✓ |
| `unstoppable(sndr)` | Hide stop requests from the child — a cancellation firewall | ✓ | ✓ |
| `stop_when(sndr, token)` | Also request stop when an external token fires | ✓ | ✓ |
| `affine` | Scheduler-affinity adaptor used by `task` to return to its scheduler (P3552) | ✓ | ✓ |

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
| `ensure_started` | *removed* | use `counting_scope` + `spawn_future`; survives as `exec::ensure_started` |
| `start_detached` | *removed* | use `spawn`; survives as `exec::start_detached` |
| `execute` | *removed* | |
| `bulk(sndr, shape, f)` | `bulk(sndr, pol, shape, f)` | execution policy added by P3481 |

## Notable stdexec-only extensions (`exec::`, no standard equivalent)

| Facility | What it does |
|---|---|
| `async_scope` | Pre-standard ancestor of `counting_scope` (the deck's examples use it) |
| `when_any(sndrs...)` | First completion wins; the rest are cancelled |
| `repeat_effect_until` / `repeat_n` | Looping combinators |
| `finally(sndr, cleanup)` | Unconditional async cleanup (async RAII)³ |
| `any_sender_of<Sigs...>` | Type-erased sender (this is an allocation point) |
| `into_tuple(sndr)` | Pack all values into one tuple value |
| `create(fn)` | Build a sender from a callback-style initiation function — handy for wrapping |
| `static_thread_pool` | Concrete fixed-size thread-pool scheduler |
| `io_uring_context` | Linux io_uring run context — timers/scheduling only, no read/write ops |
| `libdispatch_queue` | Apple Grand Central Dispatch scheduler |
| `single_thread_context`, `timed_thread_scheduler`, `trampoline_scheduler` | Assorted single-thread / timed / stack-safe contexts |

---

**Footnotes**

1. stdexec currently ships `split` as an `exec::` extension rather than in
   `stdexec::`; Beman implements the standard `[exec.split]` version.
2. stdexec's `bulk` still has the pre-P3481 shape (no policy parameter, no
   chunked variants).
3. `finally` appears in stdexec's standard-track namespace but is **not** in
   C++26.

**Caveats.** Beman self-reports "under development, not ready for production";
its status doc shows a few items (bulk, sync_wait, task, scopes, spawn) as
implemented and tested but with review/documentation still catching up. stdexec
remains experimental with ongoing API churn. Verify against each repo before
relying on a specific spelling — this sheet reflects August 2026.
