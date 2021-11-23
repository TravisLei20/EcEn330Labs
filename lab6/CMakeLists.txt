add_executable(lab6.elf
                main.c
                bhTester.h
                buttonHandler.h
                flashSequence.h
                fsTester.h
                globals.h
                simonControl.h
                simonDisplay.h
                verifySequence.h
                vsTester.h
                config.h
                buttonHandler.c
                flashSequence.c
                globals.c
                verifySequence.c
                simonDisplay.c
                vsTester.c
                fsTester.c
                bhTester.c
                simonControl.c
                )
target_link_libraries(lab6.elf ${330_LIBS} intervalTimer buttons_switches)
set_target_properties(lab6.elf PROPERTIES LINKER_LANGUAGE CXX)