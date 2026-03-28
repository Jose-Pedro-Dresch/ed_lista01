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

    int get_day_index(string day_week)
    {
        if (day_week == "segunda") return 0;
        if (day_week == "terca") return 1;
        if (day_week == "quarta") return 2;
        if (day_week == "quinta") return 3;
        if (day_week == "sexta") return 4;
        return 5;
    }

    // bubble sort
    void sort_reserves(){
        for (int i = 0; i < tamanho; i++) {
            for (int j = 0; j < tamanho-i-1; j++) {
                int day1 = get_day_index(dados[j].getDay());
                int day2 = get_day_index(dados[j+1].getDay());

                if (day1 > day2) {
                    // Troca os elementos
                    Reserve temp = dados[j];
                    dados[j] = dados[j+1];
                    dados[j+1] = temp;
                 } else if (day1 == day2) {
                    if(dados[j].getBegin() > dados[j+1].getBegin()){
                        Reserve temp = dados[j];
                        dados[j] = dados[j+1];
                        dados[j+1] = temp;
                    }
                 }
            }
        }
    }

    void remove_at(int index)
    {
    if(index < 0 || index >= tamanho)
    {
        return;
    }

    for(int i = index; i < tamanho - 1; i++)
    {
        dados[i] = dados[i+1];
    }

    tamanho--;
    }
    
    bool remove_by_course(string course_name)
    {
    for(int i = 0; i < tamanho; i++)
    {
        if(dados[i].getCourse() == course_name)
        {
            remove_at(i);
            return true;
        }
    }
    return false;
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
    int room_number;

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

    int getRoomNumber() 
    {
        return this->room_number;    
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
        room_number = 0;
    }

    Room(int capacity, int room_number)
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

    ~Room()
    {
    for (int i = 0; i < days; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
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


    bool verify_reserve(string course, string day_week, int begin, int end, int student_count) 
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

    bool reserve(string course, string day_week, int begin, int end)
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

        Reserve reser(day_week, course, begin, end);
        reservas.append(reser);

        cout << "Room " << this->getRoomNumber() << " reserved for " << course
                << " on " << day_week
                << " from " << begin
                << " to " << end << endl << endl;

        return true;
    }

    void setCapacity(int capacity) {
        this->capacity = capacity;
    }

    void setNumber(int number) {
        this->room_number = number; 
    }

    

    void print_reserves()
    {
        if(reservas.size() > 0){
            cout << "ROOM " << this->getRoomNumber() << ":" << endl << endl;

            string days[5] = {"segunda", "terca", "quarta", "quinta", "sexta"};
            string days_uppercase[5] = {"SEGUNDA", "TERCA", "QUARTA", "QUARTA", "SEXTA"};
            reservas.sort_reserves();
        
            for(int i = 0; i < 5; i++) {
                bool day_has_reserves = false;
                for (int j = 0; j < reservas.size(); j++)
                {
                    if(reservas.get(j).getDay() == days[i]) {
                        day_has_reserves = true;
                        break;
                    }
                }
                if (day_has_reserves == true) {
                    cout << "DIA: " << days_uppercase[i] << endl;
                    for(int j = 0; j < reservas.size(); j++) {
                        if(reservas.get(j).getDay() == days[i]) {
                            reservas.get(j).print();
                        }
                        
                    }
                    cout << endl;
                }
            }
        }
    }

    ArrayReservas& get_reservas()
    {
        return reservas;
    }

    bool remove_reserve(string course_name)
    {
    for(int i = 0; i < reservas.size(); i++)
    {
        Reserve r = reservas.get(i);

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

            reservas.remove_at(i); // remove do array
            return true;
        }
    }
    return false;
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
        rooms[i].setCapacity(room_capacities[i]);
        rooms[i].setNumber(i+1);
    }
}

ReservationSystem::~ReservationSystem()
{
    delete[] this->rooms;
}

bool ReservationSystem::reserve(ReservationRequest request)
{   
    for(int i = 0; i<room_count; i++) {
        cout << "TRYING TO ALLOCATE " << request.getCourseName()  <<" CLASS IN ROOM " << rooms[i].getRoomNumber() << endl;
        if(rooms[i].verify_reserve(request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour(), request.getStudentCount())) 
        {
            cout << "RESERVE FOR ROOM " << i+1 << ": " << endl;
            rooms[i].reserve(request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour());
            
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
        if(rooms[i].remove_reserve(course_name))
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
        rooms[i].print_reserves();
        cout << endl;
    }
}

int main()
{
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

    return 0;
}