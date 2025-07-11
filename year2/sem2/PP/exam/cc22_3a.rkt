#lang racket

(define (f L1 L2)
  (map (λ (x) (cons x (filter (λ (y) (= (modulo x y) 0)) L2))) L1))
(f '(25 30 100) '(2 3 5))