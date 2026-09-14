# Timing plan — *The Async Model is Here. Bring Your Own I/O (for now)*

NWCPP, 17 September 2026

**Assumptions:** 60-minute slot. 50 minutes to reach the Questions slide, 10 minutes of Q&A.
Demo held to its 8-minute hard timebox. If the slot differs, rescale the section budget
first — the three-minute checkpoints fall out of it.

Deck is **33 main slides** in four sections, plus a 6-slide appendix (`A` toggles).

---

## Section budget — the gates that matter

| Section | Slides | Budget | Gate: be here by |
|---|---|---|---|
| Open | 1–3 | 3.5 min | — |
| 01 The Problem | 4–7 | 6.5 min | **slide 8 by 10:00** |
| 02 The Model (incl. demo) | 8–16 | 21 min | **slide 17 by 31:00** |
| 03 The Ecosystem | 17–21 | 5.5 min | **slide 22 by 36:00** |
| 04 The Gap | 22–27 | 8.5 min | **slide 28 by 46:00** |
| Close | 28–31 | 4 min | **Q&A by 50:00** |

Four gates. Hit 31:00 entering the ecosystem section and everything downstream works.

Section 02 is the long one — nine slides, of which one is a divider and one is the demo.
**The arithmetic is tight:** an 8-minute demo starting at 23:00 closes exactly on the 31:00
gate, which leaves ~12.5 minutes for the seven content slides — about 1.8 minutes each.
That is achievable but has no slack in it, which is precisely why the demo is the first cut.
Drop it and those seven slides get 20 minutes, which is comfortable.

The two rebuttals (12 and 15) are the densest of the seven and the two you must not cut.
Budget them ~2 minutes each and take the time out of 10 and 14, which are the most compressible.

---

## Checkpoints

Three minutes apart, except through section 02, where every slide gets its own row — a
three-minute grid there hides a squeeze. Each row is when you should be *arriving* at that
slide, so the interval to the next row is that slide's budget.

| Time | Should be on |
|---|---|
| 0:00 | 1 — Title |
| 3:00 | 4 — §01 divider |
| 6:00 | 6 — Why `std::future` isn't the model |
| 9:00 | 7 — What about coroutines |
| 10:20 | 9 — The model (concepts) |
| 12:00 | 10 — The vocabulary |
| 13:30 | 11 — Putting it together |
| 15:30 | 12 — Isn't then just the callback |
| 17:30 | 13 — Two patterns |
| 19:30 | 14 — Structured concurrency |
| 21:00 | 15 — Just do it in a destructor |
| 23:00 | **16 — Demo starts** |
| 27:00 | 16 — Demo, ~4 min in |
| 30:00 | 16 — Demo, ~7 min in |
| 33:00 | 19 — Stdlib situation |
| 36:00 | 22 — §04 divider |
| 39:00 | 25 — The bridge |
| 42:00 | 26 — Operation state |
| 45:00 | 27 — Before you wrap |
| 48:00 | 30 — Summary |
| 50:00 | 31 — Questions |

---

## What the numbers imply about delivery

- **The demo is the relief valve.** It closes section 02 and nothing downstream depends on
  it. If you reach slide 16 past 28:00, skip it and offer it at the end if questions run short.
- **Slide 26 gets three minutes** — more than any other non-demo slide, deliberately. If you're
  at 42:00 when you reach it, take the full three.
- **Dividers are 20 seconds.** Breath, not content.
- **Slides 12 and 15 are the reason for the talk.** They answer two of the four objections from
  slide 3. If section 02 runs long, compress slides 9 and 10 — the concepts and the vocabulary — not these.
- **Section 02 has no mid-section divider** — nine slides straight through. Watch for the room
  flagging around slide 11, the first code, and use the rebuttals that follow it to re-engage
  them; they're argumentative, which reads as a change of pace.

---

## If you're behind at a gate

Cut in this order. Cut *content*, not pace — talking faster is how you lose a room.

1. **The demo (16)** — defer to the end. Biggest single block of time and fully optional.
2. **Slide 18 (timeline)** — down to 60 seconds. Three rows and the band, skip the rest.
3. **Slide 21 (Beman)** — 30 seconds: early, watch it, and the TAPS point.
4. **Slide 28 (adoption by workload)** — fold into the summary.
5. **Slide 24 (platform picture)** — headline only, skip the matrix.

That's the demo plus about three minutes, without touching the argument.

**Do not cut:** slides 12 and 15 (the two rebuttals), or slides 25 and 26 (the wrapping code).

**Already cut:** the operation-state nesting diagram, now Appendix C.

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
