(defun is-variable (symbol)
  ;; Checks if a symbol is a variable (all capitalized string).
  (and (stringp symbol)
       (every #'upper-case-p symbol)))

(defun normalize-token (token)
  ;; Normalize the token by ensuring it is a symbol and trimmed of whitespace.
  (if (stringp token)
      (intern (string-trim " " token))  ;; Converts a string to a symbol
      token))    ;; If it's already a symbol, return as is

(defun unify (predicate1 predicate2)
  ;; Unifies two predicates and returns the substitution list or nil if unification fails.
  (let ((substitutions '()))
    (if (and (equal (car predicate1) (car predicate2))
             (= (length predicate1) (length predicate2)))
        (progn
          (loop for arg1 in (cdr predicate1)
                for arg2 in (cdr predicate2)
                do (cond
                     ((equal arg1 arg2)) ; Direct match
                     ((is-variable arg1)
                      (let ((existing (find arg1 substitutions :key #'first)))
                        (if existing
                            (unless (equal (second existing) arg2)
                              (return nil))
                          (progn
                            (push (list arg1 arg2) substitutions))))); Matching variable
                     ((is-variable arg2)
                      (let ((existing (find arg2 substitutions :key #'first)))
                        (if existing
                            (unless (equal (second existing) arg1)
                              (return nil))
                          (progn
                            (push (list arg2 arg1) substitutions))))); Matching variable
                     (t (return nil))) ; If they don't match
                finally (return substitutions)))
        nil)))


(defun apply-substitution (predicate substitutions)
  ;; Applies substitutions to a predicate.
  (mapcar (lambda (arg)
            (let ((binding (find arg substitutions :key #'first :test #'equal)))
              (if binding
                  (second binding) ; Use the second element as the substitution value
                  arg)))
          predicate))

(defun apply-substitution-to-query (query substitutions)
  ;; Applies substitutions to every predicate in a query.
  (mapcar (lambda (pred) (apply-substitution pred substitutions)) query))


(defun resolve (query axioms &optional (resolved-queries '()) (depth 0) (max-depth 6))
  ;; Resolves a query using axioms with a depth-first search approach, up to max-depth.
  (cond
   ((null query) '())
   
   ;; Check if this exact query (including substitutions) has been seen before
   ((find query resolved-queries :test #'equal)
    nil)

   ;; If we have reached the maximum depth, return nil
   ((>= depth max-depth)
    nil)

   (t (let ((results '()))
        (let ((sorted-query (sort (copy-seq query)
                                (lambda (pred1 pred2)
                                  (< (count-if #'is-variable pred1)
                                     (count-if #'is-variable pred2))))))
          (loop for pred in sorted-query
                do (loop for axiom in axioms
                         do (let* ((head (car axiom))
                                  (body (if (equal (normalize-token (second axiom)) '<)
                                          (cddr axiom)
                                          nil))
                                  (substitutions (unify pred head)))
                              (when substitutions
                                (let* ((new-body (if body
                                                    (apply-substitution-to-query body substitutions)
                                                    nil))
                                      (new-query (append new-body
                                                       (apply-substitution-to-query 
                                                        (remove pred query :test #'equal) 
                                                        substitutions))))
                                  (if (null new-query)
                                      (push substitutions results)
                                      ;; Only recurse if this query hasn't been seen before
                                      (unless (find new-query resolved-queries :test #'equal)
                                        (setf results 
                                              (append (resolve new-query axioms (cons query resolved-queries) (1+ depth) max-depth)
                                                        results)))))))))
          results)))))

(defun prolog_prove (axioms query &optional (max-depth 6))
  ;; Proves a query using a list of axioms and prints the result, with optional max-depth.
  (let ((result (resolve query axioms nil 0 max-depth)))
    (if result
        (progn
          (format t "Results: ~a~%" (remove-duplicates result :test #'equal))
          (remove-duplicates result :test #'equal))
      (progn
        (format t "Results: NIL~%")
        nil))))

;; Test Cases
(let ((axioms '((("father" "jim" "jill"))
                (("mother" "mary" "jill"))
                (("father" "samm" "jim"))
                (("ancestor" "X" "Y") "<" ("parent" "X" "Y"))
                (("ancestor" "X" "Y") "<" ("ancestor" "X" "Z") ("ancestor" "Z" "Y"))
                (("parent" "X" "Y") "<" ("mother" "X" "Y"))
                (("parent" "X" "Y") "<" ("father" "X" "Y"))))
      (query1 '(("parent" "X" "jim")))
      (query2 '(("ancestor" "X" "jill")))
      (query3 '(("ancestor" "X" "jill") ("parent" "X" "jim")))
      (query4 '(("mother" "X" "jill")))
      (query5 '(("parent" "X" "jill") ("mother" "X" "jill")))
      (query6 '(("ancestor" "X" "jill") ("mother" "X" "bob"))))
  (prolog_prove axioms query1)
  (prolog_prove axioms query2)
  (prolog_prove axioms query3)
  (prolog_prove axioms query4)
  (prolog_prove axioms query5)
  (prolog_prove axioms query6))
