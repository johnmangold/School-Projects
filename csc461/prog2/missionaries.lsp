#|
		missionaries.lsp
|#

;;;-------------Global Variables Section-------------------------------------------
(defvar *M*)
(defvar *C*)
(defvar *BANK*)

;;;-------------Load DFS from external file----------------------------------------


;;;-------------Start functions to get arguments-------------------------------------
(defun intro()
	(format t "~%This is a recursive solution to the missionaries and ~%")
	(format t "cannibals problem.  It uses a depth first search to solve ~%")
	(format t "the problem.~%~%")
	(format t "Usage: (m-c m c)~%")
	(format t "        m - number of missionaries~%")
	(format t "        c - number of cannibals~%~%"))

(defun m-c(m c)
	(setf *M* m)
	(setf *C* c)
	(format t "There are ~d missionaries and ~d cannibals" *M* *C*))
	
(intro)
