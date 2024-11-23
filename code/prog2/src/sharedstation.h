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

    void trainAtStation();

private:
    /* TODO */

    unsigned nbTrains;

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
