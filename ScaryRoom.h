    #ifndef HW4_NEW_SCARYROOM_H
#define HW4_NEW_SCARYROOM_H
#include "EscapeRoomWrapper.h"


class ScaryRoom : public mtm::escaperoom::EscapeRoomWrapper {
    int ageLimit;
    int numOfScaryEnigmas;
public:
    // Constructs a new Scary Escape Room with the specified data.
    //
    // @param name : the name of the Scary escape room.
    // @param escapeTime : the maximal escape time allowed in the scary room.
    // @param level : the level of the scary escape room.
    // @param maxParticipants: the maximal participants allowed in the room.
    // @param ageLimit: the age limit of the room.
    // @param numOfScaryEnigmas: the number of scary enigmas of the room.

    //the scary room inherits from the EscapeRoomWrapper. its unique fields are:
    // ageLimit and numOfScaryEnigmas

    // @throws EscapeRoomMemoryProblemException in case of creation failure.

    ScaryRoom(char *name, const int &escapeTime, const int &level,
              const int &maxParticipants, const int &ageLimit,
              const int &numOfScaryEnigmas);

    //copy constructor
    //
    //@param scary : the scary room to be copied.
    //@throws EscapeRoomMemoryProblemException in case of creation failure.

    ScaryRoom(const ScaryRoom& scary)= default;

    // Function set a new age limit for a scary room
    //
    // @param limit: the new limit to set for the scary room.

    void setNewAgeLimit(const int &limit);

    // Function increaments the number of scary enigmans by 1.
    void incNumberOfScaryEnigmas();

    // Function returns the age limit of the room
    int getAgeLimit() const;

    mtm::escaperoom::EscapeRoomWrapper* clone() const override;


    friend std::ostream& operator<<(std::ostream& output, const ScaryRoom& room);

    std::ostream& print(std::ostream &output) const override;
};
    // Prints the data of the scary Room in the following format:
    //
    //Scary Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)
    //
    // @param output : the output stream to which the data is printed.
    // @param room : the room whose data is printed.
std::ostream& operator<<(std::ostream& output, const ScaryRoom& room);

#endif //HW4_NEW_SCARYROOM_H