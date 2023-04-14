Sistema Solar
======

Trabalho realizado durante a disciplina de Computação Gráfica do CEFET-MG. Escrito em linguagem `C++` utilizando bibliotecas como: `freeGLUT`, `SOIL`, `SDL_mixer` e `OpenGL`.



Compilação do programa:
------
1 - Compilação sem MakeFile 
```
    g++ sistema.cpp -lGL -lglut -lGLEW -lGLU -lSOIL -lm -lSDL -lSDL_mixer
    ./a.out
```

2 - Compilação com MakeFile
```
    g++ sistema.cpp -o sistema -lGL -lglut -lGLEW -lGLU -lSOIL -lm -lSDL -lSDL_mixer
    make
```


Lista de itens presentes no jogo
------

1- Mundo - '9' planetas e Sol criados a partir de texturas e sólidos esféricos

2- Câmera - '3' : Estática (3), Móvel Lateral (Default) e Móvel Superior (2)

3- Gráficos - a luz emana do Sol ao apertar a tecla 'l' ou 'L' 
    3.1- Se apertar a tecla 'o' ou 'O' o sol sai e a luz se perde

4- Skybox 

5- Anéis planetários - Saturno e Urano

6- Reshape 

7- Orbitas visíveis - apertar tecla 'v'

8- Música
    8.1- Pausa com a tecla 'p'

9- Atmosfera Terrestre 

10- Fidedignidade - apertando a tecla 'T'

11- Escrita na tela em ambas as cameras

Involvidos
------
- Docente: Glender Brás

- Discentes: Diego Simoẽs Maria, Ítalo Gustavo Donato Cordeiro e Marina Bernardes Diniz
