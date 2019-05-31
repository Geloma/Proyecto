// DLL.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Evento.h"

static nodePtr newNode( item _data )
{
	nodePtr n = (nodePtr) malloc( sizeof( node ) );
	if( n ){
		n->data = _data;
		n->next = NULL;
		n->prev = NULL;
	}
	return n;
}

static void reset( dLL* this )
{
	this->first = this->last = this->cursor = NULL;
	this->len = 0;
}

dLL* Evento_New()
{
	dLL* list = (dLL*) malloc( sizeof( dLL ) );
	if( list ){
		reset( list );
	}
	return list;
}

void Evento_Delete( dLL* this )
{
	if( this ){
		Evento_MakeEmpty( this );
		free( this );
	}
}

bool Evento_InsertBack( dLL* this, item _data )
{
	assert( this );
	
	bool done = false;

	nodePtr n = newNode( _data );
	if( n ){
		done = true; 

		if( Evento_IsEmpty( this ) ){
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

bool Evento_InsertFront( dLL* this, item _data )
{
	assert( this );
	
	bool done = false;

	nodePtr n = newNode( _data );
	if( n ){
		done = true; 

		if( Evento_IsEmpty( this ) ){
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

bool Evento_InsertAfter( dLL* this, item _data )
{
	assert( this );

	bool done = false;

	if( Evento_IsEmpty( this ) || this->cursor == this->last ){
		done = Evento_InsertBack( this, _data );
	} else {
		nodePtr n = newNode( _data );
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


bool Evento_Remove( dLL* this, itemPtr _data_back )
{
	assert( this );

	bool done = false;

	if( !Evento_IsEmpty( this ) && NULL != this->cursor ){
		done = true; 

		*_data_back = this->cursor->data;

		nodePtr left = this->cursor->prev;
		nodePtr right = this->cursor->next;
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

bool Evento_RemoveFront( dLL* this, itemPtr _data_back )
{
	assert( this );

	bool done = false;

	if( !Evento_IsEmpty( this ) ){
		done = true;
		*_data_back = this->first->data;
		nodePtr tmp = this->first->next;
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

bool Evento_RemoveBack( dLL* this, itemPtr _data_back )
{
    assert(this);
    bool done= false;
    if(!Evento_IsEmpty(this))
    {
        done=true;
        *_data_back=this->last->data;
        nodePtr tmp=this->last->prev;
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

bool Evento_RemoveAfter( dLL* this, itemPtr _data_back )
{
    assert(this);
    bool done=false;
    if(!Evento_IsEmpty(this) && this->cursor!=this->last && this->cursor!=NULL)
    {
        done=true;
        nodePtr tmp1=this->cursor->next;
        *_data_back= this->cursor->next->data;
        
        nodePtr tmp2=tmp1->next;
        free(tmp1);
        this->cursor->next=tmp2;
        if(tmp2!=NULL)
        {
            tmp2->prev=this->cursor;
        }
    }
    return done;
}

bool Evento_RemoveBefore( dLL* this, itemPtr _data_back )
{
    assert(this);
    bool done=false;
    if(!Evento_IsEmpty(this) && this->cursor!=this->first && this->cursor!=NULL)
    {
        done=true;
        nodePtr tmp1=this->cursor->prev;
        *_data_back= this->cursor->next->data;
        
        nodePtr tmp2=tmp1->prev;
        free(tmp1);
        this->cursor->prev=tmp2;
        if(tmp2!=NULL)
        {
            tmp2->next=this->cursor;
        }
    }
    return done;
}

size_t Evento_Len( dLL* this )
{
	assert( this );
	return this->len;
}

bool Evento_IsEmpty( dLL* this )
{
	assert( this );
	return this->first == NULL;
}

void Evento_MakeEmpty( dLL* this )
{
	assert( this );
	while( NULL != this->first){
		nodePtr tmp = this->first->next;
		free( this->first );
		this->first = tmp;
	}
	reset( this );
}

bool Evento_Peek( dLL* this, itemPtr _data_back )
{
    assert(this);
    bool done=false;
    if(!Evento_IsEmpty(this) && this->cursor!=NULL)
    {
        *_data_back=this->cursor->data;
        done=true;
    }
    return done;
}

void Evento_CursorFirst( dLL* this )
{
	assert( this );
	this->cursor = this->first;
}

void Evento_CursorLast( dLL* this )
{
	assert( this );
	this->cursor = this->last;
}

void Evento_CursorNext( dLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->cursor->next;
	}
}

void Evento_CursorPrev( dLL* this )
{
	assert( this );
	if( this->cursor != NULL ){
		this->cursor = this->cursor->prev;
	}
}
//Funciones predicado son funciones que reciben elementos y devuelven un bool
bool Evento_FindIf( dLL* this, item _key,bool (*cmp)(item , item ) )
{
	assert( this );

	bool found = false;
	
	for( nodePtr it = this->first; it != NULL; it = it->next ){
		if( cmp(_key, it->data)){
			found = true;
			break;
		}
	}
	return found;
}

bool Evento_Search( dLL* this, item _key,bool (*cmp)(item , item ) )
{
    assert(this);
    bool found=false;
    if(!Evento_IsEmpty(this))
    {
        for(nodePtr it=this->first;it->next!=NULL;it=it->next)
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

void Evento_Traverse( dLL* this, void (*pfun)(item) )
{
	assert( this );

	for( nodePtr it = this->first; it != NULL; it = it->next ){
		pfun( it->data );
	}
}
