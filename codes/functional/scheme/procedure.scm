; command scheme to launch interpretor
; input (load "procedure.scm")

;lambda procedure
;directly define and call lambda func
(newline)
(display ((lambda (x) (+ x 2) ) 3))

;define a func then call it
(newline)
(define add 
		(lambda (x y)
		 (+ x y)
		 )
)
(display (add 3 4))

;apply a func to all items in a list
(newline)
(define v '(1 2 3 4))
(display (apply + v))





