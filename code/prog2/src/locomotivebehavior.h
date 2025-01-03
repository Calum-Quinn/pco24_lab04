//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedstation.h"
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
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection /*, autres paramètres éventuels */, int request, int afterSection, int request2, int afterSection2, int accept, int accept2, int station, int railroadSwitch, int railroadSwitch2, int direction, SharedStation* sharedStation) :
        loco(loco), 
        sharedSection(sharedSection), 
        n(generateRandom(1,10)), 
        requestPoint(request), 
        afterSection(afterSection),
        requestPoint2(request2),
        afterSection2(afterSection2),
        acceptancePoint(accept),
        acceptancePoint2(accept2),
        station(station), 
        railroadSwitch(railroadSwitch),
        railroadSwitch2(railroadSwitch2),
        direction(direction),
        sharedStation(sharedStation)
    {
        // Eventuel code supplémentaire du constructeur
        clockwise = true;
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
     * @brief contact point before the shared section where the entrance request is sent
     */
    int requestPoint;

    /**
     * @brief contact point before the shared section where the entrance request is sent when going counter clockwise
     */
    int requestPoint2;

    /**
     * @brief contact point just before the shared section where the decision to stop or not is made
     */
    int acceptancePoint;

    /**
     * @brief contact point just before the shared section where the decision to stop or not is made when going counter clockwise
     */
    int acceptancePoint2;
    
    /**
     * @brief contact point just after the shared section
     */
    int afterSection;

    /**
     * @brief contact point just after the shared section when going in the other direction
     */
    int afterSection2;

    /**
     * @brief contact point representing the station
     */
    int station;

    /**
     * @brief switch point at the end of the shared section
     */
    int railroadSwitch;

    /**
     * @brief switch point at the end of the shared section when going counter clockwise
     */
    int railroadSwitch2;

    /**
     * @brief direction in which the train needs to go when exiting the shared section
     */
    int direction;

    SharedStation* sharedStation;

    /**
     * @brief defines in which direction the train is going to know what to modify in the shared section
     */
    bool clockwise;
};

#endif // LOCOMOTIVEBEHAVIOR_H
