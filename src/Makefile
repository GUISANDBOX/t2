PROJ_NAME=ted
ALUNO=Guilherme Deo Hauy
LIBS=-lm
OBJETOS=main.o ponto.o circulo.o retangulo.o Criasvg.o Lista.o linha.o texto.o comandosgeo.o comandosqry.o poligono.o Mergesort.o

# compilador
CC=gcc

# Flags -fstack-protector-all 
# Ver variáveis:  -Wunused-variable -Wunused-parameter
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration

# Regra principal: gera o executável
$(PROJ_NAME): $(OBJETOS)
	$(CC) $(OBJETOS) -o $(PROJ_NAME) $(LIBS)

# Regra genérica para compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJETOS) $(PROJ_NAME)