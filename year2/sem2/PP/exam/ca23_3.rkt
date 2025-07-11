#lang racket
(define (mean L)
  (let*
      (
       (sum-n-pair (foldl (λ (x acc) (cons (+ x (car acc)) (list (+ (car (cdr acc)) 1)))) '(0 0) L))
       )
    (/ (car sum-n-pair) (cadr sum-n-pair))
      )
  )

(mean '(1 2 3 4 5))