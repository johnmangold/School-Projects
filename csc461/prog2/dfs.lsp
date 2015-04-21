(defun dfs(state)
	(cond
		((null state) nil)
		((goal-state? state) state)
		(t (dfs (nconc (generate-successors state) state)))))
