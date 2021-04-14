add_executable(WEndex DataBase.cpp DataBase.h PassengerGateway.cpp PassengerGateway.h DriverGateway.cpp DriverGateway.h Driver.h Passenger.h Order.h Car.cpp Car.h)
target_link_libraries(WEndex PRIVATE sqlite_orm::sqlite_orm)

target_sources(WEndex 
    PRIVATE 
        main.cpp 
)