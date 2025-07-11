#lang racket

(define (ff L)
  (let loop ((L L) (result '()))
    (if (or (null? L) (null? (cdr L)))
        (append (reverse result) L)
        (loop (cddr L) (cons (max (car L) (cadr L)) result)))))
              