SRC:= $(wildcard src/*.c)

INCLUDE_DIR:= -Iinclude

LIBS:= -lglfw3 -lGLU -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

all:
	gcc $(SRC) -o build/executable $(LIBS) $(INCLUDE_DIR)
