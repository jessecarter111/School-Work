
(print "Please enter a list Ex: (1 2 3 4 5 6)")

(defvar *sampleList* (read))

(print "Please enter a number:")

(defvar *number* (read))

(defun my-length (my-list)
	(cond ((null my-list) 0)
		(t (+ (my-length (cdr my-list)) 1))))

(defun my-nth (n my-list)
	(cond ((zerop n) (car my-list))
		(t (my-nth (- n 1) (cdr my-list)))))

(defun my-reverse (my-list)
	(cond
		((null my-list) '())
		(t (append (my-reverse (cdr my-list)) (list (car my-list))))))

(defun get-indexs(element searchList)
	(let ((result nil))
		(dotimes (i (my-length searchList))
			(if (eq (my-nth i searchList) element)
				(push i result)))
		(my-reverse result)))

(print (get-indexs *number* *sampleList*))