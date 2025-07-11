#lang racket

(define (f L1 L2)
  (map (λ (x) (cons x (filter (λ (y) (= (modulo y x) 0)) L2))) L1))