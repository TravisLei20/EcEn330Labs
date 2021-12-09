add_executable(labSelf.elf
                main.c
                alienDisplay.h
                alienDisplay.c
                alienControl.h
                alienControl.c
                alienRegion.h
                alienRegion.c
                )
target_link_libraries(labSelf.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(labSelf.elf PROPERTIES LINKER_LANGUAGE CXX)