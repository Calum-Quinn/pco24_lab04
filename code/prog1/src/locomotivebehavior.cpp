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
        // Faire N tours
        for (int i = 0; i < n; ++i) {
            // S'il va arriver en tronçon commun, demander l'accès
            sharedSection->access(loco);
            // Quand il arrive à la fin du trançon commun, quitter proprement
            sharedSection->leave(loco);
        }

        // S'arrêter en gare à la fin du dernier tour
            // Si l'autre train n'est pas en gare, attendre

            // Attendre 2 sec
        
        // Redémarrer dans l'autre sens
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

static int generateRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
