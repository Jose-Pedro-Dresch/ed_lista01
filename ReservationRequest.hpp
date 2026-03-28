#pragma once
#include <string>

/**
 * Representa uma requisição de reserva em uma sala de aula
 * Armazena o nome da disciplina, o dia, horários de início e fim e a quantidade de alunos
 */
class ReservationRequest {

private:
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;

public:
    /**
     * Representa o construtor para uma requisição de reserva
     */
    ReservationRequest(std::string course_name, std::string weekday, int start_hour, int end_hour, int student_count);

    /**
     * Representa o destrutor para uma requisição de resreva
     */
    ~ReservationRequest();

    // Getters
    int getStartHour();
    int getEndHour();
    std::string getCourseName();
    std::string getWeekday();
    int getStudentCount();
};