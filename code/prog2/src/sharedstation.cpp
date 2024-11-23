//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "sharedstation.h"

#include <chrono>
#include <thread>
#include <pcosynchro/pcothread.h>

SharedStation::SharedStation(unsigned nbTrains) :
    nbTrains(nbTrains)
{

}

void SharedStation::trainAtStation(){

    ++nbTrainsAtStation;

    mutex.lock();

    if (nbTrainsAtStation == nbTrains) {
        // Wait for 2 seconds (usleep takes microseconds as a unit)
        PcoThread::thisThread()->usleep(2000000);
        // Release the other train
        for(unsigned i = 0; i < nbTrains; ++i){
            stationWait.release();
        }

        mutex.unlock();
    }
    else {

        // Wait for the other train
        mutex.unlock();
        stationWait.acquire();
    }
}
