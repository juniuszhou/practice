; command scheme to launch interpretor
; input (load "dataType.scm")

;boolean type
(newline)
(define b (eq? 1 2))
(display b)

;integer
(newline)
(define i (+ 1 2))
(display i)

;char
(newline)
(define c #\c)
(display c)

;symbol
(newline)
(define s 'ERROR_NUMBER_ZERO)
(display s)
(newline)
(display (symbol? s))

;string
(newline)
(define str "Hello; Hello!")
(display str)

;vector
(newline)
(define v (make-vector 6))
(vector-set! v 0 "kimois")
(display v)
(newline)
(display (vector-ref v 0))

;pair and list
(newline)
(define p (cons 6 "six"))
(display (cons p (cons (car p) (cdr p))))

;list a special pair, following example
;(1 . (2 . (3 . (4 . ())))) equals (1 2 3 4)















