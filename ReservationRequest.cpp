#include <iostream>
using namespace std;

class ReservationRequest {

private:
    string course_name;
    string weekday;
    int start_hour;
    int end_hour;
    int student_count;

public:

    ReservationRequest(string course_name, string weekday, int start_hour, int end_hour, int student_count){
        this->course_name = course_name;
        this->weekday = weekday;
        this->start_hour = start_hour;
        this->end_hour = end_hour;
        this->student_count = student_count;
    }
    
    ~ReservationRequest();

    int getStartHour() {
        return this->start_hour;
    }

    int getEndHour(){
        return this->end_hour;
    }

    string getCourseName(){
        return this->course_name;
    }

    string getWeekday(){
        return this->weekday;
    }

    int getStudentCount(){
        return this->student_count;
    }
};