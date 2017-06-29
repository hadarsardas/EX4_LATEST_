#include "KidsRoom.h"

KidsRoom::KidsRoom(char *name, const int &escapeTime, const int &level,
                   const int &maxParticipants, const int &ageLimit):
        EscapeRoomWrapper(name,escapeTime,level,maxParticipants),
        ageLimit(ageLimit) {}

mtm::escaperoom::EscapeRoomWrapper* KidsRoom::clone() const {
    return new KidsRoom(*this);
}

int KidsRoom::getAgeLimit() const {
    return ageLimit;
}

void KidsRoom::setNewAgeLimit(const int &limit) {
    if (limit<0){
        throw mtm::escaperoom::ScaryRoomIllegalAgeLimit();
    }
    ageLimit=limit;
}
std::ostream& operator<<(std::ostream& output, const KidsRoom& room){
    return room.print(output);
}


std::ostream& KidsRoom::print(std::ostream &output) const {
    return output<<"Kids Room: "<< getName() <<" (" << getMaxTime()
                 << "/"<< level() <<"/" << getMaxParticipants()
                 << "/" << getAgeLimit()<< ")";
}