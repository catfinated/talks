# Timing plan — *The Async Model is Here. Bring Your Own I/O (for now)*

NWCPP, 17 September 2026

**Assumptions:** 60-minute slot. 50 minutes to reach the Questions slide, 10 minutes of Q&A.
Demo held to its 8-minute hard timebox. If the slot differs, rescale the section budget
first — the three-minute checkpoints fall out of it.

Deck is **34 main slides** in four sections, plus a 5-slide appendix (`A` toggles).

---

## Section budget — the gates that matter

| Section | Slides | Budget | Gate: be here by |
|---|---|---|---|
| Open | 1–3 | 3.5 min | — |
| 01 The Problem | 4–7 | 6.5 min | **slide 8 by 10:00** |
| 02 The Model (incl. demo) | 8–16 | 21 min | **slide 17 by 31:00** |
| 03 The Ecosystem | 17–21 | 5.5 min | **slide 22 by 36:00** |
| 04 The Gap | 22–28 | 10 min | **slide 29 by 46:00** |
| Close | 29–32 | 4 min | **Q&A by 50:00** |

Four gates. Hit 31:00 entering the ecosystem section and everything downstream works.

Section 02 is now the long one — nine slides and the demo. It is also where your slack
lives, because the demo can be deferred.

---

## Three-minute checkpoints

| Time | Should be on |
|---|---|
| 0:00 | 1 — Title |
| 3:00 | 4 — §01 divider |
| 6:00 | 6 — Why `std::future` isn't the model |
| 9:00 | 7 — What about coroutines |
| 12:00 | 9 — Three abstractions |
| 15:00 | 10 — Three channels |
| 18:00 | 12 — Two patterns |
| 21:00 | 13 — Structured concurrency |
| 24:00 | 15 — Just do it in a destructor |
| 27:00 | 16 — Demo, ~2 min in |
| 30:00 | 16 — Demo, ~5 min in |
| 33:00 | 19 — Stdlib situation |
| 36:00 | 22 — §04 divider |
| 39:00 | 25 — The bridge |
| 42:00 | 26 — Operation state |
| 45:00 | 28 — Before you wrap |
| 48:00 | 31 — Summary |
| 50:00 | 32 — Questions |

---

## What the numbers imply about delivery

- **The demo is the relief valve.** It closes section 02 and nothing downstream depends on
  it. If you reach slide 16 past 28:00, skip it and offer it at the end if questions run short.
- **Slide 26 gets three minutes** — more than any other non-demo slide, deliberately. It's the
  material nobody else can present. If you're at 42:00 when you reach it, take the full three.
- **Dividers are 20 seconds.** Breath, not content.
- **Slides 14 and 15 are the reason for the talk.** They answer two of the four objections from
  slide 3. If section 02 runs long, compress slide 9, not these.
- **Section 02 has no mid-section divider** — nine slides straight through. Watch for the room
  flagging around slide 12 and use the two rebuttals to re-engage them; they're argumentative,
  which reads as a change of pace.

---

## If you're behind at a gate

Cut in this order. Cut *content*, not pace — talking faster is how you lose a room.

1. **The demo (16)** — defer to the end. Biggest single block of time and fully optional.
2. **Slide 18 (timeline)** — down to 60 seconds. Three rows and the band, skip the rest.
3. **Slide 21 (Beman)** — 30 seconds: early, watch it, and the TAPS point.
4. **Slide 29 (adoption by workload)** — fold into the summary.
5. **Slide 24 (platform picture)** — headline only, skip the matrix.

That's the demo plus about three minutes, without touching the argument.

**Do not cut:** slides 14 and 15 (the two rebuttals) or slide 26.

---

## Rehearsal method

- Time each section separately before timing the whole thing. A full run tells you you're four
  minutes over; sectional timings tell you where.
- Run the demo standalone at least three times against a stopwatch. It's the only segment
  where the clock isn't fully under your control.
- Take the hand-count on slide 3 (who has *written* code against stdexec, libunifex, or Asio's
  sender adaptation). It tells you how fast to take section 02.
- Rehearse the section-02 run without the demo at least once, so deferring it feels routine
  rather than like a failure.

---

## Pre-talk checklist

- [ ] Re-check the cppreference C++26 "Execution control library" row; update the date stamp
      on slide 19
- [ ] Pin the stdexec commit in `demo/CMakeLists.txt`, rebuild, re-rehearse — in that order
- [ ] Run `./run_all.sh` on the **presentation laptop**, not a dev box
- [ ] Decide at setup: local terminal or Compiler Explorer (the slide names neither)
- [ ] Make the talks repo public (references slide and cheatsheet links depend on it)
- [ ] Confirm the cheatsheet is pushed and its link resolves
- [ ] Open the deck with real fonts loaded; confirm no slide counter turns orange
