#lang racket

(define a (λ (f g L)
            (map g (filter f L))
            )
  )