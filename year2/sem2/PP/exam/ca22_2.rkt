#lang racket
(define (multicompose n f)
  (let recursion ((left n))
    (if (zero? left)
        identity
        (compose f (recursion (sub1 left)))
        )
    )
  )