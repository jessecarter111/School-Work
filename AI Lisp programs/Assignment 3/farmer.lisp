(setq *moves* '(farmer-takes-self farmer-takes-wolf
	farmer-takes-goat farmer-takes-cabbage))
;List of moves to be used for DFS and BFS

(defun make-state (f w g c) (list f w g c))
;Functions define the operations of the farmer problem
;And its problem search space

(defun farmer-side (state)
	(nth 0 state))

(defun wolf-side (state)
	(nth 1 state))

(defun goat-side (state)
	(nth 2 state))

(defun cabbage-side (state)
	(nth 3 state))

(defun farmer-takes-self (state)
	;Produces the move and determines if the move is safe
	(safe
		(make-state (opposite (farmer-side state))
			(wolf-side state)
			(goat-side state)
			(cabbage-side state))))

(defun farmer-takes-wolf (state)
	(cond ((equal (farmer-side state) (wolf-side state))
		(safe (make-state 
			(opposite (farmer-side state))
			(opposite (wolf-side state))
			(goat-side state)
			(cabbage-side state))))
	(t nil)))

(defun farmer-takes-goat (state)
	(cond ((equal (farmer-side state) (goat-side state))
		(safe (make-state 
			(opposite (farmer-side state))
			(wolf-side state)
			(opposite (goat-side state))
			(cabbage-side state))))
	(t nil)))

(defun farmer-takes-cabbage (state)
	(cond ((equal (farmer-side state) (cabbage-side state))
		(safe (make-state 
			(opposite (farmer-side state))
			(wolf-side state)
			(goat-side state)
			(opposite (cabbage-side state)))))
	(t nil)))

(defun opposite (side)
	;Returns the oppsite side of current position
	(cond ((equal side 'e) 'w)
		((equal side 'w) 'e)))

(defun safe (state)
	;Checks if current state is legal, returnig nil if not
	(cond ((and (equal (goat-side state)
					   (wolf-side state))
				(not (equal (farmer-side state) (wolf-side state))))
				nil)

			((and (equal (goat-side state) 
						 (cabbage-side state))
				(not (equal (farmer-side state) (goat-side state))))
				nil)

			(t state)))

(defun build-record (state parent) (list state parent))
;Generates a (state parent) tuple

(defun get-state (state-tuple) (nth 0 state-tuple))
;Acceses the corresponding state element of the tuple

(defun get-parent (state-tuple) (nth 1 state-tuple))
;Acceses the corresponding parent element of the tuple

(defun retrieve-by-state (state list)
;Iterates through the state record to return the states that match
;The state passed in
	(cond ((null list) nil)
	
	((equal state (get-state (car list)))
		(car list))

	(t (retrieve-by-state state (cdr list)))))

(defun generate-descendants (state moves)
;Generates all possible descendants of the current state not 
;Allowing duplicate states to be added to the list
	(cond ((null moves) nil)

		(t (let ((child (funcall (car moves) state)) 
			(rest (generate-descendants state (cdr moves))))

			(cond ((null child) rest) 
				((retrieve-by-state child rest) rest)
				((retrieve-by-state child *open*) rest)
				((retrieve-by-state child *closed*) rest)
				(t (cons (build-record child state) rest)))))))

(defun build-solution (state)
;Generates the solution by retrieving all states that led to the goal
	(cond ((null state) nil)

	(t (cons state (build-solution 
		(get-parent (retrieve-by-state state *closed*)))))))

(defun breadth-first ( )
	(cond ((null *open*) nil)
	;If *open* is null stop the recursion

		(t (let ((state (car *open*)))
			(setq *closed* (cons state *closed*))
		;Sets the current state value and adds it to the closed list 

			(cond ((equal (get-state state) *goal*)
					(build-solution *goal*))
			;If current state is goal, produce the solution path

				(t (setq *open* (append (cdr *open*)
				;Otherwise recurse on all descendants of the current state
				;The order of args in append makes *open* a FIFO queue
					(generate-descendants (get-state state) *moves*)))
					(breadth-first)))))))

(defun run-breadth (start goal)
;Initializes variables to run BFS
	(setq *open* (list (build-record start nil)))
	(setq *closed* nil)
	(setq *goal* goal)
	(breadth-first))

(defun depth-first ( )
	;Identical to BFS except for structure of *open*
	(cond ((null *open*) nil)

		(t (let ((state (car *open*)))
			(setq *closed* (cons state *closed*))

			(cond ((equal (get-state state) *goal*)
					(build-solution *goal*))

				(t (setq *open* (append 
				;Order of args in append make it a stack
					(generate-descendants (get-state state) *moves*)
					(cdr *open*))) 
					(depth-first)))))))

(defun run-depth (start goal)
	(setq *open* (list (build-record start nil)))
	(setq *closed* nil)
	(setq *goal* goal)
	(depth-first))

(print (reverse (run-breadth (make-state 'e 'w 'e 'w) (make-state 'w 'w 'w 'w))))
(print (reverse (run-depth (make-state 'e 'w 'e 'e) (make-state 'w 'w 'w 'w))))