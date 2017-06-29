#include "Enigma.h"

using mtm::escaperoom::Enigma;
using mtm::escaperoom::Difficulty;

Enigma::Enigma(const std::string &name, const Difficulty &difficulty,
               const int &numOfElements, set<string> &elements) {
    if(numOfElements!=(int)elements.size()){
        throw mtm::escaperoom::EnigmaIllegalSizeParamException();
    }
    this->name=name;
    this->difficulty=difficulty;
    this->numOfElements=numOfElements;
    this->elements=set<string>(elements);
}

Enigma::Enigma(const std::string& name, const Difficulty& difficulty){
    this->name=name;
    this->difficulty=difficulty;
    this->numOfElements=0;
    this->elements=set<string>();
}

void Enigma::addElement(const std::string& element){
    if (elements.insert(element).second) {
        numOfElements++;
    }
}
void Enigma::removeElement(const std::string& element){
    if (elements.size()==0){
        throw mtm::escaperoom::EnigmaNoElementsException();
    }
    set<string>::iterator iterator=elements.find(element);
    if (iterator==elements.end()){
        throw mtm::escaperoom::EnigmaElementNotFundException();
    }
    elements.erase(iterator);
    numOfElements--;
}
Difficulty Enigma::getDifficulty() const {
    return this->difficulty;
}
string Enigma::getName() const {
    return name;
}
bool Enigma::operator==(const Enigma &enigma) const {
    return ((getName()==enigma.getName())&&(getDifficulty()
                                            == enigma.getDifficulty()));
}
bool Enigma::operator!=(const Enigma& enigma) const{
    return (!(*this==enigma));
}
bool Enigma::operator>(const Enigma& enigma) const{
    return (getDifficulty()>enigma.getDifficulty());
}
bool Enigma::operator<(const Enigma& enigma) const{
    return (enigma>*this);
}
bool Enigma::areEqualyComplex(const Enigma &enigma) const {
    return (getDifficulty()==enigma.getDifficulty()) &&
           ((numOfElements==enigma.numOfElements));
}

std::ostream& mtm::escaperoom::operator<<(std::ostream &output, const Enigma &enigma) {
    return output<<enigma.getName() <<" ("
                 <<enigma.getDifficulty() << ") " <<enigma.numOfElements;
}
