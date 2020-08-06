(print "Please enter a number") 

(defvar number (read))

(defun factorial (n)
	(if(= n 1)
		1
		(* n (factorial (- n 1))) ) )

(print (factorial number))