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
    dg.Register("Mikhail", "Fedorov", "azaza");
    dg.Register("Vladimir", "Vova", "12345Drop");
    dg.Register("De Baby", "dad", "124");
    dg.Register("Dandy", "playStation", "game");
    dg.Register("Succi", "devilslaver337", "italian");

    int ivID = dg.Login("Lapochka", "12345Drop").id;
    int miID = dg.Login("Fedorov", "azaza").id;
    int vlID = dg.Login("Vova", "12345Drop").id;
    int deID = dg.Login("dad", "124").id;
    int daID = dg.Login("playStation", "game").id;
    int suID = dg.Login("devilslaver337", "italian").id;

    dg.ChangeStatus(ivID, Available);
    dg.ChangeStatus(miID, Available);
    dg.ChangeStatus(vlID, Available);
    dg.ChangeStatus(deID, Available);
    dg.ChangeStatus(daID, Available);
    dg.ChangeStatus(suID, Available);

    dg.UpgradeCar(ivID,BMW,Economy,Moscow,Red,"AZA765ZZA");
    dg.UpgradeCar(miID,Porsche,Business,Berlin,Black,"AZA765ZZA");
    dg.UpgradeCar(vlID,Honda,Comfort,Kazan,Red,"AZA765ZZA");
    dg.UpgradeCar(deID,Volkswagen,Economy,Paris,White,"AZA765ZZA");
    dg.UpgradeCar(daID,Toyota,ComfortPlus,London,Cold,"AZA765ZZA");
    dg.UpgradeCar(suID,MercedesBenz,Comfort,Sydney,Blue,"AZA765ZZA");

    pg.Register("Ivan Konyukhov PAS", "a", "1");
    pg.Register("Mikhail PAS", "b", "2");
    pg.Register("Vladimir PAS", "c", "3");
    pg.Register("De Baby PAS", "d", "4");
    pg.Register("Dandy PAS", "e", "5");
    pg.Register("Succi PAS", "i", "6");

    int iID = pg.Login("a", "1").id;
    int mID = pg.Login("b", "2").id;
    int vID = pg.Login("c", "3").id;
    int dID = pg.Login("d", "4").id;
    int ddID = pg.Login("e", "5").id;
    int sID = pg.Login("i", "6").id;
    //.....

    return 0;
}