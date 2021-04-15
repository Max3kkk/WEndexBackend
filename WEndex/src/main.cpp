#include "cstdlib"
#include "ctime"
#include "DataBase.h"
#include "PassengerGateway.h"
#include "Passenger.h"
#include "DriverGateway.h"
#include <sqlite_orm/sqlite_orm.h>

using namespace std;
using namespace sqlite_orm;
#define st DataBase::Storage

void ClearStorage(){
    st.remove_all<Driver>();
    st.remove_all<Car>();
    st.remove_all<Passenger>();
    st.remove_all<Order>();
    st.remove_all<PaymentMethod>();
}

int main() {
    srand(std::time(nullptr));  //for better rand()
    st.sync_schema();
    PassengerGateway pg;
    DriverGateway dg;

    ClearStorage();

    dg.Register("Ivan Konyukhov", "Lapochka", "12345Drop");
    dg.Login("Lapochka", "12345Drop");

    //ge.sync_schema();

    return 0;
}