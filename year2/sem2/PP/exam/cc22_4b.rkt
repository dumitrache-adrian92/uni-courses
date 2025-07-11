#lang racket

(define b (λ (f g L)
            (map g (filter (compose f g) L))))