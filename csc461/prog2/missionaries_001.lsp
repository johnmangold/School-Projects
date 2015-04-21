#|
					***** MISSIONARIES.LSP *****
					
Missionary and Cannibal Problem:
	Move all M missionaries and C cannibals from the left side of a river to the
right. Can only use a rowboat that fits a maximum of two people, and if either
shore has 1 or more missionaries out numbered by cannibals, the cannibals will
eat them. Calls DFS search routine in search.lsp, and ascii art in ascii.lsp.

Usage: clisp missionaries

Authors: John Mangold, Murray LaHood-Burns
Written Spring 2015 for CSC461 PL class, programming assignment 2.

Modifications:
|#

;-------------------------------------------------------------------------------

; global variables
(defvar *M*)		; number of missionaries
(defvar *C*)		; number of cannibals

;-------------------------------------------------------------------------------

; load DFS routine and ascii art from external files
(load 'ascii)
(load 'dfs)

;-------------------------------------------------------------------------------

; usage statement displayed at file load time
(defun usage ()
	(format t "~%This is a recursive solution to the missionaries and ~%")
	(format t "cannibals problem.  It uses a depth first search to solve ~%")
	(format t "the problem.~%~%")
	(format t "Usage: (m-c m c)~%")
	(format t "        m - number of missionaries~%")
	(format t "        c - number of cannibals~%~%")
)

;-------------------------------------------------------------------------------

; Missionary and Cannibal Problem
(defun m-c (m c)
	; variable check
	(format t "There are ~d missionaries and ~d cannibals.~%" m c )

	; check for unsolvable problem instance
	(when (< m c) (defeat) (return-from m-c "The cannibals have feasted!!!"))

	; initialize global vars
	(setf *M* m)
	(setf *C* c)

	; solve missionary/cannibal problem using DFS
	(format t "left bank 	right bank	canoe		last move~%")
	(format t "--------- 	---------- 	----- 		---------~%")
	(format t "~A~%"  (dfs(start-state)))

	; suppress printing NIL upon return to interpreter
	(values)
)

; Define the start state
(defun start-state () (list *M* *C* "left" ) )

; Define the goal state
(defun goal-state? (state)
	(and (= (car state) 0) (= (cadr state) 0) (string= (caddr state) "right"))
)

; Generate-successors returns a list of successors to the current state.
(defun generate-successors (state)
	; define local variables
	(let ( (ml (car state)) (cl (cadr state)) (bank (caddr state)) mr cr
		   (succs nil) )
	
		; set number of missionaries and cannibals on right
		(setq mr (- *M* ml) cr (- *C* cl))
	
		; moves if canoe is on left bank
		(when (string= bank "left")
			;(format t "~dm ~dc |\\_/      | ~dm ~dc~%" ml cl mr cr)
			
			; 1 missionary right
			(when (and (>= ml 1)
					   (or (>= (- ml 1) cl)
						   (= ml 1))
					   (>= (+ mr 1) cr))
				(setq succs (cons (list (- ml 1) cl "right") succs)))
				
			; 2 missionaries right
			(when (and (>= ml 2)
					   (or (>= (- ml 2) cl)
						   (= ml 2))
					   (>= (+ mr 2) cr))
				(setq succs (cons (list (- ml 2) cl "right") succs)))
				
			; 1 cannibal right
			(when (and (>= cl 1)
					   (or (>= mr (+ cr 1))
						   (= mr 0)))
				(setq succs (cons (list ml (- cl 1) "right") succs)))
				
			; 2 cannibals right
			(when (and (>= cl 2)
					   (or (>= mr (+ cr 2))
						   (= mr 0)))
				(setq succs (cons (list ml (- cl 2) "right") succs)))
				
			; 1 missionary and 1 cannibal right
			(when (and (>= cl 1)
					   (>= ml 1)
					   (>= (+ mr 1)
					   (+ cr 1)))
				(setq succs (cons (list (- ml 1) (- cl 1) "right") succs)))
		)
		
		; moves if canoes is on right bank
		(when (string= bank "right")
			;(format t "~dm ~dc |      \\_/| ~dm ~dc~%" ml cl mr cr)
			
			; 1 missionary left
			(when (and (>= mr 1)
					   (or (>= (- mr 1) cr)
						   (= mr 1))
					   (>= (+ ml 1) cl))
				(setq succs (cons (list (+ ml 1) cl "left") succs)))
				
			; 2 missionaries left
			(when (and (>= mr 2)
					   (or (>= (- mr 2) cr)
						   (= mr 2))
					   (>= (+ ml 2) cl))
				(setq succs (cons (list (+ ml 2) cl "left") succs)))
				
			; 1 cannibal left
			(when (and (>= cr 1)
					   (or (>= ml (+ cl 1))
						   (= ml 0)))
				(setq succs (cons (list ml (+ cl 1) "left") succs)))
				
			; 2 cannibal left
			(when (and (>= cr 2)
					   (or (>= ml (+ cl 2))
						   (= ml 0)))
				(setq succs (cons (list ml (+ cl 2) "left") succs)))
			
			; 1 missionary and 1 cannibal left
			(when (and (>= cr 1)
					   (>= mr 1)
					   (>= (+ ml 1) (+ cl 1)))
				(setq succs (cons (list (+ ml 1) (+ cl 1) "left") succs)))
		)
		
		; return list of successors, without duplicates
		(remove-duplicates succs :test #'equal)
	)
)

;-------------------------------------------------------------------------------

; print usage statement automatically upon loading file
(usage)
