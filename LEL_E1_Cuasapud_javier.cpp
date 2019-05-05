#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

//declaracion de estructuras
typedef struct {
	int dia;
	string mes;
	int anio;
} FECHA;

struct compra{
	int codigo_compra;
	int codigo_vendedor;
	int cantidad_bultos;
	char tipo_cafe;
	FECHA fecha_compra;
	float costo;
};

//declaracion de funciones 
int mostrar_menu();
void registrar_archivo(compra* vectorc,int tam);
void imprimir_compras(compra* vectorc, int tam);
float calcular_costo(char categoria, int num_bultos);
float total_vendedor(compra* vectorc,int tam,int codigo);
void quickSort(compra* A, int izq, int der);
int main (int argc, char *argv[]) {
	//declarcion de variables
	bool bandera = true;
	int pcion_digitada=-1,N=0;
	compra *vectorC;
	int codigo;
	float total_pago;
	
	//proceso
	do{
		pcion_digitada=mostrar_menu();
		cout<<"  opcion digitada  :  " ;
		cout<<pcion_digitada <<endl;
		switch(pcion_digitada){
			case 1 :
					cout <<"  indique cantidad  de compras a registrar  " <<endl;
					cin >>N;
					vectorC = new compra[N];
					registrar_archivo(vectorC,N);
				break;
			case 2 :
				if(N!=0){
					imprimir_compras(vectorC,N);
				}
				else
				{
					cout<<"no hay registrado nada "<<endl;
				}
				break;
			case 3 :
				if(N!=0){
					cout<<"ingrese codigo vendedor"<<endl;
            	    cin>>codigo;
            	     total_pago=total_vendedor(vectorC,N,codigo);
            	    if(total_pago==0){
            		    cout<<"vendedor no encontrado "<<endl;
				    }
				    else{
				      cout<< "total pagado "<< total_pago <<endl;
					  }
				}
				else
				{
					cout<<"no hay registrado nada "<<endl;
				}
				
				break;
			case 4 :
				if(N!=0){
					quickSort(vectorC,0, N-1);
					imprimir_compras(vectorC,N);
				}
				else
				{
					cout<<"no hay registrado nada "<<endl;
				}
				break;
			case 5 :
				bandera=false;
				cout<<"  hasta pronto  " <<endl;
				
				break;			
			default :{
					cout<<"  opcion digitada incorrecta  " <<endl;
					
			
			}
	
		}
		
	}while(bandera);
	
	delete [] vectorC;
	return 0;
}
//implementacion de funciones y procedimientos
int mostrar_menu()
{
	

	int opcion;
	cout<<"\n"<<endl;
	cout<<"**********************cofee.sys***************************"<<endl;
	cout<<"1.registrar compras "<<endl;
	cout<<"2 imprimir compras "<<endl;
	cout<<"3 calcular total pagado por un vendedor "<<endl;
	cout<<"4 ordenar compras desendente"<<endl;
	cout<<"5 salir"<<endl;
	cin >>opcion;
	return opcion;
}

void registrar_archivo(compra* vectorc, int tam){
  fstream archivoTXT; 
  string nombre_archivo =" informacion.txt"; //Variable para almacenar el Nombre del archivo,por ejemplo: "información.txt"
  string lineaLeida;
  char* parte;
  char linea[200];
  int contP=0; //partes 
  int iterador=0;//lineas
  cout<<"Dime el nombre_archivo del archivo:";
  cin>>nombre_archivo;
  archivoTXT.open(nombre_archivo.c_str(),ios::in); //apertura del archivoTXT	
  //Validacion para saber si el archivo está abierto
	if(archivoTXT.is_open()){
			cout<<"archivo abierto"<<endl;
			//while para recorrer cada linea hasta acabar con todas las lineas.
	    while(!archivoTXT.eof()){ 
	       //copia la primera linea en lineaLeida
			getline(archivoTXT,lineaLeida);
			//cout<<"Linea leida "<<lineaLeida<<endl;
            strcpy(linea,lineaLeida.c_str()); //convierte la lineaLeida de strings a carácteres
            parte = strtok(linea,",");//función para partir la linea según el delimitador
            while(parte != NULL){
            	switch(contP){
					case 0:
						vectorc[iterador].codigo_compra = atoi(parte);
						break;
					case 1:
						vectorc[iterador].codigo_vendedor = atoi(parte);
						break;
					case 2:
						vectorc[iterador].cantidad_bultos = atoi(parte);
						break;
					case 3:
						vectorc[iterador].tipo_cafe = *parte;
						break;
					case 4:
						vectorc[iterador].fecha_compra.dia = atoi(parte);;
						break;
					case 5:
						vectorc[iterador].fecha_compra.mes = parte;
						break;
					case 6:
						vectorc[iterador].fecha_compra.anio = atoi(parte);
						break;
					case 7:
						vectorc[iterador].costo = atof(parte);;
						break;
						
					}
				
			    contP++;
				parte = strtok(NULL,","); //continua partiendo
				
				
			} 	
			contP=0;
			iterador++;
			if(iterador>=tam){
				break;
			}

         
		}
		iterador=0;
		//cierre de archivo
		archivoTXT.close();
		cout<<"archivo cerrado "<<endl;
	}else{
		cout<<"No se puede abrir el archivo, no tiene permisos del sistema."<<endl;
	}	
}

void imprimir_compras(compra* vectorc, int tam){
	
	cout<<"informacion de los usuarios "<<endl;
	for(int i=0;i<tam;i++)
	{
	 	cout<<"codigo compra :";
	 	cout<<vectorc[i].codigo_compra;
	 	cout<<"    codigo vendedor  :";
	 	cout<<vectorc[i].codigo_vendedor;
	 	cout<<"  cantidad de  bultos :";
	 	cout<<vectorc[i].cantidad_bultos;
	 	cout<<"   tipo cafe  :";
	 	cout<<vectorc[i].tipo_cafe;
	 	cout<<"  dia :";
	 	cout<<vectorc[i].fecha_compra.dia;
	 	cout<<"  mes :";
	 	cout<<vectorc[i].fecha_compra.mes;
	 	cout<<"  anio :";
	 	cout<<vectorc[i].fecha_compra.anio;
	 	vectorc[i].costo=calcular_costo(vectorc[i].tipo_cafe,vectorc[i].cantidad_bultos);
	 	cout<<" costo ";
	 	cout<<vectorc[i].costo <<endl;
	}
}

float calcular_costo(char categoria, int num_bultos){
	
	
	
	
	if(categoria == 'A'){
		return (num_bultos*65000);
	}
	else{
		if(categoria =='B'){
			return (num_bultos*53000);
		}
		else
		if(categoria=='C'){
			return (num_bultos*48000);
		}
		
	}
	return 0;
}

float  total_vendedor(compra* vectorc,int tam,int codigo){
     
     float total_vendedor=0;
	  for(int i=0;i<tam;i++)
	  {
	  	if(vectorc[i].codigo_vendedor== codigo){
	 		total_vendedor= vectorc[i].costo+total_vendedor;
		 }
	  	
	  }
	  return total_vendedor;

	}
	
void quickSort(compra* A, int izq, int der){
 compra  piv = A[izq];
 int i = izq;
 int j = der;
 compra aux;

 while (i < j) {
  while (A[i].costo >= piv.costo && i < j) i++;
  while (A[j].costo < piv.costo) j--;
  if (i < j) {
   aux  = A[i];
   A[i] = A[j];
   A[j] = aux;
  }
 }

 A[izq] = A[j];
 A[j] = piv;
 if (izq<j - 1)
  quickSort(A, izq, j - 1);
 if (j + 1 <der)
  quickSort(A, j + 1, der);
	
}

