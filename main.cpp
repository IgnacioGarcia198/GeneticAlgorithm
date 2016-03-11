/**
 * EJEMPLO DE ALGORITMO GENÉTICO: HALLAR LA SUMA DE UN NÚMERO EN NÚMEROS PRIMOS
 **/

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <math.h>
using namespace std;

// ESTAS VARIABLES AQUÍ DEFINIDAS, SI SE LES DA UN VALOR > 0 YA NO SE PIDEN POR CONSOLA
const int cb = 30; // NÚMERO DE CIFRAS BINARIAS A UTILIZAR PARA REPRESENTAR LOS NÚMEROS. SI SE LE DA UN VALOR > 0, DETERMINA TAMBIÉN EL MÁXIMO VALOR A UTILIZAR (2**cb - 1) 
int nparam = 0; // NÚMERO DE PARÁMETROS QUE TIENE LA FUNCIÓN evalua SI SE HA REDEFINIDO
int objetivo = 0; // RESULTADO DE LA FUNCIÓN AL QUE QUEREMOS LLEGAR, PARA LO CUAL ESTAMOS AJUSTANDO LOS PARÁMETROS CON ESTE PROGRAMA.
const int pob = 10; // TAMAÑO DE LA POBLACIÓN DE CONJUNTOS SOLUCIÓN. DEBE SER PAR!!
int ngen = 0; // NÚMERO DE GENERACIONES QUE QUEREMOS QUE SE REPITA LA EVOLUCIÓN DE LA POBLACIÓN
const int neleg = 2; // NÚMERO DE INDIVIDUOS ELEGIDOS EN CADA REMEZCLA
//int max = 0; // MÁXIMO NÚMERO PARA LAS CIFRAS BINARIAS ELEGIDAS (2^cb - 1)
int maxredondo = 0;

// PROBABILIDADES:
// PROBABILIDAD DE MUTACIÓN: En tanto por 100...
int pmut = 50;
// PROBABILIDAD DE INTERCAMBIO (CRUCE O MESTIZAJE), CUANDO NO OCURRE, ES UNA COPIA IGUAL DEL PADRE...
int pcruce = 80;
// FUNCIÓN PARA EL CRUCE, DISTINTAS MANERAS DE CRUZARSE...
// FUNCIÓN PARA LA MUTACIÓN


/**
 * CALCULA EL VALOR DE LA FUNCIÓN PARA UN CONJUNTO SOLLUCIÓN sol. 
 * 
 * REDEFINA ESTA FUNCIÓN CON AQUELLA DE LA QUE QUIERE BUSCAR LOS PARÁMETROS.
 * ¡OJO! SE LA LLAMA DENTRO DE bondad, PERO PUEDE ESTAR SUSTITUIDA POR CÓDIGO ALTERNATIVO.
 **/
/*int evalua(string sol) {
  int resul = 0;
  for(int i = 0; i < nparam; i ++) {
	resul += sacaparam(sol, i);
  }
  return resul;
}*/





/**
 * CONVIERTE UN ENTER0 num A BINARIO EN STRING CON cb (+1) CIFRAS
 **/

string intabinario(int num) {
  string salida = "";
  int n = abs(num), i = 0;
  while(n >= 1) {
    if (n%2) {
      salida = "1" + salida;
    }
    else {
      salida = "0" + salida;     
    }
    n /= 2;
	i++;
  }
  while(i < cb) {
    salida = "0" + salida;
    i ++;  
  }
  if(num < 0) salida = "-" + salida;
  else salida = "+" + salida;
  return salida;
}

/**
 * CONVIERTE UN BINARIO nb EN STRING CON cb CIFRAS A ENTERO
 **/
int binarioaint(string nb) {
  int salida = 0;
  int i = cb, pot = 1;
  while(i >= 0) {
    if(nb.at(i) == '1') {
      salida += pot;
    }
    pot *= 2;
	i--;
  }
  if(nb.at(0) == '-') salida = - salida;
  return salida;
}

/**
 * SACA UN PARAMETRO DE LA SOLUCION EN BINARIO
 **/
int sacaparam(string nb, int np) {
  int pos = (cb+1)*np;
  return binarioaint(nb.substr(pos,cb+1));
}


/**
 * CALCULA EL NÚMERO DE CIFRAS DE n PASADO A BINARIO
 **/
int ncb(int n) {
  int i = 0;
  while(n >= 1) {
    n /= 2;
i++;
  }
  return i;
}

/**
 * CALCULA LO BUENO QUE ES UN CONJUNTO SOLUCIÓN SEGÚN EL OBJETIVO QUE QUEREMOS CONSEGUIR
 **/
int bondad(string sol) {
  // AQUÍ METEMOS LA LLAMADA A LA FUNCIÓN...
  int resul = 0;
  for(int i = 0; i < nparam; i ++) {
	resul += sacaparam(sol, i);
  }
  int dif = objetivo - resul;
  if(!dif) return 1+maxredondo;
  else return maxredondo / abs(dif);
}

void cruce(string &s1, string &s2) {
  cout << "cruce" << endl;
  cout << "s1: " << s1 << endl;
  cout << "s2: " << s2 << endl;
  string temp = s1;
  int largo = s1.length();
  int ptm = largo/2; // pto medio
  cout << "ptm: " << ptm << endl;
  s1.replace(ptm, largo-ptm, s2.substr(ptm));
  s2.replace(ptm, largo-ptm, temp.substr(ptm));
  cout << "salida: " << s1 << " " << s2 << endl;
}

void mutacion(string &s1) {
  cout << "mutación" << endl;
  cout << "s1: " << s1 << endl;
  int largo = s1.length();
  int pos = rand()%largo;
  cout << "pos: " << pos << endl;
  string r;
  char c = s1.at(pos);
  if(c == '0') r = "1";
  else if(c == '1') r = "0";
  else if(c == '+') r = "-";
  else r = "+";
  s1.replace(pos, 1, r);	
  cout << "salida: " << s1 << endl;
}

int main() {
  int max;
  //cout.precision(3);
  /*if(cb < 1) {
    cout << "escribe el numero maximo para el juego" << endl;
	cin >> cb;
	cb = ncb(cb);
  }*/
  max = (int) pow(2, cb) - 1;
  cout << "cb " << cb << endl;
  maxredondo=1;
  while(maxredondo < max) {
    maxredondo*=10;
  }
  maxredondo*=1000;
  if(objetivo < 1) { 
	  cout << "escribe el numero objetivo, debe ser como máximo " << max << endl;
	  cin >> objetivo;
  }
  cout << "objetivo " << intabinario(objetivo) << endl;
  
  if(nparam < 1) {
    cout << "¿Cuántos sumandos quieres hallar?" << endl;
    cin >> nparam;
  }
  cout << nparam << " parámetros" << endl;
  
  /*if(pob < 1) {
    cout << "¿Tamaño de la población? (máximo 500)" << endl;
    cin >> pob;
  }
  cout << "población: " << pob << endl;*/
  
  if(ngen < 1) {
    cout << "¿Número de generaciones?" << endl;
    cin >> ngen;
  }
  cout << ngen << " generaciones" << endl;
  
  // CREAMOS LA POBLACIÓN ALEATORIA EN BINARIO
  srand(time(NULL));
  string poblacion[pob][2];
  for(int i = 0; i < pob; i ++) {
	string conjsol = "";
	for(int j = 0; j < nparam; j ++) {
	  int a = rand()%(max + 1);
	  if(rand()%2) a = -a;
	  cout << a << endl;
	  conjsol += intabinario(a);
	}
	poblacion[i][0] = conjsol;
  }

  for(int i = 0; i < pob; i ++) {
    string sol = poblacion[i][0];
    cout << sol << " ";
    int result = 0;
	for(int j = 0; j < nparam; j ++) {
	  int param = sacaparam(sol, j);
	  result += param;
	  cout << param << " ";
    }  
	cout << result << " " << bondad(sol) << endl;
	//cout << sol << " " << solent << " " << dif << " " << fixed << bondad(dif) << endl;
  }
  
  cout << "3... 2... 1... ¡EMPIEZA LA EVOLUCIÓN!" << endl;
  
  int fila = 1, generacion = 0; //string elegidos[neleg];
  bool alcanzado = false;
  while(generacion < ngen) {
	  fila = !fila;
	cout << "GENERACIÓN: " << generacion << endl; 
    cout << endl << endl << endl;
    int filaRes = !fila;
	  // CICLO DE UNA GENERACIÓN....
	  // aquí calculamos el total de bondad en la población
    int bondades[pob], bontotal = 0;
    for(int i = 0; i < pob; i ++) {
      string sol = poblacion[i][fila];
      bondades[i] = bondad(sol);
      cout << sol << " ";
      int result = 0;
      for(int j = 0; j < nparam; j ++) {
	    int param = sacaparam(sol, j);
	    result += param;
	    cout << param << " ";
      } 
      cout << result << " " << bondades[i] << endl;
      if(bondades[i] == 1+maxredondo) alcanzado = true;
      bontotal += bondades[i];
    }
    if(alcanzado) {
	  cout << "resultado alcanzado!!" << endl;
	  break;
	}
    
    // ahora elección aleatoria con probabilidades según la bondad de cada cto solución sobre la total
    int contres = 0;
    for(int ind = 0; ind < pob; ind ++) {
      int acum = 0;
      int suerte = rand()%bontotal + 1;
      for(int i = 0; i < pob; i ++) { 
	    if((suerte > acum) && (suerte <= acum + bondades[i])) {
		  // INDIVIDUO ELEGIDO...
	      //elegidos[conteleg] = poblacion[i][fila];
	      poblacion[contres][filaRes] = poblacion[i][fila];
	      
	      
	      if(contres && (contres % 2)) {
			  // SE CRUZA
		    if(rand()%100 < pcruce) {
		      cruce(poblacion[contres][filaRes], poblacion[contres - 1][filaRes]);
		    }
		    // MUTA UN HIJO
		    if(rand()%100 < pmut) {
		      mutacion(poblacion[contres][filaRes]);
		    }
		    // MUTA EL OTRO
		    if(rand()%100 < pmut) {
		      mutacion(poblacion[contres - 1][filaRes]);
		    }
		  }
		  contres ++; 
	      break;
	    }
	    acum += bondades[i];
	    cout << bondades[i] << " " << endl;
	  }
	}
	
		
	generacion ++; 
  }
  int mpos = 0, maxbondad = 0;
  for(int i = 0; i < pob; i ++) {
      int bon= bondad(poblacion[i][fila]);
      if(bon>maxbondad) {
		  maxbondad= bon;
		  mpos = i;
	  }
  }
  
  string sol = poblacion[mpos][fila];
  cout << "MEJOR RESULTADO HALLADO: " << endl;
      cout << sol << " ";
      int result = 0;
      for(int j = 0; j < nparam; j ++) {
	    int param = sacaparam(sol, j);
	    result += param;
	    cout << param << " ";
      } 
      cout << result << " " << bondad(sol) << endl;
  
  return 0;
}
