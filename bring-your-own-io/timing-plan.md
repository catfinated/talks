# Timing plan — *The Async Model is Here. Bring Your Own I/O (for now)*

NWCPP, 17 September 2026

**Assumptions:** 60-minute slot. 50 minutes to reach the Questions slide, 10 minutes of Q&A.

Deck is **30 main slides** (plus two references slides behind Q&A) in four sections, with a
6-slide appendix on the `A` key. **The live demo is cut** — the buildable project is in the repo
and the references slide points at it.

---

## Section budget — the gates that matter

| Section | Slides | Budget | Gate: be here by |
|---|---|---|---|
| Open | 1–3 | 3.5 min | — |
| 01 The Problem | 4–7 | 6.5 min | **slide 8 by 10:00** |
| 02 The Model | 8–15 | 14 min | **slide 16 by 24:00** |
| 03 The Ecosystem | 16–22 | 10 min | **slide 23 by 34:00** |
| 04 The Bridge | 23–29 | 14 min | **Q&A by 50:00** |
| Q&A | 30 | 10 min | — |

Cutting the demo bought 8 minutes and they are spread across the three content sections,
so nothing is now squeezed. Section 02's seven content slides get 2 minutes each instead
of 1.8; §04's six get just over 2.

---

## Checkpoints

Each row is when you should be *arriving* at that slide, so the interval to the next row is
that slide's budget.

| Time | Should be on |
|---|---|
| 0:00 | 1 — Title |
| 3:30 | 4 — §01 divider |
| 6:00 | 6 — Why `std::future` isn't the model |
| 8:00 | 7 — What about coroutines |
| 10:00 | 8 — §02 divider |
| 10:20 | 9 — The model (concepts) |
| 12:20 | 10 — The vocabulary |
| 14:00 | 11 — Putting it together |
| 16:30 | 12 — Two patterns |
| 18:30 | 13 — Structured concurrency |
| 20:00 | 14 — Isn't then just the callback |
| 22:00 | 15 — Just do it in a destructor |
| 24:00 | 16 — §03 divider |
| 24:20 | 17 — The road to P2300 |
| 26:00 | 18 — Stdlib situation |
| 28:00 | 19 — NVIDIA stdexec |
| 29:30 | 20 — Beman |
| 31:00 | 21 — P2300 excludes I/O |
| 32:30 | 22 — Platform picture |
| 34:00 | 23 — §04 divider |
| 34:20 | 24 — Adoption is workload-dependent |
| 37:00 | 25 — The bridge |
| 39:30 | 26 — Operation state |
| 42:30 | 27 — Before you wrap |
| 45:00 | 28 — Sutter |
| 47:00 | 29 — Summary |
| 50:00 | 30 — Questions |

---

## What the numbers imply about delivery

- **Slide 26 (operation state) gets three minutes** — the most of any slide, deliberately. It's
  the material nobody else can present.
- **Dividers are 20 seconds.** Breath, not content.
- **Slides 14 and 15 are the reason for the talk.** They answer two of the four objections from
  slide 3. If §02 runs long, compress 10 and 14, not these.
- **Section 03 is the fast one.** Six content slides in 10 minutes, and none needs dwelling on —
  it's the survey that earns the recommendation in §04.
- **Section 02 has no divider in the middle** — seven slides straight through. Watch for the room
  flagging around slide 11, the first code, and use the two rebuttals that close the section to re-engage.

---

## If you're behind at a gate

Cut *content*, not pace — talking faster is how you lose a room.

1. **Slide 17 (timeline)** — down to 60 seconds. Three rows and the band, skip the rest.
2. **Slide 20 (Beman)** — 30 seconds: early, watch it, and the TAPS point.
3. **Slide 24 (adoption by workload)** — fold its conclusion into the summary.
4. **Slide 22 (platform picture)** — headline only, skip the matrix.
5. **Slide 19 (stdexec)** — name the three things it gives you and move on.

About five minutes without touching the argument.

**Do not cut:** slides 14 and 15 (the two rebuttals), or slides 25 and 26 (the wrapping code).

**Already cut:** the live demo, and the operation-state nesting diagram (now Appendix C).

---

## Rehearsal method

- Time each section separately before timing the whole thing. A full run tells you you're four
  minutes over; sectional timings tell you where.
- Take the hand-count on slide 3 (who has *written* code against stdexec, libunifex, or Asio's
  sender adaptation). It tells you how fast to take section 02.
- The 8 minutes the demo used to take is now slack. Resist spending it on slide 9 or 10 —
  those are the compressible ones and they will absorb time if you let them.

---

## Pre-talk checklist

- [ ] Re-check the cppreference C++26 "Execution control library" row; update the date stamp
      on slide 18
- [ ] Make the talks repo public — the cheatsheet link, the demo project and the references
      slide all depend on it
- [ ] Confirm the cheatsheet and `demo/` both resolve from the links on screen
- [ ] Re-verify the paper numbers on slide 17 against wg21.link
- [ ] Open the deck with real fonts loaded; confirm no slide counter turns orange
