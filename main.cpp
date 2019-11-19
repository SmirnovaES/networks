
#include <thread>

#include "Station.h"

void startStation( Station& station )
{
    station.sendMessage();
}

int main(int argc, char* argv[]) {
    if ( argc != 2 )
    {
        std::cout << "Wrong number of arguments. Expected: 1, received: " << argc - 1 << std::endl;
        return EXIT_FAILURE;
    }

    int N = atoi(argv[1]);

    std::vector<Station> stations;
    std::vector<std::thread> threads;

    for (int i = 0; i < N; ++i)
    {
        char a = '1' + i;
        stations.emplace_back(a);
    }

    for (int i = 0; i < N; ++i)
    {
        threads.emplace_back( startStation, std::ref(stations[i]));
    }

    for (int i = 0; i < N; ++i)
    {
        threads[i].join();
    }

    return 0;
}