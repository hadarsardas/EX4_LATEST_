#include "../EscapeRoomWrapper.h"
#include "../ScaryRoom.h"
#include "../KidsRoom.h"
#include "../Company.h"
#include "../mtmtest.h"
#include <assert.h>
#include "../Exceptions.h"
using namespace mtm::escaperoom;


void createCompany() {

    ASSERT_NO_THROW(Company("Company1","0501234567"));
    ASSERT_NO_THROW(Company("Company2","0523456789"));
}

void createRoom() {
    Company Company1("Company1","0501234567");
    ASSERT_NO_THROW(Company1.createRoom((char*)"baseRoom",40,3,6));
    ASSERT_NO_THROW(Company1.createKidsRoom((char*)"kidsRoom",45,5,5,14));
    ASSERT_NO_THROW(Company1.createScaryRoom((char *) "scaryRoom", 52,7,6,26,3));
}

void getAllRoomsTest() {
    Company Company("Company","0501234567");
    EscapeRoomWrapper Room1((char*)"The Robbery of The Century",40,3,6);
    std::set<EscapeRoomWrapper*> roomSet=Company.getAllRooms();
    ASSERT_TRUE(roomSet.insert(&Room1).second);
    ASSERT_EQUALS(roomSet.size(),1);
    ASSERT_NO_THROW(Company.createRoom((char*)"The Robbery of The Century",40,3,6));
    ASSERT_NO_THROW(Company.createRoom((char*)"Mossad",52,4,3));
    ASSERT_NO_THROW(Company.createKidsRoom((char*)"The Real Survivor",45,5,5,14));
    ASSERT_NO_THROW(Company.createKidsRoom((char *) "KidsEscape", 50,6,2,10));
    ASSERT_NO_THROW(Company.createScaryRoom((char *) "Haunted Matam Castle", 60,9,4,99,5));
    ASSERT_NO_THROW(Company.createScaryRoom((char *) "Lost Students", 52,7,6,26,3));
    std::set<EscapeRoomWrapper*> roomSet2=Company.getAllRooms();
    ASSERT_FALSE(roomSet.insert(&Room1).second);
    ASSERT_EQUALS(roomSet2.size(),6);
}

void removeRoomTest() {
    Company company("Company","0501234567");
    ASSERT_NO_THROW(company.createRoom((char *) "baseRoom1", 50, 2, 3));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "Lost Students", 52,7,6,26,3));
    ASSERT_NO_THROW(company.createKidsRoom((char*)"kidsRoom",45,5,5,14));
    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.removeRoom(ScaryRoom((char*) "Matam Horror", 54,3,2,21,4)));
    ASSERT_NO_THROW(company.removeRoom(ScaryRoom((char*) "Lost Students", 52,7,6,26,3)));
    ASSERT_NO_THROW(company.createKidsRoom((char*)"kidsRoom",45,5,5,14));
    std::set<EscapeRoomWrapper*> roomSet=company.getAllRooms();
    ASSERT_EQUALS(roomSet.size(),3);
    ASSERT_NO_THROW(company.removeRoom(KidsRoom((char*)"kidsRoom",45,5,5,14)));
    std::set<EscapeRoomWrapper*> roomSet2=company.getAllRooms();
    ASSERT_EQUALS(roomSet2.size(),2);
    ASSERT_NO_THROW(company.removeRoom(KidsRoom((char*)"kidsRoom",45,5,5,14)));
    std::set<EscapeRoomWrapper*> roomSet3=company.getAllRooms();
    ASSERT_EQUALS(roomSet3.size(),1);
    ASSERT_NO_THROW(company.removeRoom(EscapeRoomWrapper((char*)"baseRoom1",50,2,3)));
    std::set<EscapeRoomWrapper*> roomSet4=company.getAllRooms();
    ASSERT_EQUALS(roomSet4.size(),0);
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeRoom(EscapeRoomWrapper((char*)"baseRoom1",50,2,3)));

}

void addRemoveEnigmaTest() {
    Company company("CS","1010011001");
    ASSERT_NO_THROW(company.createRoom((char *) "Taub1", 50, 2, 3));
    EscapeRoomWrapper baseRoom((char *) "Taub1", 50, 2, 3);
    ASSERT_NO_THROW(company.createScaryRoom((char *) "The basement", 20,2,6,26,6));
    ScaryRoom scaryRoom((char *) "The basement", 20,2,6,26,6);
    ASSERT_NO_THROW(company.createKidsRoom((char*)"Atudaim Room",45,5,5,14));
    KidsRoom kidsRoom((char*)"Atudaim Room",45,5,5,14);
    KidsRoom babyRoom((char*)"BABIES",45,5,5,14);
    Enigma enigma1("Matam",HARD_ENIGMA);
    Enigma enigma2("Infi1",MEDIUM_ENIGMA);
    set<string> enigma3Set= {"stack","pc","emt", "r0","mov"};
    Enigma enigma3("ATAM",HARD_ENIGMA,5,enigma3Set);
    ASSERT_THROWS(CompanyRoomNotFoundException,company.addEnigma(babyRoom, enigma1));
    ASSERT_NO_THROW(company.addEnigma(baseRoom, enigma1));
    ASSERT_NO_THROW(company.addEnigma(kidsRoom, enigma2));
    ASSERT_NO_THROW(company.removeEnigma(baseRoom,enigma1));
    ASSERT_THROWS(CompanyRoomNotFoundException, company.removeEnigma(babyRoom,enigma1));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,company.removeEnigma(baseRoom,enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, company.removeEnigma(kidsRoom,enigma3));
    ASSERT_NO_THROW(company.removeEnigma(kidsRoom,enigma2));
}
void addRemoveItemTest() {
    Company company("CS","1010011001");
    Enigma enigma1("taub1", EASY_ENIGMA);
    Enigma enigma2("taub2", HARD_ENIGMA);
    Enigma enigma3("amado", MEDIUM_ENIGMA);

    ASSERT_NO_THROW(company.createRoom((char *) "Taub", 50, 2, 3));

    EscapeRoomWrapper room1((char *) "Taub", 50, 2, 3);
    EscapeRoomWrapper room2((char *) "Amado", 40, 3, 5);
    EscapeRoomWrapper room3((char *) "Fishbach", 40, 3, 5);

    ASSERT_THROWS(CompanyRoomNotFoundException,
                  company.addItem(room2, enigma1, "ulman"));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,
                  company.addItem(room1, enigma2, "ulman"));
    ASSERT_NO_THROW(company.addEnigma(room1, enigma2));
    ASSERT_NO_THROW(company.addItem(room1, enigma2, "ulman412"));
    ASSERT_NO_THROW(company.addItem(room1, enigma1, "ulman321"));
    ASSERT_NO_THROW(company.createRoom((char *) "Amado", 40, 3, 5));
    ASSERT_NO_THROW(company.removeItem(room1,enigma2,"ulman412"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,company.removeItem(room2,enigma2,"ulman321"));
    ASSERT_THROWS(CompanyRoomNotFoundException,company.removeItem(room3,enigma2,"ulman321"));
    ASSERT_NO_THROW(company.addEnigma(room2, enigma2));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(room2,enigma2,"ulman321"));
    ASSERT_NO_THROW(company.addItem(room1, enigma2, "ulman412"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,company.removeItem(room2,enigma2,"ulman321"));
}
void getAllRoomsByTypeTest() {
    Company company("CS","1010011001");
    ASSERT_NO_THROW(company.createRoom((char *) "Taub1", 50, 2, 3));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "The basement", 20,2,6,26,6));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "The library", 20,2,6,26,6));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "The bell", 24,3,8,22,4));
    ASSERT_NO_THROW(company.createKidsRoom((char*)"Atudaim Room",45,5,5,14));
    ASSERT_NO_THROW(company.createKidsRoom((char*)"Aza Dorms",2,3,5,12));
    std::set<EscapeRoomWrapper*> roomSetScary=company.getAllRoomsByType(SCARY_ROOM);
    std::set<EscapeRoomWrapper*> roomSetKids=company.getAllRoomsByType(KIDS_ROOM);
    std::set<EscapeRoomWrapper*> roomSetBase=company.getAllRoomsByType(BASE_ROOM);
    ASSERT_EQUALS(roomSetBase.size(),1);
    ASSERT_EQUALS(roomSetScary.size(),3);
    ASSERT_EQUALS(roomSetKids.size(),2);
}
void getRoomByNameTest(){
    Company company("CS","1010011001");
    ASSERT_NO_THROW(company.createRoom((char *) "Ulman202", 50, 2, 3));
    ASSERT_NO_THROW(company.createScaryRoom((char *) "Chucky", 20,2,6,26,4));
    ASSERT_NO_THROW(company.createKidsRoom((char*)"SpongeBob",45,5,5,14));
    EscapeRoomWrapper* RoomByName=company.getRoomByName("SpongeBob");
    ASSERT_EQUALS((*RoomByName).getName(),"SpongeBob");
    ASSERT_THROWS(CompanyRoomNotFoundException,company.getRoomByName("Frozen"));
    EscapeRoomWrapper* RoomByName2=company.getRoomByName("Chucky");
    ASSERT_EQUALS((*RoomByName2).getName(),"Chucky");
    ASSERT_EQUALS((*RoomByName2).getMaxParticipants(),6);
}

int main() {
    RUN_TEST(createCompany);
    RUN_TEST(createRoom);
    RUN_TEST(getAllRoomsTest);
    RUN_TEST(removeRoomTest);
    RUN_TEST(addRemoveEnigmaTest);
    RUN_TEST(addRemoveItemTest);
    RUN_TEST(getAllRoomsByTypeTest);
    RUN_TEST(getRoomByNameTest);
}