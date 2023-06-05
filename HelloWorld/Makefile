OBJECTS = ./func_add_temp.o
all: ${OBJECTS}

	gcc hex_binary_add.c ${OBJECTS} -o hex_binary_add

clean:
#del temp.exe
# %.o %.c can be used for
	del func_add_temp.o

func_add_temp.o:func_add_temp.c

	gcc -c func_add_temp.c -o func_add_temp.o