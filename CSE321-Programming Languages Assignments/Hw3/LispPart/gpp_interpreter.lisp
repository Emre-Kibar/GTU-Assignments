(load "gpp_lexer.lisp")

(defvar *identifier-map* (make-hash-table :test 'equal))
;; Global hash table to store identifier names and their values.

(defun store-identifier (name value)
  "Store an identifier with its value in the hash table."
  (setf (gethash name *identifier-map*) value))

(defun get-identifier (name)
  "Retrieve the value of an identifier from the hash table."
  (or (gethash name *identifier-map*) (error "Identifier ~A not found!" name)))

(defun parse-float (value)
  "Converts the VALUEF token (e.g., '12f0' or '12f23') into a float."
  (let* ((split-pos (position #\f value))  ;; Find the position of 'f'
         (integer-part (parse-integer (subseq value 0 split-pos)))  ;; Integer part
         (fractional-part (subseq value (1+ split-pos)))  ;; Fractional part
         (fractional-as-float (if (string= fractional-part "")
                                  0.0
                                  (/ (parse-integer fractional-part)
                                     (expt 10 (length fractional-part))))))
    (+ (float integer-part) fractional-as-float)))  ;; Combine as float


(defun float-to-f-format (value)
  "Converts a float into the VALUEF format (e.g., 12.23 → '12f23')."
  (let* ((integer-part (truncate value))  ;; Extract integer part
         (fractional-part (- value integer-part))  ;; Extract fractional part
         (fractional-str (if (zerop fractional-part)
                             "0"  ;; If no fractional part, return "f0"
                             (format nil "~d" (truncate (* fractional-part 10000)))))) ;; Limit to 4 decimal places
    (format nil "~af~a" integer-part fractional-str)))  ;; Combine parts



(defun calculate-expi (operator left-value right-value)
  "Calculates the result of the arithmetic operation and converts it to f-separated form."
  (let ((result
         (case (intern operator)  ;; Convert the string operator to a symbol
           ((+) (+ left-value right-value))
           ((-) (- left-value right-value))
           ((*) (* left-value right-value))
           ((/) (if (zerop right-value) 
                    (error "Division by zero!") 
                    (/ left-value right-value)))
           (otherwise (error "Unknown operator: ~A" operator)))))
    (float-to-f-format result)))  ;; Convert result to f-separated form

(defun normalize-token (token)
  "Normalize the token by ensuring it is a symbol and trimmed of whitespace."
  (if (stringp token)
      (intern (string-trim " " token))  ;; Converts a string to a symbol
      token))    

(defun convert-expiarth (unreducedTokens unconvertedTokens)
  "Reduce sequences in unreducedTokens matching EXPIARTH rules and calculate the result."
  (let ((reducedConvertedTokens '())  ;; To hold reduced tokens
        (reducedUnconvertedTokens '())
        (index 0))           ;; Track current position in tokens
    (loop while (< index (length unreducedTokens))
          do (let ((token (normalize-token (nth index unreducedTokens))))
               (cond
                 ;; Detect subexpression: ( OP_OP operator operand1 operand2 OP_CP )
                 ((and (eq token 'OP_OP)                      
                       (or (eq (normalize-token (nth (1+ index) unreducedTokens)) 'OP_PLUS)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'OP_MINUS)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'OP_MULT)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'OP_DIV))                       
                       (eq (normalize-token (nth (+ index 4) unreducedTokens)) 'OP_CP))

                  ;; Extract operator and operands
                  (let* ((operator (nth (1+ index) unconvertedTokens))
                         (left-token (nth (+ index 2) unconvertedTokens))
                         (right-token (nth (+ index 3) unconvertedTokens))
                         (left-value (if (eq (normalize-token (nth (+ index 2) unreducedTokens)) 'VALUEF) 
                                        (parse-float left-token)  ;; If it's a VALUEF, parse it directly
                                        (parse-float (get-identifier left-token))))  ;; If it's an IDENTIFIER, get the value from the map
                         (right-value (if (eq (normalize-token (nth (+ index 3) unreducedTokens)) 'VALUEF) 
                                         (parse-float right-token)  ;; If it's a VALUEF, parse it directly
                                         (parse-float (get-identifier right-token))))
                         (result (calculate-expi operator left-value right-value)))

                    ;; Replace subexpression with EXPIARTH
                    (push 'EXPIARTH reducedConvertedTokens)
                    ;; Replace the result in unconvertedTokens
                    (push result reducedUnconvertedTokens)
                    ;; Skip the reduced tokens
                    (setf index (+ index 5))))

                 ;; For nested expressions, defer reduction
                 (t 
                  (push token reducedConvertedTokens)
                  (push (nth index unconvertedTokens) reducedUnconvertedTokens)
                  (setf index (+ index 1))))))

    (values (nreverse reducedConvertedTokens) (nreverse reducedUnconvertedTokens))))    

(defun parse-boolean (value)
  "Convert a token or value into a boolean. Recognizes true, false, and nil."
  (cond
    ((or (eq value 'KW_TRUE) (equal value "true") (equal value t)) t)
    ((or (eq value 'KW_FALSE) (equal value "false")) nil)
    ((or (eq value 'KW_NIL) (equal value "nil") (equal value nil)) nil)
    (t (error "Invalid boolean value: ~A" value))))

(defun calculate-expb (operator &rest operands)
  "Evaluate a logical or boolean expression based on the operator and operands."
  (cond
    ;; Logical AND
    ((eq operator 'KW_AND)
     (and (parse-boolean (nth 0 operands))
          (parse-boolean (nth 1 operands))))

    ;; Logical OR
    ((eq operator 'KW_OR)
     (or (parse-boolean (nth 0 operands))
         (parse-boolean (nth 1 operands))))

    ;; Logical NOT (Unary operator)
    ((eq operator 'KW_NOT)
     (not (parse-boolean (nth 0 operands))))

    ;; Equality operator
    ((eq operator 'KW_EQUAL)
     (equal (nth 0 operands) (nth 1 operands)))

    ;; Less-than operator
    ((eq operator 'KW_LESS)
     (< (parse-float (nth 0 operands))
        (parse-float (nth 1 operands))))

    ;; Handle unknown operators
    (t (error "Unknown operator: ~A" operator))))    

(defun convert-expb (unreducedTokens unconvertedTokens)
  "Reduce sequences in unreducedTokens matching logical and boolean rules and calculate the result."
  (let ((reducedConvertedTokens '())  ;; To hold reduced tokens
        (reducedUnconvertedTokens '())
        (index 0))           ;; Track current position in tokens
    (loop while (< index (length unreducedTokens))
          do (let ((token (normalize-token (nth index unreducedTokens))))
               (cond
                 ;; Detect subexpression: ( OP_OP operator operand1 operand2 OP_CP )
                 ((and (eq token 'OP_OP)                      
                       (or (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_AND)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_OR)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_EQUAL)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_LESS))                       
                       (eq (normalize-token (nth (+ index 4) unreducedTokens)) 'OP_CP))

                  ;; Extract operator and operands
                  (let* ((operator (normalize-token (nth (1+ index) unreducedTokens)))
                         (left-token (nth (+ index 2) unconvertedTokens))
                         (right-token (nth (+ index 3) unconvertedTokens))
                         (left-value (if (eq (normalize-token (nth (+ index 2) unreducedTokens)) 'IDENTIFIER) 
                                        (get-identifier left-token);; If it's an IDENTIFIER, get the value from the map
                                        left-token))  ;; If it's a VALUEF, parse it directly                                    
                         (right-value (if (eq (normalize-token (nth (+ index 3) unreducedTokens)) 'IDENTIFIER) 
                                         (get-identifier right-token)
                                         right-token))  ;; If it's a VALUEF, parse it directly              
                         (result (calculate-expb operator left-value right-value)))

                    ;; Replace subexpression with EXPB
                    (push 'EXPB reducedConvertedTokens)
                    ;; Replace the result in unconvertedTokens
                    (push result reducedUnconvertedTokens)
                    ;; Skip the reduced tokens
                    (setf index (+ index 5))))

                 ;; Detect unary operator: ( OP_OP KW_NOT operand OP_CP )
                 ((and (eq token 'OP_OP)                      
                       (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_NOT)                       
                       (eq (normalize-token (nth (+ index 3) unreducedTokens)) 'OP_CP))

                  ;; Extract operand and calculate result
                  (let* ((operand-token (nth (+ index 2) unconvertedTokens))
                         (result (calculate-expb 'KW_NOT operand-token)))

                    ;; Replace subexpression with EXPB
                    (push 'EXPB reducedConvertedTokens)
                    ;; Replace the result in unconvertedTokens
                    (push result reducedUnconvertedTokens)
                    ;; Skip the reduced tokens
                    (setf index (+ index 4))))

                 ;; Detect boolean literals: ( OP_OP KW_TRUE | KW_FALSE | KW_NIL OP_CP )
                 ((and (eq token 'OP_OP)                      
                       (or (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_TRUE)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_FALSE)
                           (eq (normalize-token (nth (1+ index) unreducedTokens)) 'KW_NIL))                       
                       (eq (normalize-token (nth (+ index 2) unreducedTokens)) 'OP_CP))

                  ;; Extract literal and calculate result
                  (let ((literal-token (nth (1+ index) unconvertedTokens)))
                    ;; Replace subexpression with EXPB
                    (push 'EXPB reducedConvertedTokens)
                    ;; Replace the result in unconvertedTokens
                    (push literal-token reducedUnconvertedTokens)
                    ;; Skip the reduced tokens
                    (setf index (+ index 3))))

                 ;; For nested expressions or non-matching tokens, defer reduction
                 (t 
                  (push token reducedConvertedTokens)
                  (push (nth index unconvertedTokens) reducedUnconvertedTokens)
                  (setf index (+ index 1))))))

    (values (nreverse reducedConvertedTokens) (nreverse reducedUnconvertedTokens))))

(defun reduce-tokens (tokensToReduce unconvertedTokens)
  "Reduce tokens recursively using EXPIARTH and logical/boolean rules."
  (let ((prev-tokens nil)
        (current-tokens tokensToReduce))
    (loop
      while (not (equal prev-tokens current-tokens))  ;; Stop if no further reduction occurs
      do (progn
           ;; Apply EXPIARTH reduction
           (multiple-value-setq (current-tokens unconvertedTokens)
             (convert-expiarth current-tokens unconvertedTokens))
           ;; Apply EXPB reduction
           (multiple-value-setq (current-tokens unconvertedTokens)
             (convert-expb current-tokens unconvertedTokens)))
      (setf prev-tokens current-tokens))
    (values current-tokens unconvertedTokens)))


(defun checkLine (reducedTokens updated-unconvertedTokens outfile)
  "Check the reducedTokens and unconvertedTokens to write results to the output file based on their state."
  (let ((lineSize (length reducedTokens)))
    (cond
      ;; Case: Single token EXPIARTH
      ((and (= lineSize 1)
            (eq (normalize-token (car reducedTokens)) 'EXPIARTH))
       (format outfile "Result: ~A~%" (car updated-unconvertedTokens)))

      ((and (= lineSize 1)
            (eq (normalize-token (car reducedTokens)) 'EXPB))
       (format outfile "Result: ~A~%" (car updated-unconvertedTokens)))

      ((and (= lineSize 3)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (eq (normalize-token (nth 1 reducedTokens)) 'KW_EXIT)
            (eq (normalize-token (nth 2 reducedTokens)) 'OP_CP))
       (format outfile "Exiting program...~%")
       (close outfile)  ;; Close the output file before exiting
       (exit))  ;; Terminate the program

      ((and (= lineSize 4)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (eq (normalize-token (nth 1 reducedTokens)) 'KW_DISP)
            (eq (normalize-token (nth 3 reducedTokens)) 'OP_CP))
        (if (eq (normalize-token (nth 2 reducedTokens)) 'IDENTIFIER)
          (format outfile "Result: ~A = ~A~%" (nth 2 updated-unconvertedTokens) (get-identifier (nth 2 updated-unconvertedTokens)))
          (format outfile "Result: ~A~%" (nth 2 updated-unconvertedTokens)))) 

      ;; Case: Identifier declaration: OP_OP KW_DEFVAR IDENTIFIER VALUEF/EXPIARTH OP_CP
      ((and (= lineSize 5)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (eq (normalize-token (nth 1 reducedTokens)) 'KW_DEFVAR)
            (eq (normalize-token (nth 4 reducedTokens)) 'OP_CP))
       (let* ((identifier (nth 2 updated-unconvertedTokens))  
              (value-token (nth 3 updated-unconvertedTokens)))  
         (store-identifier identifier value-token)  
         (format outfile "Result: ~A = ~A~%" identifier (get-identifier identifier))))

      ;; Case: Identifier update: OP_OP KW_SET IDENTIFIER VALUEF/EXPIARTH OP_CP
      ((and (= lineSize 5)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (eq (normalize-token (nth 1 reducedTokens)) 'KW_SET)
            (eq (normalize-token (nth 4 reducedTokens)) 'OP_CP))
      (let* ((identifier (nth 2 updated-unconvertedTokens))  
              (value-token (nth 3 updated-unconvertedTokens)))  
        (if (get-identifier identifier)  
            (progn
                (store-identifier identifier value-token)  
                (format outfile "Result: ~A = ~A~%" identifier (get-identifier identifier)))
            (error "Identifier ~A not found!" identifier))))


      ;; Case: Specific pattern: OP_OP OP_PLUS EXPIARTH EXPIARTH OP_CP
      ((and (= lineSize 5)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (or (eq (normalize-token (nth 1 reducedTokens)) 'OP_PLUS)
                (eq (normalize-token (nth 1 reducedTokens)) 'OP_MINUS)
                (eq (normalize-token (nth 1 reducedTokens)) 'OP_MULT)
                (eq (normalize-token (nth 1 reducedTokens)) 'OP_DIV))
            (eq (normalize-token (nth 2 reducedTokens)) 'EXPIARTH)
            (eq (normalize-token (nth 3 reducedTokens)) 'EXPIARTH)
            (eq (normalize-token (nth 4 reducedTokens)) 'OP_CP))
       (let* ((operator (nth 1 updated-unconvertedTokens))
              (left-value (parse-float (nth 2 updated-unconvertedTokens)))
              (right-value (parse-float (nth 3 updated-unconvertedTokens)))
              (result (calculate-expi operator left-value right-value)))
         (format outfile "Result: ~A~%" result)))

      ((and (= lineSize 4)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (eq (normalize-token (nth 1 reducedTokens)) 'KW_NOT)
            (eq (normalize-token (nth 2 reducedTokens)) 'EXPB)
            (eq (normalize-token (nth 3 reducedTokens)) 'OP_CP))
       (let* ((operator (normalize-token (nth 1 reducedTokens)))
              (value (parse-boolean (nth 2 updated-unconvertedTokens)))
              (result (calculate-expb operator value)))
         (format outfile "Result: ~A~%" result)))   

      ((and (= lineSize 5)
            (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
            (or (eq (normalize-token (nth 1 reducedTokens)) 'KW_AND)
                (eq (normalize-token (nth 1 reducedTokens)) 'KW_OR)
                (eq (normalize-token (nth 1 reducedTokens)) 'KW_EQUAL)
                (eq (normalize-token (nth 1 reducedTokens)) 'KW_LESS))
            (eq (normalize-token (nth 2 reducedTokens)) 'EXPB)
            (eq (normalize-token (nth 3 reducedTokens)) 'EXPB)
            (eq (normalize-token (nth 4 reducedTokens)) 'OP_CP))
       (let* ((operator (normalize-token (nth 1 reducedTokens)))
              (left-value (parse-boolean (nth 2 updated-unconvertedTokens)))
              (right-value (parse-boolean (nth 3 updated-unconvertedTokens)))
              (result (calculate-expb operator left-value right-value)))
         (format outfile "Result: ~A~%" result)))

    ;; Checking for OP_OP KW_IF EXPB *sometokens* OP_CP
    ((and (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
          (eq (normalize-token (nth 1 reducedTokens)) 'KW_IF)
          (eq (normalize-token (nth 2 reducedTokens)) 'EXPB)
          (eq (normalize-token (nth (- lineSize 1) reducedTokens)) 'OP_CP))
      (let* ((condition (nth 2 updated-unconvertedTokens))  ;; Parse the boolean condition
            (sometokensReduced (subseq reducedTokens 3 (- lineSize 1)))  ;; Extract reduced tokens (after KW_IF and EXPB)
            (sometokensUnconverted (subseq updated-unconvertedTokens 3 (- lineSize 1))))  ;; Extract unconverted tokens (after KW_IF and EXPB)
        (if (eq condition t)
            (checkLine sometokensReduced sometokensUnconverted outfile)  ;; If condition is true, process the remaining tokens
            (format outfile "Result: if condition is incorrect~%"))))  ;; Otherwise, print an error message

      ((and (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
          (eq (normalize-token (nth 1 reducedTokens)) 'KW_DEFFUN)
          (eq (normalize-token (nth 2 reducedTokens)) 'IDENTIFIER)
          (eq (normalize-token (nth 3 reducedTokens)) 'OP_OP)
          (eq (normalize-token (nth (- lineSize 1) reducedTokens)) 'OP_CP))
          (format outfile "Result: Function '~A' is defined~%" (nth 2 updated-unconvertedTokens)))  

      ((and (eq (normalize-token (nth 0 reducedTokens)) 'OP_OP)
          (eq (normalize-token (nth 1 reducedTokens)) 'KW_WHILE)
          (eq (normalize-token (nth 2 reducedTokens)) 'EXPB)
          (eq (normalize-token (nth (- lineSize 1) reducedTokens)) 'OP_CP))
          (if (eq (nth 2 updated-unconvertedTokens) t)
            (format outfile "Result: while condition is correct. Entered loop.~%")  
            (format outfile "Result: while condition is incorrect. Not entered loop.~%")))        

      ;; Default: Unhandled cases
      (t (format outfile "Syntax incorrect or Unhandled line with tokens: ~A~%" reducedTokens)))))

(defun process (convertedTokens unconvertedTokens outfile)
  "Process tokens by reducing them based on the EXPIARTH rules, writing results to the output file."
  (multiple-value-bind (reducedTokens updated-unconvertedTokens)
      (reduce-tokens convertedTokens unconvertedTokens)
    (checkLine reducedTokens updated-unconvertedTokens outfile)))

(defun gppinterpreter (&optional inputFile)
  "Main function to read an input file and process each line, writing results to output.txt."
  (format t "Welcome to GPP Lexer! The analyzed lines printed 'output.txt'.~%")
  ;; If an input file is provided
  (when inputFile
    (with-open-file (stream inputFile :direction :input)
      (with-open-file (outfile "output.txt" :direction :output :if-exists :supersede)
        (loop for line = (read-line stream nil)
              while line
              do (let ((line-tokens '())
                       (original-tokens '()))  ;; Initialize an empty list for tokens
                   
                   (setf original-tokens (tokenize line))    
                   ;; Tokenize the line and collect DFA results
                   (dolist (token original-tokens)
                     (push (dfa token) line-tokens))
                   
                   ;; Process tokens, passing the output file stream
                   (process (nreverse line-tokens) original-tokens outfile)))))))


;; Example input
(gppinterpreter "input.txt")
(quit)


