#include <iostream>
#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"
using namespace std;

int main()
{
    // Exemplo de inicialização do sistema
    
    //int capacities[3] = {30, 50, 80};
    //ReservationSystem system(3, capacities);


    int capacities[4] = {15, 40, 50, 15};
    ReservationSystem system(4, capacities);

    ReservationRequest request1("TACD", "segunda", 9, 14, 20);
    ReservationRequest request2("Algebra Linear", "sexta", 9, 14, 40);
    ReservationRequest request3("Matematica Discreta", "quinta", 9, 14, 20);
    ReservationRequest request4("Banco de Dados", "segunda", 11, 15, 20);
    ReservationRequest request5("Estrutura de Dados", "quarta", 10, 20, 20);
    ReservationRequest request6("Probabilidade", "segunda", 7, 8, 60);
    ReservationRequest request7("Análise", "segunda", 16, 18, 20);
    
    system.reserve(request1);
    system.reserve(request2);
    system.reserve(request3);
    system.reserve(request4);
    system.reserve(request5);
    system.reserve(request6);
    system.reserve(request7);

    system.printSchedule();

    system.cancel("Banco de Dados");
    system.printSchedule();
}