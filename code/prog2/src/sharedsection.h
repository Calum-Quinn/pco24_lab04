//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>
#include <pcosynchro/pcomutex.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface
{
public:

    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection() : sem(0), occupied(false), priority(PriorityMode::HIGH_PRIORITY) {
        // TODO

        // Initialise sem to 1 so it can be used like a mutex
        // Initialise occupied to false as the trains don't start on the shared portion of track
        // Initialise the priority mode to value the highest priority
        // Initialise requests to base values representing the absence of a request
        requests[0] = -1;
        requests[1] = -1;
    }

    /**
     * @brief access Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée par une autre locomotive.
     * Si la locomotive et son thread ont été mis en attente,
     * le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     */
    void access(Locomotive &loco) override {
        // TODO
        loco.afficherMessage("My priority " + QString::number(requests[indexConverter(loco, true)]));
        loco.afficherMessage("The other priority is " + QString::number(requests[indexConverter(loco, false)]));
        loco.afficherMessage("The requests look like this {" + QString::number(requests[0]) + "," + QString::number(requests[1]) + "}");
        loco.afficherMessage("My priority is less important than the other one");
        loco.afficherMessage(QString::number(requests[indexConverter(loco, priority == PriorityMode::HIGH_PRIORITY ? true : false)]) + "<" + QString::number(requests[indexConverter(loco, priority == PriorityMode::HIGH_PRIORITY ? false : true)]));

        // Check whether the shared portion is occupied or if another train with a higher priority is waiting
            // the indexes are chosen depending on the priority mode so that the if is executed if the train has a less valued priority value than the other one waiting
        if (occupied || requests[indexConverter(loco, priority == PriorityMode::HIGH_PRIORITY ? true : false)] < requests[indexConverter(loco, priority == PriorityMode::HIGH_PRIORITY ? false : true)]) {
            loco.arreter();
            sem.acquire(); // Blocks the train as the common part is occupied or higher priority train is there
            mut.lock();
            occupied = true; // Sets occupied to true as the other train has now left and set it to false
            mut.unlock();
            loco.demarrer();
        }
        else {
            mut.lock();
            occupied = true;
            mut.unlock();
        }

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {
        // TODO

        // Update the shared variables
        mut.lock();
        requests[indexConverter(loco, true)] = -1;
        occupied = false; // Show the other train that the track is now free
        if (requests[indexConverter(loco, false)] != -1) {
            sem.release(); // Release the hold on the common portion if another train is waiting
        }
        mut.unlock();

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
    }

    void request(Locomotive& loco) override {
        // Store the priority of the train (no getter or setter for priority)
        mut.lock();
        requests[indexConverter(loco, true)] = loco.priority;
        mut.unlock();
    }

    void togglePriorityMode() override {
        // Invert the priority mode
        priority = priority == PriorityMode::HIGH_PRIORITY ? PriorityMode::LOW_PRIORITY : PriorityMode::HIGH_PRIORITY;
    }

private:

    /* A vous d'ajouter ce qu'il vous faut */

    // Méthodes privées ...
    // Attribut privés ...
    PcoSemaphore sem; // To get a train to wait if the common part of track is occupied
    PcoMutex mut; // To lock the shared variables during modification
    bool occupied;  // Indicates whether the common part is currently occupied
    PriorityMode priority; // Stores the current priority mode
    int requests[2]; // Stores the current requests for access to the shared portion

    int indexConverter(Locomotive& loco, bool thisTrain) {
        // Define the index depending on the train
        // This could be done better with a more logical definition of trains and numbers (e.g. a vector of trains)
        // thisTrain allows finding the other trains priority based on it's index
        return (loco.numero() == 7) ^ thisTrain ? 1 : 0;
    }
};


#endif // SHAREDSECTION_H
