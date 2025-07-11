#lang racket

(define (n-times-n n)
  (let loop ((ecx n) (result '()))
    (if (zero? ecx)
        result
        (loop (sub1 ecx) (cons n result))
        )
    )
  )