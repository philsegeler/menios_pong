
build:
	meson compile -C builddir

clean-web:
	rm -rf builddir
	meson setup builddir --cross-file emscripten_linux.cross
	cp cross_config/menios_pong.html builddir/menios_pong.html

run-web: build
	emrun --no_browser builddir/menios_pong.html

clean:
	rm -rf builddir
	meson setup builddir

run: build
	./builddir/menios_pong

clean-windows:
	rm -rf builddir
	meson setup builddir --cross-file mingw_linux.cross
	cp cross_config/libEGL.dll builddir/libEGL.dll
	cp cross_config/libGLESv2.dll builddir/libGLESv2.dll
	cp cross_config/d3dcompiler_43.dll builddir/d3dcompiler_43.dll
	cp /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll builddir/libwinpthread-1.dll

run-windows: build
	wine builddir/menios_pong.exe
