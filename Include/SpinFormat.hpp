#include <vector>
#include <string>
#include <cmath>
#include <iostream>



//Struct for prize distribution
struct Payout {
    double first; // prize for 1st place
    double second; // prize for 2nd place
    double third; // prize for 3rd place
};

//Struct for game multiplier and set prize distribution
struct PrizepoolGridEntry {
    int multiplier;   // ex: 2, 3, 5, 10...
    Payout payout;    // ex: { 2.0, 0.0, 0.0 } en buy-ins
};

//Struct who set the chance to get a multiplier
struct MultiDistrib {
    int multiplier; // multiplier affected
    double probability; // probability to get the multi affected
};

//Struct who set a Lobby
struct SetLobby {
    std::string room; // Name of the room
    double buyin; // Buy in
    double rake; // Total rake %
    std::vector<PrizepoolGridEntry> prizepool; // vector of a struct for prizepool
    std::vector<MultiDistrib> distrib; // vector of a struct for distribution prize
    
    double sumProbabilities() const; // fonction qui comptabilise les probabilité
    bool validate() const; // fonction qui check la validité de la struct
    bool hasPayoutFor(int multiplier) const; // fonction qui verifie que le multiplier est aussi present dans prizepool
};