
#pragma once

#include <stdlib.h>

#define CORE_API

/**
*  @brief
*    Singleton template
*
*  @remarks
*    If you want to export a class based on this template by creating e.g. a dynamic library, you have to explicitly
*    instantiate that template class, so that the compiler can import it instead of creating an own class base
*    on the class template. If you don't do this, a call to ::GetInstance() will result in different objects
*    being created for each module, e.g. the library will then get another Singleton-instance than an application using
*    that library. This is of course not desired.
*    Please note that the example above may not be compatible with each legacy compiler like GCC 4.2.1 used on Mac OS X 10.6.
*    -> The C++11 feature "extern template" (C++11, see e.g. http://www2.research.att.com/~bs/C++0xFAQ.html#extern-templates) can only be used on modern compilers like GCC 4.6
*    -> In PixelLight itself, we can't break legacy compiler support, especially when only the singletons are responsible for the break
*    -> As workaround, singleton implementations adding "GetInstance()" and "HasInstance()" within their interface
*
*  @note
*    - As the class same indicates, this is an implementation of the singleton design pattern
*    - Do only use singletons, if they *really* make sense - not just because it's comfortable to have a global instance, this may lead to a shaky design...
*/
template <class AType> class CORE_API Singleton
{
public:
	/**
	*  @brief
	*    Returns the class instance
	*
	*  @return
	*    Pointer to the instance, assumed to be never a null pointer
	*
	*  @note
	*    - Returns a pointer to the singleton instance.
	*      The instance will be created if it has not been created before.
	*    - The returned pointer can be a null pointer if the instance has already
	*      been destroyed, that is on deinitialization of the program.
	*      So be careful when using a singleton during deinitialization
	*      of the program, or better - don't do it :-)
	*/
	static AType *GetInstance();

	/**
	*  @brief
	*    Returns whether or not there's an instance
	*
	*  @return
	*    'true' if there's an instance, else 'false'
	*/
	static bool HasInstance();


	static void Create();
	static void Destroy();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
protected:
	/**
	*  @brief
	*    Constructor
	*/
	Singleton();

	/**
	*  @brief
	*    Destructor
	*/
	virtual ~Singleton();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
private:
	/**
	*  @brief
	*    Destruction guard, deletes a singleton on deinitialization
	*/
	class __Destruction_Guard {
	public:
		__Destruction_Guard()
		{
		}
		~__Destruction_Guard()
		{
			if (Singleton<AType>::__Instance) {
				// Don't use reinterpret_cast in here or hell breaks loose when starting programs
				delete static_cast<Singleton<AType>*>(Singleton<AType>::__Instance);
			}
		}
		inline void init() {}
	};

	// Static data
	static __Destruction_Guard __Guard;	/**< Destroys the object on shutdown */
	static AType *__Instance;			/**< Pointer to the singleton instance, can be a null pointer */
	static bool __Destroyed;			/**< Destruction flag - set only on shutdown */

	// Undefined methods to prevent usage
	Singleton(const Singleton&);
	Singleton& operator =(Singleton);


};

template <class AType> typename Singleton<AType>::__Destruction_Guard Singleton<AType>::__Guard;
template <class AType> AType *Singleton<AType>::__Instance = NULL;
template <class AType> bool   Singleton<AType>::__Destroyed = false;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the class instance
*/
template <class AType> AType *Singleton<AType>::GetInstance()
{
	// [HACK] This is necessary for the compiler to instantiate __Guard
	__Guard.init();

	// Check if the instance must be created
	if (!__Instance && !__Destroyed) {
		// Create instance
		return new AType();
	}
	else {
		// Return instance
		return __Instance;
	}
}


template <class AType>
void Singleton<AType>::Create()
{
	Singleton<AType>::GetInstance();
}


template <class AType>
void Singleton<AType>::Destroy()
{
	delete static_cast<Singleton<AType>*>(Singleton<AType>::__Instance);
}


/**
*  @brief
*    Returns whether or not there's an instance
*/
template <class AType> bool Singleton<AType>::HasInstance()
{
	return (__Instance != NULL);
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
template <class AType> Singleton<AType>::Singleton()
{
	// Register instance - Don't use reinterpret_cast in here or hell breaks loose when starting programs
	__Instance = static_cast<AType*>(this);
}

/**
*  @brief
*    Destructor
*/
template <class AType> Singleton<AType>::~Singleton()
{
	// Unregister instance
	if (__Instance == this) {
		__Instance = NULL;
		__Destroyed = true;
	}
}
