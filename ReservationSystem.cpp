#include <iostream>
#include "ReservationRequest.hpp"
using namespace std;

class Reserve {
    int days;
    int schedule;
    int** mat;

    public:

    int getDays(){
        return this->days;
    }

    int getSchedule(){
        return this->schedule;
    }

    int** getMat(){
        return this->mat;
    }

    Reserve(int days, int schedule){
        this->days = days;
        this->schedule = schedule;

        this->mat = new int*[days];
        for(int i = 0; i<days; i++){
            this->mat[i] = new int[schedule];
            for(int j = 0; j<schedule; j++){
                this->mat[i][j] = 0;
            }
        }
    }

    bool reserve(string day_week,int begin, int end) {
        int day;

        if (day_week == "segunda"){
            day == 0;
        } else if (day_week == "terca") {
            day = 1;
        } else if (day_week == "quarta") {
            day = 2;
        }   else if (day_week == "quinta") {
            day = 3;
        }  else if (day_week == "sexta") {
            day = 4;
        } else {
            cout << "Informe um dia válido " << endl;
        }


        int* schedule_day = mat[day];
        begin = begin - 7;
        end = end - 7;
        for(int i = begin; i< end; i++){
            if(schedule_day[i] == 1){
                cout << "Room not available for this time" << endl;
                return false;
            } 
        } 

        for(int i = begin; i< end; i++){
                schedule_day[i] = 1;
            }
            cout << "Room reserved for " << day_week << " from " << begin+7 << " to " << end+7 << endl;

        return true;
    }

    void printSchedule(){
        string days_week[5] = {"segunda", "terca", "quarta", "quinta", "quinta"};

        for(int i = 0; i<5; i++) {
            int* schedule_day = mat[i];
            for(int j = 0; j<this->schedule; j++){
                
            }
        }
    }



    //~Reserve();    
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities){
        this->room_count = room_count;
        this->room_capacities;
    }

    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

int main(){
    Reserve res(5, 7);

    /*
    for(int i = 0; i<res.getDays(); i++){
        for(int j = 0; j<res.getSchedule(); j++){
            cout<<res.getMat()[i][j];
        }
    }
    */

    res.reserve("segunda", 8, 10);
    res.reserve("segunda", 10, 13);
    res.reserve("terca", 7, 9);
    res.reserve("segunda", 7, 9); 

}