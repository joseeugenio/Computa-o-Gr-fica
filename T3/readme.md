# T3 -  Pipeline Gráfico

O objetivo do trablaho é implementar transformações geométricas presentes na estrutura do pipeline gráfico. As implementações serão feitas com o auxilio da biblioteca GLM executadas pelo OpenGL Moderno. 

## Bibliotecas utilizadas

Bibliotecas GLM [1] e GLEW [2]. 

## Compilação 

Caso a biblioteca esteja instalada de forma correta, teremos em sua saída ao compilar o arquivo: 

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T3/1.png" />
</p>

## Atividade

No programa template foi necessário alterar os conteúdos das matrizes "MODEL", "VIEW" e "PROJECTION".

#### Matriz Model
````        
float model_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                         0.0f, 1.0f, 0.0f, 0.0f, 
                         0.0f, 0.0f, 1.0f, 0.0f, 
                         0.0f, 0.0f, 0.0f, 1.0f};
                         
glm::mat4 model_mat = glm::make_mat4(model_array);
````
#### Matriz View
````        
float view_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                        0.0f, 1.0f, 0.0f, 0.0f, 
                        0.0f, 0.0f, 1.0f, 0.0f, 
                        0.0f, 0.0f, 0.0f, 1.0f};
                        
glm::mat4 view_mat = glm::make_mat4(view_array);
````
#### Matriz Projection
````        
float proj_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                        0.0f, 1.0f, 0.0f, 0.0f, 
                        0.0f, 0.0f, 1.0f, 0.0f, 
                        0.0f, 0.0f, 0.0f, 1.0f};
                        
glm::mat4 proj_mat = glm::make_mat4(proj_array);
````


## Exercício 1 - Escala
* Modificação da matriz "MODEL" transformando a imagem original gerada.


Fator escala (x, y, z) = ( 3/1 , 3/2 , 1). Matriz modificada será:

````        
float model_array[16] = {0.333f, 0.0f, 0.0f, 0.0f, 
                         0.0f, 1.5f, 0.0f, 0.0f, 
                         0.0f, 0.0f, 1.0f, 0.0f, 
                         0.0f, 0.0f, 0.0f, 1.0f};
                         
glm::mat4 model_mat = glm::make_mat4(model_array);
````

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T3/2.png" />
</p>

```` 
$ in vec3 aPos;
$ in vec3 aColor;
```` 

## Exercício 2 - Translação

* Translação modificando a matriz "MODEL"

Os fatores de Translação (x, y, z) = (1, 0, 0). Para tal a matriz "MODEL" deverá ser modificada para ter a seguinte maneira, de acorodo com os parametros:

````        
    float model_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                             0.0f, 1.0f, 0.0f, 0.0f, 
                             0.0f, 0.0f, 1.0f, 0.0f, 
                             1.0f, 0.0f, 0.0f, 1.0f};
                             
    glm::mat4 model_mat = glm::make_mat4(model_array);
````

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T3/4.png" />
</p>
````
$ vec3 aPos;
````
## Exercício 3 - Projeção Perspectiva 
* Nesse momento, a matriz utilizada será a "PROJECTION". A matriz "PROJECTION", sofrerá uma projeção, considerando a câmera na origem do seu sistema de coordenadas, onde d é a distãncia do centro de projeção até a origem do sistema de coordenadas da câmera:

````
1   0   0   0
0   1   0   0
0   0   1   d
0   0 -1/d  0
````

Como parametro d = 1/2, modificando a matriz "PROJECTION", obtendo:

````        
float proj_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                        0.0f, 1.0f, 0.0f, 0.0f, 
                        0.0f, 0.0f, 1.0f, -2.0f, 
                        0.0f, 0.0f, -0.5f, 1.0f};
                        
glm::mat4 proj_mat = glm::make_mat4(proj_array);

````

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T3/6.png" />
</p>

## Exercício 4 - Posição da Câmera

Devemos modificiar a matriz "VIEW" rotacionando a camera em profundidade. 
Para tal, transformaremos o Espaço do Universo para o da Câmera mudando o sistemas de coordenadas que colocará em cheque os vértices relacionando a câmera, mudando a base da mesma. Logo é necessário definir a posição da câmera através dos vetores: Posição da Câmera, Direção da Câmera e Up Vector. Todos precisam estar no sistema ortogonal e retornar a matriz "Mview", resultante do produto entre a base transposta pela matriz de translação.

Fazendo a implementação:


````        
    glm::vec3 pos_cam = glm::vec3(-0.1f, 0.1f, 0.25f); //vetor posição da camera
    glm::vec3 up_cam = glm::vec3(0.0f, 1.0f, 0.0f);//vetor up da camera
    glm::vec3 ponto_cam = glm::vec3(0.0f, 0.0f, 0.0f);//vetor ponto que a camera esta apontando
    
    
    glm::vec3 z_cam = -glm::normalize(ponto_cam - pos_cam);
    glm::vec3 x_cam = glm::normalize(glm::cross(up_cam, z_cam));
    glm::vec3 y_cam = glm::normalize(glm::cross(z_cam, x_cam));

    float Bt_aux[16]={x_cam[0], y_cam[0], z_cam[0], 0.0f,
                      x_cam[1], y_cam[1], z_cam[1], 0.0f,
                      x_cam[2], y_cam[2], z_cam[2], 0.0f,
                      0.0f,0.0f,0.0f, 1.0f};
                  
    float T_aux[16]={1.0f, 0.0f, 0.0f, 0.0f,   
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                    -pos_cam[0], -pos_cam[1], -pos_cam[2], 1.0f};
                 
    glm::mat4 T = glm::make_mat4(T_aux);
    
    glm::mat4 Bt = glm::make_mat4(Bt_aux);
    
    glm:: mat4 view_mat = Bt * T;
````

Com a modficação da matriz de Projeção no exercicio anterior e com a essa nova matriz VIEW o programa gera a seguinte saída:


<p align="center">
  <img src= "https://github.com/joseeugenio/ICG/blob/master/T3/8.png" />
</p>


## Exercício 5 - Transformações Livres

Modificando as três matrizes, podemos gerar um cenário diferente. Com isso temos:


Matriz Model
````        
float model_array[16] = {2.0f, 0.0f, 0.0f, 0.0f, 
                         0.0f, 1.7f, 0.0f, 0.0f, 
                         0.0f, 0.0f, 1.0f, 0.0f, 
                         0.0f, 0.0f, 0.0f, 1.0f};
glm::mat4 model_mat = glm::make_mat4(model_array);
````

Matriz View
````        
float view_array[16] = {-1.0f, 0.0f, 0.0f, 0.0f, 
                         0.0f, -1.0f, 0.0f, 0.0f, 
                         0.0f, 0.0f, 1.0f, 0.0f, 
                         0.0f, 0.0f, 0.0f, 1.0f};
glm::mat4 view_mat = glm::make_mat4(view_array);
````

Matriz Projection
````        
float proj_array[16] = {1.0f, 0.0f, 0.0f, 0.0f, 
                        0.0f, 1.0f, 0.0f, 0.0f, 
                        0.0f, 0.0f, 1.0f, -2.0f, 
                        0.0f, 0.0f, -0.5f, 1.0f};
glm::mat4 proj_mat = glm::make_mat4(proj_array);
````
Com essas modificações obtemos o seguinte resultado: 

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T3/dif.png" />
</p>

## Referencias e Links

[1] https://glm.g-truc.net/0.9.9/index.html
[2] https://www.youtube.com/watch?v=XlMEK58FaGM
[3] https://www.youtube.com/watch?v=bIK95aWk-Bo
[4] http://www.rhydianedwards.co.uk/2017/08/05/setting-up-sdl-glew-and-glm-in-codeblocks-on-linux/
[5] https://www.youtube.com/watch?v=SqOLkfXDzlY
[6] http://glew.sourceforge.net/
[7] Material Christian Pagot
