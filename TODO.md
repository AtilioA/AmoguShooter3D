# TODO

- [x] A largura da arena, em z, deverá ser 1/2 vezes a altura da arena, em y;
- [ ] Os obstáculos deverão se estender de um lado ao outro da arena, ou seja, ao longo de z;
- [ ] Os personagens deverão ser iniciados em sua coordenada x e y, sendo a coordenada z um valor aleatório que o coloque dentro da arena;
- [ ] O sistema de colisão será parecido com o do trabalho anterior, porém agora representado por um cilindro da altura do jogador e com raio suficiente para conter tronco do jogador;
- [ ] A arena terá um formato de paralelepípedo e o jogador não poderá sair da arena;
- [ ] As teclas a e d servirão respectivamente para girar o jogador no sentido anti-horário e horário quando visto de cima da arena;
- [ ] As teclas a e d servirão respectivamente para mover o jogador para frente e para trás (?);
- [x] Pular utilizando a barra de espaço;
- [ ] A bala deve seguir na direção em que a arma estiver apontando no espaço 3D;
- [ ] O jogo deverá conter pelo menos um modelo de luz na arena (pontual ou direcional);
- [ ] Além disso, o jogo deverá ter um modo noturno (fazer a troca de modos com a tecla “n”) em que todas as luzes da arena são apagadas, sendo ligado somente uma lanterna na arma (braço) do jogador apontando na mesma direção da arma;
- [ ] A tecla '1' (opção padrão) deverá acionar uma câmera perspectiva posicionada no olho do jogador e olhando para frente;
- [ ] A tecla '2' deverá acionar uma câmera na arma do jogador, ou seja, como se fosse uma mira;
- [ ] A tecla '3' deverá acionar uma câmera perspectiva posicionada inicialmente atrás do jogador;
   - [ ] Essa última câmera poderá ser rotacionada (360 graus em torno do jogador e ±60 graus para cima e para baixo do centro do jogador) quando pressionada a tecla x, resultando em um movimento esférico em volta do jogador;
- [ ] Minimapa:
   - [ ] Utilizar uma câmera ortogonal para desenhar um minimapa da arena, descrevendo a sua posição (verde) e a posição dos oponentes (vermelho);

## Pontuação

|Subitens|Pontos|
|---|---|
|Movimentos do oponente|0.1~0.25/0.5|
|Colisões|0.0/0.5|
|Jogo (morrer, ganhar, mensagens)|0.0/1.0|
|Andar|0.0/1.0|
|Pulo|0.1~0.5/1.0|
|Tiro|0.0/1.0|
|Iluminação 1|0.0/0.5|
|Câmera 1|0.1~0.2/1.0|
|Câmera 2|0.0/1.0|
|Câmera 3|0.0~0.1/1.0|
|Minimapa|0.0/1.0|
|Holofote (modo noturno + lanterna)|0.0/0.5|
<!-- |Textura|0.0/1.0| -->
<!-- |Modelos avançados|0.0/1.0| -->

|Total|Pontos|
|---|---|
|Total pessimista|0.3|
|Total otimista|1.05|
