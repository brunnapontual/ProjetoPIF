all: rpg

rpg: main.c lib.c screen.c
    gcc -o rpg main.c lib.c screen.c

clean:
    rm -f rpg
