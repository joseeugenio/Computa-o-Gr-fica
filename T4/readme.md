# T4 - Implementação dos Modelos de Iluminação

* Implementação e criação de três modelos de iluminação utilizados na rasterização como ambiente, difuso e especular, utilizando o vertex shader do OpenGL.  

# Dependências 

* Bibliotecas GLM [1] e GLEW [2].

Com a instalação das bibliotecas de forma correta, o resultado da compilação será: 
<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T4/ex.jpeg" />
</p>

# Atividade

O software em sua configuração original, renderiza o a imagem do bule utilizando apenas o modelo de reflexão ambiente. Nosso exercicio consistirá em alterar o conteúdo do vertex shader (arquivo vertex_shader.glsl), adcionando os modelos de reflexão difuso e especular.

# Exercicio 1

MO "Vertex Shader" deverá ser modificado para que ele passe a incluir, além do modelo de iluminação ambiente, também o modelo difuso. Para tal é necessário calcular o  valor atualizado do vetor normal N. Depois das transformações feitas pela matriz "Model", bem como o vetor L que direciona para vértice da fonte de iluminação. 

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T4/1.jpeg" />
</p>

* O vetor K_d é o coeficiente de reflectância difusa:
````        
vec3 K_d = vec3(0.0f, 0.0f, 0.8f);
````
* Com isso é possível calcular o novo valor do vetor normal N e o valor do vetor L: 

````        
vec3 L = normalize(I_p_pos - (model_mat * vec4(obj_spc_vertex_pos, 1.0)).xyz);
   
vec3 N = normalize(mat3(transpose(inverse(model_mat))) * obj_spc_N);
   
````
* calculando o cos(θ),o agente formulador do modelo de iluminação difuso:
          
                                 I = I a κ a + I p κ d cos θ

cos(θ):
````        
float cos_teta = dot(N, L);
   
````
Modelo de Iluminação Difuso:

````        
I = I_a * k_a + I_p * K_d * cos_teta;
   
````
Gerando: 

<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T4/22.jpeg" />
</p>

# Exercicio 2
Modificar o "Vertex Shader", do exercício anterior, incluindo o modelo especular, ou de "Phong". Será preciso fazer os seguintes calculos: vetor R,  reflexão da luz L, e o vetor da câmera V. 

Calculando o vetor R, de reflexão da luz L e o vetor V, obtemos:

````        
vec3 R = -reflect(L, N);

vec3 V = normalize(cam_pos - (model_mat * vec4(obj_spc_vertex_pos, 1.0)).xyz);
````

Calculando o cos(α), com o intuito de formar o modelo de iluminação difuso:

````        
I = I a κ a + I p (κ d cos θ + κ s (cos α)^n )
````

cos(α)^n, com n = 65:

````        
    float cos_alfa = dot(R, V);
    float r = cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa*cos_alfa.....
````
A potenciação foi calculada de forma manual, porque a função "pow" apresentou erros. Sendo assim tivemos o seguinte resultado:
<p align="center">
  <img src="https://github.com/joseeugenio/ICG/blob/master/T4/44.jpeg" />
</p>

# Referências e Links
[1] https://glm.g-truc.net/0.9.9/index.html
[2] http://glew.sourceforge.net/
[3] http://www2.dbd.puc-rio.br/pergamum/tesesabertas/0812608_10_cap_05.pdf
[4] http://www.ic.uff.br/~anselmo/cursos/CGI/slidesNovos/rasterizacao.pdf
[5] Material do professor Christian Pagot
