INC:=-I../src -I../include -I../include/glad

all: $(filter-out ../src/main.c,$(wildcard ../src/*.c))
	cp -r ../shaders .
	gcc -ftest-coverage -fprofile-arcs -O0 $(INC) -o test_shader ../tests/test_shader.c ../include/glad/*.c $(filter-out ../src/main.c,$(wildcard ../src/*.c)) -ldl -lm -lglfw -lcurl -lgcov --coverage
	./test_shader && cp ../src/*.c . && rm main.c && gcov -abcfu *.c
