#pragma once
#include "ReservationRequest.hpp"
#include <string>

///===============================================================================================================================
//// RESERVE

/**
 * Representa uma reserva de aula do sistema
 * Armazena o dia, horários de início e fim e o nome da disciplina
 */
class Reserve
{
    std::string week_day;
    std::string course;
    int begin;
    int end;

public:
    /**
     * Representa o construtor sem parâmetros de uma reserva (usado na hora de alocar memória no array dinâmico)
     */

     /**
     * Representa o destrutor de uma reserva 
     */
    Reserve();

    /**
     * Representa o construtor parametrizado
     */
    Reserve(std::string week_day, std::string course, int begin, int end);

    /**
     * Exibe os dados da reserva (horários de início, fim e o nome da disciplina)
     */
    void print();

    std::string getCourse();
    std::string getDay();
    int getBegin();
    int getEnd();
};

///===============================================================================================================================
//// RESERVES ARRAYS

/**
 * Representa um array dinâmico que armazena reservas
 * Possui capacidade, tamanho e uma lista propriamente dita de reservas
 * Quando estoura o limite de capacidade, dobra-se a capacidade
 */ 
class ReservesArray
{
protected:
    int capacity;
    int size;
    Reserve *data;

public:
    /**
     * Representa o construtor de um array dinâmico de reservas (sempre inciado com capacidade 10)
     */
    ReservesArray();

    /**
     * Representa o destrutor de um array dinâmico de reservas
     */
    ~ReservesArray();

    /**
     * Função que acrescenta uma nova reserva ao array
     */
    void append(Reserve r);

    /**
     * Função que muda a capacidade do array (usada quando estoura a capacidade)
     */
    void resize(int new_capacity);

    /**
     * Função que associa a cada dia da semana um valor para futuro ordenamento
     */
    int get_day_index(std::string day_week);

    /**
     * Função que ordena o array de reservas por dia da semana e horários das aulas 
     * Usa o algoritmo do Bubble sort
     */
    void sort_reserves();
    
    void remove_at(int index);
    bool remove_by_course(std::string course_name);

    /**
     * Função para acessar a reserva no índice i do array
     */
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

    /**
     * Representa o construtor padrão de uma sala
     * Recebe apenas a capacidade e o número da sala
     * Nesse projeto days é fixo (5, de segunda a sexta)
     * E schedule é fixo (14, pois há 20-7+1=14 horas disponíveis de cada sala de aula, das 7h às 21h)
     */
    Room(int capacity, int room_number);

    /**
     * Representa o destrutor de uma sala
     */
    ~Room(); 

    /**
     * Função que associa a cada dia da semana um valor para acessa-lo na matriz de horários mat
     * No íncide 0 há segunda, no íncide 1 terça e assim por diante
     */
    int get_day_index(std::string day_week);

    /**
     * Função que verifica se uma sala pode ser alocadada dada uma solitiação de reserva,
     * considerando capacidade e disponibilidade de horários
     * Retorna true se for possível e false caso contrário
     */
    bool verify_reserve(std::string course, std::string day_week, int begin, int end, int student_count);

    /**
     * Função que efetua uma reserva de sala se possível
     * Cria um objeto de reserva e armazena-o em seu array de reservas
     * Retorna true se possível e false caso contrário
     */
    bool reserve(std::string course, std::string day_week, int begin, int end);

    /**
     * Função que exibe todas as reservas (se houver) da semana
     * para a sala em questão
     */
    void print_reserves();

    bool remove_reserve(std::string course_name);

};

///===============================================================================================================================
//// RESERVATION SYSTEM



/**
 * Representa o sistema de reserva
 * Ele recebe a quantidade de salas e suas capaciades,
 * armazena os objetos de sala em uma lista (ponteiros para esses objetos),
 * recebe uma requisição de reserva e percorre cada uma de suas salas até encontrar (ou não)
 * alguma que permita a alocação. 
 * Também pode cancelar uma reserva para uma determinada disciplina
 * e exibir todas as reservas de todas as salas na semana
 */
class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    Room** rooms;

public:
    /**
     * Representa o construtor padrão de um sistema de reserva
     * Recebe a quantidade de salas e suas capacidades,
     * cria e armazena os objetos de salas correspondentes
     */
    ReservationSystem(int room_count, int* room_capacities);

    /**
     * Representa o destrutor de um sistema de reserva
     */
    ~ReservationSystem();

    /**
     * Função que recebe uma requisição de reserva e percorre cada uma de suas salas, 
     * efetuando (se possível) a reserva na primeira disponível
     * Retorna true se possível e false caso contrário
     */
    bool reserve(ReservationRequest request);

    bool cancel(std::string course_name);

    /**
     * Função que exibe todas as reservas de todas as salas na semana
     * Percorre a lista de salas e chama o método de exibir que cada sala possuí
     * Cada sala sabe printar suas reservas, ele apenas chama a exibição de reservas
     * de cada uma de suas salas
     */
    void printSchedule();
};