(setf
  (get 'A 'successors) '(B)
  (get 'B 'successors) '(D C)
  (get 'C 'successors) '(D)
  (get 'D 'successors) '(B))
;Graph data structure
(setf
	(get 'A 'costs) '(3)
	(get 'B 'costs) '(5 1)
	(get 'C 'costs) '(2)
	(get 'D 'costs) '(2))
;Weights for the graph

(defvar *paths* '())
;Global var to hold all paths from original find path function in q2

(defun find-path(current goal path total) ;Generally the same as function in q2
	(cond ((null current) nil)   

		((equal current goal)
			(push (reverse (cons total (cons current path))) *paths*))
			;Adds the path with its weight appended to the end to *paths*	
		((not (member current path))
			(loop for i from 0 to (- (length (get current 'successors)) 1) do
					(find-path (nth i (get current 'successors)) goal 
						(cons current path) 
						(+ total (nth i (get current 'costs))))))))
						;Adds the cost of current node to total


(defun shortest-path (start goal)
	(find-path start goal nil 0)
	(let (temp '()) ;Temp stores path with lowest total weight
		(loop for x in *paths* do ;Loops over all paths in *paths*
			(cond ((equal temp '()) (setq temp x))
				((<= (nth 0 (last x)) (nth 0 (last temp))) 
					(setq temp x))))
		;If the current path has lower weight than one stored in temp,
		;Changes temp to that path
		(print temp))) ;Prints temp i.e path with lowest weight

(shortest-path 'D 'B)