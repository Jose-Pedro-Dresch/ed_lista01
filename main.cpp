#include <iostream>
#include "../include/ReservationSystem.hpp"
#include "../include/ReservationRequest.hpp"
using namespace std;

int main()
{
    // Exemplo de inicialização do sistema
    int capacities[3] = {30, 50, 80};

    ReservationSystem system(3, capacities);
}