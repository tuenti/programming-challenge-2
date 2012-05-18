.PHONY : myall

amyall : 20_fast_64.exe



.PHONY : all

all : 20.exe 20_fast.exe 20_fast_64.exe 20_fast_old.exe 20_fast_old_64.exe



.PHONY : distclean

distclean : clean



.PHONY : clean

clean :

	del /F /Q 20.exe 20_fast.exe 20_fast_64.exe 20_fast_old.exe 20_fast_old_64.exe > NUL 2> NUL



20.exe : 20.c

	gcc 20.c -o 20.exe -O3 -Wall -Wextra



20_fast.exe : 20_fast.c

	gcc 20_fast.c -o 20_fast.exe -O3 -Wall -Wextra -finline-limit=999999999 -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations -ftree-loop-linear -fivopts -fvect-cost-model -ftracer -funroll-loops -freorder-blocks-and-partition -fwhole-program



20_fast_64.exe : 20_fast.c

	mingw64\bin\x86_64-w64-mingw32-gcc 20_fast.c -o 20_fast_64.exe -O3 -Wall -Wextra -finline-limit=999999999 -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations -fivopts -fvect-cost-model -ftracer -funroll-loops -freorder-blocks-and-partition -fwhole-program



20_fast_old.exe : 20_fast_old.c

	gcc 20_fast_old.c -o 20_fast_old.exe -O3 -Wall -Wextra -finline-limit=999999999 -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations -ftree-loop-linear -fivopts -fvect-cost-model -ftracer -funroll-loops -freorder-blocks-and-partition -fwhole-program



20_fast_old_64.exe : 20_fast_old.c

	mingw64\bin\x86_64-w64-mingw32-gcc 20_fast_old.c -o 20_fast_old_64.exe -O3 -Wall -Wextra -finline-limit=999999999 -fgcse-sm -fgcse-las -fgcse-after-reload -funsafe-loop-optimizations -fivopts -fvect-cost-model -ftracer -funroll-loops -freorder-blocks-and-partition -fwhole-program





