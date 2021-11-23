add_executable(lab5.elf
                main.c
                minimax.c
                minimax.h
                testBoards.h
                testBoards.c
                ticTacToeControl.c 
                ticTacToeControl.h 
                ticTacToeDisplay.h
                ticTacToeDisplay.c
                config.h)
target_link_libraries(lab5.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(lab5.elf PROPERTIES LINKER_LANGUAGE CXX)