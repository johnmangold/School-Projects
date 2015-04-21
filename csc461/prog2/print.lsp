#|
	Author: John Mangold, Murray Lahood-Burns
	Description: Given a list of states, it prints the states from start
		     to finish properly formatted.  Displays number of cannibals
		     and missionaries on left bank, on right bank, position of
		     the canoe, and a statement of the number of people moved
		     and to which bank.
	Arguments: state
	Returns: None
|#
(defun print_mc (state)
	(format t "left bank    right bank    canoe    last move~%")
	(format t "---------    ----------    -----    ---------~%")

	(format t "~d M, ~d C      0 M, 0 C     ~a     start position~%"
		(car (car state)) (cadr (car state)) (caddr (car state)))
		
	(setf prev (car state))
	(setf rest (cdr state))
	(setf bank -1)
	(dolist (node rest)
		;;;(when (equal node nil) return-from print-mc)
		(if (= bank -1)
			;left bank
			(progn
				(setf mm (- (car prev) (car node)))
				(setf mc (- (cadr prev) (cadr node)))
				(format t "~d M, ~d C      ~d M, ~d C     ~a     move ~d M, ~d C left to right~%"
					(car node) (cadr node) (- *M* (car node)) (- *C* (cadr node)) (caddr node) mm mc)
			)
			
			;right bank
			(progn
				(setf mm (- (car node) (car prev)))
				(setf mc (- (cadr node) (cadr prev)))
				(format t "~d M, ~d C      ~d M, ~d C     ~a     move ~d M, ~d C right to left~%"
					(car node) (cadr node) (- *M* (car node)) (- *C* (cadr node)) (caddr node) mm mc)
			)
		)
		(setf prev node)
		(setf bank (* bank -1))
	)
)
