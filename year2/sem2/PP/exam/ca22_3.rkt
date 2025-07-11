#lang racket

(define (cartesian-app functions values)
  (foldr append '()
         (map (λ (f) (map f values)) functions)
         )
  )