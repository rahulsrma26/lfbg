project(examples)

add_executable(random_pixels random_pixels.cpp)
target_link_libraries(random_pixels lfbg)

add_executable(text_scroll text_scroll.cpp)
target_link_libraries(text_scroll lfbg)
