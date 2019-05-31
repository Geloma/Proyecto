#include <stdio.h>
#include <stdlib.h>
// para malloc and friends

#include <assert.h>
// para los asserts

#include <stdbool.h>
// para bool, true y FALSE

typedef struct Evento{
    char nombre[ 50 ];
    char lugar [ 100 ];
    int cupo;
    int dia;
    int mes;
    int year;
}Evento;

typedef Evento item;
typedef item* itemPtr;


typedef struct node     
{
	item data;          
	struct node* next; 
	struct node* prev; 
} node;               

typedef node* nodePtr; //<1>

typedef struct dLL
{
	nodePtr first;     //<2>
	nodePtr last;
	nodePtr cursor;
	size_t len;
} dLL;


dLL*   Evento_New();
void   Evento_Delete(      dLL* this );
bool   Evento_InsertBack(  dLL* this, item _data );
bool   Evento_InsertFront( dLL* this, item _data );
bool   Evento_InsertAfter( dLL* this, item _data );
bool   Evento_Remove(      dLL* this, itemPtr _data_back );
bool   Evento_RemoveFront( dLL* this, itemPtr _data_back );
bool   Evento_RemoveBack(  dLL* this, itemPtr _data_back );
bool   Evento_RemoveAfter( dLL* this, itemPtr _data_back );
bool   Evento_RemoveBefore(dLL* this, itemPtr _data_back );
size_t Evento_Len(         dLL* this );
bool   Evento_IsEmpty(     dLL* this );
void   Evento_MakeEmpty(   dLL* this );
bool   Evento_Peek(        dLL* this, itemPtr _data_back );
void   Evento_CursorFirst( dLL* this );
void   Evento_CursorLast(  dLL* this );
void   Evento_CursorNext(  dLL* this );
void   Evento_CursorPrev(  dLL* this );
bool   Evento_FindIf( dLL* this, item _key,bool (*cmp)(item , item ) );
bool   Evento_Search(       dLL* this, item _key,bool (*cmp)(item , item ) );
void   Evento_Traverse(    dLL* this, void (*pfun)(item) ); //<1>
