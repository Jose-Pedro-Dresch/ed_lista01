#include <iostream>
#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"
using namespace std;

int main()
{

    int capacities[4] = {20, 30, 50, 40};
    ReservationSystem system(4, capacities);

    // Compatível com a sala 1
    ReservationRequest request1("TACD", "segunda", 9, 11, 15);
    // Não poderá ser na sala 1 por conflito de horário
    ReservationRequest request2("Algebra Linear", "segunda", 10, 11, 20);
    // Poderá ser na sala 1 porque começa diretamente após o fim de TACD
    ReservationRequest request3("Matematica Discreta", "segunda", 11, 12, 20);
    // Não poderá ser na sala 1 na sala 2 por capacidade insuficiente de alunos
    ReservationRequest request4("Banco de Dados", "terca", 11, 15, 40);
    // Não poderá ocorrer em nenhuma sala por falta de capacidade
    ReservationRequest request5("Analise", "sexta", 20, 21, 60);
    // Poderá ocorrer na sala 3
    ReservationRequest request6("Probabilidade", "quinta", 8, 9, 50);
    ReservationRequest request7("AEDV", "quarta", 8, 9, 20);
    ReservationRequest request8("Calculo", "quinta", 7, 8, 35);
    
    // O sistema utiliza seu método de reserva para cada solicitação
    system.reserve(request1);
    system.reserve(request2);
    system.reserve(request3);
    system.reserve(request4);
    system.reserve(request5);
    system.reserve(request6);
    system.reserve(request7);
    system.reserve(request8);

    // O sistema printa as reservas da semana
    system.printSchedule();

    // Vamos cancelar a aula de Álgebra Linear (que está na sala 2)
    system.cancel("Algebra Linear");

    // Mostramos novamente a grade de horários após o cancelamento
    system.printSchedule();
}