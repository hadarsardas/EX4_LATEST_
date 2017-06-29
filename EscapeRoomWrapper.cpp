#include <iostream>
#include <cstring>
#include "EscapeRoomWrapper.h"
#include <vector>
#include <algorithm>

using mtm::escaperoom::EscapeRoomWrapper;
using mtm::escaperoom::Enigma;

EscapeRoomWrapper::EscapeRoomWrapper(char *name, const int &escapeTime,
                                     const int &level,
                                     const int &maxParticipants) {
    escapy=escapeRoomCreate(name, escapeTime, maxParticipants, level);
    if (escapy==NULL){
        throw EscapeRoomMemoryProblemException();
    }
    std::vector<Enigma> riddles;
    this->riddles=riddles;
}
EscapeRoomWrapper* EscapeRoomWrapper::clone() const {
    return new EscapeRoomWrapper(*this);
}

void EscapeRoomWrapper::addEnigma(const Enigma& enigma){
    riddles.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma& enigma){
    if (riddles.size()==0){
        throw mtm::escaperoom::EscapeRoomNoEnigmasException();
    }
    std::vector<Enigma>::iterator it=(std::find(riddles.begin(),riddles.end(),enigma));
    if(it==riddles.end()){
        throw mtm::escaperoom::EscapeRoomEnigmaNotFoundException();
    }
    riddles.erase(it);
}

Enigma EscapeRoomWrapper::getHardestEnigma(){
    if (riddles.size()==0){
        throw mtm::escaperoom::EscapeRoomNoEnigmasException();
    }
    Enigma max=*(riddles.begin());
    std::vector<Enigma>::iterator it=riddles.begin();
    for (std::vector<Enigma>::iterator it=riddles.begin();it!=riddles.end();it++){
        if ((*it).getDifficulty() > max.getDifficulty()){
            max=(*it);
        }
    }
    return max;
}

std::vector<Enigma>& EscapeRoomWrapper::getAllEnigmas(){
    return riddles;
}

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level){
    escapy=escapeRoomCreate(name, 60, 6, level);
    if (escapy==NULL){
        throw mtm::escaperoom::EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::~EscapeRoomWrapper(){
    escapeRoomDestroy(escapy);
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room) {
    escapy=escapeRoomCopy(room.escapy);
    if (escapy==NULL){
        throw mtm::escaperoom::EscapeRoomMemoryProblemException();
    }
    for (auto &&enigma : room.riddles) {
        riddles.push_back(enigma);
    }
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room){
    if (this==&room){
        return *this;
    }
    escapeRoomDestroy(this->escapy);
    escapy=escapeRoomCopy(room.escapy);
    return *this;
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper &room) const {
    return (areEqualRooms(this->escapy, room.escapy) &&
            this->getName() ==room.getName());
}
bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper &room) const {
    return !(*this==room);
}
bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper &room) const {
    return (isBiggerRoom(this->escapy, room.escapy));
}
bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper &room) const {
    return (isBiggerRoom(room.escapy, this->escapy));
}

int EscapeRoomWrapper::level() const{
    return getLevel(this->escapy);
}
void EscapeRoomWrapper::rate(const int& newRate) const{
    RoomResult result=updateRate(this->escapy, newRate);
    if (result==ESCAPEROOM_BAD_PARAM || result==ESCAPEROOM_NULL_ARG){
        throw mtm::escaperoom::EscapeRoomIllegalRateException();
    }
}
std::string EscapeRoomWrapper::getName() const{
    char* room_name=roomGetName(escapy);
    std::string name_str(room_name);
    free(room_name);
    return name_str;
}
double EscapeRoomWrapper::getRate() const{
    return roomGetRate(this->escapy);
}
int EscapeRoomWrapper::getMaxTime() const{
    return roomGetMaxTime(this->escapy);
}
int EscapeRoomWrapper::getMaxParticipants() const {
    return roomGetMaxParticipants(this->escapy);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output,
                                          const EscapeRoomWrapper& room){
    return room.print(output);
}
std::ostream& EscapeRoomWrapper::print(std::ostream &output) const {
    return output << getName() << " (" <<getMaxTime()<<"/" << level() <<"/"<<
                  getMaxParticipants() << ")";
}