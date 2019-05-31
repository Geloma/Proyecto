#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

#include "Ticket.h"
#include "Evento.h"

int menuevento()
{
    while(1)
    {
    int opc;
    printf("***Bienvenido al control de eventos***\n");
    printf("1.Crear evento\n");
    printf("2.Ver información de evento\n");
    printf("3.Menu de boletos\n");
    printf("0.Salir\n");
    scanf("%d",&opc);
    return opc;
    }
}

int menuboletos()
{
    printf("1.Comprar boletos\n");
    printf("2.Consultar la informacion de boleto\n");
    printf("3.Cancelar tu boleto\n");
    int opc;
    scanf("%d",&opc);
    return opc;
}

void print_evento(Evento r)
{
    printf("Nombre: %s\n",r.nombre);
    printf("Lugar: %s\n",r.lugar);
    printf("Cupo: %s\n",r.cupo);
    printf("Fecha: %d/%d/%d\n",r.dia,r.mes,r.year);
}
bool compara_evento(Evento s1, Evento s2)
{
    return(s1.nombre!=s2.nombre);
}

bool compara_ticket(Node s1, Node s2)
{
    return(s1.data!=s2.data);
}

int main()
{
    srand(time(0));
    DLL* event=Evento_New();
    while(1)
    {
        switch(menuevento())
        {
            case 0:
            {
                Evento_Delete(event);
                return 0;
            }
            
            case 1:
            {
                char nom,lugar;
                int cupo,dia,mes,year;
                printf("Datos de evento:\n");
                gets(&nom);
                printf("Nombre:");
                gets(&nom);
                printf("Lugar:");
                gets(&lugar);
                printf("Cupo:");
                scanf("%d",&cupo);
                printf("Fecha:\n");
                printf("Dia:");
                scanf("%d",&dia);
                printf("Mes:");
                scanf("%d",&mes);
                printf("Año:");
                scanf("%d",&year);
                Evento_InsertBack(event,(struct Evento){&nom,&lugar,&cupo,&dia,&mes,&year});
                printf(" \n Evento registrado\n" );
            }
            break;
            
            case 2:
            {
                char nom;
                printf("Ingresa el nombre del evento:");
                scanf("%s",&nom);
                Evento_FindIf(event,(struct Evento){&nom},compara_evento)?
		        printf("Si se encontro\n") :
		        printf( "No se encontro el evento registrado\n");
            }
            break;
            
            case 3:
            {
                int newopc=menuboletos();
                DLL* ticket=Ticket_New();
                if(newopc==1)
                {
                    int value = rand() % 100;
                    Ticket_InsertBack(ticket,value);
                    printf("\nTu ticket es el numero: %d\n",value);
                }
                if(newopc==2)
                {
                    printf("Dame el numero de tu ticket:");
                    int bol;
                    scanf("%d",&bol);
                    Ticket_FindIf(ticket,&bol,compara_ticket)?
                    printf("Si se encontro\n") :
		            printf( "No se encontro el evento registrado\n");
                }
            }
            break;
            default:
                printf("Opcion no valida");
                break;
        }
    }
    
}
