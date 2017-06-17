
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -lpthread")

find_package(Threads)


# If pkg-config is not installed on the system, then the
# CHECK_INSTALL_DIR variable must be set to the install
# location of Check. For example, on Windows, this may
# be: C:/Program Files/check
set(CHECK_INSTALL_DIR "/bin/share/check/")

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

set(TEST_USER check_user.c)
set(TEST_CHANNEL check_channel.c)

add_executable(check_user ${TEST_USER})
target_link_libraries(check_user user_lib ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

add_executable(check_channel ${TEST_CHANNEL})
target_link_libraries(check_channel channel_lib ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
