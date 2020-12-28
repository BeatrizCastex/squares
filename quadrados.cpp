/*
Beatriz de Camargo Castex Ferreira - 10728077 - USP São Carlos - IFSC
2019/1

Programa que lê coordenadas e tamanhos de quadrados e vê se eles se intersectam e calcula a área da intersecção

Exemplo de entrada:

S1 1.2 3.4 5
S2 1.9 2.3 3

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Primeiro criamos uma Structure que irá quardar nossas entradas
struct square
{
  std::string nome; //identificador do quadrado
  double x; // coordenada x do ponto inferior esquerdo do quadrado
  double y; // coordenada y do ponto inferior direito do quadrado
  double comprimento; // tamanho de um lado do quadrado
  double lado_x; // coordenada x na extremidade oposta de "x" no eixo horizontal
  double lado_y; //coordenada y na extremidade oposta de "y" no eixo vertical
};

// Função para montar um quadrado
void build(square &s, std::string var_nome, double var_x, double var_y, double var_comp){
  s.nome = var_nome;
  s.x = var_x;
  s.y = var_y;
  s.comprimento = var_comp;
  s.lado_x = var_x+var_comp;
  s.lado_y = var_y+var_comp;
}

// Função para ver se dois lados(ou pontos) de um quadrado estão dentro do lado do outro quadrados
bool inside(double lado_1, double lado_2){

  bool var_inside;

  if( lado_2 < lado_1){
    var_inside = true;
  }
  else{
    var_inside = false;
  }

  return var_inside;
}

// Função para ver se dois quadrados se intersectam
bool intersect(double xo, double yo, double ladoo, double xn, double yn, double ladon){
  bool intersecta = false;

  // Caso xn esteja fora da área de influência de xo não ocorre intersecção.
  // Testando se é possível haver uma intersecção. (xn deve estar dentro da área de influência de xo e isso só acontece se xo<xn)
  if (xo < xn) {
    	// Vendo se o ponto inferior esquerdo do quadrado n está dentro do lado do quadrado o.
      if (inside(ladoo, xn) == true){
        intersecta = true;
      }
  }
  // Se os dois quadrados estiverem no mesmo ponto existe a chance de não intersectarem, se eles apenas compartilharem um lado. Para haver intersecção os lados devem se cruzar.
  else if (xo == xn){
    // Não queremos repetir quadrados. Se houver intersecção ela será contada apenas quando tivermos xo do quadrado maior.
    if(inside(ladoo, ladon) == true){
      intersecta = true;
    }
  }
	// Se um quadrado estiver meio dentro de outro mas em uma posição em que xn > xo mas yn < yo ou o contrário.
	else if ((xo > xn) && (yn > yo)){
		if(inside(ladon, ladoo)){
			intersecta = true;
		}
	}
  return intersecta;
}

// Função que calcula a área de intersecção
double intersection_area(square &so, square &sn){

	double area;

	// Se um quadrado estiver dentro do outro:
	if (((so.lado_x)>(sn.lado_x)) && ((so.lado_y)>(sn.lado_y))){

		// A área vai ser a área do quadrado então: comprimento_n²
		area = sn.comprimento*sn.comprimento;

	}

	//Se um quadrado estiver "meio dentro" do outro por x:
	else if ((so.lado_x) > (sn.lado_x)){
		// altura = lado do quadrado de baixo - y do ponto que intersecta e base = lado do quadrado de baixo - a diferença entre os lados dos dois quadrados
		area = ((so.lado_y)-sn.y)*(sn.comprimento);

	}

	// Se um quadrado estiver "meio dentro" do outro por y:
	else if((so.lado_y)>(sn.lado_y)){
		// altura = lado do quadrado de baixo - a diferença entre os lados dos dois quadrados e base = lado do quadrado de baixo - x do ponto que intersecta
		area = ((so.lado_x)-sn.x)*(sn.comprimento);
	}

	// Se um quadrado estiver meio dentro de outro mas em uma posição em que xn > xo mas yn < yo.
	else if(so.x > sn.x){

		// altura = lado do quadrado de baixo - altura do quadrado de cima
		// base = (lado do quadrado de cima - lado do quadrado de baixo) - (x do quadrado de baixo - x do quadrado de cima)
		area = (so.lado_y - sn.y)*so.comprimento;
	}

	// Se um quadrado estiver meio dentro de outro mas em uma posição em que xn < xo mas yn > yo.
	else if(so.y > sn.y){

		// altura = lado do quadrado de baixo - altura do quadrado de cima
		// base = (lado do quadrado de cima - lado do quadrado de baixo) - (x do quadrado de baixo - x do quadrado de cima)
		area = (so.lado_x - sn.x)*so.comprimento;
	}


	else{

		// Para ver o comprimento base de uma intersecção: xo+lo - xn
		// Para ver a altura de uma intersecção: yo+lo - yn
		area = ((so.lado_x)-sn.x)*((so.lado_y)-sn.y);

	}

	return area;

}

int main(int, char const *[]) {

    // Variáveis
    std::vector<square> quadrados; // Vetor onde serão guardados os sturcts com as entradas
    int n = 0; // Número de quadrados
    double A; // área de intersecção


    // Lendo um arquivo
    std::ifstream dados("squares.dat");
    std::string aux_nome;
    double aux_x, aux_y, aux_comp;

    // Existem entradas a serem lidas
    while(!dados.eof()){

      // Lemos os dados de uma linha
      dados >> aux_nome;
      // Precisamos que a primeira entrada seja válida (não vazia)
      if (dados.good()){

        dados >> aux_x;
        dados >> aux_y;
        dados >> aux_comp;

        // Criamos um elemento struct no vetor para cada linha
        quadrados.push_back(square());
        build(quadrados[n], aux_nome, aux_x, aux_y, aux_comp);

        ++n;
      }
    }
    // todas as entradas foram lidas

    //Verificando se há intersecção dos quadrados
  	//escolhemos um quadrado
    for(int i = 0; i < n; ++i){
  		//escolhemos outro quadrado
      for(int j = 0; j < n; ++j){
  			if (j != i){

          // Se intersecta devemos imprimir os quadrados que intersectam
          // Verificamos se há intersecção pelo ponto x e pelo ponto y
  				if ((intersect(quadrados[i].x, quadrados[i].y, quadrados[i].lado_x, quadrados[j].x, quadrados[j].y, quadrados[j].lado_x ) == true) && (intersect(quadrados[i].y, quadrados[i].x, quadrados[i].lado_y, quadrados[j].y, quadrados[j].x, quadrados[j].lado_y ) == true)){

  					A = intersection_area(quadrados[i], quadrados[j]);

  					std::cout << quadrados[i].nome << " intercepts " << quadrados[j].nome << " with area "  << A << "\n";


  				}
  			}
  		}
  	}

    return 0;
}
