.PHONY : all
all : 17.exe

.PHONY : distclean
distclean : clean

.PHONY : clean
clean :
	del /F /Q 17.exe > NUL 2> NUL

17.exe : 17.c
	gcc 17.c -o 17.exe -O3 -Wall -Wextra -Werror -lm


