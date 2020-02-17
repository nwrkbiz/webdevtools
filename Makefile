all: linux_amd64 linux_i386 linux_armhf linux_mips linux_mipsel linux_ppc linux_s390x windows_32 windows_64

linux_amd64:
	x86_64-linux-gnu-g++ -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

linux_i386:
	x86_64-linux-gnu-g++ -m32 -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

linux_armhf:
	arm-linux-gnueabihf-g++ -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

linux_mipsel:
	mipsel-linux-gnu-g++ -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -latomic -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

linux_mips:
	mips-linux-gnu-g++ -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -latomic  -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

linux_ppc:
	powerpc-linux-gnu-g++ -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -latomic -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

linux_s390x:
	s390x-linux-gnu-g++ -O3 main.cpp View.cpp ViewFluid.cpp -std=c++17 -g -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib -static -lc -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images  -lXinerama -lXft  -lXrender -lXfixes -lXext -lX11 -lxcb -lXau -lXdmcp -lpng -lfreetype -lrt -lz -lpthread -ldl -lm -o web_tools.$@

windows_32:
	i686-w64-mingw32-windres main.rc mainrc.32.o
	i686-w64-mingw32-g++ -O3 -m32 main.cpp View.cpp ViewFluid.cpp mainrc.32.o -std=c++17 -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib  -static -mwindows -DWIN32 -D_WIN32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images -lpng -lfreetype -lz -lm -mwindows -lole32 -luuid -lcomctl32 -lpthread -lwsock32 -lws2_32 -lksuser -lwinmm -lcrypt32 -o web_tools.$@.exe

windows_64:
	x86_64-w64-mingw32-windres main.rc mainrc.64.o
	x86_64-w64-mingw32-g++ -O3 main.cpp View.cpp ViewFluid.cpp mainrc.64.o -std=c++17 -static-libstdc++ -static-libgcc -I3rdParty/$@/include -L3rdParty/$@/lib  -static -mwindows -DWIN32 -D_WIN32 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64  -lboost_system -lboost_iostreams -lssl -lcrypto -lstdc++fs -lfltk -lfltk_images -lpng -lfreetype -lz -lm -mwindows -lole32 -luuid -lcomctl32 -lpthread -lwsock32 -lws2_32 -lksuser -lwinmm -lcrypt32 -o web_tools.$@.exe

clean:
	rm -rf mainrc.32.o mainrc.64.o web_tools.linux_amd64 web_tools.linux_i386 web_tools.linux_armhf web_tools.linux_mips web_tools.linux_mipsel web_tools.linux_ppc web_tools.linux_s390x web_tools.windows_32.exe web_tools.windows_64.exe