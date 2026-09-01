# Timing plan — *The Async Model is Here. Bring Your Own I/O (for now)*

NWCPP, 17 September 2026

**Assumptions:** 60-minute slot. 50 minutes to reach the Questions slide, 10 minutes of Q&A.
Demo held to its 8-minute hard timebox. If the slot differs, rescale the section budget
first — the three-minute checkpoints fall out of it.

---

## Section budget — the gates that matter

| Section | Slides | Budget | Gate: be here by |
|---|---|---|---|
| Open | 1–3 | 3.5 min | — |
| 01 The Problem | 4–7 | 6.5 min | **slide 8 by 10:00** |
| 02 The Model | 8–12 | 10 min | **slide 13 by 20:00** |
| 03 The API (incl. demo) | 13–17 | 11 min | **slide 18 by 31:00** |
| 04 The Ecosystem | 18–22 | 5.5 min | **slide 23 by 36:00** |
| 05 The Gap | 23–28 | 9.5 min | **slide 29 by 46:00** |
| Close | 29–32 | 4 min | **Q&A by 50:00** |

The four bolded gates are what you actually check against. Hit 31:00 entering section 04
and everything downstream works.

---

## Three-minute checkpoints

| Time | Should be on |
|---|---|
| 0:00 | 1 — Title |
| 3:00 | 4 — §01 divider |
| 6:00 | 6 — Why `std::future` isn't the model |
| 9:00 | 7 — What about coroutines |
| 12:00 | 9 — The vocabulary |
| 15:00 | 10 — Three channels |
| 18:00 | 12 — Just do it in a destructor |
| 21:00 | 15 — Two patterns |
| 24:00 | 17 — Demo, ~1 min in |
| 27:00 | 17 — Demo, ~4 min in |
| 30:00 | 18 — §04 divider |
| 33:00 | 20 — Stdlib situation |
| 36:00 | 23 — §05 divider |
| 39:00 | 26 — The bridge |
| 42:00 | 27 — Operation state |
| 45:00 | 28 — Before you wrap |
| 48:00 | 31 — Summary |
| 50:00 | 32 — Questions |

---

## What the numbers imply about delivery

- **The demo now closes section 03**, so every algorithm in its "things to try" list has
  already been introduced. It's a synthesis, not a first taste — and it's the last thing
  before the ecosystem section, so it should land as a payoff.
- **Slide 27 gets three minutes** — more than any non-demo slide, deliberately. It's the
  material nobody else can present. If you're at 42:00 when you reach it, take the full three.
- **Dividers are 20 seconds each.** Breath, not content.
- **Section 02 is five slides in ten minutes** — vocabulary, three channels, and the two
  rebuttals. The rebuttals are the reason for the talk; if the section runs long, compress
  the vocabulary slide, not them.
- **The demo is your variance.** Everything before it is recoverable; a demo that runs to 12
  minutes eats the I/O section. Use the fallback ladder at 8:00 regardless of where you are.

---

## If you're behind at a gate

Cut in this order. Cut *content*, not pace — talking faster is how you lose a room.

1. **Slide 19 (timeline)** — down to 60 seconds. Read three rows and the band, skip the rest.
2. **Slide 22 (Beman)** — 30 seconds. One sentence: early, watch it, and the TAPS point.
3. **Slide 29 (adoption by workload)** — fold into the summary.
4. **Slide 25 (platform picture)** — say the headline, skip the matrix.

About three minutes of slack without touching the argument.

**Do not cut under time pressure:** slides 11 and 12 (the two rebuttals — the reason for
giving this talk) or slide 27.

---

## Rehearsal method

- Time each section separately before timing the whole thing. A full run tells you you're four
  minutes over; sectional timings tell you where.
- Run the demo standalone at least three times against a stopwatch. It's the only segment
  where the clock isn't fully under your control.
- Take the hand-count on slide 3 (who has *written* code against stdexec, libunifex, or Asio's
  sender adaptation). It tells you how fast to take section 02.

---

## Pre-talk checklist

- [ ] Re-check the cppreference C++26 "Execution control library" row; update the date stamp
      on slide 20
- [ ] Pin the stdexec commit in `demo/CMakeLists.txt`, rebuild, re-rehearse — in that order
- [ ] Run `./run_all.sh` on the **presentation laptop**, not a dev box
- [ ] Decide at setup: local terminal or Compiler Explorer (the slide names neither)
- [ ] Make the talks repo public (references slide and cheatsheet links depend on it)
- [ ] Confirm the cheatsheet is pushed and its link resolves
- [ ] Open the deck with real fonts loaded; confirm no slide counter turns orange
