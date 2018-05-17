COMPILE = g++

delete: delete.cpp access_data.cpp access_index.cpp BS.cpp
	${COMPILE} delete.cpp access_data.cpp access_index.cpp BS.cpp -g -o delete

delete.cpp : BS.h metadata.h access_data.h access_index.h get_input.h add



add: add.cpp access_data.cpp access_index.cpp BS.cpp
	${COMPILE} add.cpp access_data.cpp access_index.cpp BS.cpp -g -o add

add.cpp : BS.h metadata.h access_data.h access_index.h get_input.h show



show: access_data.cpp access_index.cpp BS.cpp show.cpp
	${COMPILE} show.cpp access_data.cpp access_index.cpp BS.cpp -g -o show

show.cpp : BS.h metadata.h access_data.h access_index.h get_input.h list



list: list.cpp access_data.cpp access_index.cpp BS.cpp
	${COMPILE} list.cpp access_data.cpp access_index.cpp BS.cpp -g -o list

list.cpp : BS.h metadata.h access_data.h access_index.h load



load: load.cpp access_data.cpp access_index.cpp BS.cpp
	${COMPILE} load.cpp access_data.cpp access_index.cpp BS.cpp -g -o load

load.cpp : BS.h metadata.h access_data.h access_index.h showdata.cpp
