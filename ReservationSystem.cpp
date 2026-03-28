#include <iostream>
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
using namespace std;

///===============================================================================================================================
//// RESERVE
class Reserve
{
    string week_day;
    string course;
    int begin;
    int end;

public:
    Reserve()
    {
        week_day = "";
        course = "";
        begin = 0;
        end = 0;
    }
    Reserve(string week_day, string course, int begin, int end)
    {
        this->week_day = week_day;
        this->course = course;
        this->begin = begin;
        this->end = end;
    }

    void print()
    {
        cout << "Dia: " << week_day << endl;
        cout << begin << "h~" << end << "h: " << course << endl;
    }

    string getCourse() { return course; }
    string getDay() { return week_day; }
    int getBegin() { return begin; }
    int getEnd() { return end; }
};

///===============================================================================================================================
//// ARRAY RESERVAS
class ArrayReservas
{
protected:
    int capacidade;
    int tamanho;
    Reserve *dados;

public:
    ArrayReservas()
    { // Initialization
        this->capacidade = 10;
        this->tamanho = 0;
        this->dados = new Reserve[capacidade];
    }

    ~ArrayReservas()
    {
        delete[] this->dados;
    }

    void append(Reserve r)
    {
        if (this->capacidade == this->tamanho)
        {
            resize(2 * this->capacidade);
        }
        this->dados[this->tamanho] = r;
        this->tamanho++;
    }

    void resize(int nova_capacidade)
    {
        Reserve *novo_dados = new Reserve[nova_capacidade];
        for (int i = 0; i < this->tamanho; i++)
        {
            novo_dados[i] = this->dados[i];
        }
        delete[] this->dados;
        this->dados = novo_dados;
        this->capacidade = nova_capacidade;
    }

    Reserve get(int i)
    {
        return dados[i];
    }

    int size()
    {
        return tamanho;
    }
};

///===============================================================================================================================
//// ROOM

class Room
{
    int capacity;
    int days;
    int schedule;
    int **mat;
    ArrayReservas reservas;

public:
    int getCapacity()
    {
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

    Room()
    {
        capacity = 0;
        days = 5;
        schedule = 14;
        mat = new int *[days];
        for (int i = 0; i < days; i++)
        {
            mat[i] = new int[schedule]{0};
        }
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

    bool verify_capacity(int student_count)
    {
        if (this->capacity < student_count)
        {
            cout << "Room not big enough!" << endl;
            return false;
        }
        else
        {
            return true;
        }
    }

    int get_day_index(string day_week)
    {
        if (day_week == "segunda")
        {
            return 0;
        }
        if (day_week == "terca")
        {
            return 1;
        }
        if (day_week == "quarta")
        {
            return 2;
        }
        if (day_week == "quinta")
        {
            return 3;
        }
        if (day_week == "sexta")
        {
            return 4;
        }

        return -1;
    }

    bool verify_availability(string day_week, int begin, int end)
    {
        int day = get_day_index(day_week);

        if (day == -1)
        {
            cout << "Informe um dia válido" << endl;
            return false;
        }

        int *schedule_day = mat[day];
        int begin_array = begin - 7;
        int end_array = end - 7;

        for (int i = begin_array; i < end_array; i++)
        {
            if (schedule_day[i] == 1)
            {
                cout << "Room not available for this time" << endl;
                return false;
            }
        }
        return true;
    }

    bool reserve(string course, string day_week, int begin, int end, int student_count)
    {
        int day = get_day_index(day_week);

        if (day == -1)
        {
            cout << "Informe um dia válido" << endl;
            return false;
        }

        if (verify_availability(day_week, begin, end) && verify_capacity(student_count))
        {
            int *schedule_day = mat[day];
            int begin_array = begin - 7;
            int end_array = end - 7;

            for (int i = begin_array; i < end_array; i++)
            {
                schedule_day[i] = 1;
            }

            Reserve r(day_week, course, begin, end);
            reservas.append(r);

            cout << "Room reserved for " << course
                 << " on " << day_week
                 << " from " << begin
                 << " to " << end << endl;

            return true;
        }
        return false;
    }

    void print_reserves()
    {
        for (int i = 0; i < reservas.size(); i++)
        {
            reservas.get(i).print();
        }
    }
};

///===============================================================================================================================
//// RESERVATION SYSTEM

ReservationSystem::ReservationSystem(int room_count, int *room_capacities)
{
    this->room_count = room_count;
    this->room_capacities = room_capacities;
    this->rooms = new Room[room_count];

    for (int i = 0; i < room_count; i++)
    {
        rooms[i] = Room(room_capacities[i]);
    }
}

ReservationSystem::~ReservationSystem()
{
}

bool ReservationSystem::reserve(ReservationRequest request)
{
    return false;
}

bool ReservationSystem::cancel(std::string course_name)
{
    return false;
}

void ReservationSystem::printSchedule()
{
    for (int i = 0; i < room_count; i++)
    {
        rooms[i].print_reserves();
    }
}

int main()
{
    Room room1(30);
    Room room2(40);
    Room room3(60);
    Room room4(15);
    Room rooms[4] = {room1, room2, room3, room4};

    int capacities[4] = {1, 2, 3, 4};
    ReservationSystem system(4, capacities);

    room1.reserve("TACD", "segunda", 9, 14, 30);
    room1.reserve("Banco de Dados", "segunda", 11, 15, 25);
    room1.reserve("Estrutura de Dados", "quarta", 10, 13, 20);
    room1.reserve("Estrutura de Dados", "quarta", 10, 13, 20);
    room1.print_reserves();

    return 0;
}