#include <iostream>
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
using namespace std;

///===============================================================================================================================
//// RESERVE

Reserve::Reserve()
{
    week_day = "";
    course = "";
    begin = 0;
    end = 0;
}

Reserve::Reserve(string week_day, string course, int begin, int end)
{
    this->week_day = week_day;
    this->course = course;
    this->begin = begin;
    this->end = end;
}

void Reserve::print()
{
    cout << begin << "h~" << end << "h: " << course << endl;
}

string Reserve::getCourse() { return course; }
string Reserve::getDay() { return week_day; }
int Reserve::getBegin() { return begin; }
int Reserve::getEnd() { return end; }


///===============================================================================================================================
//// ARRAY RESERVAS

ReservesArray::ReservesArray()
{ // Initialization
        this->capacity = 10;
        this->size = 0;
        this->data = new Reserve[capacity];
}

ReservesArray::~ReservesArray()
{
        delete[] this->data;
}

void ReservesArray::append(Reserve r)
{
    if (this->capacity == this->size)
    {
        resize(2 * this->capacity);
    }
    this->data[this->size] = r;
    this->size++;
}

void ReservesArray::resize(int new_capacity)
{
    Reserve *novo_dados = new Reserve[new_capacity];
    for (int i = 0; i < this->size; i++)
    {
        novo_dados[i] = this->data[i];
    }
    delete[] this->data;
    this->data = novo_dados;
    this->capacity = new_capacity;
}

int ReservesArray::get_day_index(string day_week)
{
    if (day_week == "segunda") return 0;
    if (day_week == "terca") return 1;
    if (day_week == "quarta") return 2;
    if (day_week == "quinta") return 3;
    if (day_week == "sexta") return 4;
    return -1;
}

// bubble sort
void ReservesArray::sort_reserves(){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size-i-1; j++) {
            int day1 = get_day_index(data[j].getDay());
            int day2 = get_day_index(data[j+1].getDay());

            if (day1 > day2) {
                // Troca os elementos
                Reserve temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
                } else if (day1 == day2) {
                if(data[j].getBegin() > data[j+1].getBegin()){
                    Reserve temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
                }
        }
    }
}

void ReservesArray::remove_at(int index)
{
if(index < 0 || index >= size)
{
    return;
}

for(int i = index; i < size - 1; i++)
{
    data[i] = data[i+1];
}

size--;
}
    
bool ReservesArray::remove_by_course(string course_name)
{
for(int i = 0; i < size; i++)
{
    if(data[i].getCourse() == course_name)
    {
        remove_at(i);
        return true;
    }
}
return false;
}


Reserve ReservesArray::getReserveByIndex(int i)
{
    return data[i];
}

int ReservesArray::getSize()
{
    return size;
}


///===============================================================================================================================
//// ROOM

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

int** Room::getMat()
{
    return this->mat;
}


ReservesArray& Room::get_reservas()
{
    return reserves;
}

int Room::getRoomNumber() 
{
    return this->room_number;    
}


Room::Room(int capacity, int room_number)
{
    this->capacity = capacity;
    this->days = 5;
    this->schedule = 14;

    this->mat = new int *[days];
    for (int i = 0; i < days; i++)
    {
        this->mat[i] = new int[schedule]{0};
    }
    this->room_number = room_number;
}

Room::~Room()
{
for (int i = 0; i < days; i++)
{
    delete[] mat[i];
}
delete[] mat;
}   

int Room::get_day_index(string day_week)
{
    if (day_week == "segunda") return 0;
    if (day_week == "terca") return 1;
    if (day_week == "quarta") return 2;
    if (day_week == "quinta") return 3;
    if (day_week == "sexta") return 4;
    return -1;
}


bool Room::verify_reserve(string course, string day_week, int begin, int end, int student_count) 
{
    if (this->capacity < student_count)
    {
        // cout << "Room " << this->getRoomNumber() << " not big enough!" << endl;
        return false;
    }
    else
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
            // cout << "Room " << this->getRoomNumber() << " not available for this time" << endl;
            return false;
        }
    }
    return true;
    }
}

bool Room::reserve(string course, string day_week, int begin, int end)
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
        schedule_day[i] = 1;
    }

    Reserve r(day_week, course, begin, end);
    reserves.append(r);

    cout << "Room " << this->getRoomNumber() << " reserved for " << course
            << " on " << day_week
            << " from " << begin
            << " to " << end << endl << endl;

    return true;
}

void Room::print_reserves()
{
    if(reserves.getSize() > 0){
        cout << "ROOM " << this->getRoomNumber() << ":" << endl << endl;

        string days[5] = {"segunda", "terca", "quarta", "quinta", "sexta"};
        string days_uppercase[5] = {"SEGUNDA", "TERCA", "QUARTA", "QUARTA", "SEXTA"};
        reserves.sort_reserves();
    
        for(int i = 0; i < 5; i++) {
            bool day_has_reserves = false;
            for (int j = 0; j < reserves.getSize(); j++)
            {
                if(reserves.getReserveByIndex(j).getDay() == days[i]) {
                    day_has_reserves = true;
                    break;
                }
            }
            if (day_has_reserves == true) {
                cout << "DIA: " << days_uppercase[i] << endl;
                for(int j = 0; j < reserves.getSize(); j++) {
                    if(reserves.getReserveByIndex(j).getDay() == days[i]) {
                        reserves.getReserveByIndex(j).print();
                    }
                    
                }
                cout << endl;
            }
        }
    }
}

bool Room::remove_reserve(string course_name)
{
for(int i = 0; i < reserves.getSize(); i++)
{
    Reserve r = reserves.getReserveByIndex(i);

    if(r.getCourse() == course_name)
    {
        int day = get_day_index(r.getDay());
        int begin_array = r.getBegin() - 7;
        int end_array = r.getEnd() - 7;

        int* schedule_day = mat[day];

        for(int j = begin_array; j < end_array; j++)
        {
            schedule_day[j] = 0; // libera o horário
        }

        reserves.remove_at(i); // remove do array
        return true;
    }
}
return false;
}

///===============================================================================================================================
//// RESERVATION SYSTEM

ReservationSystem::ReservationSystem(int room_count, int *room_capacities)
{
    this->room_count = room_count;
    this->room_capacities = room_capacities;
    this->rooms = new Room*[room_count];

    for (int i = 0; i < room_count; i++)
    {
        this->rooms[i] = new Room(room_capacities[i], i+1);
    }
}

ReservationSystem::~ReservationSystem()
{
    for(int i = 0; i<room_count; i++) {
        delete this->rooms[i];
    }

    delete[] this->rooms;
}

bool ReservationSystem::reserve(ReservationRequest request)
{   
    for(int i = 0; i<room_count; i++) {
        cout << "Trying to allocate " << request.getCourseName()  <<" class in room " << rooms[i]->getRoomNumber() << endl;
        if(rooms[i]->verify_reserve(request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour(), request.getStudentCount())) 
        {
            cout << "RESERVE FOR ROOM " << i+1 << " COMPLETED!!!" << endl;
            rooms[i]->reserve(request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour());
            
            return true;
        }
    }
    cout << "Request for " << request.getCourseName() << " denied!" << endl << endl;
    return false;
}

bool ReservationSystem::cancel(std::string course_name)
{
    for(int i = 0; i < room_count; i++)
    {
        if(rooms[i]->remove_reserve(course_name))
        {
            cout << "Reserve for " << course_name << " canceled !"<< endl << endl;
            return true;
        }
    }
    return false;
}

void ReservationSystem::printSchedule()
{
    cout << "PRINTING SCHEDULE: " << endl<< endl;
    for (int i = 0; i < room_count; i++)
    {
        rooms[i]->print_reserves();
        cout << endl;
    }
}
