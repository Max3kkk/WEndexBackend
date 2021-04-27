#include "cstdlib"
#include "ctime"
#include "DataBase.h"
#include "PassengerGateway.h"
#include "Passenger.h"
#include "DriverGateway.h"
#include "AdminGateway.h"
#include <sqlite_orm/sqlite_orm.h>

using namespace std;
using namespace sqlite_orm;
#define st DataBase::Storage

void ClearStorage() {
    st.remove_all<Driver>();
    st.remove_all<Car>();
    st.remove_all<Passenger>();
    st.remove_all<Order>();
    st.remove_all<PaymentMethod>();
    st.remove_all<PinnedAddress>();
    st.remove_all<Car>();
    st.remove_all<Device>();
    st.remove_all<BlockedMethod>();
    st.remove_all<Admin>();
}

int main() {
    srand(std::time(nullptr));  //for better rand()
    st.sync_schema();
    PassengerGateway pg;
    DriverGateway dg;
    AdminGateway ag;

    ClearStorage();
    //Drivers
    dg.Register("Ivan Konyukhov", "Lapochka", "12345Drop");
    dg.Register("Mikhail", "Fedorov", "azaza");
    dg.Register("Vladimir", "Vova", "12345Drop");
    auto dIvan = dg.Login("Lapochka", "12345Drop");
    auto dMikhail = dg.Login("Fedorov", "azaza");
    auto dVladimir = dg.Login("Vova", "12345Drop");

    //Passengers
    pg.Register("Igor", "m8pie", "pass");
    pg.Register("Nickolas", "moon", "moon");
    pg.Register("Talya", "animka", "mydrdate");
    auto pIgor = pg.Login("m8pie", "pass");
    auto pNicolas = pg.Login("moon", "moon");
    auto pTalya = pg.Login("animka", "mydrdate");

    // Admin
    ag.Register("Boss", "godPrayer", "smthHere");
    auto aBoss = ag.Login("godPrayer", "smthHere");

    dg.ChangeStatus(dIvan.id, Available);
    dg.ChangeStatus(dMikhail.id, Available);
    dg.ChangeStatus(dVladimir.id, Available);

    dg.UpgradeCar(dIvan.id, BMW, Economy, Red);
    dg.UpgradeCar(dMikhail.id, Porsche, Business, Black);
    dg.UpgradeCar(dVladimir.id, Honda, Comfort, Red);

    dg.SeeCar(dVladimir.id);

    auto carId = dg.AddNewCar(dMikhail.id, Honda, ComfortPlus, Gold).id;
    dg.SwitchCar(dMikhail.id, carId);
    dg.SeeCar(dMikhail.id);

    auto devIg1 = pg.addDevice(pIgor.id, Avrora, "MyInternshipDevice");
    auto devIg2 = pg.addDevice(pIgor.id, Windows, "GamingLaptop");
    pg.SwitchDevice(pIgor.id, devIg1.id);
    pg.removeDevice(pIgor.id, devIg2.id);

    pg.addPaymentMethod(pNicolas.id, OrganTrade);
    pg.switchPaymentType(pNicolas.id, OrganTrade);
    pg.removePaymentMethod(pNicolas.id, Cash);
    pg.SeePaymentMethods(pNicolas.id);

    pg.addPinnedAddress(pNicolas.id, Moscow);
    pg.addPinnedAddress(pNicolas.id, Kazan);
    pg.removePinnedAddress(pNicolas.id, Kazan);
    pg.SeePinedAddresses(pNicolas.id);

    auto ord = pg.makeOrder(pNicolas.id, OrganTrade, ComfortPlus, Moscow, Innopolis);
    pg.printCurrentCoordinates(pNicolas.id);

    ag.ValidateCar(aBoss.id, dMikhail.id);
    ag.BlockMethod(aBoss.id, dVladimir.id, FindAllAvailableOrders);
    ag.BlockMethod(aBoss.id, dVladimir.id, UpgradeCurrentCar);
    ag.UnBlockMethod(aBoss.id, dVladimir.id, UpgradeCurrentCar);

    dg.doRandomAvailableOrder(dMikhail.id);
    dg.SeeOrderHistory(dMikhail.id);
    pg.askForBill(pNicolas.id);
    pg.SeeOrderHistory(pNicolas.id);

    ag.seeAllCars(aBoss.id);
    ag.seeAllDevices(aBoss.id);
    ag.seeAllDrivers(aBoss.id);
    ag.seeAllOrders(aBoss.id);
    ag.seeAllPassengers(aBoss.id);
    ag.seeAllPaymentMethods(aBoss.id);
    ag.seeBlockedMethods(aBoss.id);
    return 0;
}