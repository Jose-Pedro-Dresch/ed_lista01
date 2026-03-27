#include <iostream>
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
using namespace std;

class Reserve
{
    string week_day;
    string course;
    int begin;
    int end;

public:
    Reserve(string week_day, string course, int begin, int end)
    {
        this->week_day = week_day;
        this->course = course;
        this->begin = begin;
        this->end = end;

    }

    //~Reserve();
};

class Room
{
    int capacity;
    int days;
    int schedule;
    int **mat;
    Reserve reserves[70];

public:
    int getCapacity() {
        return this->capacity;
    }

    int getDays()
    {
        return this->days;
    }

    int getSchedule()
    {
        return this->schedule;
    }

    int **getMat()
    {
        return this->mat;
    }

    Room(int capacity)
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

    bool verify_capacity(int capacity){
        if(this->capacity < capacity){
            cout << "Room not big enough!" << endl;
            return false;
        }  else {
            return true;
        }
    }

    bool verify_availability(string day_week, int begin, int end) {
        int day;
        if (day_week == "segunda")
        {
            day = 0;
        }
        else if (day_week == "terca")
        {
            day = 1;
        }
        else if (day_week == "quarta")
        {
            day = 2;
        }
        else if (day_week == "quinta")
        {
            day = 3;
        }
        else if (day_week == "sexta")
        {
            day = 4;
        }
        else
        {
            cout << "Informe um dia válido " << endl;
        }

        int *schedule_day = mat[day];
        begin = begin - 7;
        end = end - 7;
        for (int i = begin; i < end; i++)
        {
            if (schedule_day[i] == 1)
            {
                cout << "Room not available for this time" << endl;
                return false;
            } 
        } return true;
    }

    bool reserve(string day_week, int begin, int end, int capacity)
    {
    if(verify_availability(day_week, begin,end) && verify_capacity(capacity)){
        int day;

        if (day_week == "segunda")
        {
            day = 0;
        }
        else if (day_week == "terca")
        {
            day = 1;
        }
        else if (day_week == "quarta")
        {
            day = 2;
        }
        else if (day_week == "quinta")
        {
            day = 3;
        }
        else if (day_week == "sexta")
        {
            day = 4;
        }
        else
        {
            cout << "Informe um dia válido " << endl;
        }

        int *schedule_day = mat[day];
        begin = begin - 7;
        end = end - 7;

        for (int i = begin; i < end; i++)
        {
            schedule_day[i] = 1;
        }
        cout << "Room reserved for " << day_week << " from " << begin + 7 << " to " << end + 7 << endl;

            return true;
        } else {
            return false;
        }
    }


};



class ReservationSystem
{

private:
    int room_count;
    Room* rooms;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:
    ReservationSystem(int room_count, Room *rooms)
    {
        this->room_count = room_count;
        this->rooms = rooms;
    }

    ~ReservationSystem();

    bool reserve(ReservationRequest request) {
        for(int i = 0; i<room_count; i++){
            if(rooms[i].reserve(request.getWeekday(), request.getStartHour(), request.getEndHour(), request.getStudentCount())){
                return true;
            } 
        }  
        return false;
           
        

    }

    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

int main()
{
    Room room1(30);
    Room room2(40);
    Room room3(60);
    Room room4(15);
    Room rooms[4] = {room1, room2, room3, room4};

    ReservationSystem system(4, rooms);


}