
default :
	make build 
	cd build/ && ./main

build : 
	mkdir build
	cd build && cmake .. && make

clean :

	rm -rf build colors/resources_embedded include/textures.h

