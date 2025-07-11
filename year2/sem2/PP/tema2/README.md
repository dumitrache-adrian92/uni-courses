This is a priority queue based on binomial heaps written in Haskell.

An imperative style priority queue relies on O(1) array operations for
efficiency. Array operations are way slower in Haskell, so using a binomial
heap is a better choice, since it relies on O(log n) tree operations. This
includes tree merging, meaning that it can be done faster than in a classic
implementation.

Loved working on this! It made me realize that functional languages might be
something that I want to work professionally with in the future.
