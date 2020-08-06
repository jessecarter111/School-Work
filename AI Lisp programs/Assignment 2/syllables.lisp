(setq *word* '(a n a c o n d a))

(setq *vowels* '(a e i o u y));List of all vowels
(setq *consonants* '(b c d f g h j k l m n p q r s t v w x z))
;^ List of all consonants

(defun syllables (word);The main function
	(let ((retval nil));Creates a local empty list to store result
		;Loops over all letters of the word
		(loop for i from 0 to (- (length word) 1) do
		
			;Puts current letter into return list
			(push (nth i word) retval)
			
			;Checks first syllable pattern V C V,
			;If current set of letters matches
			;Inserts - to seperate the syllable
			(if (and (>= (length retval) 3)
					 (member (nth 0 retval) *vowels*) 
					 (member (nth 1 retval) *consonants*)
				 	 (member (nth 2 retval) *vowels*))
				(push '- retval))

			;Checks second syllable pattern V C C V
			(if (and (>= (length retval) 2)
					 (member (nth 1 retval) *vowels*) 
					 (member (nth 0 retval) *consonants*)
					 ;Uses look ahead in the word passed in 
					 ;to determine if patter is present
					 ;That way can just push - rather than 
					 ;Needing a seperate function to insert
					 ;at a specific index
				 	 (member (nth (+ i 1) word) *consonants*)
				 	 (member (nth (+ i 2) word) *vowels*))
				(push '- retval)))
	;Reverses list to print new, "syllabized" word
	(print (nreverse retval))))
		
(syllables *word*)