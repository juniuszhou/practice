; command scheme to launch interpretor
; input (load "let.scm")

;boolean type
(newline)
(define x 20)
(define ret 0)

(let ((x 1) ( y x))
	(set! ret (+ x y))
)
;the result is 21
(display ret)

(newline)
(set! ret 0)
(let* ((x 1) ( y x))
	(set! ret (+ x y))
)
;the result is 2
(display ret)


;define func aslo local 
(letrec ((local-even? (lambda (n)
                        (if (= n 0) #t
                            (local-odd? (- n 1)))))
        (local-odd? (lambda (n)
                       (if (= n 0) #f
                           (local-even? (- n 1))))))
(display (list (local-even? 23) (local-odd? 23))))
 
  
  
  
  