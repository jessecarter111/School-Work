(setf
  (get 'A 'successors) '(B E)
  (get 'B 'successors) '(C E)
  (get 'C 'successors) '(D E)
  (get 'D 'successors) '()
  (get 'E 'successors) '(A B D C))
;Data abstraction of the graph

(defun find-path(current goal path)
	;Based off solution to farmer problem in textbook
	(cond ((null current) nil);End condition   

		((equal current goal);If the current node is the goal
			(print (reverse (cons current path))));add it to path and print it

		((not (member current path));If the node isn't already in path
			(loop for i from 0 to 
				;For each node in successors, recurse on it with find-path
				(- (length (get current 'successors)) 1) do
					(find-path (nth i (get current 'successors)) goal 
						(cons current path))))))

(defun pathfinder (state goal)
	(find-path state goal nil))

(pathfinder 'A 'D)