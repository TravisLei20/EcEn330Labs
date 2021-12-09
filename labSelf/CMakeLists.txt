add_executable(labSelf.elf
                main.c
                battleshipDisplay.h
                battleshipDisplay.c
                battleshipControl.h
                battleshipControl.c
                battleshipRegion.h
                battleshipRegion.c
                )
target_link_libraries(labSelf.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(labSelf.elf PROPERTIES LINKER_LANGUAGE CXX)