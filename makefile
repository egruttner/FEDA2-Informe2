CC = g++
CFLAGS = -std=c++14 -O2

SRCS = main.cpp 
OBJS = $(SRCS:.cpp=.o)

TEST_CASES_NUMBER := $(shell seq 1 5) #rango de archivos de input y output

# Experimentos con posición fija, cambio de tamaño
RANGE_1 = 1 2 3 4 5 6

# -> BINOMIAL HEAP
# 1 INSERCIÓN
# 2 UNIÓN
# 3 ELIMINACIÓN

# -> BINARY HEAP
# 4 INSERCIÓN
# 5 UNIÓN
# 6 ELIMINACIÓN

INPUT_PREFIX := datasets/input$(num_dataset)/input

OUTPUT_PREFIX := output/output$(num_dataset)/output

all: program
	for j in $(RANGE_1); do \
		echo "Crea cabecera en CSV"; \
		./program $$j --head $$num_dataset; \
		for i in $(TEST_CASES_NUMBER); do \
			echo "./program --pruebas $$j $$num_dataset < $(INPUT_PREFIX)$$i.txt > $(OUTPUT_PREFIX)$$j$$i.txt"; \
			./program $$j --pruebas $$num_dataset < $(INPUT_PREFIX)$$i.txt > $(OUTPUT_PREFIX)$$j$$i.txt; \
		done; \
	done

program: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o program

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) program output*