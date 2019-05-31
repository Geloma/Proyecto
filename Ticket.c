// Ticket.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Ticket.h"

static NodePtr newNode( Item _data )
{
	NodePtr n = (NodePtr) malloc( sizeof( Node ) );
	if( n ){
		n->data = _data;
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

static void reset( DLL* this )
{
	this->first = this->last = this->cursor = NULL;
	this->len = 0;
}

DLL* Ticket_New()
{
	DLL* list = (DLL*) malloc( sizeof( DLL ) );
	if( list ){
		reset( list );
	}
	return list;
}

void Ticket_Delete( DLL* this )
{
	if( this ){
		Ticket_MakeEmpty( this );
		free( this );
	}
}

bool Ticket_InsertBack( DLL* this, Item _data )
{
	assert( this );
	
	bool done = false;

	NodePtr n = newNode( _data );
	if( n ){
		done = true; 

		if( Ticket_IsEmpty( this ) ){
			this->first = this->last = n;
			this->len = 1;
		} else {
			this->last->next = n;
			n->prev = this->last;
			this->last = n;
			++this->len;
		}
	}
	return done;
}

bool Ticket_InsertFront( DLL* this, Item _data )
{
	assert( this );
	
	bool done = false;

	NodePtr n = newNode( _data );
	if( n ){
		done = true; 

		if( Ticket_IsEmpty( this ) ){
			this->first = this->last = n;
			this->len = 1;
		} else {
			n->next = this->first;
			this->first->prev = n;
			this->first = n;
			++this->len;
		}
	}
	return done;
}

bool Ticket_InsertAfter( DLL* this, Item _data )
{
	assert( this );

	bool done = false;

	if( Ticket_IsEmpty( this ) || this->cursor == this->last ){
		done = Ticket_InsertBack( this, _data );
	} else {
		NodePtr n = newNode( _data );
		if( n ){
			done = true;

			n->next = this->cursor->next;
			this->cursor->next->prev = n;
			this->cursor->next = n;
			n->prev = this->cursor;
			++this->len;
		}
	}
	return done;
}

bool Ticket_Remove( DLL* this, ItemPtr _data_back )
{
	assert( this );

	bool done = false;

	if( !Ticket_IsEmpty( this ) && NULL != this->cursor ){
		done = true; 

		*_data_back = this->cursor->data;

		NodePtr left = this->cursor->prev;
		NodePtr right = this->cursor->next;
		free( this->cursor );

		if( left == NULL && right == NULL ){
			reset( this );
		} else {
			this->cursor = left;
			this->cursor->next = right;
			right->prev = this->cursor;
			--this->len;
		}
	}
	return done;
}

bool Ticket_RemoveFront( DLL* this, ItemPtr _data_back )
{
	assert( this );

	bool done = false;

	if( !Ticket_IsEmpty( this ) ){
		done = true;
		*_data_back = this->first->data;
		NodePtr tmp = this->first->next;
		free( this->first );
		this->first = tmp;

		if( NULL != this->first ){
			this->first->prev = NULL;
			--this->len;
		} else {
			reset( this );
		}
	}
	return done;
}

bool Ticket_RemoveBack( DLL* this, ItemPtr _data_back )
{
    assert(this);
    bool done= false;
    if(!Ticket_IsEmpty(this))
    {
        done=true;
        *_data_back=this->last->data;
        NodePtr tmp=this->last->prev;
        free(this->last);
        this->last=tmp;
        if(NULL!=this->last)
        {
            this->last->next=NULL;
            --this->len;
        }
        else
        {
            reset(this);
        }
    }
    return done;
}

bool Ticket_RemoveAfter( DLL* this, ItemPtr _data_back )
{
    assert(this);
    bool done=false;
    if(!Ticket_IsEmpty(this) && this->cursor!=this->last && this->cursor!=NULL)
    {
        done=true;
        NodePtr tmp1=this->cursor->next;
        *_data_back= this->cursor->next->data;
        
        NodePtr tmp2=tmp1->next;
        free(tmp1);
        this->cursor->next=tmp2;
        if(tmp2!=NULL)
        {
            tmp2->prev=this->cursor;
        }
    }
    return done;
}

bool Ticket_RemoveBefore( DLL* this, ItemPtr _data_back )
{
    assert(this);
    bool done=false;
    if(!Ticket_IsEmpty(this) && this->cursor!=this->first && this->cursor!=NULL)
    {
        done=true;
        NodePtr tmp1=this->cursor->prev;
        *_data_back= this->cursor->next->data;
        
        NodePtr tmp2=tmp1->prev;
        free(tmp1);
        this->cursor->prev=tmp2;
        if(tmp2!=NULL)
        {
            tmp2->next=this->cursor;
        }
    }
    return done;
}

size_t Ticket_Len( DLL* this )
{
	assert( this );
	return this->len;
}

bool Ticket_IsEmpty( DLL* this )
{
	assert( this );
	return this->first == NULL;
}

void Ticket_MakeEmpty( DLL* this )
{
	assert( this );
	while( NULL != this->first){
		NodePtr tmp = this->first->next;
		free( this->first );
		this->first = tmp;
	}
	reset( this );
}

bool Ticket_Peek( DLL* this, ItemPtr _data_back )
{
    assert(this);
    bool done=false;
    if(!Ticket_IsEmpty(this) && this->cursor!=NULL)
    {
        *_data_back=this->cursor->data;
        done=true;
    }
    return done;
}

void Ticket_CursorFirst( DLL* this )
{
	assert( this );
	this->cursor = this->first;
}

void Ticket_CursorLast( DLL* this )
{
	assert( this );
	this->cursor = this->last;
}

void Ticket_CursorNext( DLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->cursor->next;
	}
}

void Ticket_CursorPrev( DLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->cursor->prev;
	}
}
//Funciones predicado son funciones que reciben elementos y devuelven un bool
bool Ticket_FindIf( DLL* this, Item _key,bool (*cmp)(Item , Item ) )
{
	assert( this );

	bool found = false;
	
	for( NodePtr it = this->first; it != NULL; it = it->next ){
		if( cmp(_key, it->data)){
			found = true;
			break;
		}
	}
	return found;
}

bool Ticket_Search( DLL* this, Item _key,bool (*cmp)(Item , Item ) )
{
    assert(this);
    bool found=false;
    if(!Ticket_IsEmpty(this))
    {
        for(NodePtr it=this->first;it->next!=NULL;it=it->next)
        {
            if( cmp(_key, it->data))
            {
                found=true;
                this->cursor=it;
                break;
            }
        }
    }
}

void Ticket_Traverse( DLL* this, void (*pfun)(Item) )
{
	assert( this );

	for( NodePtr it = this->first; it != NULL; it = it->next ){
		pfun( it->data );
	}
}
