#pragma once
#include "ReservationRequest.hpp"
#include <string>

///===============================================================================================================================
//// RESERVE

class Reserve
{
    std::string week_day;
    std::string course;
    int begin;
    int end;

public:
    Reserve();

    Reserve(std::string week_day, std::string course, int begin, int end);

    void print();

    std::string getCourse();
    std::string getDay();
    int getBegin();
    int getEnd();
};

///===============================================================================================================================
//// RESERVES ARRAYS

class ReservesArray
{
protected:
    int capacity;
    int size;
    Reserve *data;

public:
    ReservesArray();
    ~ReservesArray();

    void append(Reserve r);
    void resize(int new_capacity);
    int get_day_index(std::string day_week);
    // bubble sort
    void sort_reserves();
    void remove_at(int index);
    bool remove_by_course(std::string course_name);

    Reserve getReserveByIndex(int i);

    int getSize();
};


///===============================================================================================================================
//// ROOM

class Room
{
    int capacity;
    int days;
    int schedule;
    int **mat;
    ReservesArray reserves;
    int room_number;

public:
    int getCapacity();
    int getDays();
    int getSchedule();
    int **getMat();
    ReservesArray& get_reservas();
    int getRoomNumber();

    Room(int capacity, int room_number);
    ~Room(); 

    int get_day_index(std::string day_week);
    bool verify_reserve(std::string course, std::string day_week, int begin, int end, int student_count);
    bool reserve(std::string course, std::string day_week, int begin, int end);
    void print_reserves();
    bool remove_reserve(std::string course_name);

};

///===============================================================================================================================
//// RESERVATION SYSTEM



// Classe que representa o sistema de reserva
class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    Room** rooms;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};