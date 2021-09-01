set(target RandomBot)

add_executable(${target} main.cc)

target_link_libraries(${target} PRIVATE Arena)
