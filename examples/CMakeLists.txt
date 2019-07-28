project(examples)

add_executable(demo demo.cpp)
target_link_libraries(demo lfbg)

add_executable(text_scroll text_scroll.cpp)
target_link_libraries(text_scroll lfbg)

add_executable(n_body n_body.cpp)
target_link_libraries(n_body lfbg)

add_executable(snake snake.cpp)
target_link_libraries(snake lfbg)

add_executable(mouse mouse.cpp)
target_link_libraries(mouse lfbg)

add_executable(vga vga.cpp)
target_link_libraries(vga lfbg)

add_executable(test test.cpp)
target_link_libraries(test lfbg)
