//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :
    //sharedSection->access(loco);
    //sharedSection->leave(loco);

    while (!PcoThread::thisThread()->stopRequested()) {
        // Go round n times
        for (int i = 0; i < n; ++i) {
            // If it detects it's going to enter a common part of track, request access

            // HOW DETECT SHARED AREA???
                // I DONT KNOW HOW TO FIND/DECLARE WHERE IT IS


            sharedSection->access(loco);
            // Once finished with the common part, leave properly
            sharedSection->leave(loco);
        }

        // Stop at the station at the end of the last loop
            // If the other train is not yet in it's station, wait

            // Wait for 2 seconds (usleep takes microseconds as a unit)
            PcoThread::thisThread()->usleep(2000000);
        
        // Start up again but in the other direction
        loco.inverserSens();
        loco.demarrer();
    }
    

    while(true) {
        // On attend qu'une locomotive arrive sur le contact 1.
        // Pertinent de faire ça dans les deux threads? Pas sûr...
        attendre_contact(1);
        loco.afficherMessage("J'ai atteint le contact 1");
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}

int LocomotiveBehavior::generateRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
