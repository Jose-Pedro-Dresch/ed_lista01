#include <iostream>
#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"
using namespace std;

///===============================================================================================================================
///===============================================================================================================================
//// RESERVE

Reserve::Reserve()
// Construtor sem parâmetros de Reserve
// usado para alocar espaços de memória para reservas no array dinâmico de reservas)
{
    week_day = "";
    course = "";
    begin = 0;
    end = 0;
}

Reserve::Reserve(string week_day, string course, int begin, int end)
// Construtor de reserve
{
    this->week_day = week_day;
    this->course = course;
    this->begin = begin;
    this->end = end;
}

void Reserve::print()

{ // printa o horário e curso da reserva (ex: 9h~11h: Estrutura de Dados)
    cout << begin << "h~" << end << "h: " << course << endl;
}

// Getters
string Reserve::getCourse() { return course; }
string Reserve::getDay() { return week_day; }
int Reserve::getBegin() { return begin; }
int Reserve::getEnd() { return end; }

///===============================================================================================================================
///===============================================================================================================================
//// ARRAY RESERVAS

ReservesArray::ReservesArray()
// Construtor do array dinâmico de Reservas
{
    this->capacity = 10;
    this->size = 0;
    this->data = new Reserve[capacity];
}

ReservesArray::~ReservesArray()
// Elimina a lista de reservas
{
    delete[] this->data;
}

void ReservesArray::append(Reserve r)
{
    // Se já estourou a capacidade máxima de reservas cria uma nova lista com o dobro da capacidade;
    if (this->capacity == this->size)
    {
        resize(2 * this->capacity);
    }
    this->data[this->size] = r;
    this->size++;
}

void ReservesArray::resize(int new_capacity)
// Redimensiona a lista de reservas para quando estourar a capacidade do array
{
    // Cria a nova lista com a nova capacidade
    Reserve *novo_dados = new Reserve[new_capacity];
    for (int i = 0; i < this->size; i++)
    {
        // Associa os dados já existentes à nova lista
        novo_dados[i] = this->data[i];
    }
    // Remove a lista antiga, pega a nova e seta a nova capacidade
    delete[] this->data;
    this->data = novo_dados;
    this->capacity = new_capacity;
}

int ReservesArray::get_day_index(string day_week)
{
    // Associa cada string de dia a um valor (para futura comparação de ordem)
    if (day_week == "segunda")
        return 0;
    if (day_week == "terca")
        return 1;
    if (day_week == "quarta")
        return 2;
    if (day_week == "quinta")
        return 3;
    if (day_week == "sexta")
        return 4;
    return -1;
}

// Bubble sort para ordenar as reservas
void ReservesArray::sort_reserves()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {

            // Pega os valores numéricos associados a cada dia para fazer a comparação
            int day1 = get_day_index(data[j].getDay());
            int day2 = get_day_index(data[j + 1].getDay());

            if (day1 > day2)
            {
                // Troca os elementos (ex: "segunda" < "terça" <=> (0<1))
                Reserve temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
            else if (day1 == day2)
            {
                // Se os dois adjascentes já estão no mesmo dia,
                // ordenamos pelo horário de início
                if (data[j].getBegin() > data[j + 1].getBegin())
                {
                    Reserve temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}

// Remove um elemento do array de reservas a partir do índice dado
void ReservesArray::remove_at(int index)
{
    // Validação do index
    if (index < 0 || index >= size)
    {
        return;
    }

    // Coloca à esquerda todos os elementos à frente do que retiramos
    for (int i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }

    size--;
}

Reserve ReservesArray::getReserveByIndex(int i)
// Retorna a reserva pelo índice dela na lista
{
    return data[i];
}

int ReservesArray::getSize()
{
    return size;
}

///===============================================================================================================================
///===============================================================================================================================
//// ROOM

// Getters
int Room::getCapacity() { return this->capacity; }
int Room::getDays() { return this->days; }
int Room::getSchedule() { return this->schedule; }
int **Room::getMat() { return this->mat; }
ReservesArray &Room::get_reservas() { return reserves; }
int Room::getRoomNumber() { return this->room_number; }

Room::Room(int capacity, int room_number)
// Construtor da Room, recebe capacity e room_number
// days é 5 nesse projeto (segunda à sexta)
// schedule é 14 nesse projeto - horários de 7h às 20h (consideramos o horário de início apenas)
// Preenchemos a mat (matriz de horários) com 0
{
    this->capacity = capacity;
    this->days = 5;
    this->schedule = 14;

    this->mat = new int *[days];
    for (int i = 0; i < days; i++)
    {
        // 0 no índice mat[i][j] significa que o dia i e horário das j até ás j+1 está disponível (1 caso contrário)
        // Exemplo: mat[2][4] significa que o horário das 11h (4+7) da quarta (dia 2) está reservado
        // Lembrando que +7 ocorre porque a aula inicia às 7h
        this->mat[i] = new int[schedule]{0};
    }
    this->room_number = room_number;
}

Room::~Room()
{
    for (int i = 0; i < days; i++)
    {
        // Destruímos os dados de cada dia
        delete[] mat[i];
    }
    // Destruímos a matriz
    delete[] mat;
}

int Room::get_day_index(string day_week)
// Associa cada string de dia a um valor (correspondente na matriz de horários)
{
    if (day_week == "segunda")
        return 0;
    if (day_week == "terca")
        return 1;
    if (day_week == "quarta")
        return 2;
    if (day_week == "quinta")
        return 3;
    if (day_week == "sexta")
        return 4;
    return -1;
}

bool Room::verify_reserve(string course, string day_week, int begin, int end, int student_count)
{
    // Verifica se comporta a quantidade de alunos
    if (this->capacity < student_count)
    {
        // Optou-se por deixar comentada essa linha para não poluir muito o terminal
        // cout << "Room " << this->getRoomNumber() << " não comporta essa quantidade de alunos!" << endl;
        return false;
    }
    else
    { // pegamos o índice correspondente à cada dia
        int day = get_day_index(day_week);

        if (day == -1)
        {
            cout << "Informe um dia válido" << endl;
            return false;
        }

        int *schedule_day = mat[day]; // Pegamos a grade de horários somente do dia em questão
        int begin_array = begin - 7;  // Diminuímos 7 porque a aula começa às 7h e o índice do array começa em 0
        int end_array = end - 7;      // Diminuímos 7 porque a aula começa às 7h e o índice do array começa em 0

        for (int i = begin_array; i < end_array; i++)
        {
            // Se algum horário estiver reservada nesse horário não efetua-se a reserva
            if (schedule_day[i] == 1)
            {
                // Optou-se por deixar comentada essa linha para não poluir muito o terminal
                // cout << "Room " << this->getRoomNumber() << " indisponível para esse horário" << endl;
                return false;
            }
        }
        return true; // Se tiver capacidade e estiver disponível
    }
}

bool Room::reserve(string course, string day_week, int begin, int end)
{
    // Pega o índice correspondente do dia
    int day = get_day_index(day_week);
    if (day == -1)
    {
        cout << "Informe um dia válido" << endl;
        return false;
    }

    int *schedule_day = mat[day]; // Pegamos a grade de horários somente do dia em questão
    int begin_array = begin - 7;  // Diminuímos 7 porque a aula começa às 7h e o índice do array começa em 0
    int end_array = end - 7;      // Diminuímos 7 porque a aula começa às 7h e o índice do array começa em 0

    for (int i = begin_array; i < end_array; i++)
    {
        // Marca os horários do intervalo como preenchidos
        schedule_day[i] = 1;
    }

    // Cria um objeto de reserva e guarda no array de reservas
    Reserve r(day_week, course, begin, end);
    reserves.append(r);

    return true;
}

void Room::print_reserves()
// Uma sala printa os horários resevados de cada dia
{
    // Só printa se tiver alguma reserva marcada
    if (reserves.getSize() > 0)
    {
        cout << "ROOM " << this->getRoomNumber() << ":" << endl
             << endl;

        string days[5] = {"segunda", "terca", "quarta", "quinta", "sexta"};
        string days_uppercase[5] = {"SEGUNDA", "TERCA", "QUARTA", "QUINTA", "SEXTA"};

        // Ordena os horários por dia e hora de início da aula
        reserves.sort_reserves();

        // For para cad dia da semana
        for (int i = 0; i < 5; i++)
        {
            // Primeiro verifica se no dia em questão tem alguma aula marcada
            // Se não tiver não printa nada sobre esse dia
            bool day_has_reserves = false;
            for (int j = 0; j < reserves.getSize(); j++)
            {
                if (reserves.getReserveByIndex(j).getDay() == days[i])
                {
                    day_has_reserves = true;
                    break;
                }
            }

            // Se houver alguma reserva para o dia em questão, printa todas as reservas desse dia
            if (day_has_reserves == true)
            {
                cout << "DIA: " << days_uppercase[i] << endl;
                for (int j = 0; j < reserves.getSize(); j++)
                {
                    if (reserves.getReserveByIndex(j).getDay() == days[i])
                    {
                        // Chama o print de cada reserva desse dia (que mostra horáios e nome da aula)
                        reserves.getReserveByIndex(j).print();
                    }
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}

// Remove uma reserva dado o nome da disciplina
bool Room::remove_reserve(string course_name)
{
    // Percorre o array de reservas
    for (int i = 0; i < reserves.getSize(); i++)
    {
        // Verifica qual é a reserva correta a ser removida
        Reserve r = reserves.getReserveByIndex(i);

        if (r.getCourse() == course_name)
        {
            // Atualiza a matriz de ocupação
            int day = get_day_index(r.getDay());
            int begin_array = r.getBegin() - 7;
            int end_array = r.getEnd() - 7;

            int *schedule_day = mat[day];

            for (int j = begin_array; j < end_array; j++)
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
///===============================================================================================================================
//// RESERVATION SYSTEM

ReservationSystem::ReservationSystem(int room_count, int *room_capacities)
// Construtor da ReservationSystem recebe número de salas e suas capacidades
{
    this->room_count = room_count;
    this->room_capacities = room_capacities;
    this->rooms = new Room *[room_count];

    for (int i = 0; i < room_count; i++)
    {
        // Armazena uma lista de Rooms com as capacidades que forem passadas no construtor
        // Cria também cada sala com seu número (1, 2, 3, ...)
        this->rooms[i] = new Room(room_capacities[i], i + 1);
    }
}

ReservationSystem::~ReservationSystem()
{
    // Remove o Room em cada índice da lista de Rooms
    for (int i = 0; i < room_count; i++)
    {
        delete this->rooms[i];
    }

    // Remove a lista em si
    delete[] this->rooms;
}

bool ReservationSystem::reserve(ReservationRequest request)
{
     // Verificação de horários de início e fim de uma aula
    if (request.getStartHour() < 7 || request.getEndHour() > 21 || request.getStartHour() >= request.getEndHour()) 
    {
        cout << "Horário inválido de solicitação para aula de "<< request.getCourseName() << " - o período de aulas é 7h~21h!!!" << endl << endl;
        return false;
    }


    // Percorre cada sala na lista de salas até encontrar uma que pode ser alocada (se houver)
    for (int i = 0; i < room_count; i++)
    {
        cout << "Tentando alocar a aula de " << request.getCourseName() << " na sala " << rooms[i]->getRoomNumber() << endl;
        if (rooms[i]->verify_reserve(request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour(), request.getStudentCount()))
        // Se pode a sala permite reserva, ela é efetivada:
        {
            cout << "Reserva da aula de " << request.getCourseName() << " ("
                 << request.getWeekday() << " - " << request.getStartHour() << "h~" << request.getEndHour() << "h) "
                                                                                                               "efetuada na sala "
                 << rooms[i]->getRoomNumber() << "!!!" << endl
                 << endl;

            // Efetua a reserva
            rooms[i]->reserve(request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour());

            return true;
        }
    }
    // Se nenhuma sala puder ser alocada, retorna false
    cout << "Requisição para a aula de " << request.getCourseName() << " não pôde ser efetuada!!!" << endl
         << endl;
    return false;
}

// Método do sistema para cancelar uma reserva a partir do nome da disciplina
bool ReservationSystem::cancel(std::string course_name)
{
    // Percorre cada sala em busca da reserva a cancelar
    for (int i = 0; i < room_count; i++)
    {
        // Se encontrou, cancela
        if (rooms[i]->remove_reserve(course_name))
        {
            cout << "Reserva para a aula de " << course_name << " cancelada na sala " << rooms[i]->getRoomNumber() << "!!!"<< endl
                 << endl;
            return true;
        }
    }
    // Se não, retorna falso
    return false;
}

void ReservationSystem::printSchedule()
{
    cout << "PRINTANDO HORÁRIOS DA SEMANA: " << endl
         << endl;
    for (int i = 0; i < room_count; i++)
    {
        // Chama o print da grade horária de cada sala (cada sala sabe se printar)
        rooms[i]->print_reserves();
    }
}
