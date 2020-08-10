#ifndef MYGL_H
#define MYGL_H

#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>
#include  "core.h"
#include  "frame_buffer.h"
#include  "math.h"

void MyGlDraw(void);

// Declaração da função que chamará as funções implementadas pelo aluno

void PutPixel(int x, int y, int rgba[]);

void DrawLine(int x0, int y0, int x1, int y1, int rgbaP0[], int rgbaP1[]);

//int * InterpolColor(int *color0, int *color1, float distancia);

//
// >>> Declare aqui as funções que você implementar <<<
//

#endif  // MYGL_H
