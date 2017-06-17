add_library(user_lib STATIC user.c)
add_library(channel_lib STATIC channel.c)

add_executable(irc_server main.c)

target_link_libraries(irc_server LINK_PUBLIC user_lib)
target_link_libraries(irc_server LINK_PUBLIC channel_lib)
