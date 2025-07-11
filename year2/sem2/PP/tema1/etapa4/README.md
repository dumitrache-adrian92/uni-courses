A solution to the [Stable Marriage Problem](https://en.wikipedia.org/wiki/Stable_marriage_problem)
written in Racket using the Gale-Shapley algorithm. It was my introduction to
writing functional code and the reason I started liking it lol. Learned tail recursion, streams and so many other things doing this.

Sample usage:
```racket
; mpref = male preferences, list of lists in the format '(male female1 female2 ...)
; wpref = female preferences, list of lists in the format '(female male1 male2 ...)
(gale-shapley mpref wpref) ; returns a list of stable engagements
(update-stable-match engagements mpref wpref) ; updates the engagements list    according to new preferences
```