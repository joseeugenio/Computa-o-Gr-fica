

# T1 - Rasterização de Pontos e Linhas 

#### Alunos: Guilherme Moreira Rodrigues 2016205105 e Lucas Santos Alves 2016015204

#### Relatório sobre o primeiro trabalho da disciplina de introdução à computação gráfica. 
* Nesta atividade foi implementado algoritmos para a rasterização de pontos e linhas. Além de desenhar triangulos atráves da rasterização das linhas para compor suas arestas. Todas as primitivas foram rasterizadas simulando-se o acesso direto a memória de vídeo.


<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/acessomemoria.png" />
</p>


Um framework (https://github.com/capagot/icg/tree/master/mygl_framework) foi fornecido pelo professor Christian Azambuja Pagot, afim de facilitar o acesso à memória de vídeo.

 # Rasterização de Pontos 
* Para fazermos a rasterização de pontos utilizamos o framework, mostrado acima, e implementamos nele a função que posiciona e colore um pixel, chamamos a função de "*PutPixel*". Abaixo podemos ver a função inplementada na linguagem C. 

``` 
void PutPixel(int x, int y, int *rgba){
    
    for(int i = 0; i < 4; i++){
        fb_ptr[4*y*IMAGE_WIDTH + 4*x + i] = rgba[i];
    }

}
```
Passando a função implementada na função "*Display()*" do framework, através da função "*MyGlDrwan*" com os parametros pré-definidos, como mostrado:
```
void MyGlDrawn(void){
  PutPixel(100, 200, color0);
  PutPixel(200, 100, color1);
  PutPixel(200, 300, color2);
}
```
compilando, obtemos a seguinte saída:

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/pontos.png" />
</p>

# Rasterização de Linha

 * A tarefa de desenhar um pixel foi realizada, agora o desafio aplica-se em desenhar uma linha interpolando as cores dos pixels
dela, assim foi criado a função *"DrawLine"* para solução. Porém, faz-se necessário o ajuste das retas para que as elas 
rasterizem nos oito octantes possíveis, na qual variam em relação a um ΔY e um ΔX. Esses deltas que determinam a inclinação 
da reta são obtidos através da diferença entre pontos finais e pontos inicias, determinando em qual octante ela está 
localizada. 

* Podemos ver as restrições ilustradas na imagem abaixo:

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/octantes.png" />
</p>

Segue a lógica da solução baseada na posições de x e y do ponto em relação à referência de orientação.

```
if(dx > dy) {
  x += pX;
  p += dy;

   if(p >= dx) {
      y += pY;
      p -= dx;
    }
 } else {
     y += pY;
     p += dx;
     
  if(p >= dy) {
      x += pX;
      p -= dy;
   }
}

```

### Interpolação Linear

Com a função "*DrawLine*" rasterizando retas com cores fixas RGBA, fizemos a interpolação linear das cores dos pontos que compõe a reta afim de aplicar um efeito *degradê*. Calcula-se a diferença entre os 4 canais de cores (RGBA) do primeiro pixel com a do segundo pixel e dividimos essa variação pelo deslocamento da reta baseada nos pontos (x0, y0) e (x1, y1). Com isso, a cada incremento no comprimento da reta o canal de cores (RGBA) também é incrementado.

Inciamos o primeiro pixel com uma cor pré-definada 
``` 
    r = color0[0];
    g = color0[1];
    b = color0[2];
    a = color0[3];
```
Calcula a diferença entre os 4 canais de cores (RGBA) do primeiro pixel com a do segundo pixel e dividimos essa variação pelo deslocamento da reta baseada nos pontos (x0, y0) e (x1, y1).

```
//compara os valores de RGB para os pontos final e inicial aproximando os numeros de pontos da reta
    comparaR = (color1[0] - color0[0]) / distancia_total;
    comparaG = (color1[1] - color0[1]) / distancia_total;
    comparaB = (color1[2] - color0[2]) / distancia_total;
    comparaA = (color1[3] - color0[3]) / distancia_total;
```
Com isso, a cada incremento no comprimento da reta o canal de cores (RGBA) também é incrementado dentro do while.
```
   r += comparaR;
   g += comparaG;
   b += comparaB;
   a += comparaA;
```
Passando a função implementada na função "*Display()*" do framework, através da função "*MyGlDrwan*" com os parametros pré-definidos como mostrado abaixo:

```
void MyGlDrawn(void){
  
    DrawLine(0, 0, 511, 511, color2, color0);
    DrawLine(511, 0, 0, 511, color2, color1);

    DrawLine(383, 0, 127, 511, color2, color0);
    DrawLine(127, 0, 383, 511, color2, color1);

}
```
Obtemos a seguinte saída: 

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/saida8octantes.png" />
</p>

# Rasterização do Triângulo

* Na função DrawTriangle usamos a estratégia de fazer apenas uma função que faz chamada de outra função (DrawLine) três vezes, como mostrado no exemplo abaixo:

```
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int *color0, int *color1, int *color2) {

    DrawLine(x1, y1, x2, y2, color0, color1);
    DrawLine(x2, y2, x3, y3, color1, color2);
    DrawLine(x3, y3, x1, y1, color2, color0);

}

```
Passando a função implementada na função "*Display()*" do framework, através da função "*MyGlDrwan*" com os parametros pré-definidos como mostrado abaixo:

```
void MyGlDrawn(void){
  
   DrawTriangle(106, 406, 256, 106, 406, 406, color0, color1, color2);

}

```
Obtemos a seguinte saída:

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/triangulo.png" />
</p>

# Conclusão
Por fim, após varios problemas enfrentados na construção do algoritmo, conseguimos soluciona-los com uma boa base teorica sobre os problemas propostos pelo professor e o entendimento do pseudocodigo do algoritmo de bresenham, com isso a tarefa foi finalizada com sucesso.  

# Referencias
[1]https://pt.qwe.wiki/wiki/Bresenham%27s_line_algorithm

[2]https://letslearnbits.blogspot.com/2014/10/icgt1-interpolacao-de-cores.html

[3]http://letslearnbits.blogspot.com/2014/10/icgt1-algoritmo-de-bresenham.html

[4]https://bitunico.wordpress.com/2012/12/16/rasterizacao-em-cc-algoritmo-de-bresenham

[5] Notas de Aula do Professor Christian Azambuja Pagot.
