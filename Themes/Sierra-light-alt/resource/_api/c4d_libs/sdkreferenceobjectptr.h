#ifdef	REFERENCEOBJECTPTR_H__

#define	SDKReferenceObjectPtr	ReferenceObjectPtr

#else
#ifndef __SDKReferenceObjectPtr__
#define __SDKReferenceObjectPtr__

#include <stddef.h>

/*
	Reference Object Pointer template for automatic destruction of unused objects.
	Simultaneous access to a SDKReferenceObjectPtr from different threads must be
	synchronized because the assignment operators are not atomic.
*/

class SDKReferenceObjectBasePtr
{
protected:
	SDKReferenceObject	*itf;
};


template <class ObjectInterface> class SDKReferenceObjectPtr : public SDKReferenceObjectBasePtr
{
public:

	//----------------------------------------------------------------------------------------
	// Initialize a new reference object
	// Function result:		-
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr()
	{
		itf = nullptr;
	}

	//----------------------------------------------------------------------------------------
	// Initialize a new reference object with reference data from an existing object
	// Function result:		-
	// src:								reference object containing an interface pointer
	//----------------------------------------------------------------------------------------
	inline SDKReferenceObjectPtr( const SDKReferenceObjectPtr &src )
	{
		if ( src.itf )
			src.itf->add_reference();															// there is an additional reference to the interface
		itf = src.itf;																					// get pointer
	}

	//----------------------------------------------------------------------------------------
	// Initialize a new reference object with reference data from an existing object
	// This constructor is for assignment from a different type of SDKReferenceObjectPtr without
	// use of additional pointer casts
	// Function result:		-
	// src:								reference object containing an interface pointer
	//----------------------------------------------------------------------------------------
	inline SDKReferenceObjectPtr( const SDKReferenceObjectBasePtr &src )
	{
		if ( ((SDKReferenceObjectPtr&) src).itf )
			((SDKReferenceObjectPtr&) src).itf->add_reference();															// there is an additional reference to the interface
		itf = ((SDKReferenceObjectPtr&) src).itf;																					// get pointer
	}

	//----------------------------------------------------------------------------------------
	// Assign a null pointer to a new reference object
	// Function result:		-
	// zero:							0
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr( int zero )
	{
		itf = nullptr;
	}

	//----------------------------------------------------------------------------------------
	// Initialize a new reference object with an interface/class pointer
	// Function result:		-
	// src_itf:						interface pointer
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr( const ObjectInterface *src_itf )
	{
		if ( src_itf )
			((ObjectInterface *) src_itf)->add_reference();				// there is an additional reference to the interface

		itf = (ObjectInterface *) src_itf;
	}

	//----------------------------------------------------------------------------------------
	// Destroy reference object, remove reference to the interface
	// Function result:		-
	//----------------------------------------------------------------------------------------
	~SDKReferenceObjectPtr()
	{
		if ( itf )
			itf->remove_reference();															// remove reference to the interface

		itf = nullptr;
	}

	//----------------------------------------------------------------------------------------
	// Function result:		pointer to the interface
	//----------------------------------------------------------------------------------------
	inline ObjectInterface	*GetPtr( void ) const
	{
		return((ObjectInterface *) itf );
	}

	//----------------------------------------------------------------------------------------
	// Remove a reference
	// Function result:		*this
	// zero:							0
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr&	operator=( int zero )
	{
		SDKReferenceObject	*old_itf;

		old_itf = itf;
		itf = (ObjectInterface *) 0;														// assign the new pointer

		if ( old_itf )
			old_itf->remove_reference();													// remove reference to the object

		return( *this );
	}

	//----------------------------------------------------------------------------------------
	// Assign a reference to an already intialized reference object
	// Function result:		*this
	// src:								reference object containing an interface pointer
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr&	operator=( const SDKReferenceObjectPtr &src )
	{
		SDKReferenceObject	*old_itf;

		old_itf = itf;
		itf = src.itf;																					// assign the new pointer

		if ( itf )
			itf->add_reference();																	// add another reference to the new object
		if ( old_itf )
			old_itf->remove_reference();													// remove reference to the previous object

		return( *this );
	}

	//----------------------------------------------------------------------------------------
	// Assign a reference to an already intialized reference object
	// This operator is for assignment from a different type of SDKReferenceObjectPtr without
	// use of additional pointer casts
	// Function result:		*this
	// src:								reference object (of a different type)  containing an interface pointer
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr&	operator=( const SDKReferenceObjectBasePtr &src )
	{
		SDKReferenceObject	*old_itf;

		old_itf = itf;
		itf = ((SDKReferenceObjectPtr&) src).itf;								// assign the new pointer

		if ( itf )
			itf->add_reference();																	// add another reference to the new object
		if ( old_itf )
			old_itf->remove_reference();													// remove reference to the previous object

		return( *this );
	}

	//----------------------------------------------------------------------------------------
	// Assign a reference to an already intialized reference object
	// Function result:		*this
	// src_itf:						interface pointer
	//----------------------------------------------------------------------------------------
	SDKReferenceObjectPtr&	operator=( ObjectInterface *src_itf )
	{
		SDKReferenceObject	*old_itf;

		old_itf = itf;
		itf = src_itf;																					// assign the new pointer

		if ( src_itf )
			src_itf->add_reference();															// add another reference to the new object
		if ( old_itf )
			old_itf->remove_reference();													// remove reference to the previous object

		return( *this );
	}

	//----------------------------------------------------------------------------------------
	// Return the object pointer
	// Function result:		pointer to the interface
	//----------------------------------------------------------------------------------------
	inline operator ObjectInterface*( void ) const
	{
		return((ObjectInterface *) itf );
	}

	//----------------------------------------------------------------------------------------
	// override the -> operator (make the SDKReferenceObjectPtr look like a real pointer)
	// Function result:		pointer to the interface
	//----------------------------------------------------------------------------------------
	inline ObjectInterface	*operator->( void ) const
	{
		return((ObjectInterface *) itf );
	}

	//----------------------------------------------------------------------------------------
	// compare reference and object pointer
	// Function result:		...
	//----------------------------------------------------------------------------------------
	inline Bool operator ==( ObjectInterface *x  ) const
	{
		return((ObjectInterface *) itf == x );
	}

	//----------------------------------------------------------------------------------------
	// Tell us wheter an interface has been assigned
	// Function result:
	//----------------------------------------------------------------------------------------
	inline Bool	IsNull( void ) const
	{
		return( itf == nullptr );
	}
};

#endif
#endif

