#
# To build this you'll need to adjust the directories below. Make sure that the command line is
# 	x64 Native Tools Command Prompt for VS 2022
# to run make you should use
#   > nmake /f Makefile.mak
# 

linalg_vector_tests: 
	cl linalg_vector_tests.cpp \
	/I c:\Projects\libfabbri\third-party\catch2-v2.13.9\include \
	/I c:\Projects\libfabbri\third-party\mpreal-v3.7.0\include \
	/I c:\vcpkg\installed\x64-windows\include \
	c:\vcpkg\installed\x64-windows\lib\mpfr.lib \
	c:\vcpkg\installed\x64-windows\lib\gmp.lib

copy_dll:
	copy c:\vcpkg\installed\x64-windows\bin\mpfr-6.dll .
	copy c:\vcpkg\installed\x64-windows\bin\gmp-10.dll .

clean:
	del /f linalg_vector_tests.exe 2>nul
	del /f linalg_vector_tests.obj 2>nul

clean-all: clean
	del /f mpfr-6.dll 2>nul
	del /f gmp-10.dll 2>nul
