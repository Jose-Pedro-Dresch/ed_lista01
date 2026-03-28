# Room Reservation System - Data Structure - List 01 

## Descrição do Projeto
Este projeto implementa um sistema de reservas de salas de aula para os cinco dias úteis da semana, das 7h às 21h (14 horários de ínicio possíveis para uma reserva).  
O sistema recebe solicitações contendo disciplina, dia da semana, intervalo de horário e número de alunos, e deve atribuir automaticamente **a primeira sala disponível** que tenha capacidade e horários compatíveis.

As funcionalidades incluem:
- Realizar reservas;
- Cancelar reservas existentes;
- Exibir a grade de horários de todas as salas.

A implementação segue as restrições do enunciado:
- **sem estruturas da STL** (vector, list, map, etc);
- manipulação manual de memória (stack e heap) com new/delete.

---

## Instruções de Compilação
Para compilar o projeto, execute no terminal:

```bash
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system
```

Assim, para rodar o executável do programa:

```bash
./reservation_system
```

## Organização Interna dos Dados
As classes do sistema são as seguintes:
- **ReservationRequest**:
    Condensa os dados para uma reserva. É o objeto que o sistema recebe para efetuar uma reserva.
  
- **ReservationSystem**:
    É responsável por receber um objeto de request e efetuar a reserva. Ele gerencia um array de salas.
  
- **Room**:
    Esse objeto possui um array de reservas alocadas e uma matriz de ocupação representando os dias e horários (5 x 14 com zeros representando horários livres e uns representando horários preenchidos).
  
- **Reserve**:
    Representa uma reserva de fato, sendo criada pela sala considerada disponível para um certo request.
  
- **ReservesArray**
    Array dinâmico pertencente a uma sala com a função de alocar objetos de reserva, bem como adicionar e remover esses objetos de si.

Com isso, as relações entre elas são:
- **ReservationRequest** e **ReservationSystem**: Associação, pois elas apenas "se conhecem".
  
- **ReservationSystem** e **Room**: Composição, já que o sistema instancia as salas dentro de si mesmo.

- **Room** e **ReservesArray**: Composição, porque sala instancia um array de reservas em si mesma.
  
- **Room** e **Reserve**: Composição, pelo fato que uma sala instancia uma reserva quando o sistema recebe um request válido.
  
- **ReservesArray** e **Reserve**: Agregação, pois quando ocorre uma reserva, o array de reservas daquela sala aloca mais um elemento e passa a conter ele.
