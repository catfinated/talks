# The Async Model is Here. Bring Your Own I/O (for now)

A talk on C++26's `std::execution` (P2300) from a user and implementer
perspective: the model, the ecosystem, and the I/O gap the standard
deliberately left open.

**[Northwest C++ Users' Group](https://nwcpp.org/) — 17 September 2026**

## The talk

I've built a lot of async infrastructure over my career — I/O and compute
schedulers both. I also followed the executor proposals for a while, and tuned
out when they missed C++20, then C++23. An io_uring scheduler came during that
gap, designed without reference to senders.

Leahy's *std::execution in Asio Codebases* (CppCon 2025) pulled me back in. This
talk is what I found holding that infrastructure up against P2300 — what the
model gives you, what the ecosystem actually ships, and why the standard async
model arrived without any async I/O in it.

It also takes a few objections from colleagues seriously enough to answer them:
that it's too hard to use, that the pipes are sugar over callbacks, and that
cancellation and cleanup can live in destructors.

## What's here

| File | |
|---|---|
| [`index.html`](index.html) | The slides. Self-contained — open it in a browser, no build step. |
| [`sender-algorithms-cheatsheet.md`](sender-algorithms-cheatsheet.md) | Every sender algorithm with signatures, gotchas, and stdexec/Beman availability. Also as [PDF](sender-algorithms-cheatsheet.pdf). |
| [`timing-plan.md`](timing-plan.md) | Section budgets and checkpoints for delivering it in a 60-minute slot. |

### Viewing the slides

| Key | |
|---|---|
| `←` `→` | navigate |
| `F` | fullscreen |
| `N` | speaker notes — the detail that didn't fit on the slides |
| `A` | appendix — reference material held back for Q&A |

## Related

- [catfinated/fiberexec](https://github.com/catfinated/fiberexec) — my research
  runtime: io_uring under fibers under senders. The cancellation flow diagrammed
  in the talk is its actual behaviour.
- [NVIDIA/stdexec](https://github.com/NVIDIA/stdexec) — the reference
  implementation, and what you'd experiment with today.

---

Views are my own; this is personal research, not the work or views of my employer.

Research and slides prepared with AI assistance. Claims are checked against
primary sources — papers, standard wording, and vendor status pages — cited
throughout. Ecosystem and vendor-status claims are stamped with the date they
were checked and will age; the cheatsheet was verified August 2026.
