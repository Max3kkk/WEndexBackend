cmake_minimum_required(VERSION 3.17)
project(RoomAccess)

set(CMAKE_CXX_STANDARD 17)

add_executable(RoomAccess src/main.cpp src/Users/User.cpp include/Users/User.h include/AccessLevel.h src/Rooms/Room.cpp include/Rooms/Room.h src/Users/Admin.cpp include/Users/Admin.h src/Users/Student.cpp include/Users/Student.h src/Users/Professor.cpp include/Users/Professor.h src/Users/LabEmployee.cpp include/Users/LabEmployee.h src/Users/Director.cpp include/Users/Director.h src/Rooms/ClassRoom.cpp include/Rooms/ClassRoom.h src/Rooms/LectureRoom.cpp include/Rooms/LectureRoom.h src/Rooms/ConferenceRoom.cpp include/Rooms/ConferenceRoom.h src/Rooms/Cabinet.cpp include/Rooms/Cabinet.h src/Rooms/DirectorCabinet.cpp include/Rooms/DirectorCabinet.h src/DataBaseManager.cpp include/DataBaseManager.h src/Controller.cpp include/Controller.h src/Users/Guest.cpp include/Users/Guest.h)