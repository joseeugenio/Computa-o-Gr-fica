# T4 - Implementaçãoo de Modelos de Iluminação

O objetivo deste trabaho consiste em criar modelos de iluminação tradicionamente utilizados na rasterização: ambiente, difuso e especular. Aqui será implementado os três modelos utilizando o vertex shader do OpenGL.  

# Dependências 

O código disponibilizado depende de software de terceiros, como as bibliotecas GLM [1] e GLEW [2].

# Compilação
```` 
 $ g++ -Wall -Wextra -Wpedantic -std=c++17 -O0 -g3 -DDEBUG main.cpp -lglut -lGLEW -lGLU
-lGL -o saida
````
Contudo, basta acessar o repositorio do projeto e executar.

````        
$ make all
````

Quando compilado, caso tudo esteja correto, o programa apresentará a seguinte janela como saída: 

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/xicara1.jpeg" />
</p>

# Atividade

O programa template, em sua configuração original, renderiza o teapot utilizando apenas o modelo
de reflexão ambiente. Esta atividade consiste em se alterar, no programa template, o conteúdo do
vertex shader (arquivo vertex_shader.glsl) de forma a se adicionarem os modelos de reflexão difuso
e especular.

# Exercicio 1

Modificar o vertex shader (arquivo vertex_shader.glsl), de forma que ele passe a incluir, além do
modelo de iluminação ambiente, também o modelo difuso. Para isto, será necessário calcular o novo
valor do vetor normal N, após as transformações feitas pela matriz Model, bem como o vetor L que
aponta do vértice para a fonte de luz. Após a implementação, se tudo estiver correto, o resultado obtido deverá ser igual ao da figura abaixo:

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/questao1.jpeg" />
</p>

Para chegarmos ao resultado esperado, primeiramente criamos o vetor K_d que é o coeficiente de reflectância difusa:
````        
vec3 K_d = vec3(0.0f, 0.0f, 0.8f);
````
com isso devemos agora calcular o novo valor do vetor normal N, bem como o valor do vetor L que aponta do vértice para a fonte de luz: 

````        
vec3 L = normalize(I_p_pos - (model_mat * vec4(obj_spc_vertex_pos, 1.0)).xyz);
   
vec3 N = normalize(mat3(transpose(inverse(model_mat))) * obj_spc_N);
   
````
agora devemos calcular o cos(θ), para formular o modelo de iluminação difuso da seguinte forma: 
          
                                 I = I a κ a + I p κ d cos θ

obtemos o cos(θ) da seguinte forma:
````        
float cos_teta = dot(N, L);
   
````
Com o modelo de iluminação difuso pronto:

````        
I = I_a * k_a + I_p * K_d * cos_teta;
   
````
Obtemos o resultado esperado, ilustrado na figura abaixo: 

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/xicara_exercicio1.jpeg" />
</p>

# Exercicio 2
Modificar o vertex shader (arquivo vertex_shader.glsl) do exercício anterior de forma que ele passe
a incluir, além do modelo de iluminação ambiente e difuso, também o modelo especular, ou de Phong.
Para isto, será necessário calcular o vetor R, de reflexão da luz L, e o vetor da câmera V, que aponta
do vértice em questão para a câmera. Após a implementação, se tudo estiver correto, o resultado obtido deverá ser igual ao da figura abaixo:

<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/exe2.jpeg" />
</p>

Para isto é preciso calcular o vetor R, de reflexão da luz L e o vetor V, que aponta do vértice em questão para a camera, com isso temos:

````        
vec3 R = -reflect(L, N);

vec3 V = normalize(cam_pos - (model_mat * vec4(obj_spc_vertex_pos, 1.0)).xyz);
````

Agora devemos calcular o cos(α), para formular o modelo de iluminação difuso da seguinte forma:

````        
I = I a κ a + I p (κ d cos θ + κ s (cos α)^n )
````

obtemos o cos(α)^n, onde n = 65, da seguinte forma:

````        
    float cos_alfa = dot(R, V);
    float r = cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa.....
````
A função "pow" apresentou erro, não somente neste trabalho como também em trabalhos de colegas de sala de aula, com isso foi calculado a potenciação de forma manual, como mostrado acima. Assim, finalmente, obtivemos o resultado esperado que pode ser visto na imagem abaixo: 
<p align="center">
  <img src="https://github.com/GuilhermeMRodrigues/Computacao_Grafica/blob/master/imagens/respsota2_atv4.jpeg" />
</p>

# Referências e Links
[1] https://glm.g-truc.net/0.9.9/index.html

[2] http://glew.sourceforge.net/

[3] Slides Do Professor Disponibilizados no Sigaa
