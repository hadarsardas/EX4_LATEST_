#include "Company.h"
using::mtm::escaperoom::Company;
using mtm::escaperoom::EscapeRoomWrapper;
Company::Company(string name, string phoneNumber) {
    this->name=name;
    this->phoneNumber=phoneNumber;
    this->rooms=set<EscapeRoomWrapper*>();
}
Company::~Company() {
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        delete (*it);
    }
}
void Company::createRoom(char *name, const int &escapeTime, const int &level,
                         const int &maxParticipants) {
    EscapeRoomWrapper *room_ptr=NULL;
    try {
        room_ptr = new EscapeRoomWrapper(name, escapeTime, level,
                                                            maxParticipants);
    }
    catch (EscapeRoomMemoryProblemException){
        throw CompanyMemoryProblemException();
    }
    rooms.insert(room_ptr);
}
void Company::createScaryRoom(char *name, const int &escapeTime,
                              const int &level, const int &maxParticipants,
                              const int &ageLimit,
                              const int &numOfScaryEnigmas) {
    EscapeRoomWrapper* scary_ptr= new ScaryRoom(name,escapeTime,level,
                                                maxParticipants, ageLimit,
                                                numOfScaryEnigmas);
    rooms.insert(scary_ptr);
}
void Company::createKidsRoom(char *name, const int &escapeTime,
                             const int &level, const int &maxParticipants,
                             const int &ageLimit) {
    EscapeRoomWrapper* kids_ptr=
            new KidsRoom(name,escapeTime,level,maxParticipants,ageLimit);
    rooms.insert(kids_ptr);
}
set<mtm::escaperoom::EscapeRoomWrapper*> Company::getAllRooms() const {
    return rooms;
}
void Company::removeRoom(const EscapeRoomWrapper &room) {
    if (rooms.size() == 0) {
        throw CompanyRoomNotFoundException();
    }
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        if(**it==room){
            delete *it;
            rooms.erase(*it);
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}

void Company::addEnigma(const EscapeRoomWrapper &room, const Enigma &enigma) {
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        if (**it==room){
            (*it)->addEnigma(enigma);
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}
void Company::removeEnigma(const EscapeRoomWrapper &room,
                           const Enigma &enigma) {
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        if ((**it)==room){
            if ((*it)->getAllEnigmas().size()==0){
                throw CompanyRoomHasNoEnigmasException();
            }
            try {
                (*it)->removeEnigma(enigma);
            } catch (EscapeRoomNoEnigmasException){
                throw CompanyRoomHasNoEnigmasException();
            }catch (EscapeRoomEnigmaNotFoundException){
                throw CompanyRoomEnigmaNotFoundException();
            }
            return;
        }
    }
    throw CompanyRoomNotFoundException();
}
void Company::addItem(const EscapeRoomWrapper &room, const Enigma &enigma,
                      const string &element) {
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        if ((**it)==room){
            for (std::vector<Enigma>::iterator
                         riddle_it=((*it)->getAllEnigmas().begin());
                 riddle_it!=((*it)->getAllEnigmas().end());riddle_it++){
                if ((*riddle_it)==enigma){
                    (*riddle_it).addElement(element);
                    return;
                }
            }
            throw CompanyRoomEnigmaNotFoundException();
        }
    }
    throw CompanyRoomNotFoundException();
}

void Company::removeItem(const EscapeRoomWrapper &room, const Enigma &enigma,
                         const string &element) {
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        if ((*(EscapeRoomWrapper*)(*it))==room){
            for (std::vector<Enigma>::iterator
                         riddle_it=((*it)->getAllEnigmas().begin());
                 riddle_it!=((*it)->getAllEnigmas().end());riddle_it++){
                if ((*riddle_it)==enigma){
                    try{
                        (*riddle_it).removeElement(element);
                    }
                    catch (EnigmaNoElementsException){
                        throw CompanyRoomEnigmaHasNoElementsException();
                    }
                    catch (EnigmaElementNotFundException){
                        throw CompanyRoomEnigmaElementNotFoundException();
                    }
                    return;
                }
            }
            throw CompanyRoomEnigmaNotFoundException();
        }
    }
    throw CompanyRoomNotFoundException();
}
set<EscapeRoomWrapper*> Company::getAllRoomsByType(RoomType type) const {
    set<EscapeRoomWrapper*> setRoom;
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        KidsRoom* kidsRoom_ptr= dynamic_cast<KidsRoom*>(*it);
        ScaryRoom* scaryRoom_ptr= dynamic_cast<ScaryRoom*>(*it);
        if ((type==SCARY_ROOM)&&
                (scaryRoom_ptr!=NULL)) {
            setRoom.insert(*it);
        }
        else if ((type==KIDS_ROOM)&&
                (kidsRoom_ptr!=NULL)){
            setRoom.insert(*it);
        }
        else if((type==BASE_ROOM)&&
                (kidsRoom_ptr==NULL)
                &&(scaryRoom_ptr==NULL)){
            setRoom.insert(*it);
            }
        }
    return setRoom;
}

EscapeRoomWrapper* Company::getRoomByName(const string &name) const {
    for(std::set<EscapeRoomWrapper*>::iterator it=rooms.begin();it!=rooms.end();
        it++){
        if ((*it)->getName()==name){
            return *it;
        }
    }
    throw CompanyRoomNotFoundException();
}
Company::Company(const Company &company) {
    this->name=company.name;
    this->phoneNumber=company.phoneNumber;
    std::set<EscapeRoomWrapper*> new_rooms;
    for(std::set<EscapeRoomWrapper*>::iterator it=company.rooms.begin();
        it!=company.rooms.end(); it++){
        EscapeRoomWrapper* new_room=(*it)->clone();
        rooms.insert(new_room);
    }
}

Company& Company::operator=(const Company &company) {
    if (this == &company) {
        return *this;
    }
    for (std::set<EscapeRoomWrapper *>::iterator it = rooms.begin();
         it != rooms.end();
         it++) {
        delete(*it);
    }
    rooms.clear();
    for (std::set<EscapeRoomWrapper *>::iterator it = company.rooms.begin();
         it != company.rooms.end(); it++) {
        EscapeRoomWrapper *new_room = (*it)->clone();
        rooms.insert(new_room);
    }
    name = company.name;
    phoneNumber = company.phoneNumber;
    return *this;
}
std::ostream &
::mtm::escaperoom::operator<<(std::ostream &output, const Company &company) {
    output<<company.name << " : " << company.phoneNumber<< std::endl;
    for (auto &&room : company.rooms) {
        output << (*room) << std::endl;
    }
    return output;
}
