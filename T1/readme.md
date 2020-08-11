

# Atividade 1 - Rasterização de Pontos e Linhas utilizando o opengl

#### José Eugenio - 11506862

#### Relatório: 
* Esta atividade teve como objetivo implementar o algoritmo para rasterização de pontos e linhas. O objetivo principal da atividade é desenhar triangulos utilizando rasterizador de linhas. Para tal, pode-se conseguir solucionar o probelma com preenchimento de suas arestas. Todo o proceso foi feito utilizando as primitivas rasterizadas com oo acesso direto a memória de vídeo.


 # Rasterizador de Pontos 
* Para fazer a rasterizção foi necessário utilizar o framework disponibliziado pelo professor [1]. O framework foi siponiblilizado justamente para facilitar o accesso a memória de vídeo. Nele, foi necessário identificar e implementar a função ("*PutPixel*") para alocação de posicionamento e coloração do pixel, implementada na linguagem C, onde a função recebe como parametro sua posição no espaço (X,Y) e sua cor.

``` 
void PutPixel(int x, int y, int *rgba)
{
    for(int i = 0; i < 4; i++)
    {
        fb_ptr[4*y*IMAGE_WIDTH + 4*x + i] = rgba[i];
    }
}
```
* A função "*Display()*" do framework, através da função "*MyGlDrwan*" com os parametros de posição e cores pré-definidos:
```
void MyGlDrawn(void)
{
  PutPixel(100, 200, color0); //vermelho
  PutPixel(200, 100, color1); //verde
  PutPixel(200, 300, color2); //azul
}
```
* assim teremos em nossa saída 3 pixeis em destaque:

<p align="center">
  <img src=""https://github.com/joseeugenio/ICG/blob/master/T1/pontos%20ok.png"" />
</p>

# Rasterizador de Linha

 * Através da função *"DrawLine"* pode-se desenhar uma linha, usando os pixeis já destacados no passo anterior, como núvcleo da linha. O ajuste das retas deve ser feita nos oito octantes, na qual variam em relação a um "ΔY" e um "ΔX", determinando a inclinação da reta. Ambos podem ser obtidos através da diferença entre pontos finais e pontos inicias (ΔY = y - y0 // ΔX = x - x0), determinando sua localização no octante.

* Decisão baseada na posições de x e y do ponto em relação a cada orientação no plano:

```
if(dx > dy) 
{
  x += pX;
  p += dy;

   if(p >= dx) 
   {
      y += pY;
      p -= dx;
    }
 } else 
 {
     y += pY;
     p += dx;
     
  if(p >= dy) 
  {
      x += pX;
      p -= dy;
   }
}

```

### Interpolação Linear

A função "*DrawLine*" será usada para rasterizar as retas de cores fixas RGBA,  um efeito "degradê" será aplicado utilizando os procedimentos de interpolação linear das cores dos pontos que compõe a reta. Calcula-se a diferença entre os 4 canais de cores (RGBA) do primeiro pixel com a do segundo pixel e dividimos essa variação pelo deslocamento da reta baseada nos pontos (x0, y0) e (x1, y1). Com isso, a cada incremento no comprimento da reta o canal de cores (RGBA) também é incrementado.

Primeiro pixel com uma cor pré-definada 
``` 
    r = color0[0];
    g = color0[1];
    b = color0[2];
    a = color0[3];
```
A diferença entre os 4 canais de cores (RGBA) do primeiro pixel com a do segundo pixel será divididapela variação do deslocamento da reta baseada nos pontos (x0,y0) e (x1,y1).

```
    comparaR = (color1[0] - color0[0]) / distancia_total;
    comparaG = (color1[1] - color0[1]) / distancia_total;
    comparaB = (color1[2] - color0[2]) / distancia_total;
    comparaA = (color1[3] - color0[3]) / distancia_total;
```
A cada incremento no comprimento da reta o canal de cores (RGBA) também é incrementado dentro da condição.
```
   r += comparaR;
   g += comparaG;
   b += comparaB;
   a += comparaA;
```
Passando a função implementada na função "*Display()*" do framework [1], através da função "*MyGlDrwan*" com os parametros pré-definidos como mostrado abaixo:

```
void MyGlDrawn(void)
{
    DrawLine(0, 0, 511, 511, color2, color0);
    DrawLine(511, 0, 0, 511, color2, color1);

    DrawLine(383, 0, 127, 511, color2, color0);
    DrawLine(127, 0, 383, 511, color2, color1);
}
```
saída: 

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T1/rast.png" />
</p>

# Rasterização do Triângulo

* Na função "*DrawTriangle*", a estratégia utilizada para fazer com que uma função  chame a outra função (DrawLine) três vezes, como mostrado no exemplo abaixo:

```
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int *color0, int *color1, int *color2) 
{
    DrawLine(x1, y1, x2, y2, color0, color1);
    DrawLine(x2, y2, x3, y3, color1, color2);
    DrawLine(x3, y3, x1, y1, color2, color0);
}

```
Passando a função implementada na função "*Display()*" do framework, através da função "*MyGlDrwan*" com os parametros pré-definidos como mostrado abaixo:

```
void MyGlDrawn(void)
{  
   DrawTriangle(106, 406, 256, 106, 406, 406, color0, color1, color2);
}

```
saída:

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T1/triang%20ok.png" />
</p>

# Conclusão
Varios problemas inciais foram enfrentados na construção do algoritmo, principalmente em correção de bugs relacionado a instalação do Opengl. Mesmo com as adversidades, o objetivo da atividade foi concluído através de foruns e vídeos disponíveis. A compreensão do algoritmo de bresenham, foi se suma importância para a conclusão da atividade.

# Referencias
[1] https://github.com/capagot/icg/tree/master/mygl_framework
[2] https://letslearnbits.blogspot.com/2014/10/icgt1-interpolacao-de-cores.html
[3] https://pt.qwe.wiki/wiki/Bresenham%27s_line_algorithm
[4] http://icgdadepressao.blogspot.com/2016/03/rasterizacao-triangulos-com-o-algoritmo.html
[5] https://bitunico.wordpress.com/2012/12/16/rasterizacao-em-cc-algoritmo-de-bresenham
[6] Notas de Aula do Professor Christian Azambuja Pagot.
[7] http://letslearnbits.blogspot.com/2014/10/icgt1-algoritmo-de-bresenham.html
