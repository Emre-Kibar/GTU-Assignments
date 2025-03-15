; Search the string for a substring and returns true if there is else returns false.
(defun contains-substring (substring string)
  (not (null (search substring string))))

; Trims initial and trailing spaces and determine the line-type based on keywords and characters.
(defun line-type (line)
  (let ((trimmed-line (string-trim " " line))) 
    (cond
      ((contains-substring "printf" trimmed-line) 'printf-statement)
      ((contains-substring "return" trimmed-line) 'return-statement)
      ((and (contains-substring "if" trimmed-line)
            (contains-substring "(" trimmed-line)
            (contains-substring ")" trimmed-line)) 'if-statement)
      ((and (contains-substring "for" trimmed-line)
            (contains-substring "(" trimmed-line)
            (contains-substring ")" trimmed-line)) 'for-loop)
      ((and (contains-substring "while" trimmed-line)
            (contains-substring "(" trimmed-line)
            (contains-substring ")" trimmed-line)) 'while-loop)
      ((and (contains-substring "(" trimmed-line)
            (contains-substring "{" trimmed-line)) 'function-definition)
      ((and (contains-substring "(" trimmed-line)
            (contains-substring ";" trimmed-line)
            (not (contains-substring "=" trimmed-line))) 'function-prototype-definition)
      ((and (contains-substring "(" trimmed-line)
            (contains-substring ")" trimmed-line)
            (not (contains-substring "=" trimmed-line))) 'function-call)
      ((or (contains-substring "int" trimmed-line)
           (contains-substring "float" trimmed-line)
           (contains-substring "double" trimmed-line)
           (contains-substring "char" trimmed-line)) 'variable-definition) 
      ((contains-substring "=" trimmed-line) 'assignment)     
      ((contains-substring "}" trimmed-line) 'block-end)
      (t 'unknown))))

; Return the conversion-function based on lineType.
(defun conversion-foo (type)
  (cond
    ((eq type 'if-statement) 'convert-if)
    ((eq type 'for-loop) 'convert-for)
    ((eq type 'while-loop) 'convert-while)
    ((eq type 'variable-definition) 'convert-var-def)
    ((eq type 'assignment) 'convert-assignment)
    ((eq type 'function-definition) 'convert-func-def)
    ((eq type 'function-prototype-definition) 'convert-func-pro-def)
    ((eq type 'function-call) 'convert-func-call)
    ((eq type 'printf-statement) 'convert-print)
    ((eq type 'return-statement) 'convert-return)
    ((eq type 'block-end) 'convert-block-end)
    (t 'convert-unknown))) 

; Calls the conversion-function with the line.
(defun convert (line conversion-fn)
  (funcall conversion-fn line))

(defun split-by-delimiter (line delimiter)
  (remove-if #'(lambda (x) (string= x ""))  ; Remove empty substrings caused by consecutive delimiters
             (let ((result '()))  ; Initialize an empty list to store results
               (loop while (find delimiter line)  ; Continue until no delimiter is found
                     for delimiter-pos = (position delimiter line)  ; Position of the delimiter
                     for part = (subseq line 0 delimiter-pos)  ; Extract part before the delimiter
                     do (progn
                          (push part result)  ; Collect the part
                          (setf line (subseq line (1+ delimiter-pos)))))  ; Update the line after the current delimiter
               (push line result)  ; Add the remaining part of the line
               (nreverse result))))  ; Reverse the list to maintain the original order

(defun replace-operators (token)
  ; Replace C-style operators in the given token with Lisp equivalents.
  (cond
    ((string= token "<=") "<=")
    ((string= token ">=") ">=")
    ((string= token "==") "=")
    ((string= token "!=") "/=")
    ((string= token "<") "<")
    ((string= token ">") ">")
    (t token)))  ; Return the token unchanged if no match

;if (x == a) {             
(defun convert-if (line)
  (let* ((tokens (split-by-delimiter line #\Space))
         ;; Extract the condition part, skipping the 'if' and parentheses
         (condition (subseq tokens 1 (- (length tokens) 1)))
         (first-operand (subseq (first condition) 1))         ;; Remove the opening parenthesis
         (operator (second condition))                        ;; Operator (e.g., ==)
         (second-operand (subseq (third condition) 0 (1- (length (third condition))))) ;; Remove the closing parenthesis
         (modified-operator (replace-operators operator)))
    ;; Format the Lisp 'if' expression
    (format nil "(if (~a ~a ~a)" modified-operator first-operand second-operand)))

;for (int i = 0; i < 10; i++) {
(defun convert-for (line)
  (let* ((tokens (split-by-delimiter line #\Space))                  ; Split the line into tokens
         (init (subseq tokens 1 5))                                  ; Extract the initialization part: "(int i = 0;"
         (condition (subseq tokens 5 8))                             ; Extract the condition part: "i < 10;"
         (increment (nth 8 tokens)))                                  ; Extract the increment part: "i++)"
    (let* ((var-name (nth 1 init))                                   ; Variable name: "i"
           (start-value (remove-if-not #'digit-char-p (nth 3 init)))  ; Extracts the digits from the start value
           (end-value (remove-if-not #'digit-char-p (nth 2 condition)))  ; Extracts the digits from the end value
           (increment-sign (if (search "++" increment) 'up 'down)))  ; Check increment/decrement
      
      (format nil "(loop for ~a from ~a ~a ~a do" 
              var-name 
              start-value 
              (if (eq increment-sign 'up) "below" "above")  ; Use 'below for increment, 'above for decrement
              end-value))))

;while (i < 10) {
(defun convert-while (line)
  (let* ((tokens (split-by-delimiter line #\Space))  ; Split the line into tokens
         (condition (subseq tokens 1 (- (length tokens) 1)))  ; Extract the condition part
         (first-operand (subseq (first condition) 1))         ;; Remove the opening parenthesis
         (operator (second condition))                        ;; Operator (e.g., ==)
         (second-operand (subseq (third condition) 0 (1- (length (third condition)))))
         (modified-operator (replace-operators operator)))  ; Concatenate tokens into a single string
    (format nil "(loop while (~a ~a ~a) do" modified-operator first-operand second-operand )))  ; Format with single condition string    

;var1 = sum(2, 3); / int var1 = sum(2, 3);
(defun convert-assignment-by-func (line var-def-check)
  (let* ((equal-pos (position #\= line))                        ; Find position of the '='
         (var-name (string-trim " " (subseq line 0 equal-pos))) ; Extract variable name before '='
         ;; Split var-name into tokens and check length
         (var-tokens (split-by-delimiter var-name #\Space))      ; Split var-name by spaces
         (final-var-name (if (= (length var-tokens) 2)           ; Check if length is 2
                             (second var-tokens)                 ; Take the second token
                             var-name))                          ; Otherwise, keep var-name as is
         (func-call-part (string-trim " " (subseq line (1+ equal-pos)))) ; Extract function call part after '='
         (func-name-end (position #\( func-call-part))           ; Find where the function name ends (before '(')
         (func-name (subseq func-call-part 0 func-name-end))     ; Extract function name
         (args-start (1+ func-name-end))                         ; Start of the arguments (after '(')
         (args-end (position #\) func-call-part))                ; End of arguments (before ')')
         (args (subseq func-call-part args-start args-end)))     ; Extract arguments between '(' and ')'

    ;; Now we clean up and reformat the arguments by splitting them on commas
    (let ((args-list (mapcar (lambda (x) (string-trim " " x))
                             (split-by-delimiter args #\,))))      ; Split arguments by comma, and trim spaces
      ;; Format based on check value
      (if (= var-def-check 1)
          (format nil "(let (~a (~a ~{~a~^ ~})))" final-var-name func-name args-list)
          (format nil "(setf ~a (~a ~{~a~^ ~}))" final-var-name func-name args-list)))))


;int var1; / int var1 = 10; / int var1 = a + b; / int var1 = sum(2, 3);
(defun convert-var-def (line)
  ;; Get the formatted line up to the semicolon
  (let* ((formatted-line (string-trim " " (subseq line 0 (search ";" line)))))
    ;; Check if the line has both an opening and closing parenthesis after the '='
    (if (and (search "=" formatted-line) (search "(" formatted-line) (search ")" formatted-line))
        ;; If it’s a function call assignment, delegate to convert-assignment-by-func
        (convert-assignment-by-func formatted-line 1)
        ;; Otherwise, process as a variable definition or operation
        (let* ((tokens (split-by-delimiter formatted-line #\Space))
               (var-name (nth 1 tokens))
               (value (if (and (> (length tokens) 3)
                               (string= (nth 2 tokens) "="))
                          (subseq tokens 3)
                          nil)))
          (if value
              ;; Check if the value is a single element or an operation
              (if (= (length value) 1)
                  (format nil "(let (~a ~a))" var-name (first value))
                  ;; Process as an operation
                  (let ((operator (second value))
                        (first-operand (first value))
                        (second-operand (third value)))
                    (if (and operator first-operand second-operand
                             (member (string operator)
                                     '("+" "-" "*" "/" "==" "!=" "<" ">" "<=" ">=") :test #'string=))
                        (format nil "(let (~a (~a ~a ~a)))" var-name operator first-operand second-operand)
                        ;; Fallback to simple let binding
                        (format nil "(let (~a ~a))" var-name (first value)))))
              ;; If no value, declare the variable
              (format nil "(defvar ~a)" var-name))))))


;var1 = 10; / var1 = a + b; /var1 = sum(2, 3);
(defun convert-assignment (line)
  ;; Trim whitespace from the beginning and end of the line, then get the formatted line up to the semicolon
  (let* ((formatted-line (string-trim " " (subseq line 0 (search ";" line)))))
    ;; Check if the line has both an opening and closing parenthesis after the '='
    (if (and (search "(" formatted-line) (search ")" formatted-line))
        ;; If it’s a function call assignment, delegate to convert-assignment-by-func
        (convert-assignment-by-func formatted-line 0)
        ;; Else process as a regular assignment
        (let* ((tokens (split-by-delimiter formatted-line #\Space))
               (var-name (first tokens))
               (value (subseq tokens 2)))  ; Get everything after the variable name and '='
          ;; Check if the value is a single element or an operation
          (if (= (length value) 1)
              (format nil "(setf ~a ~a)" var-name (first value))
              ;; Process as an operation
              (let ((operator (second value))
                    (first-operand (first value))
                    (second-operand (third value)))
                (if (and operator first-operand second-operand
                         (member (string operator)
                                 '("+" "-" "*" "/" "==" "!=" "<" ">" "<=" ">=") :test #'string=))
                    (format nil "(setf ~a (~a ~a ~a))" var-name operator first-operand second-operand)
                    ;; If invalid, default to simple assignment
                    (format nil "(setf ~a ~a)" var-name (first value)))))))))

;int sum(int a, int b) {  / float mult(int a, int b, int c) {
(defun convert-func-def (line)
  (let* ((func-name-end (position #\( line))               ; Find the position where the function name ends
         (func-declaration (split-by-delimiter (subseq line 0 func-name-end) #\Space)) ; Split the part before '('
         (func-name (car (last func-declaration)))          ; Extract the function name (last part of the declaration)
         (params-start (1+ func-name-end))                 ; Start of the parameters
         (params-end (position #\) line))                  ; End of the parameters
         (params-string (subseq line params-start params-end)) ; Extract the parameter substring
         (params-list (mapcar #'(lambda (param)
                                  (string-trim " " (nth 1 (split-by-delimiter param #\Space))))  ; Keep only the variable name
                              (split-by-delimiter params-string #\,))))  ; Split parameters by commas

    ;; Format the output as (defun func-name (param1 param2 ...) ...)
    (format nil "(defun ~a (~{~a~^ ~})" func-name params-list))) ; Close the parentheses correctly

;int sum(int a, int b);  / float mult(int a, int b, int c); 
(defun convert-func-pro-def (line)
  (let* ((func-name-end (position #\( line))                ; Find where the function name ends (before '(')
         (func-declaration (split-by-delimiter (subseq line 0 func-name-end) #\Space)) ; Split the declaration
         (func-name (car (last func-declaration)))          ; Extract the function name (last part)
         (return-type (car func-declaration))               ; Extract the return type (first part)
         (params-start (1+ func-name-end))                  ; Start of the parameters
         (params-end (position #\) line))                   ; End of the parameters
         (params-string (subseq line params-start params-end)) ; Extract the parameter substring
         (params-list (mapcar #'(lambda (param)
                                  (nth 0 (split-by-delimiter param #\Space)))  ; Extract the data type only (e.g., 'int')
                              (split-by-delimiter params-string #\,))) ; Split parameters by commas
         ;; Map C types to Lisp types for parameters
         (mapped-types (mapcar #'(lambda (type)
                                   (cond
                                     ((string= type "int") "integer")
                                     ((string= type "float") "float")
                                     ((string= type "double") "float")
                                     ((string= type "char") "character")
                                     (t "unknown")))        ; Add other types if necessary
                               params-list))
         ;; Map return type from C to Lisp
         (mapped-return-type (cond
                               ((string= return-type "int") "integer")
                               ((string= return-type "float") "float")
                               ((string= return-type "double") "float")
                               ((string= return-type "char") "character")
                               (t "unknown"))))              ; Handle unknown types
         
    ;; Format the output as a declaim statement
    (format nil "(declaim (ftype (function (~{~a~^ ~}) ~a) ~a))"
            mapped-types mapped-return-type func-name)))

;sum(a, b); / mult(a, b, c, d);         
(defun convert-func-call (line)
  ;; Step 1: Remove the semicolon at the end of the line
  (let* ((clean-line (string-trim ";" line))
         ;; Step 2: Find where the function name ends (before '(')
         (func-name-end (position #\( clean-line))
         ;; Extract the function name
         (func-name (string-trim " " (subseq clean-line 0 func-name-end)))
         ;; Step 3: Find the arguments between '(' and ')'
         (args-start (1+ func-name-end))  ; Start of arguments (after '(')
         (args-end (position #\) clean-line))  ; End of arguments (before ')')
         ;; Extract and clean up the arguments
         (args-string (if args-end
                          (subseq clean-line args-start args-end)
                            ""))  ; If no closing parenthesis, assume no arguments
         (args (mapcar #'(lambda (arg) (string-trim " " arg))
                       (split-by-delimiter args-string #\,))))  ; Split arguments by comma

    ;; Step 4: Format the function call in Lisp-style: (func-name arg1 arg2 ...)
    (format nil "(~a ~{~a~^ ~})" func-name args)))


(defun replace-format-specifiers (format-string)
  ;; Define a list of replacement pairs, where each car is the C-style format specifier 
  ;; and each cdr is the corresponding Lisp format specifier.
  (let ((replacements '(("%d" . "~d")   ; integer
                        ("%s" . "~a")   ; string
                        ("%f" . "~f")   ; float
                        ("%c" . "~c")   ; character
                        ("\\n" . "~%")))) ; newline
    ;; Loop over each pair in replacements
    (dolist (pair replacements format-string)
      ;; Continuously search for the C-style specifier in the format-string
      (loop 
         for pos = (search (car pair) format-string) ;; Find the position of the C-style specifier
         while pos ;; While a match is found
         do 
           ;; Replace the C-style specifier with the corresponding Lisp specifier
           (setf format-string 
                 (concatenate 'string 
                              (subseq format-string 0 pos) ;; Text before the found specifier
                              (cdr pair)                   ;; Replacement Lisp specifier
                              (subseq format-string (+ pos (length (car pair))))))))) ;; Text after
  ;; Return the modified format-string
  format-string)

; printf("Hello, World! %d", variable); / printf("%d %c %f %s", int1, char1, float1, string1);
(defun convert-print (line)
  (let* ((func-name-end (position #\( line))                     ; Find the position where the function name ends
         (params-start (1+ func-name-end))                      ; Start of the parameters
         (params-end (position #\) line))                        ; End of the parameters
         (params-string (subseq line params-start params-end))   ; Extract the parameter substring
         ;; Find the start and end of the format string within the params
         (args-start (position #\" params-string))               ; Start of the format string
         (format-string-end (position #\" params-string :start (1+ args-start))) ; End of the format string
         (format-string (subseq params-string (1+ args-start) format-string-end)) ; Extract format string
         ;; Convert the format string C specifiers to Lisp format specifiers
         (converted-format-string (replace-format-specifiers format-string))
         ;; Extract the arguments part (after the format string)
         (args-part (subseq params-string (1+ format-string-end)) )
         ;; Extract and clean up the arguments list
         (args-list (mapcar #'(lambda (x) (string-trim " " x))
                            (split-by-delimiter (subseq args-part 0 (position #\) args-part)) #\,))))
    
    ;; Format the output as (format t "~d~a" var1 var2 ...)
    (format nil "(format t ~S ~{~a~^ ~})" converted-format-string args-list)))

; return a; / return 3; / return a + b;
(defun convert-return (line)
  ;; Step 1: Remove the semicolon at the end of the line and any extra whitespace
  (let* ((formatted-line (string-trim " " (subseq line 0 (search ";" line))))
         (clean-line (string-trim '(#\Space #\; #\Newline) formatted-line))
         ;; Step 2: Split the line into tokens, filtering out empty spaces
         (tokens (remove "" (split-by-delimiter clean-line #\Space)))
         ;; Step 3: Remove the first token ("return") and keep the rest as the expression
         (expression (cdr tokens)))
    
    ;; Step 4: Convert based on the number of tokens in the expression
    (if (= (length expression) 1)
        ;; Single token case, wrap it in parentheses as the return expression
        (format nil "(~a)" (car expression))
        
        ;; Multi-token case, format in prefix notation with the operator and operands
        (let ((operator (second expression))
              (firstOperand (first expression))
              (secondOperand (third expression)))
          (format nil "(~a ~a ~a)" operator firstOperand secondOperand)))))

;}
(defun convert-block-end (line)
  ;; Use the line variable in some way
  (format nil "Converting block end for: ~a" line)
  ")")
  
(defun convert-unknown (line)
  (format nil ";; Unknown line type: ~a" line)
  "")  

; Reads the input file line by line and returns them. 
(defun read-file (file)
  (with-open-file (stream file)
    (loop for line = (read-line stream nil nil)
          while line collect line)))

; Writes all converted lines into the output file.
(defun write-file (file lines)
  (with-open-file (stream file :direction :output :if-exists :supersede)
    (dolist (line lines)
      (write-line line stream))))  

; Creates a string formed with whitespaces for indentation.
(defun calculate-indentation (indent-level)
  (make-string (* indent-level 2) :initial-element #\Space)) 

(defun recursive-process (lines &optional (indent-level 0) (if-flag 0) (if-close 0))
  (if (null lines)
      '()
      (let* ((line (car lines)) ;Takes the first line.
             (type (line-type line)) ;Determine type of the line.
             (conversion-func (conversion-foo type)) ; Determine the conversion function based on line type.
             (converted-line (convert line conversion-func)) ; Convert the line based on selected conversion function
             (updated-if-flag (if (contains-substring "if" line) 1 0)) ; If the line is "if" line then updated-if-flag is 1 else 0. This indicates the "if" line encountered.
             (updated-if-close (if (and (= updated-if-flag 1) (= if-close 0)) 1 if-close))) ; updated-if-close initialized 1 or current if-close value based on conditions.

        (cond
         ;; Case: If the line "if" line then it will be printed "(progn)" in the next line.
         ((and (eq type 'if-statement)(contains-substring "{" line))
          (cons (concatenate 'string (calculate-indentation indent-level) converted-line (string #\Newline) (calculate-indentation (+ indent-level 1)) "(progn" )
                (recursive-process (cdr lines) (1+ indent-level) updated-if-flag updated-if-close)))

         ;; Case: Opening brace `{`
         ((contains-substring "{" line)
          (cons (concatenate 'string (calculate-indentation indent-level) converted-line)
                (recursive-process (cdr lines) (1+ indent-level) updated-if-flag updated-if-close)))

         ;; Case: Closing brace `}` and `if-close` is 1
         ((and (contains-substring "}" line) (= if-close 1))
          ;; Add `))` to close both `if` and `progn`
          (let ((new-line (concatenate 'string (calculate-indentation (- indent-level 2)) converted-line ")")))
            (cons new-line
                  (recursive-process (cdr lines) (- indent-level 2) updated-if-flag 0)))) ; Reset if-close to 0 because if block ended.

         ;; Case: Closing brace `}` without if-close
         ((contains-substring "}" line)
          (cons (concatenate 'string (calculate-indentation (1- indent-level)) converted-line)
                (recursive-process (cdr lines) (1- indent-level) updated-if-flag updated-if-close)))

         ;; Default case: Regular line
         (t
          ;; Adjust indentation based on if-flag
          (if (= if-flag 1)
              ;; If flag is set, increase indentation by +2 (for `if` and `progn`), then proceed
              (cons (concatenate 'string (calculate-indentation (+ indent-level 1)) converted-line)
                    (recursive-process (cdr lines) (+ indent-level 1) updated-if-flag updated-if-close))
              ;; Otherwise, use the regular indentation level
              (cons (concatenate 'string (calculate-indentation indent-level) converted-line)
                    (recursive-process (cdr lines) indent-level updated-if-flag updated-if-close))))))))

; Reads the line and convert the lines one by one at the end writes them into output file
(defun main (input-file output-file)
  (let* ((lines (read-file input-file))
         (converted-lines (recursive-process lines)))
    (write-file output-file converted-lines)))

