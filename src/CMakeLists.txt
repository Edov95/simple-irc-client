add_library(user_lib STATIC user.c)

add_executable(irc_server main.c)

target_link_libraries(irc_server LINK_PUBLIC user_lib) 
