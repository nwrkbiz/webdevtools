all: linux_x64 linux_x86 windows_x86

linux_x64:
	g++ main.cpp View.cpp ViewFluid.cpp -std=c++17 -static-libstdc++ -static-libgcc -I3rdParty/lib_include/linux_x64 -L3rdParty/lib/linux_x64 -Wl,-Bstatic -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images -lfltk_png -lX11 -lxcb -lXau -lXdmcp -lrt -lz -Wl,-Bdynamic -lpthread -ldl -lm -o web_tools.x64

linux_x86:
	g++ -m32 main.cpp View.cpp ViewFluid.cpp -std=c++17 -static-libstdc++ -static-libgcc -I3rdParty/lib_include/linux_x86 -L3rdParty/lib/linux_x86 -Wl,-Bstatic -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images -lfltk_png -lX11 -lxcb -lXau -lXdmcp -lrt -lz -Wl,-Bdynamic -lpthread -ldl -lm -o web_tools.x86

windows_x86:
	i686-w64-mingw32-windres main.rc mainrc.o
	i686-w64-mingw32-g++ -m32 main.cpp View.cpp ViewFluid.cpp mainrc.o -std=c++17 -static-libstdc++ -static-libgcc -I3rdParty/lib_include/windows_x86 -L3rdParty/lib/windows_x86 -static -mwindows -DWIN32 -D_WIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images -lfltk_png -lz -lm -mwindows -lole32 -luuid -lcomctl32 -lpthread -lwsock32 -lws2_32 -lksuser -lwinmm -lcrypt32 -o web_tools.win32.exe

clean:
	rm -rf mainres.o web_tools.win32.exe web_tools.x86 web_tools.x64