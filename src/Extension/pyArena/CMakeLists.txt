# Target name
set(target pyArena)

# Sources
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

pybind11_add_module(${target} ${sources})

target_include_directories(${target} 
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

target_link_libraries(${target}
	PRIVATE
	Arena
	${DEFAULT_LINKER_OPTIONS}
)
