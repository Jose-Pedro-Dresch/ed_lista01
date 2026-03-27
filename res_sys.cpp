#include <iostream>
#include "ReservationRequest.hpp"
#include "res_sys.hpp"

using namespace std;

// ========================
// Reserve
// ========================

Reserve::Reserve() {}

Reserve::Reserve(string week_day, string course, int begin, int end)
{
    this->week_day = week_day;
    this->course = course;
    this->begin = begin;
    this->end = end;
}

// ========================
// Room
// ========================

Room::Room(int capacity)
{
    this->capacity = capacity;
    this->days = 5;
    this->schedule = 14;

    this->mat = new int *[days];
    for (int i = 0; i < days; i++)
    {
        this->mat[i] = new int[schedule];
        for (int j = 0; j < schedule; j++)
        {
            this->mat[i][j] = 0;
        }
    }
}

Room::~Room()
{
    for (int i = 0; i < days; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

int Room::getCapacity()
{
    return this->capacity;
}

int Room::getDays()
{
    return this->days;
}

int Room::getSchedule()
{
    return this->schedule;
}

int **Room::getMat()
{
    return this->mat;
}

int Room::dayToIndex(const string& day_week) const
{
    if (day_week == "segunda") return 0;
    if (day_week == "terca")   return 1;
    if (day_week == "quarta")  return 2;
    if (day_week == "quinta")  return 3;
    if (day_week == "sexta")   return 4;
    return -1;
}

bool Room::verify_capacity(int capacity)
{
    if (this->capacity < capacity)
    {
        cout << "Room not big enough!" << endl;
        return false;
    }
    return true;
}

bool Room::verify_availability(string day_week, int begin, int end)
{
    int day = dayToIndex(day_week);

    if (day == -1)
    {
        cout << "Informe um dia valido" << endl;
        return false;
    }

    if (begin < 7 || end > 21 || begin >= end)
    {
        cout << "Horario invalido" << endl;
        return false;
    }

    begin -= 7;
    end -= 7;

    int *schedule_day = mat[day];

    for (int i = begin; i < end; i++)
    {
        if (schedule_day[i] == 1)
        {
            cout << "Room not available for this time" << endl;
            return false;
        }
    }

    return true;
}

bool Room::reserve(string day_week, int begin, int end, int capacity)
{
    if (!verify_capacity(capacity) || !verify_availability(day_week, begin, end))
    {
        return false;
    }

    int day = dayToIndex(day_week);

    begin -= 7;
    end -= 7;

    for (int i = begin; i < end; i++)
    {
        mat[day][i] = 1;
    }

    cout << "Room reserved for " << day_week
         << " from " << begin + 7
         << " to " << end + 7 << endl;

    return true;
}

// ========================
// ReservationSystem
// ========================

ReservationSystem::ReservationSystem(int room_count, Room *rooms)
{
    this->room_count = room_count;
    this->rooms = rooms;
}

ReservationSystem::~ReservationSystem() {}

bool ReservationSystem::reserve(ReservationRequest request)
{
    for (int i = 0; i < room_count; i++)
    {
        if (rooms[i].reserve(
                request.getWeekday(),
                request.getStartHour(),
                request.getEndHour(),
                request.getStudentCount()))
        {
            return true;
        }
    }
    return false;
}

bool ReservationSystem::cancel(std::string course_name)
{
    return false;
}

void ReservationSystem::printSchedule()
{
}
