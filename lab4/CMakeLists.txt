add_executable(lab4.elf
                main.c
                clockControl.h
                clockControl.c
                clockDisplay.h
                clockDisplay.c
                config.h)
target_link_libraries(lab4.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(lab4.elf PROPERTIES LINKER_LANGUAGE CXX)