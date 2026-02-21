#include "SpinFormat.hpp"

double SetLobby::sumProbabilities() const{
    double total;

    total = 0;
    /*
    Fonction qui calcul le total des probabilité dans calcul.
    Elle return un double contenant les valeurs ajouter de tout les distrib.
    return : total (double qui contient le total de valeur de probability)
    */
    for (size_t i = 0; i < distrib.size(); i++){
        total += distrib[i].probability; // ajoute la valeur contenue dans probability a total.
    }
    return (total); // valeur totale de toutes les probabilité des different distrib.
}

bool SetLobby::hasPayoutFor(int multiplier) const{
    /*
    Fonction qui vérifie la presence de multiplier dans prizepool.
    Return true si trouvé, sinon false.
    */
    for (size_t i = 0; i < prizepool.size(); i++){
        if (prizepool[i].multiplier == multiplier)
            return (true);
    }
    return (false);
}

bool SetLobby::validate() const{

    /*
    Fonction qui vérifie la conformité des arguments présent dans la
    structure SetLobby et renvois true si les arguments sont conforme,
    ou false si ils ne le sont pas.
    Return : False = arguments non valides.
             True =  argument valides
    */
    if (buyin <= 0 || rake < 0 || rake > 1 || 
            distrib.size() < 1 || prizepool.size() < 1)
        return (false);
        /*
        vérifie si le buyin, le rake,
        la taille de distrib et de prizepool sont valides.
        */
    for (size_t i = 0; i < prizepool.size(); i++){
        if (prizepool[i].multiplier <= 0)
            return (false);
        for (size_t j = i + 1; j < prizepool.size(); j++){
            if (prizepool[i].multiplier == prizepool[j].multiplier)
                return (false);
        }
    }
        /*
        Verifie qu'il n'y a pas de doublon, ni de valeur inférieur
        ou egales à 0 dans prizepool.
        */
    for (size_t i = 0; i < distrib.size(); i++){
        if (distrib[i].probability < 0 || distrib[i].multiplier <=0 || 
                (!(hasPayoutFor(distrib[i].multiplier))))
            return (false);
    }
        /*
        Verifie que les valeur dans distrib sont valable,
        et qu'elles sont bien présente dans prizepool via hasPayoutFor.
        Si dans distrib, laprobabilité est inférieur a 0, ou dans distrib
        si la valeur multiplier est inférieur ou égal a 0.
        */
    for (size_t i = 0; i < distrib.size(); i++){
        for (size_t j = i + 1; j < distrib.size(); j++){
            if (distrib[i].multiplier == distrib[j].multiplier)
                return (false);
        }
    }
        /*
        Vérifie qu'il n'y a aucun doublon présent dans distrib multiplier.
        */
    if (std::fabs(sumProbabilities() - 1.0) > 0.0001)
        return (false);
        /*
        Verifie que le resultat de la fonction sumProbabilities est de 1
        avec une marge autorize de + ou - 0.0001.
        */
    return (true); // Retourne valide si tout les test précédent ont été
                   // passé avec succés.
}

int main(){
    SetLobby lob;
    MultiDistrib a;
    MultiDistrib b;
    MultiDistrib c;

    lob.room = "Win";
    lob.buyin = 2.0;
    lob.rake = 0.07;
    a.multiplier = 2;
    a.probability = 0.66;
    b.multiplier = 3;
    b.probability = 0.24;
    c.multiplier = 5;
    c.probability = 0.1;
    lob.distrib.push_back(a);
    lob.distrib.push_back(b);
    lob.distrib.push_back(c);
    std::cout << "total : " << lob.sumProbabilities() << std::endl;
};