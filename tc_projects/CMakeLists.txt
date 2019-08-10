project(tc_projects)

add_executable(checkers checkers.cpp)
target_link_libraries(checkers lfbg)

add_executable(3dhouse 3dhouse.cpp)
target_link_libraries(3dhouse lfbg)
