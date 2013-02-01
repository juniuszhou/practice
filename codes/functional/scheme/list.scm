; command scheme to launch interpretor
; input (load "list.scm")


(display (cons "hello" "world!"))
(newline)
(display (cons 1 2))
(newline)
(define x (list 1 2 3))
(newline)
(display x)
(set! x (append x (list 4 5 6)))
(display x)
(for-each 
	(lambda (a)
	(display a)
	(display " " )
	)
	x
)
(newline)
;show first element of list
(display (list-ref x 0))

