
all: build compile

build:
	-mkdir build
ifeq ($(OS),Windows_NT)
	rem visual studio 2017 (version number 15.0)
	cd build && cmake -G "Visual Studio 15" ..
else
	cd build; cmake ..
	#cd build; cmake -DCMAKE_BUILD_TYPE=Debug ..
endif

compile:
ifeq ($(OS),Windows_NT)
	@echo ""
	@echo "Open the project with Visual Studio and compile it ;-)"
else
	make -C build
endif

clean:
ifeq ($(OS),Windows_NT)
	-rmdir build /s /q
else
	rm -rf build
endif

