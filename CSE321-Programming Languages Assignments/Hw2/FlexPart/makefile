FLEX = flex
COMPILER = gcc
FILE = gpp_lexer
INPUTFILE = input.txt
OUTPUTFILE = output.txt


all: flex interactive input output

flex: ${FILE}.l
	${FLEX} -o ${FILE}.c $(FILE).l
	${COMPILER} ${FILE}.c -o ${FILE}

interactive:	
	./${FILE}

input:
	./${FILE} ${INPUTFILE}

output:
	./${FILE} ${INPUTFILE} > ${OUTPUTFILE}