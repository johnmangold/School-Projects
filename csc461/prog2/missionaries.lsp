#|
		missionaries.lsp
|#

;;;-------------Global Variables Section-------------------------------------------
(defvar *M*)
(defvar *C*)
(defvar *BANK*)

;;;-------------Load DFS from external file----------------------------------------


;;;-------------Start functions-------------------------------------
(defun intro()
	(format t "~%~%This is a recursive solution to the missionaries and ~%")
	(format t "cannibals problem.  It uses a depth first search to solve ~%")
	(format t "the problem.~%~%")
	(format t "Usage: (m-c m c)~%")
	(format t "        m - number of missionaries~%")
	(format t "        c - number of cannibals~%~%"))

(defun m-c(m c)
	(setf *M* m)
	(setf *C* c)
	(setf *BANK* -1)
	
	;;;Check that the cannibals don't out number the missionaries to start
	(when (< *M* *C*) (return-from m-c "The cannibals have feasted!!!"))
	
	;;;begin dfs search by passing it the start_state function
	
	(format t "There are ~d missionaries and ~d cannibals" *M* *C*))
	
;;; Create start state with everyone on left bank
(defun start_state() (*M* *C* *BANK*))

;;;Check for goal reached
(defun goal(state)
	(and (= (car state) 0) (= (cadr state) 0) (= (caddr state) 1)))
	
;;;Generate succesors
;;;Possible moves:
;;;Move 1 missionary and 1 cannibal
;;;Move 2 missionaries
;;;Move 2 cannibals
;;;Ghost ride the whip(not really an option but it felt right to list it)
;;;Write the creation of each successor
	
(intro)
