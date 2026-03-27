#pragma once
#include <string>

namespace reservationrequest {
// Classe que representa o pedido de reserva
class ReservationRequest
{

private:
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;

public:
    ReservationRequest(std::string course_name, std::string weekday, int start_hour, int end_hour, int student_count);
    ~ReservationRequest();

    int getStartHour();
    int getEndHour();
    std::string getCourseName();
    std::string getWeekday();
    int getStudentCount();
};
}