//---------------LIBRERIAS-----------------
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MODIFICADO "modificado.dat"

//-------------------ESTRUCTURAS-----------------
struct empleados{

int legajo;
char nombre[30];
char categoria;
float sueldo;
int activo;

};
//------------------------------------------------PROTOTIPOS---------------------------------------
void crearArchivo(FILE *archivo);
void Alta(FILE *archivo);
void listarDatos(FILE *archivo);
void buscar(FILE *archivo);
void modificar(FILE *archivo);
void actualizar(FILE *archivo);
void bajaLogica(FILE *archivo);
void bajaFisica(FILE *archivo);


//--------------FUNCION MAIN-----------------
int main(){
int op;

    FILE *archivo;

    do{
    printf("\t\tINGRESE LA OPCION QUE DESEA EJECUTAR\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\t(1): Crear un Archivo\n");
    printf("\t\t(2): Alta \n");
    printf("\t\t(3): Listar datos \n");
    printf("\t\t(4): Buscar por Legajo o por Nombre\n");
    printf("\t\t(5): Modificar Categoria y Sueldo\n");
    printf("\t\t(6): Actualizar Sueldos\n");
    printf("\t\t(7): Baja Logica\n");
    printf("\t\t(8): Baja fisica\n");
    printf("\t\t(0):INGRESE 0 SI DESEA SALIR DEL PROGRAMA\n.");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\t");
    scanf("%d",&op);

    switch(op){

case 1:
    crearArchivo(archivo);

    break;
case 2:
    Alta(archivo);
    break;
case 3:
    listarDatos(archivo);
    break;
case 4:
    buscar(archivo);
    break;
case 5:
    modificar(archivo);
    break;
case 6:
    actualizar(archivo);
    break;
case 7:
    bajaLogica(archivo);
    break;
case 8:
    bajaFisica(archivo);
    break;
case 0:
    break;

    }
    system("cls");
    }while(op >= 1 && op <= 8);

    return 0;
}

//----------------------------------------------------FUNCIONES--------------------------------------------------------
//-------------CREAR ARCHIVO-----------------------
void crearArchivo(FILE *archivo){
struct empleados datos={0,"0",'0',0,0};
    int i,cantidadEmpleados;

   if ( ( archivo = fopen( "empleados.dat", "wb" ) ) == NULL ){
      printf( "Error: El Archivo no pudo crearse.\n" );
   }
   else {
    printf("Archivo creado exitosamente.\n");
    }
    system("pause");
    system("cls");
    do{
    printf("Cantidad de empleados: ");
    scanf("%d",&cantidadEmpleados);
    fflush(stdin);
    if(cantidadEmpleados <= 0){
        printf("Error: Una cantidad no puede ser negativa\n");
    }
    }while(cantidadEmpleados <= 0);
    for(i=0;i<cantidadEmpleados;i++){
        fwrite(&datos,sizeof(struct empleados),1,archivo);
    }

    fclose(archivo);

    printf("\n");
}
//-----------------------ALTA DE EMPLEADOS------------------------
void Alta(FILE *archivo){
    struct empleados datos, data;
    int legajo;
system("cls");

    //ABRIR ARCHIVO PARA LEER Y ESCRIBIR
    if((archivo = fopen("empleados.dat","r+b"))==NULL){
        printf("No se puede abrir el archivo");
        exit(-1);
    };



      printf("SI DESEA NO CARGAR MAS EMPLEADOS INGRESE LEGAJO NRO 0\n");

    do{
        //NUMERO DE LEGAJO(POSICION EN EL ARCHIVO)
    do{

        printf("Ingrese Numero de Legajo:\n");
        scanf("%d",&datos.legajo);
        fflush(stdin);
        if (datos.legajo< 0){
            printf("Error: El legajo debe ser un numero positivo\n");
        }
    }while(datos.legajo < 0);

    if(datos.legajo != 0){

    //NOMBRE

    printf("Ingrese Nombre del empleado\n");
    gets(datos.nombre);
    fflush(stdin);
    //CATEGORIA
    do{
    printf("Ingrese su categoria:\n");
    scanf("%c",&datos.categoria);
    fflush(stdin);
    if(datos.categoria != 'A' && datos.categoria != 'B' && datos.categoria != 'C' && datos.categoria != 'a' && datos.categoria != 'b' && datos.categoria != 'c' ){
        printf("INGRESE UNA CATERGORIA CORRECTA!\n");
    }
    }while(datos.categoria != 'A' && datos.categoria != 'B' && datos.categoria != 'C' && datos.categoria != 'a' && datos.categoria != 'b' && datos.categoria != 'c' );

    //SUELDO
    do{
    printf("Ingrese el sueldo del empleado:\n");
    scanf("%f",&datos.sueldo);
    fflush(stdin);
    if(datos.sueldo <= 0){
        printf("Error: Un sueldo no puede ser 0 ni negativo.\n");
    }
    }while(datos.sueldo <= 0);

    //ACTIVO
    do{
    printf("Ingrese (1) si el empleado esta activo, (0) si el empleado esta dado de baja logica.\n");
    scanf("%d",&datos.activo);
    fflush(stdin);
    }while(datos.activo != 0 && datos.activo != 1);

    //APUNTAR PUNTERO DEL ARCHIVO A SU DIRECCION CORRESPONDIENTE
    fseek(archivo,0,SEEK_SET); // APUNTO EL CURSOR AL PRINCIPIO
    fseek(archivo,(datos.legajo-1)*sizeof(struct empleados),SEEK_CUR);
    fread(&data,sizeof(struct empleados),1,archivo);
    if(data.legajo == 0){
    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(datos.legajo-1)*sizeof(struct empleados),SEEK_CUR);
    fwrite(&datos,sizeof(struct empleados),1,archivo); //escribo los datos en el archivo
    }
    else{
        printf("Ya hay un empleado cargado en esta posicion\n");
    }
    }
    }while(datos.legajo != 0);
    fclose(archivo);

    return;
}

//------------------------------LISTAR DATOS DE EMPLEADOS---------------------------
void listarDatos(FILE *archivo){
struct empleados datos;
int op;
int i=0,cant;

system("cls");
    //ABRIR ARCHIVO PARA LEER
    if((archivo = fopen("empleados.dat","rb"))==NULL){
        printf("No se puede abrir el archivo");
        exit(-1);
    };



    //INGRESO LA OPCION DESEADA POR EL USAURIO
    do{
    printf("INGRSE LA OPCION DESEADA\n\n");
    printf("Ingrese 1 si quiere ver solo los empleados Activos.\n");
    printf("Ingrese 0 si quiere todos los empleados empleados\n ");
    scanf("%d",&op);
    fflush(stdin);
    if(op != 0 && op != 1){
        printf("Error: Ingrese alguna de las opciones correctcas\n");
    }
    }while(op != 0 && op != 1);


    switch(op){
case 1:

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    while(i<cant){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        if(datos.activo==1){
            printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
        }
        i++;
    }
system("pause");
break;

case 0:

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    for(i=0;i<cant;i++){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    }
    system("pause");
    break;

    }


    //cierro mi archivo
    fclose(archivo);
return;
}



//---------------------BUSCAR EMPLEADO---------------------------------------
void buscar(FILE *archivo){
struct empleados datos;
int op;
int j,cant,i;
char nombre[30];
system("cls");
    //ABRIR ARCHIVO PARA LEER
    if((archivo = fopen("empleados.dat","rb"))==NULL){
        printf("No se puede abrir el archivo");
        exit(-1);
    }

    do{
    printf("INGRESE LA OPCION DESEADA:\n");
    printf("Ingrese 1 si quiere buscar por legajo\n");
    printf("Ingrese 2 si quiere buscar por Nombre\n");
    scanf("%d",&op);
    fflush(stdin);
    if(op != 1 && op != 2){
        printf("Error: Ingrese una opcion valida\n");
    }
    }while(op != 1 && op != 2);


switch (op){
case 1:
    printf("Ingresar numero legajo");
    scanf("%d",&j);
    fflush(stdin);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(j-1)*sizeof(struct empleados),SEEK_CUR);

    fread(&datos,sizeof(struct empleados),1,archivo);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
    system("pause");
    break;
case 2:

    printf("Ingrese el nombre del empleado que desee buscar: \n");
    gets(nombre);
    fflush(stdin);

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    while(i<cant){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        if((strcmp(nombre,datos.nombre))==0){
            printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
        }
        i++;
    }

    system("pause");
    break;

}
    //CIERRO EL ARCHIVO
    fclose(archivo);
return ;
}


//------------------MODIFICAR UN EMPLEADO---------------------------

void modificar(FILE *archivo){
struct empleados datos;
int op, j, cant, i,seguro;
float nuevoSueldo;
char nombre[30], categoria;
system("cls");

if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");
    exit(-1);
}
    printf("ELIJA LA OPCION DESEADA\n");
    printf("(1) Modificar un campo y buscar por Numero de legajo\n");
    printf("(2) Modificar un campo y buscar por Nombre de empleado\n");
    scanf("%d",&op);

    switch (op){

    case 1:
    printf("Ingresar numero legajo:\n");
    scanf("%d",&j);
    fflush(stdin);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(j-1)*sizeof(struct empleados),SEEK_CUR);

    fread(&datos,sizeof(struct empleados),1,archivo);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    do{
    printf("\n");
    printf("Seguro que desea modificar el campo?\nIngrese (1) por SI (2) por NO \n");
    scanf("%d",&seguro);
    fflush(stdin);

    if (seguro != 1 && seguro != 2){
        printf("ERROR: ingrese una opcion correcta\n");
    }
    }while(seguro != 1 && seguro !=2);

    if(seguro == 1){
        fseek(archivo,-sizeof(struct empleados),SEEK_CUR); //apunto al lugar a modificar
        printf("ingrese el Nuevo sueldo:\n");
        scanf("%f",&nuevoSueldo);
        fflush(stdin);
        datos.sueldo = nuevoSueldo;

        printf("ingrese la nueva Categoria:\n");
        scanf("%c",&categoria);
        fflush(stdin);
        datos.categoria = categoria;

        fwrite(&datos,sizeof(struct empleados),1,archivo);


    }
    system("pause");
    break;
    case 2:

    printf("Ingrese el nombre del empleado que desee modificar: \n");
    gets(nombre);
    fflush(stdin);

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);


    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    while(i<cant){

        fseek(archivo,0,SEEK_SET);//apunto al princpio del archivo
        fseek(archivo,i*sizeof(struct empleados),SEEK_CUR);//apunto a la posicion a buscar
        fread(&datos,sizeof(struct empleados),1,archivo); //comparo si son iguales de forma secuencial
        if((strcmp(nombre,datos.nombre))==0){
            printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
            do{
            printf("\n");
            printf("Seguro que desea modificar el campo?\nIngrese (1) por SI (2) por NO \n");
            scanf("%d",&seguro);
            fflush(stdin);
            if(seguro != 1 && seguro != 2){
                printf("ERROR: ingrese una opcion valida\n");
            }
    if (seguro != 1 && seguro != 2){
        printf("ERROR: ingrese una opcion correcta\n");
    }
    }while(seguro != 1 && seguro !=2);

    if(seguro == 1){
        fseek(archivo,-sizeof(struct empleados),SEEK_CUR); //apunto al lugar a modificar
        printf("ingrese la nueva Categoria:\n");
        scanf("%c",&categoria);
        fflush(stdin);
        datos.categoria = categoria;

        printf("ingrese el Nuevo sueldo:\n");
        scanf("%f",&nuevoSueldo);
        fflush(stdin);
        datos.sueldo = nuevoSueldo;

        fwrite(&datos,sizeof(struct empleados),1,archivo);

    }
        }
        i++;
    }
    system("pause");
    break;

    }

 fclose(archivo);
return;
}
//--------------------ACTUALIZAR SUELDO POR PARITARIAS----------------------
void actualizar(FILE *archivo){
struct empleados datos;
int cant,i,porcentaje;
char cate;
float nuevoSueldo;
system("cls");
if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");   //ABRO EL ARCHIVO
    exit(-1);
}
    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");


    fseek(archivo,0,SEEK_SET);
    for(i=0; i<cant; i++){
        fseek(archivo,i*sizeof(struct empleados),SEEK_CUR);
        fread(&datos,sizeof(struct empleados),1,archivo);
        fseek(archivo,0,SEEK_SET);
        printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    }

    do{
    printf("Ingrese la categoria a modificar\n");
    cate=getch();
    fflush(stdin);
    if (cate != 'A' && cate != 'B' && cate != 'C' && cate != 'a' && cate != 'b' && cate != 'c' ){
        printf("Error: Ingrese una opcion valida\n");
    }
    }while(cate != 'A' && cate != 'B' && cate != 'C' && cate != 'a' && cate != 'b' && cate != 'c' );

    do{
    printf("ingrese el porcentaje a modificar del sueldo\n");
    scanf("%d",&porcentaje);
    fflush(stdin);
    if(porcentaje < 0){
        printf("Error: El porcentaje no puede ser un numero negativo\n");
    }
    }while(porcentaje < 0 );

    fseek(archivo,0,SEEK_END);
    cant = ftell(archivo)/sizeof (struct empleados);
    fseek(archivo,0,SEEK_SET);

    for(i= 0; i<cant; i++){
        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);

    if(datos.categoria == cate){
        datos.sueldo = datos.sueldo * (1+porcentaje/100.0);

        fseek(archivo,i*sizeof(struct empleados),SEEK_SET);
        fwrite(&datos,sizeof(struct empleados),1,archivo);
        fseek(archivo,0,SEEK_SET);

    }

    }

system("pause");
fclose(archivo);
return;
}

//---------------------------------BAJA LOGICA DE UN EMPLEADO POR NUMERO DE LEGAJO-----------------
void bajaLogica(FILE *archivo){
struct empleados datos;
int j,seguro,cant,i;
system("cls");
if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");   //ABRO EL ARCHIVO
    exit(-1);
}

    printf("Ingresar numero legajo");
    scanf("%d",&j);
    fflush(stdin);

    fseek(archivo,0,SEEK_SET);
    fseek(archivo,(j-1)*sizeof(struct empleados),SEEK_CUR);

    fread(&datos,sizeof(struct empleados),1,archivo);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    fseek(archivo,-sizeof(struct empleados),SEEK_CUR);

    if(datos.activo == 1){
        printf("Seguro que desea modificar el campo Activo?\n(1)SI\n(2)NO\n");
        scanf("%d",&seguro);
        if(seguro == 1){
        datos.activo = 0;
        fwrite(&datos,sizeof(struct empleados),1,archivo);
        }
    }
    else{
        printf("Error: El campo Activo esta en 0\n");
    }

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);
    fseek(archivo,0,SEEK_SET);
    for(i =0 ;i<cant;i++){
    if(datos.activo == 1){
    fread(&datos,sizeof(struct empleados),1,archivo);
    printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);
    }
    }


system("pause");
fclose(archivo);
return;
}

//----------------BAJA FISICA DE UN EMPLEADO----------------


void bajaFisica(FILE *archivo){
struct empleados datos;
int i, cant;
FILE *modificado;
system("cls");
    if((archivo = fopen("empleados.dat","r+b"))==NULL){
    printf("No se puede abrir el archivo");   //ABRO EL ARCHIVO
    exit(-1);
}


    if((modificado = fopen("modificado.dat","w+b"))==NULL){
    printf("No se puede abrir el archivo");   //ABRO EL ARCHIVO
    exit(-1);
    }
     else {
    printf("Archivo creado exitosamente.\n");
    }

    fseek(archivo,0,SEEK_END);
    cant=ftell(archivo)/sizeof(struct empleados);
    fseek(archivo,0,SEEK_SET);
    for(i=0; i<cant; i++){
        fread(&datos,sizeof(struct empleados),1,archivo);
        if(datos.activo == 1){
        fwrite(&datos,sizeof(struct empleados),1,modificado);
        }
    }

    fseek(modificado,0,SEEK_END);
    cant=ftell(modificado)/sizeof(struct empleados);

    printf("Legajo\tNombre\tCategoria\tSueldo\tEstado\n");
    fseek(archivo,0,SEEK_SET);

    for(i=0;i<cant;i++){
        fseek(modificado,i*sizeof(struct empleados),SEEK_SET);
        fread(&datos,sizeof(struct empleados),1,archivo);
        printf( "%-8d%-10s%c%20.2f%6d\n", datos.legajo, datos.nombre, datos.categoria, datos.sueldo, datos.activo);

    }
    system("pause");



fclose(modificado);
fclose(archivo);
return;
}
