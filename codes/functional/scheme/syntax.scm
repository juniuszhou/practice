; command scheme to launch interpretor
; input (load "syntax.scm")
; it is shown how to define a syntax expansion
; it is similar to MACRO definition
(define-syntax coroutine
  (syntax-rules ()
    ((coroutine arg ...)
     (display arg ...)
    )
   )
 )

 (coroutine "hello")
       