#Compiler used
COMPILER=clang
#Output binary name
OUTPUT_BINARY=bkk
#Optimization level of code
OPTIMIZATION_LEVEL=z
#File to compile
MAIN_FILE=main.c
#Flags
FLAGS=-O$(OPTIMIZATION_LEVEL) -o $(OUTPUT_BINARY)

executable:
	$(COMPILER) $(FLAGS) $(MAIN_FILE)

clean:
	rm $(OUTPUT_BINARY)
