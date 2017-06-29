#include "../ScaryRoom.h"
#include "../mtmtest.h"

static void makeRooms(){
    ScaryRoom ring=ScaryRoom((char*)"The ring", 60, 10, 7, 10, 4);
    ASSERT_EQUALS(ring.level(), 10);
    ASSERT_EQUALS(ring.getMaxTime(), 60);
    ASSERT_EQUALS(ring.getAgeLimit(),10 );
    ASSERT_EQUALS(ring.getMaxParticipants(),7);
    ASSERT_EQUALS(ring.getName(), (char*)"The ring");
    ScaryRoom scream=ScaryRoom((char*)"The scream", 70, 5, 8, 18, 6);
    ASSERT_EQUALS(scream.getMaxTime(), 70);
    ASSERT_EQUALS(scream.level(), 5);
    ASSERT_EQUALS(scream.getAgeLimit(),18 );
    ASSERT_EQUALS(scream.getMaxParticipants(),8);
    ASSERT_EQUALS(scream.getName(), (char*)"The scream");
}

static void ageLimit(){
    ScaryRoom mtm=ScaryRoom((char*)"MATAM", 90, 10, 2, 18, 5);
    ASSERT_EQUALS(mtm.getMaxTime(), 90);
    ASSERT_EQUALS(mtm.level(), 10);
    ASSERT_EQUALS(mtm.getAgeLimit(),18);
    ASSERT_EQUALS(mtm.getMaxParticipants(),2);
    ASSERT_EQUALS(mtm.getName(), (char*)"MATAM");
    mtm.setNewAgeLimit(20);
    ASSERT_EQUALS(mtm.getAgeLimit(),20);
    mtm.setNewAgeLimit(10);
    ASSERT_EQUALS(mtm.getAgeLimit(),10);
    ASSERT_THROWS(mtm::escaperoom::ScaryRoomIllegalAgeLimit,
                  mtm.setNewAgeLimit(-8));
    mtm.setNewAgeLimit(0);
    ASSERT_EQUALS(mtm.getAgeLimit(),0);
}
static void rateCheck(){
    ScaryRoom grudge=ScaryRoom((char*)"The Grudge", 30, 8, 6, 22, 10);
    grudge.rate(5);
    ASSERT_EQUALS(grudge.getRate(), 5);
    grudge.rate(2);
    ASSERT_EQUALS(grudge.getRate(), 3.5);
    grudge.rate(5);
    ASSERT_EQUALS(grudge.getRate(), 4);
    grudge.rate(4);
    ASSERT_EQUALS(grudge.getRate(), 4);
    grudge.rate(1);
    ASSERT_EQUALS(grudge.getRate(), 3.4);
}
static void printCheck(){
    ScaryRoom Saw=ScaryRoom((char*)"The saw", 60, 4, 6, 21, 5);
    ASSERT_PRINT("Scary Room: The saw (60/4/6/21)", Saw);
    ScaryRoom chaki=ScaryRoom((char*)"Chaki", 40, 10, 5, 18, 4);
    ASSERT_PRINT("Scary Room: Chaki (40/10/5/18)", chaki);
}

int main(){
    RUN_TEST(makeRooms);
    RUN_TEST(ageLimit);
    RUN_TEST(rateCheck);
    RUN_TEST(printCheck);
}