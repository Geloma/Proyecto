#include <stdio.h>
#include <stdlib.h>
// para malloc and friends

#include <assert.h>
// para los asserts

#include <stdbool.h>
// para bool, true y FALSE


typedef int Item;
typedef Item* ItemPtr;

typedef struct Node     
{
	Item data;          
	struct Node* next; 
	struct Node* prev; 
} Node;               

typedef Node* NodePtr; //<1>

typedef struct DLL
{
	NodePtr first;     //<2>
	NodePtr last;
	NodePtr cursor;
	size_t len;
} DLL;


DLL*   Ticket_New();
void   Ticket_Delete(      DLL* this );
bool   Ticket_InsertBack(  DLL* this, Item _data );
bool   Ticket_InsertFront( DLL* this, Item _data );
bool   Ticket_InsertAfter( DLL* this, Item _data );
bool   Ticket_Remove(      DLL* this, ItemPtr _data_back );
bool   Ticket_RemoveFront( DLL* this, ItemPtr _data_back );
bool   Ticket_RemoveBack(  DLL* this, ItemPtr _data_back );
bool   Ticket_RemoveAfter( DLL* this, ItemPtr _data_back );
bool   Ticket_RemoveBefore(DLL* this, ItemPtr _data_back );
size_t Ticket_Len(         DLL* this );
bool   Ticket_IsEmpty(     DLL* this );
void   Ticket_MakeEmpty(   DLL* this );
bool   Ticket_Peek(        DLL* this, ItemPtr _data_back );
void   Ticket_CursorFirst( DLL* this );
void   Ticket_CursorLast(  DLL* this );
void   Ticket_CursorNext(  DLL* this );
void   Ticket_CursorPrev(  DLL* this );
bool   Ticket_FindIf( DLL* this, Item _key,bool (*cmp)(Item , Item ) );
bool   Ticket_Search(      DLL* this, Item _key,bool (*cmp)(Item , Item ) );
void   Ticket_Traverse(    DLL* this, void (*pfun)(Item) ); //<1>


