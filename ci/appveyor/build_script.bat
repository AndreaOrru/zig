cd %APPVEYOR_BUILD_FOLDER%
echo MSYS2 directory: %MSYS2_DIR%
echo MSYS2 system: %MSYSTEM%
SET "PATH=C:\%MSYS2_DIR%\%MSYSTEM%\bin;C:\%MSYS2_DIR%\usr\bin;%PATH%"

bash -lc "pacman -Syu --noconfirm"
bash -lc "pacman -Su --noconfirm"
bash -lc "pacman -S --noconfirm make mingw64/mingw-w64-x86_64-make mingw64/mingw-w64-x86_64-cmake mingw64/mingw-w64-x86_64-clang mingw64/mingw-w64-x86_64-llvm mingw64/mingw-w64-x86_64-lld mingw64/mingw-w64-x86_64-gcc"

bash -lc "mkdir build && cd build && cmake .. -G""MSYS Makefiles"" -DCMAKE_INSTALL_PREFIX=$(pwd) -DZIG_LIBC_LIB_DIR=$(dirname $(cc -print-file-name=crt1.o)) -DZIG_LIBC_INCLUDE_DIR=$(echo -n | cc -E -x c - -v 2>&1 | grep -B1 ""End of search list."" | head -n1 | cut -c 2- | sed ""s/ .*//"") -DZIG_LIBC_STATIC_LIB_DIR=$(dirname $(cc -print-file-name=crtbegin.o)) && make && make install"
