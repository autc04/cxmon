add_library(mon

    src/mon.h
    src/mon.cpp
    src/mon_disass.h
    src/mon_disass.cpp
    src/mon_cmd.h
    src/mon_cmd.cpp
    src/mon_6502.cpp
    src/mon_atraps.h
    src/mon_lowmem.h
    src/mon_lowmem.cpp
    src/mon_ppc.cpp
    src/mon_z80.cpp
    
    src/disass/bfd.h
    src/disass/ansidecl.h
    src/disass/dis-asm.h
    src/disass/floatformat.h
    src/disass/floatformat.c
    src/disass/i386-dis.c
    src/disass/m68k-dis.c
    src/disass/m68k-opc.c
    src/disass/m68k.h
    src/disass/opintl.h
    )
target_include_directories(mon PUBLIC src)

target_compile_definitions(mon PRIVATE NO_AUTOCONF)
if(NOT WIN32)
    find_path(Readline_INCLUDE_DIR NAMES readline/readline.h)
    find_library(Readline_LIBRARY NAMES readline)

    if(Readline_INCLUDE_DIR AND Readline_LIBRARY)
        target_compile_definitions(mon PRIVATE
            HAVE_LIBREADLINE
            HAVE_READLINE_READLINE_H
            HAVE_READLINE_HISTORY_H)
        target_include_directories(mon PRIVATE ${Readline_INCLUDE_DIR})
        target_link_libraries(mon ${Readline_LIBRARY})
    endif()
endif()

add_executable(cxmon
    src/main.cpp)

target_link_libraries(cxmon mon)
