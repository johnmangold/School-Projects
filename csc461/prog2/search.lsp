(defun dfs(state)
	; format start-state into a list
	(when (equal (list "left") (last state))
		(setq state (list state)))

	; base case
	(when (goal-state? (car (last state)))
		(return-from dfs state))
	
	; generate children for current state
	(dolist (child (generate-successors (car (last state))))
		; if child has not already been encountered, add to path
		(unless (find_child child state)
			; depth first search
			(setq path ( dfs (append state (list child))))
			
			; return path if goal is reached
			(when (goal-state? (car (last path)))
				(return-from dfs path))
		)
	)

	; return failure
	nil
)

(defun find_child (child path)
	; check path if child already exists
	(dolist (i path)
		(when (equal child i)
			(return-from find_child t)
		)
	)
	
	; return nil if not found
	nil
)