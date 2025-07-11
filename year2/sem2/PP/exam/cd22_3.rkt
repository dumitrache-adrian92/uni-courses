#lang racket

(define f (λ (functions)
            (λ (values)
              (map (λ (func val) (func val)) functions values)
              )
            )
  )