#ifndef HW4_NEW_KIDSROOM_H
#define HW4_NEW_KIDSROOM_H
#include "EscapeRoomWrapper.h"
#include <iostream>
class KidsRoom : public mtm::escaperoom::EscapeRoomWrapper {
    int ageLimit;
public:
// Constructs a new Kids Escape Room with the specified data.
//
// @param name : the name of the kids escape room.
// @param escapeTime : the maximal escape time allowed in the kids room.
// @param level : the level of the kids escape room.
    // @param maxParticipants: the maximal participants allowed in the room.
    // @param ageLimit: the age limit of the room.

    //the kids room inherits from the EscapeRoomWrapper. its unique field is
    // ageLimit

    // @throws EscapeRoomMemoryProblemException in case of creation failure.

    KidsRoom(char *name, const int &escapeTime, const int &level,
             const int &maxParticipants, const int &ageLimit);

    //copy constructor
    //
    //@param kids : the kids room to be copied.
    //@throws EscapeRoomMemoryProblemException in case of creation failure.

    KidsRoom(const KidsRoom &kids) = default;

    mtm::escaperoom::EscapeRoomWrapper *clone() const override;

    // Function set a new age limit for a kids room
    //
    // @param limit: the new limit to set for the kids room.

    void setNewAgeLimit(const int &limit);

    // Function returns the room's age limit.
    //
    // @params: no params.

    int getAgeLimit() const;

    // Prints the data of the kids Room in the following format:
    //
    //     Kids Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)
    //
    // @param output : the output stream to which the data is printed.
    // @param room : the room whose data is printed.
    friend std::ostream &
    operator<<(std::ostream &output, const KidsRoom &room);

    std::ostream &print(std::ostream &output) const override;
};
std::ostream& operator<<(std::ostream& output, const KidsRoom& room) ;
#endif //HW4_NEW_KIDSROOM_H