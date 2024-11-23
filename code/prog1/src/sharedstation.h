#ifndef SHARED_STATION_H
#define SHARED_STATION_H

#include <pcosynchro/pcosemaphore.h>
#include <pcosynchro/pcomutex.h>

class SharedStation
{
public:
    SharedStation(unsigned nbTrains);

    /* Implémentez toute la logique que vous avez besoin pour que les locomotives
     * s'attendent correctement à la station */

    /**
     * @brief Signal that the train arrived at station. If he is the last, he will release the other. Otherwise he will wait that all trains arrive at the station.
     */
    void trainAtStation();

private:

    /**
     * @brief total number of trains
     */
    unsigned nbTrains;

    /**
     * @brief number of trains at their station
     */
    unsigned nbTrainsAtStation = 0;

    /**
     * @brief semaphore to wait for the other train at the station
     */
    PcoSemaphore stationWait;

    /**
     * @brief mutex pour gérer l'accès au variables partagées
     */
    PcoMutex mutex;
};

#endif // SHARED_STATION_H
