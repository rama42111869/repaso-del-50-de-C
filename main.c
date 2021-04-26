#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

typedef struct
{
    int legajo;
    char nombreYapellido[30];
    int edad;
    int anio;
} stAlumno;


int main()
{
    int n,b;
    int anio;
    stAlumno alumno[100];
    Pila p;
    inicpila(&p);
    char archivo1[]= {"ejercicio1.bin"};
    char archivo2[]= {"ejercicio4.dat"};
    printf("Elija uno de los 15 ejercicios \n");
    fflush(stdin);
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        printf("ingrese el elemento a agregar\n");
        fflush(stdin);
        scanf("%d",&b);
        agregaElementoAlFinalDelArchivo(archivo1,b);
        break;
    case 2:
        mostrarArchivoBinario(archivo1);
        break;
    case 3:
        b=cuentaarchivos(archivo1);
        printf("Cantidad de elementos del archivo %d",b);
        break;
    case 4:
        b=cargaAlumnos(archivo2);
        break;
    case 5:
        muestraAlumnos(archivo2);
        break;
    case 6:
        cargaUnAlumno(archivo2);
        break;
    case 7:
        pasardearchivoapila(archivo2,&p);
        mostrar(&p);
        break;
    case 8:
        b=contarMayores(archivo2);
        printf("La cantidad de alumnos mayores es %d",b);
        break;
    case 9:
        mostrar17y25(archivo2);
        break;
    case 10:
        buscarmayor(archivo2);
        break;
    case 11:
        printf("ingrese el anio a buscar\n-1ro)1\n-2do)2\n-3ro)3\n-4to)4\n-5to)5\n-6to)6\n");
        fflush(stdin);
        scanf("%d",&anio);
        b=contaralumnosporcurso(archivo2,anio);
        printf("la cantidad de alumnos por curso es %d\t",anio);
        break;
    case 12:
        b=cargaralumnos(alumno,3);
        cargaAlumnosConArreglo(archivo2,alumno,b);
        break;
    case 13:
        b=contaregistroarchivo(archivo2);
        printf("la cantidad de registros es %d\n",b);
        break;
    case 14:
        printf("ingrese la posicion (del 1 al 10)\n");
        fflush(stdin);
        scanf("%d",&b);
        mostraralumnoelegido(archivo2,b);
        break;
    case 15:
        inversionararchivo(archivo2);
        break;
    }
    return 0;
}

///ejercicio 1:Funcion para agregar un elemento al final de un archivo
void agregaElementoAlFinalDelArchivo(char nombre_archivo[], int dato)
{
    FILE *archi;
    archi=fopen(nombre_archivo, "a+b");
    if(archi!=NULL)
    {
        fwrite(&dato, sizeof(int), 1, archi);
        fclose(archi);
    }
}

///ejercicio 2: mostrar archivo en binario
void mostrarArchivoBinario(char nombre_archivo[])
{
    FILE *archi;
    archi=fopen(nombre_archivo,"rb");
    int aux;
    if(archi!=NULL)
    {
        printf("\nContenido del archivo:\n\n");
        while(fread(&aux, sizeof(int),1,archi)>0)
        {
            printf("%d ",aux);
        }
        fclose(archi);
    }
}

///ejercicio 3: cantidad de registros
int cuentaarchivos(char nombre_archivo[])
{
    int rta=0;
    int aux=0;
    FILE * archi;
    archi=fopen(nombre_archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(int), 1, archi)>0)
        {
            rta++;
        }
        fclose(archi);
    }
    return rta;
}

///ejercicio 4: cargar archivos hasta 5
void cargaAlumnos(char nombre_archivo[])
{
    int cont =0;
    stAlumno a;
    FILE * archi;
    archi=fopen(nombre_archivo,"r+b");
    if(archi==NULL)
    {
        archi=fopen(nombre_archivo,"w+b");
    }
    if(archi!=NULL)
    {
        printf("Ingreso de alumnos: \n");
        while(cont<5)
        {
            printf("\t%d de 5",cont+1);
            puts("\n----------------------------------");
            printf("\n Ingrese legajo: \t");
            scanf("%d", &a.legajo);
            printf("\n Ingrese nombre y apellido: \t");
            fflush(stdin);
            gets(a.nombreYapellido);
            printf("\n Ingrese edad: \t");
            scanf("%d", &a.edad);
            printf("\n Ingrese anio que cursa: \t");
            scanf("%d", &a.anio);
            puts("----------------------------------\n");
            fwrite(&a,sizeof(stAlumno),1,archi);
            cont++;
        }
        fclose(archi);
    }
}

///5a)Funcion mostrar estructura
void mostrarAlumno(stAlumno a)
{
    puts("\n---------------------------------------");
    printf("\nLegajo: %d\t",a.legajo);
    printf("\nNombre y Apellido: %s\t",a.nombreYapellido);
    printf("\nEdad: %d\t",a.edad);
    printf("\nAnio: %d\t",a.anio);
    puts("\n---------------------------------------");
}


///5b)funcion mostrar archivo:
void muestraAlumnos(char nombre_archivo[])
{
    FILE *archi;
    stAlumno a;
    archi=fopen(nombre_archivo, "rb");
    int i=0;
    if (archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&a,sizeof(stAlumno),1,archi);
            if(!feof(archi))
            {
                printf("\nRegistro numero %d",i++);
                mostrarAlumno(a);
            }
        }
        fclose(archi);
    }
}


///ejercicio 6: agregar un elemento(alumno) al final
void cargaUnAlumno(char nombre_archivo[])
{
    FILE *archi;
    stAlumno a;
    archi=fopen(nombre_archivo,"a+b");
    if(archi!=NULL)
    {
        puts("\n----------------------------------");
        printf("\n Ingrese legajo: ");
        scanf("%d", &a.legajo);
        printf("\n Ingrese nombre y apellido: ");
        fflush(stdin);
        gets(a.nombreYapellido);
        printf("\n Ingrese edad: ");
        scanf("%d", &a.edad);
        printf("\n Ingrese año que cursa: ");
        scanf("%d", &a.anio);
        puts("----------------------------------\n");
        fwrite(&a,sizeof(stAlumno),1,archi);
        fclose(archi);
    }
}

///ejercicio 7:pasar a una pila los nros de legajo
void pasardearchivoapila(char nombre_archivo[], Pila * p)
{
    FILE * archi;
    stAlumno a;
    archi=fopen(nombre_archivo, "rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&a,sizeof(stAlumno),1,archi);
            if(!feof(archi))
            {
                if(a.edad>=18)
                    apilar(p,a.legajo);
            }
        }
        fclose(archi);
    }
}

///ejercicio 8:Contar alumnos mayores de edad
int contarMayores(char nombre_archivo[])
{
    FILE * archi;
    stAlumno a;
    archi=fopen(nombre_archivo, "rb");
    int rta=0;
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&a,sizeof(stAlumno),1,archi);
            if(!feof(archi))
            {
                if(a.edad>=18)
                    rta++;
            }
        }
        fclose(archi);
    }
    return rta;
}


///ejercicio 9:mostrar alumnos entre 17 y 25
void mostrar17y25(char nombre_archivo[])
{
    FILE * archi;
    stAlumno a;
    archi=fopen(nombre_archivo, "rb");
    int rta=0;
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&a,sizeof(stAlumno),1,archi);
            if(!feof(archi))
            {
                if((a.edad>=17)&&(a.edad<=25))
                {
                    mostrarAlumno(a);
                }
            }
        }
        fclose(archi);
    }
    return rta;
}

///ejercicio 10:mostrar al alumno con mayor edad
void buscarmayor(char archivo[])
{
    FILE * archi;
    stAlumno a;
    stAlumno mayor;
    archi=fopen(archivo, "rb");
    if(archi!=NULL)
    {
        fread(&mayor,sizeof(stAlumno),1,archi);
        while(!feof(archi))
        {
            fread(&a,sizeof(stAlumno),1,archi);
            if(!feof(archi))
            {
                if(mayor.edad<a.edad)
                    mayor=a;
            }
        }
        fclose(archi);
        puts("\nEl alumno con mayor edad es:");
        mostrarAlumno(mayor);
    }
}

///ejercicio 11: contar alumnos por curso
int contaralumnosporcurso(char nombre_archivo[], int anio)
{
    int rta=0;
    FILE * archi;
    stAlumno aux;
    archi=fopen( nombre_archivo,"rb");
    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&aux,sizeof(stAlumno),1,archi);
            if(!feof(archi))
            {
                if(aux.anio==anio)
                {
                    rta++;
                }
            }
        }
        fclose(archi);
    }
    return rta;
}
///funcion para cargar el arreglo con archivos hasta que yo quiera
int cargaralumnos(stAlumno a[], int dimension)
{
    int i=0;
    char letra ='s';
    printf("\n\nIngrese nuevos alumnos\n\n");
    while(letra=='s'&&i<dimension)
    {
        puts("\n----------------------------------");
        printf("\n Ingrese legajo: ");
        scanf("%d", &a[i].legajo);
        printf("\n Ingrese nombre y apellido: ");
        fflush(stdin);
        gets(a[i].nombreYapellido);
        printf("\n Ingrese edad: ");
        scanf("%d", &a[i].edad);
        printf("\n Ingrese año que cursa: ");
        scanf("%d", &a[i].anio);
        puts("\n----------------------------------");
        i++;
        printf("\n Seguis?: ");
        fflush(stdin);
        scanf("%c", &letra);
    }
    return i;
}

///ejercicio 12: recibir como parámetro un arreglo de tipo alumno y lo copiarlo al archivo.
void cargaAlumnosConArreglo(char archivo[], stAlumno arregloAlumnos[], int cant)
{
    FILE *archi;
    int i=0;
    archi=fopen(archivo,"ab");
    if(archi!=NULL)
    {
        i=fwrite(arregloAlumnos,sizeof(stAlumno),cant,archi);
        fclose(archi);
        printf("Cantidad de registros grabados: %d",i);
    }
}


///ejercicio 13: contar registro archivos
int contaregistroarchivo(char nombre_archivo[])
{
    int cantidad =0;
    FILE * archi;
    archi = fopen(nombre_archivo,"rb");
    if(archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cantidad = ftell(archi)/sizeof(stAlumno);
        fclose(archi);
    }
    return cantidad;
}

///ejercicio 14: mostrar alumno elegido
void mostraralumnoelegido(char archivo[], int pos)
{
    FILE * archi;
    stAlumno a;
    archi=fopen(archivo, "rb");
    int i=0;
    if(archi!=NULL)
    {
        fseek(archi, sizeof(stAlumno)*pos, SEEK_SET);
        fread(&a,sizeof(stAlumno),1,archi);
        fclose(archi);
        puts("\nEl alumno que se encuentra en el registro es:");
        mostrarAlumno(a);
    }
}

///ejercicio 15: archivo invertido
void inversionararchivo(char nombre_archivo[])
{
    stAlumno alu_principio;
    stAlumno alu_final;
    int inicio=0;
    int fin=0;
    int cantidad=0;
    FILE * archi;
    archi=fopen(nombre_archivo, "r+b");
    if(archi!=NULL)
    {
        fseek(archi, 0, SEEK_END);
        cantidad=ftell(archi)/sizeof(stAlumno);
        fin=cantidad-1;
        while(inicio<fin)
        {
            // vamos al ppio y leemos
            fseek(archi, inicio*sizeof(stAlumno),SEEK_SET);
            fread(&alu_principio, sizeof(stAlumno), 1, archi);

            // vamos al final y leemos
            fseek(archi, fin*sizeof(stAlumno), SEEK_SET);
            fread(&alu_final, sizeof(stAlumno), 1, archi);

            // vamos al ppio y escribimos
            fseek(archi, inicio*sizeof(stAlumno),SEEK_SET);
            fwrite(&alu_final, sizeof(stAlumno), 1, archi);

            // vamos al final y escribimos
            fseek(archi, fin*sizeof(stAlumno), SEEK_SET);
            fwrite(&alu_principio, sizeof(stAlumno), 1, archi);

            inicio++;
            fin--;
        }
        fclose(archi);
    }
}
