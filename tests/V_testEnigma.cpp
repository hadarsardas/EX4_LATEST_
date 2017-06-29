#include "../Enigma.h"
#include "../mtmtest.h"
#include <cstring>
#include <assert.h>
#include <vector>
#include "../Exceptions.h"
using namespace std;
using std::vector;

using namespace mtm::escaperoom;


void testOperators() {
    Enigma Enigma1("enigma1",HARD_ENIGMA);
    Enigma Enigma2("enigma1",HARD_ENIGMA);
    Enigma Enigma3("enigma1",HARD_ENIGMA);
    Enigma Enigma4("enigma1",MEDIUM_ENIGMA);
    Enigma Enigma5("enigma2",MEDIUM_ENIGMA);
    Enigma Enigma6("enigma3",EASY_ENIGMA);
    ASSERT_TRUE(Enigma1==Enigma2);
    ASSERT_TRUE(Enigma2==Enigma3);
    ASSERT_TRUE(Enigma4<Enigma3);
    ASSERT_TRUE(Enigma4!=Enigma3);
    ASSERT_FALSE(Enigma4>Enigma3);
    ASSERT_FALSE(Enigma4==Enigma3);
    ASSERT_TRUE(Enigma6<Enigma5);
    ASSERT_TRUE(Enigma5>Enigma6);

}

void getTest(){
    Enigma Enigma1("enigma1",HARD_ENIGMA);
    ASSERT_EQUALS(Enigma1.getName(),"enigma1");
    ASSERT_EQUALS(Enigma1.getDifficulty(),HARD_ENIGMA);
    ASSERT_NOT_EQUAL(Enigma1.getDifficulty(),MEDIUM_ENIGMA);
}
void areEqualyComplexTest(){
    set<string> s1;
    s1.insert("mtm");
    s1.insert("last");
    s1.insert("finally");
    s1.insert("will");
    s1.insert("be");
    s1.insert("over");
    Enigma Enigma1("enigma1",HARD_ENIGMA,6,s1);
    Enigma Enigma2("enigma2",HARD_ENIGMA,6,s1);
    Enigma Enigma3("enigma2",HARD_ENIGMA,6,s1);
    Enigma Enigma4("enigma2",MEDIUM_ENIGMA,6,s1);
    ASSERT_THROWS(EnigmaIllegalSizeParamException,Enigma("enigma2",MEDIUM_ENIGMA,4,s1));
    ASSERT_TRUE(Enigma1.areEqualyComplex(Enigma2));
    ASSERT_TRUE(Enigma2.areEqualyComplex(Enigma1));
    ASSERT_TRUE(Enigma2.areEqualyComplex(Enigma3));
    ASSERT_FALSE(Enigma4.areEqualyComplex(Enigma3));
}
void copyTest(){
    set<string> s1;
    s1.insert("mtm");
    s1.insert("last");
    s1.insert("finally");
    s1.insert("will");
    s1.insert("be");
    s1.insert("over");
    Enigma Enigma1("enigma1",HARD_ENIGMA,6,s1);
    Enigma Enigma2=Enigma(Enigma1);
    ASSERT_EQUALS(Enigma1.getName(),Enigma2.getName());
    ASSERT_EQUALS(Enigma1.getDifficulty(),Enigma2.getDifficulty());
    ASSERT_TRUE(Enigma1.areEqualyComplex(Enigma2));
}
void assignmentTest(){
    set<string> s1;
    s1.insert("mtm");
    s1.insert("last");
    s1.insert("finally");
    s1.insert("will");
    s1.insert("be");
    s1.insert("over");
    set<string> s2=s1;
    s2.insert("yay");
    s2.insert("us");
    Enigma Enigma1("enigma1",HARD_ENIGMA,6,s1);
    Enigma Enigma2("enigma2",EASY_ENIGMA,8,s2);
    ASSERT_NOT_EQUAL(Enigma1.getName(),Enigma2.getName());
    ASSERT_NOT_EQUAL(Enigma1.getDifficulty(),Enigma2.getDifficulty());
    ASSERT_FALSE(Enigma1.areEqualyComplex(Enigma2));
    Enigma2=Enigma1;
    ASSERT_EQUALS(Enigma1.getName(),Enigma2.getName());
    ASSERT_EQUALS(Enigma1.getDifficulty(),Enigma2.getDifficulty());
    ASSERT_TRUE(Enigma1.areEqualyComplex(Enigma2));
}
void printTest(){
    set<string> s1;
    s1.insert("mtm");
    s1.insert("last");
    s1.insert("finally");
    s1.insert("will");
    s1.insert("be");
    s1.insert("over");
    set<string> s2=s1;
    s2.insert("hope");
    s2.insert("we");
    s2.insert("will");
    s2.insert("pass");
    Enigma Enigma1("enigma1",HARD_ENIGMA,6,s1);
    Enigma Enigma2("enigma2",EASY_ENIGMA,9,s2);
    ASSERT_PRINT("enigma1 (2) 6",Enigma1);
    ASSERT_PRINT("enigma2 (0) 9",Enigma2);
}
void EnigmaIllegalSize(){
    set<string> s1;
    s1.insert("abc");
    s1.insert("def");
    s1.insert("ghi");
    set<string> s2=s1;
    s2.insert("jkl");
    Enigma Enigma1("enigma1",HARD_ENIGMA,3,s1);
    ASSERT_NO_THROW(Enigma("enigma2",EASY_ENIGMA,4,s2));
    Enigma Enigma2("enigma2",EASY_ENIGMA,4,s2);
    s2.insert("abc");
    ASSERT_THROWS(EnigmaIllegalSizeParamException,
                  Enigma("enigma1",HARD_ENIGMA,5,s2));
    Enigma1.addElement("WOW!");
    Enigma2.addElement("YAY!");

}


int main() {
    RUN_TEST(testOperators);
    RUN_TEST(getTest);
    RUN_TEST(areEqualyComplexTest);
    RUN_TEST(copyTest);
    RUN_TEST(EnigmaIllegalSize);
    RUN_TEST(assignmentTest);
    RUN_TEST(printTest);
}