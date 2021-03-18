cmake_minimum_required(VERSION 3.17)
project(RoomAccess)

set(CMAKE_CXX_STANDARD 17)

add_executable(RoomAccess src/main.cpp src/User.cpp include/User.h include/AccessLevel.h src/Room.cpp include/Room.h src/Admin.cpp include/Admin.h src/Student.cpp include/Student.h src/Professor.cpp include/Professor.h src/LabEmployee.cpp include/LabEmployee.h src/Director.cpp include/Director.h src/ClassRoom.cpp include/ClassRoom.h src/LectureRoom.cpp include/LectureRoom.h src/ConferenceRoom.cpp include/ConferenceRoom.h src/Cabinet.cpp include/Cabinet.h src/DirectorCabinet.cpp include/DirectorCabinet.h src/DataBaseManager.cpp include/DataBaseManager.h src/Controller.cpp include/Controller.h)