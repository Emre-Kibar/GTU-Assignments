(defun split-parentheses (token)
  ;; Splits a token into smaller tokens by extracting leading and trailing parentheses separately.
  (let ((leading '())
        (trailing '())
        (cleared-part token))  ;; Start with the entire token as the cleared part
    ;; Extract leading parentheses
    (loop
       while (and (not (string= cleared-part "")) (char= (char cleared-part 0) #\())
       do (progn
            (push "(" leading)
            (setf cleared-part (subseq cleared-part 1))))
    ;; Extract trailing parentheses
    (loop
       while (and (not (string= cleared-part "")) (char= (char cleared-part (1- (length cleared-part))) #\)))
       do (progn
            (push ")" trailing)
            (setf cleared-part (subseq cleared-part 0 (1- (length cleared-part))))))
    ;; Collect results: leading parentheses, cleared part (if any), and trailing parentheses
    (append (nreverse leading)  ;; Reverse leading to maintain original order
            (if (not (string= cleared-part "")) (list cleared-part))  ;; Push cleared part if not empty
            trailing)))  ;; No need to reverse trailing, as it was built in reverse order

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

(defun string-prefix (prefix string)
  ;; Check if the string starts with the given prefix.
  (let ((prefix-length (length prefix))
        (string-length (length string)))
    (and (>= string-length prefix-length) ;; Ensure the string is long enough
         (loop for i from 0 below prefix-length
               always (char= (elt string i) (elt prefix i))))))

(defun fraction-match (string)
  ;; Check if the string matches the pattern (e.g., fractional number like 12f34).
  (let ((f-position (position #\f string)))  ;; Find the position of 'f' in the string
    (and f-position
         (> f-position 0)  ;; Ensure there are digits before 'f'
         (< f-position (- (length string) 1))  ;; Ensure there are digits after 'f'
         (every #'digit-char-p (subseq string 0 f-position))  ;; Check for digits before 'f'
         (every #'digit-char-p (subseq string (1+ f-position))))))  ;; Check for digits after 'f'


(defun tokenize (line)
  ;; Split the line into tokens, handling parentheses and comments, and trimming whitespace.
  (let ((trimmed-line (string-trim '(#\Space #\Tab #\Newline #\Return) line))  ;; Trim unwanted characters
        (tokens '()))
    ;; Check if the line starts with ';;'
    (if (string-prefix ";;" trimmed-line)
        ;; Entire line is a comment
        (progn
          (push trimmed-line tokens))  ;; Push the entire line as a single token
        ;; Otherwise, handle code and inline comments
        (let* ((comment-pos (position #\; trimmed-line))  ;; Find the position of the first semicolon
               (code (if comment-pos (subseq trimmed-line 0 comment-pos) trimmed-line))  ;; Code before the first semicolon
               (comment (if comment-pos (subseq trimmed-line comment-pos))))  ;; Everything from the first semicolon
          ;; Tokenize code part
          (when code
            (dolist (word (remove-if #'(lambda (x) (string= x "")) 
                                     (mapcan #'(lambda (word) (split-parentheses word)) 
                                             (split-by-delimiter code #\Space))))
              (push word tokens)))
          ;; Add the comment as a single token, if it exists
          (when comment
            (push comment tokens))))
    (nreverse tokens)))


(defun dfa (token)
  ;; Determine the type of token or report syntax errors for invalid characters.
  (let ((clean-token (string-trim '(#\Space #\Tab) (string-downcase token)))) ;; Normalize token
    (cond
      ;; Keywords
      ((member clean-token '("and" "or" "not" "equal" "less" "nil" "list"
                             "append" "concat" "set" "deffun" "for" "if"
                             "exit" "load" "print" "true" "false") :test #'string=)
       (format nil "KW_~A" 
               (if (string= clean-token "print") 
                   "DISP" 
                   (string-upcase clean-token))))

      ;; Operators
      ((member clean-token '("+" "-" "/" "*" "(" ")" ",") :test #'string=)
       (cond ((string= clean-token "+") "OP_PLUS")
             ((string= clean-token "-") "OP_MINUS")
             ((string= clean-token "/") "OP_DIV")
             ((string= clean-token "*") "OP_MULT")
             ((string= clean-token "(") "OP_OP")
             ((string= clean-token ")") "OP_CP")
             ((string= clean-token ",") "OP_COMMA")))

      ;; Comments
      ((string-prefix ";;" clean-token) "COMMENT") ;; Using string-prefix

      ;; Single semicolon error
      ((and (string-prefix ";" clean-token)
            (not (string-prefix ";;" clean-token)))
       "COMMENT_ERROR: You must use ';;' for comments.")

      ;; Check for invalid characters
      ((some (lambda (c)
               (not (or (alpha-char-p c) ;; Alphabetic characters
                        (digit-char-p c) ;; Digits
                        (member c '(#\+ #\- #\/ #\* #\( #\) #\, #\; #\_ #\Space))))) ;; Valid operators and symbols
             clean-token)
       (let ((invalid-char (some (lambda (c)
                                   (if (not (or (alpha-char-p c)
                                                (digit-char-p c)
                                                (member c '(#\+ #\- #\/ #\* #\( #\) #\, #\; #\_ #\Space))))
                                       c
                                       nil))
                                 clean-token)))
         (format nil "CHARACTER_ERROR: ~A is an invalid character" invalid-char)))

      ;; Unsigned integers
      ((every #'digit-char-p clean-token) "VALUEI")

      ;; Fractions
      ((fraction-match clean-token) "VALUEF") ;; Using fraction-match

      ;; Check if the token has multiple 'f's for a fraction-like pattern
      ((let ((f-count (count #\f token)))
        (and (> f-count 1)
              (every #'digit-char-p (remove #\f token))))
        "VALUEF_ERROR: Fractions must contain exactly one 'f'.")

      ;; Identifiers
      ((and (alpha-char-p (char clean-token 0))
            (every (lambda (c) (or (alpha-char-p c)
                                   (digit-char-p c)
                                   (char= c #\_))) clean-token))
        "IDENTIFIER")

      ;; Check if the token starts with digits but contains alphabetic characters
      ((and (digit-char-p (char token 0))
            (some #'alpha-char-p token))
        "IDENTIFIER_ERROR: Identifiers cannot start with a number.")

      ;; General syntax error
      (t (format nil "SYNTAX_ERROR: ~A cannot be tokenized" clean-token)))))


(defun gppinterpreter (&optional inputFile)
  (format t "Welcome to GPP Lexer!~%")
  
  ;; If an input file is provided
  (when inputFile
    (with-open-file (stream inputFile :direction :input)
      (with-open-file (outfile "output.txt" :direction :output :if-exists :supersede)
        (loop for line = (read-line stream nil)
              while line
              do (let ((tokens (tokenize line)))
                   (dolist (token tokens)
                     (format outfile "~A~%" (dfa token))))))))
  ;; If no input file, process terminal input until "exit"
  (loop
    ;; Print the prompt
    (format t "Enter line(Type 'exit' to quit.): ")
    (force-output)  ;; Ensure that the prompt is printed immediately
    (let ((line (read-line)))  ;; Then read the input
      (if (string= line "exit")
          (progn
            ;; Send 'exit' to DFA for processing before quitting
            (format t "~A~%" (dfa "exit"))
            (return))  ;; Exit after processing 'exit'
          ;; Otherwise, process the input as usual
          (let ((tokens (tokenize line)))  ;; Tokenize the input
            (dolist (token tokens)
              (format t "~A~%" (dfa token))))))))

(gppinterpreter "input.txt")
