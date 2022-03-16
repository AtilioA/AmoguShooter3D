# TODO

- [x] A largura da arena, em z, deverá ser 1/2 vezes a altura da arena, em y;
- [x] Os obstáculos deverão se estender de um lado ao outro da arena, ou seja, ao longo de z;
- [x] Os personagens deverão ser iniciados em sua coordenada x e y, sendo a coordenada z um valor aleatório que o coloque dentro da arena;
- [x] O sistema de colisão será parecido com o do trabalho anterior, porém agora representado por um cilindro da altura do jogador e com raio suficiente para conter tronco do jogador;
- [x] A arena terá um formato de paralelepípedo e o jogador não poderá sair da arena;
- [x] As teclas a e d servirão respectivamente para girar o jogador no sentido anti-horário e horário quando visto de cima da arena;
- [ ] As teclas a e d servirão respectivamente para mover o jogador para frente e para trás (?);
- [x] Pular utilizando a barra de espaço;
- [x] A bala deve seguir na direção em que a arma estiver apontando no espaço 3D;
- [ ] O jogo deverá conter pelo menos um modelo de luz na arena (pontual ou direcional);
- [ ] Além disso, o jogo deverá ter um modo noturno (fazer a troca de modos com a tecla “n”) em que todas as luzes da arena são apagadas, sendo ligado somente uma lanterna na arma (braço) do jogador apontando na mesma direção da arma;
- [x] A tecla '1' (opção padrão) deverá acionar uma câmera perspectiva posicionada no olho do jogador e olhando para frente;
- [x] A tecla '2' deverá acionar uma câmera na arma do jogador, ou seja, como se fosse uma mira;
- [x] A tecla '3' deverá acionar uma câmera perspectiva posicionada inicialmente atrás do jogador;
   - [x] Essa última câmera poderá ser rotacionada (360 graus em torno do jogador e ±60 graus para cima e para baixo do centro do jogador) quando pressionada a tecla x, resultando em um movimento esférico em volta do jogador;
- [ ] Minimapa:
   - [ ] Utilizar uma câmera ortogonal para desenhar um minimapa da arena, descrevendo a sua posição (verde) e a posição dos oponentes (vermelho);

## Pontuação

|Subitens|Pontos|Falta|
|---|---|---|
|Movimentos do oponente|0.25/0.5|Criar aimbot|
|Colisões|0.25~0.5/0.5|(Cilindro de colisão não será feito)|
|Jogo (morrer, ganhar, mensagens)|1.0~1.0/1.0|
|Andar|0.25~0.5/1.0|Verificar se animações funcionam em 3D|
|Pulo|0.75~1.0/1.0|Realizar mais testes|
|Tiro|0.5~0.75/1.0|Criar braço 3D, realizar mais testes|
|Câmera 1|0.75~1.0/1.0||
|Câmera 2|0.25~0.5/1.0|Paralela ao cano da arma, seria possível ver parte da arma.|
|Câmera 3|0.75~1.0/1.0||
|Minimapa|0.0/1.0|
|Iluminação 1|0.0/0.5|
|Holofote (modo noturno + lanterna)|0.0/0.5|
<!-- |Textura|0.0/1.0| -->
<!-- |Modelos avançados|0.0/1.0| -->

|Total|Pontos|
|---|---|
|Total pessimista|5.00|
|Total otimista|6.00|
