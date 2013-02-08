; sudo apt-get install mit-scheme
; command scheme to launch interpretor
; input (load "condition.scm")

; if then else
(newline)
(if (and
	(> 90 80)
	#f
	)
	(display "branch true here")
	(display "branch false here")
)

;in case of the scheme you used doesn't support when
(define-macro when
  (lambda (test . branch)
    (list 'if test
      (cons 'begin branch))))
	  
;when and unless statement
#| need investigate why it doesn't work
   some interpretor don't support when/unless
(newline)
(define a 20)
(when (> a 10)
	   (begin
	    (display a)
		(newline)
		(set! a (- a 1))
		)
)
|#

;con can be used to replace nested if/else

(cond ((char<? c #\c) -1)
      ((char=? c #\c) 0)
      (else 1))

; case to match too much conditions
(case c
  ((#\a) 1)
  ((#\b) 2)
  ((#\c) 3)
  (else 4))
  

