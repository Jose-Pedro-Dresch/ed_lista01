#pragma once
#include "ReservationRequest.hpp"
#include <string>
using namespace reservationrequest;



class Room; // forward declaration

// Classe que representa o sistema de reserva
class ReservationSystem
{
private:
    int room_count;
    Room* rooms;

public:
    ReservationSystem(int room_count, Room *rooms);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();
};