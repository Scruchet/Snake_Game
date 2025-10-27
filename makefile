
default :
	make build 
	cd build/ && ./main

build : 
	mkdir build
	cd build && cmake .. && make

regular :
	cp colors/regular_colors/* colors/assets
	cd scripts && ./color_chose.sh 0
color :
	cp colors/colorful_snake/* colors/assets
	cd scripts && ./color_chose.sh 1

clean :

	rm -rf build colors/resources_embedded include/textures.h

