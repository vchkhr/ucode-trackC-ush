NAME = libmx.a

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: create_obj LIBMX compile

create_obj:
	mkdir obj

LIBMX:
	clang $(FLAGS) -Iinc -c src/*.c
	mv *.o obj/

compile:
	ar -rc $(NAME) obj/*.o
	ranlib $(NAME)

clean:
	rm -rf obj

uninstall:
	rm -rf obj
	rm -rf $(NAME)

reinstall:
	make uninstall
	make
