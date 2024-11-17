//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedsectioninterface.h"
#include <pcosynchro/pcosemaphore.h>
#include <pcosynchro/pcomutex.h>

#include <random>

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection /*, autres paramètres éventuels */, int beforeSection, int afterSection, int station, int railroadSwitch, int direction, PcoSemaphore* stationWait, bool* wait, PcoMutex* mutex) : 
        loco(loco), 
        sharedSection(sharedSection), 
        n(generateRandom(1,10)), 
        beforeSection(beforeSection), 
        afterSection(afterSection), 
        station(station), 
        railroadSwitch(railroadSwitch), 
        direction(direction),
        stationWait(stationWait),
        wait(wait),
        mutex(mutex) {
        // Eventuel code supplémentaire du constructeur
    }

protected:
    /*!
     * \brief run Fonction lancée par le thread, représente le comportement de la locomotive
     */
    void run() override;

    /*!
     * \brief printStartMessage Message affiché lors du démarrage du thread
     */
    void printStartMessage() override;

    /*!
     * \brief printCompletionMessage Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override;

    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SharedSectionInterface> sharedSection;

    /*
     * Vous êtes libres d'ajouter des méthodes ou attributs
     *
     * Par exemple la priorité ou le parcours
     */

    /**
     * @brief function to generate a random integer within a specified range
     */
    static int generateRandom(int min, int max);

    /**
     * @brief number of loops to go through before stopping at the station
     */
    const int n;

    /**
     * @brief contact point just before the shared section
     */
    int beforeSection;
    
    /**
     * @brief contact point just after the shared section
     */
    int afterSection;

    /**
     * @brief contact point representing the station
     */
    int station;

    /**
     * @brief switch point at the end of the shared section
     */
    int railroadSwitch;

    /**
     * @brief direction in which the train needs to go when exiting the shared section
     */
    int direction;

    /**
     * @brief semaphore to wait for the other train at the station
     */
    PcoSemaphore* stationWait;

    /**
     * @brief boolean to know whether the other train is in the station
     */
    bool* wait;

    /**
     * @brief mutex pour gérer l'accès au variables partagées
     */
    PcoMutex* mutex;
};

#endif // LOCOMOTIVEBEHAVIOR_H
