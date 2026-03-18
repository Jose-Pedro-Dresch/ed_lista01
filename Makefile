# Nome do executável que é gerado na raiz
TARGET = reservation_system

# O compilador usado
CXX = g++

# Flags (opções) de compilação: -Wall mostra todos os avisos de erro
CXXFLAGS = -Wall

# Todos os arquivos .cpp são compilados juntos
SRCS = tests/main.cpp src/ReservationRequest.cpp src/ReservationSystem.cpp

# Ao digitar 'make', gera o executável
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# 'make clean' apaga o executável
clean:
	rm -f $(TARGET)