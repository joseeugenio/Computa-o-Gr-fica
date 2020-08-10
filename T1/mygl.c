#include "mygl.h"

//
// >>> Defina aqui as funções que você implementar <<< 
//

// Definição da função que chamará as funções implementadas pelo aluno

void PutPixel(int x, int y, int *rgba){
    
    for(int i = 0; i < 4; i++){
        fb_ptr[4*y*IMAGE_WIDTH + 4*x + i] = rgba[i];
    }

}

void DrawLine(int x0, int y0, int x1, int y1, int *color0, int *color1) {

    int dx, dy, x, y, pY, pX, p, caminho;
    float distancia_total, comparaR, comparaG, comparaB, comparaA, r, g, b, a;

    //calcula a distancia entre os pixels final e inicial
    dx = x1 - x0;
    dy = y1 - y0;

    //define as orientações dos quadrantes 
    if(dx < 0){
        pX = -1;    
    }else{
        pX = 1;    
    }
    
    if(dy < 0){
        pY = -1;    
    }else{
        pY = 1;    
    }
    
    dx = abs(dx);
    dy = abs(dy);

    //calcula o numero de interações necessarias baseada nos eixos delta y e delta x
    if(dx > dy){
        caminho = dx;    
    }else{
        caminho = dy;    
    }
    p = caminho/2;

    //calculo do compimento total da reta baseado nos pontos (x0, y0) e (x1, y1) para interpolar as cores 
    distancia_total = sqrt(pow(dx,2) + pow(dy,2));

  
     //cor inicial do primeiro pixel; 
    r = color0[0];
    g = color0[1];
    b = color0[2];
    a = color0[3];


    //compara os valores de RGB para os pontos final e inicial aproximando os numeros de pontos da reta
    comparaR = (color1[0] - color0[0]) / distancia_total;
    comparaG = (color1[1] - color0[1]) / distancia_total;
    comparaB = (color1[2] - color0[2]) / distancia_total;
    comparaA = (color1[3] - color0[3]) / distancia_total;
  


    //Inicialização do ponto atual
    x = x0;
    y = y0;

    //Desenha ponto inicial com a cor incial color0
    PutPixel(x, y, color0);

    while(caminho > 0) {

        //ajuste da reta baseada nos delta x e delta y
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

       //interpolação linear das cores  

        r += comparaR;
        g += comparaG;
        b += comparaB;
        a += comparaA;

        int RGBA[4] = {r, g, b, a};

        //Desenha ponto atual com a cor atualizada do proximo pixel
        PutPixel(x, y, RGBA);

        //Atualização da variável de iteração do laço
        caminho--;
    }

    //Desenha ponto final com cor apropriada
    PutPixel(x, y, color1);
}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
                  int *color0, int *color1, int *color2) {

    DrawLine(x1, y1, x2, y2, color0, color1);
    DrawLine(x2, y2, x3, y3, color1, color2);
    DrawLine(x3, y3, x1, y1, color2, color0);

}


void MyGlDraw(void) {
     
    int color0[4] = {255, 0, 0, 255}; //vermelho
    int color1[4] = {0, 255, 0, 255}; //verde
    int color2[4] = {0, 0, 255, 255}; //azul

    
    //teste linha lilás
    /*for (int i=0; i<250; ++i) {
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 0] = 255;
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 1] = 0;
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 2] = 255;
        fb_ptr[4*i + 4*i*IMAGE_WIDTH + 3] = 255;
    }*/


    //Denhsa 3 pontos vermelho, verde e azul
    /*PutPixel(100, 200, color0);
    PutPixel(200, 100, color1);
    PutPixel(200, 300, color2);*/

    //Desenha * na tela
    /*DrawLine(0, 0, 511, 511, color2, color0);
    DrawLine(511, 0, 0, 511, color2, color1);
    
    DrawLine(256, 127, 256, 383, color2, color1);
    DrawLine(127, 256, 383, 256, color2, color2);
    
    DrawLine(383, 0, 127, 511, color2, color0);
    DrawLine(127, 0, 383, 511, color2, color1);*/


    DrawTriangle(106, 406, 256, 106, 406, 406, color0, color1, color2);


    //
    // >>> Chame aqui as funções que você implementou <<<
    //
}
