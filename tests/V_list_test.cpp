#include <functional>
#include "../list.h"
#include "../Exceptions.h"
#include "mtmtest.h"
#include <cstring>
using std::string;

class SameAs {
private:
    int target;
    string str;
public:
    SameAs(int i) : target(i) {}
    SameAs(string str) : str(str) {}
    bool operator()(const int &i) const {
        return i == target;
    }
    bool operator()(const string& i) const {
        return i == str;
    }
};


struct lessThen {
    /*bool operator() (const int i1, const int i2){
        return (i1 < i2);
    }*/
    bool operator() (const string& str1, const string& str2){
        return (str1 < str2);
    }
};

static void abc_insert(List<string> &list){
    list.insert("y");
    list.insert("v");
    list.insert("x");
    list.insert("w");
    list.insert("u");
    list.insert("z");
    list.insert("b");
    list.insert("k");
    list.insert("t");
    list.insert("r");
    list.insert("o");
    list.insert("d");
    list.insert("s");
    list.insert("q");
    list.insert("p");
    list.insert("n");
    list.insert("m");
    list.insert("l");
    list.insert("j");
    list.insert("f");
    list.insert("i");
    list.insert("h");
    list.insert("g");
    list.insert("e");
    list.insert("c");
    list.insert("a");
}


static void listInsert() {
    List<int> list;
    list.insert(10);
    List<int>::Iterator it=list.begin();
    ASSERT_EQUALS(*it, 10);
    list.insert(4,list.begin());
    ASSERT_EQUALS(*(it), 10);
    list.insert(9,list.begin());
    it=list.begin();
    ASSERT_EQUALS(*it, 9);
    ASSERT_TRUE(list.getSize()==3);
}
static void listRemove() {
    List<int> list;
    for (int i=0;i<8;i++){
        list.insert(i);
    }
    List<int>::Iterator it=list.begin();
    for (int i=0; i<6;i++){
        it++;
    }
    list.remove(it);
    it=list.begin();
    ASSERT_TRUE(list.getSize()==7);
    for (int i=0;i<7;i++){
        ASSERT_FALSE(*it==6);
    }
    it++;
    list.remove(it);
    ASSERT_TRUE(list.getSize()==6);
    for (int i=0;i<6;i++){
        ASSERT_FALSE(*it==1);
    }
}
static void listIterator() {
    List<int> list;
    for (int i=0;i<8;i++){
        list.insert(i);
    }
    List<int>::Iterator it=list.begin();
    for (int i=0;i<8;i++){
        ASSERT_TRUE(*it==i);
        it++;
    }
    it=list.begin();
    for (int i=0;i<7;i++){
        it++;
    }
    it--;
    ASSERT_TRUE(*it==6);
    --it;
    ASSERT_TRUE(*it==5);
    it++;
    ASSERT_TRUE(*it==6);
}
static void listException() {
    List<int> list;
    List<int>::Iterator it=list.begin();
    List<int> list2;
    List<int>::Iterator it2=list2.begin();
    ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list.remove(it));
    ASSERT_THROWS(mtm::ListExceptions::ElementNotFound, list.insert(3,it2));
}
static void listBegin(){
    List<string> list;
    list.insert("hey");
    list.insert("how are you doin?");
    ASSERT_TRUE(*(list.begin())=="hey");
    List<string>::Iterator it=list.begin();
    list.insert("Joey", it);
    ASSERT_TRUE(*(list.begin())=="Joey");
    it=list.begin();
    list.insert("is saying", it);
    ASSERT_TRUE(*(list.begin())=="is saying");
    it++;
    it++;
    list.insert("Tribbiani", it);
    ASSERT_TRUE(*(list.begin())=="is saying");
    list.remove(list.begin());
    ASSERT_TRUE(*(list.begin())=="Joey");

}
static void listSize(){
   List<int> list;
    for (int i=0;i<100;i++){
        list.insert(i);
    }
    ASSERT_EQUALS(list.getSize(),100);
    list.insert(101);
    ASSERT_NOT_EQUAL(list.getSize(),100);
    ASSERT_EQUALS(list.getSize(),101);
    list.remove(list.begin());
    list.remove(list.begin());
    ASSERT_NOT_EQUAL(list.getSize(),100);
    ASSERT_EQUALS(list.getSize(),99);
    List<int>::Iterator it=list.begin();
    for(int i=0;i<9;i++){
        list.remove(it);
        it=list.begin()++;
    }
    ASSERT_EQUALS(list.getSize(),90);
}
static void listEqual(){
    List<string> list1;
    List<string> list2;
    list1.insert("My");
    list2.insert("My");
    list1.insert("Name");
    list2.insert("Name");
    list1.insert("is");
    list2.insert("is");
    list1.insert("Slim");
    list2.insert("Slim");
    list1.insert("Shady");
    list2.insert("Shady");
    ASSERT_TRUE(list1==list2);
    ASSERT_FALSE(list1!=list2);
    list1.insert("Please");
    ASSERT_TRUE(list1!=list2);
    ASSERT_FALSE(list1==list2);
    list2.insert("Please");
    ASSERT_TRUE(list1==list2);
    ASSERT_FALSE(list1!=list2);
    List<int> int_list1;
    List<int> int_list2;
    for (int i=1;i<=50;i++){
        int_list1.insert(i);
        int_list2.insert(i);
    }
    ASSERT_TRUE(int_list1==int_list2);
    ASSERT_FALSE(int_list1!=int_list2);
    int_list1.insert(600);
    ASSERT_TRUE(int_list1!=int_list2);
    ASSERT_FALSE(int_list1==int_list2);
}
static void listPredicate() {
    List<int> int_list;
    for (int i=0;i<=1000;i+=4){
        int_list.insert(i);
    }
    List<int>::Iterator it = int_list.find(SameAs(16));
    ASSERT_TRUE(*it==16);
    it = int_list.find(SameAs(996));
    ASSERT_TRUE(*it==996);
    it = int_list.find(SameAs(555));
    ASSERT_TRUE(it==int_list.end());
    List<string> string_list;
    string s1=("Diamond");
    string_list.insert(s1);
    string s2="Gold";
    string_list.insert(s2);
    string s3="Silver";
    string_list.insert(s3);
    string s4="Bronze";
    string_list.insert(s4);
    string s5="Steel";
    string_list.insert(s5);
    List<string>::Iterator it2 = string_list.find(SameAs(s1));
    ASSERT_TRUE(it2==(string_list.begin()));
    it2=string_list.find(SameAs(s2));
    ASSERT_TRUE(it2==++(string_list.begin()));
    it2=string_list.find(SameAs(s3));
    ASSERT_TRUE(it2==++++(string_list.begin()));
    it2=string_list.find(SameAs(s4));
    ASSERT_TRUE(it2==++++++(string_list.begin()));
    it2= string_list.find(SameAs(s5));
    ASSERT_TRUE(it2==++++++++(string_list.begin()));
    it2=string_list.find(SameAs("1234"));
    ASSERT_TRUE(it2==string_list.end());
}
static void listSort(){
    List<string> string_list;
    abc_insert(string_list);
    string_list.sort(std::less<string>());
    List<string>::Iterator it1 = string_list.begin();
    List<string>::Iterator it2 = string_list.begin();
    it2++;
    std::less<string> is_less;
    for (int i=0;i<25;i++){
        ASSERT_TRUE(is_less(*it1, *it2));
        it1++;
        it2++;
    }
    it1=string_list.begin();
    ASSERT_TRUE(*it1=="a");
    ++++++++++it1;
    ASSERT_TRUE(*it1=="f");
    ++++++++++it1;
    ASSERT_TRUE(*it1=="k");
}


int main(){
    RUN_TEST(listInsert);
    RUN_TEST(listRemove);
    RUN_TEST(listIterator);
    RUN_TEST(listException);
    RUN_TEST(listBegin);
    RUN_TEST(listSize);
    RUN_TEST(listEqual);
    RUN_TEST(listPredicate);
    RUN_TEST(listSort);
}


