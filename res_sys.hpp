#pragma once
#include <string>
#include "ReservationRequest.hpp"

class Reserve
{
    std::string week_day;
    std::string course;
    int begin;
    int end;

public:
    Reserve();
    Reserve(std::string week_day, std::string course, int begin, int end);
};

class Room
{
    int capacity;
    int days;
    int schedule;
    int **mat;
    Reserve reserves[70];

    int dayToIndex(const std::string& day_week) const;

public:
    Room(int capacity);
    ~Room();

    int getCapacity();
    int getDays();
    int getSchedule();
    int **getMat();

    bool verify_capacity(int capacity);
    bool verify_availability(std::string day_week, int begin, int end);
    bool reserve(std::string day_week, int begin, int end, int capacity);
};

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