#lang racket

(define (pow-x x)
  (let loop ((current x))
    (stream-cons current (loop (* current x)))
    )
  )

(stream->list (stream-take (pow-x 2) 5))