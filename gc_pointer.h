#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>
#include "gc_details.h"
#include "gc_iterator.h"
/*
    Pointer implements a pointer type that uses
    garbage collection to release unused memory.
    A Pointer must only be used to point to memory
    that was dynamically allocated using new.
    When used to refer to an allocated array,
    specify the array size.
*/
template <class T, int size = 0>
class Pointer{
private:
    // refContainer maintains the garbage collection list.
    static std::list<PtrDetails<T> > refContainer;
    // addr points to the allocated memory to which
    // this Pointer pointer currently points.
    T *addr;
    /*  isArray is true if this Pointer points
        to an allocated array. It is false
        otherwise. 
    */

    bool isArray; 
    // true if pointing to array
    // If this Pointer is pointing to an allocated
    // array, then arraySize contains its size.
    unsigned arraySize; // size of the array
    static bool first; // true when first Pointer is created
    // Return an iterator to pointer details in refContainer.
    typename std::list<PtrDetails<T> >::iterator findPtrInfo(T *ptr);
public:
    // Define an iterator type for Pointer<T>.
    typedef Iter<T> GCiterator;
    // Empty constructor
    // NOTE: templates aren't able to have prototypes with default arguments
    // this is why constructor is designed like this:
    Pointer(){
        Pointer(NULL);
    }
    Pointer(T*);
    // Copy constructor.
    Pointer(const Pointer &);
    // Destructor for Pointer.
    ~Pointer();
    // Collect garbage. Returns true if at least
    // one object was freed.
    static bool collect();
    // Overload assignment of pointer to Pointer.
    T *operator=(T *t);
    // Overload assignment of Pointer to Pointer.
    Pointer &operator=(Pointer &rv);
    // Return a reference to the object pointed
    // to by this Pointer.
    T &operator*(){
        return *addr;
    }
    // Return the address being pointed to.
    T *operator->() { return addr; }
    // Return a reference to the object at the
    // index specified by i.
    T &operator[](int i){ return addr[i];}
    // Conversion function to T *.
    operator T *() { return addr; }
    // Return an Iter to the start of the allocated memory.
    Iter<T> begin(){
        int _size;
        if (isArray)
            _size = arraySize;
        else
            _size = 1;
        return Iter<T>(addr, addr, addr + _size);
    }
    // Return an Iter to one past the end of an allocated array.
    Iter<T> end(){
        int _size;
        if (isArray)
            _size = arraySize;
        else
            _size = 1;
        return Iter<T>(addr + _size, addr, addr + _size);
    }
    // Return the size of refContainer for this type of Pointer.
    static int refContainerSize() { return refContainer.size(); }
    // A utility function that displays refContainer.
    static void showlist();
    // Clear refContainer when program exits.
    static void shutdown();
};

// STATIC INITIALIZATION
// Creates storage for the static variables
template <class T, int size>
std::list<PtrDetails<T> > Pointer<T, size>::refContainer;
template <class T, int size>
bool Pointer<T, size>::first = true;

// Constructor for both initialized and uninitialized objects. -> see class interface
template<class T,int size>
Pointer<T,size>::Pointer(T *t){
    // Register shutdown() as an exit function.
    if (first)
        atexit(shutdown);
    first = false;

    //from lhosszu
    // Create new PtrDetails instance, and push it to the refContainer list
    PtrDetails<T> p_details(t, size);
    refContainer.push_back(p_details);
    //Initialize Pointer member variables
    addr = p_details.memPtr;
    arraySize = p_details.arraySize;
    isArray = p_details.isArray;
    //Find PtrDetails in the refContainer, and increment refcount
    typename std::list<PtrDetails<T>>::iterator p_details_iterator; 
    p_details_iterator = findPtrInfo(addr);
    p_details_iterator -> refcount++;
    //from lhosszu

    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab

}
// Copy constructor.
template< class T, int size>
Pointer<T,size>::Pointer(const Pointer &ob){

    //from lhosszu
    //Initialize member variables for new object, based on ob
    this -> addr = ob.addr;
    this -> arraySize = ob.arraySize;
    this -> isArray = ob.isArray;
    //Find the PtrDetails pointing to that memory address, and increment refcount
    typename std::list<PtrDetails<T>>::iterator p_details_iterator;
    p_details_iterator = findPtrInfo(ob.addr);
    p_details_iterator -> refcount++;
    //from lhosszu


    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab
}

//Destructor for Pointer.   
//Decrement refcount if object goes out of scope
//Free the memory with collect()
template <class T, int size>  //this line is needed before every function built.
Pointer<T, size>::~Pointer(){
    typename std::list<PtrDetails<T> >::iterator p_details;  //p_details ??
    p_details = findPtrInfo(addr);    //p_details???

    //from lhosszu
    if(p_details -> refcount){
        p_details -> refcount--;
    }
    collect();
    //from lhosszu



    //TODO:  Finalize Pointer destructor
    //decrement ref count

    //PtrDetails::refcount--;  //I added needs to be called to gc_details

    //Collect garbage when a pointer goes out of scope

    //For real use, you might want to collect unused memory less frequently,
    //such as after refContainer has reached a certain size, after a certain number of Pointers
    //have gone out of scope, or when memory is low.
}


// Collect garbage. Returns true if at least
// one object was freed.
template <class T, int size>
bool Pointer<T, size>::collect(){
    bool memfreed = false;
    typename std::list<PtrDetails<T> >::iterator p_details;
    do{
        //Scan refContainer looking for unreferenced pointers.
        for (p_details = refContainer.begin(); p_details != refContainer.end(); p_details++){  //p_details, not p??

            //from lhosszu
            if((p_details -> refcount) > 0) continue;   //skip if in use
            memfreed = true;   // memfreed??
            refContainer.remove(*p_details);  //remove the unused entry
            if(p_details -> memPtr != nullptr){
                if(p_details -> isArray){
                    delete[] p_details -> memPtr;
                    } else {
                        delete p_details -> memPtr;
                        }
                        }
            //from lhosszu
        


            //TODO: Implement collect()
            //If in-use, skip.
            //Remove unused entry from refContainer.

            //Free memory unless the Pointer is null.

            //Restart the search.
            break;
        }
    } while (p_details != refContainer.end());   //p_details ??
    return memfreed;    //is_memory_freed??


    //return false;      //this line was in the prewritten, but NOT the lab. memfreed is set to
    //false in the beginning of this function, so if it isn't changed then it will return false
} //DONE


// Overload assignment of pointer to Pointer.
template <class T, int size>
T *Pointer<T, size>::operator=(T *t){

    //from lhosszu
    //Find PtrDetails pointing to the addr, decrement the refcount
    typename std::list<PtrDetails<T>>::iterator p_details;
    p_details = findPtrInfo(addr);
    p_details -> refcount--;
    //Create new object, push it to refContainer and initialize member variables
    PtrDetails<T> p(t, size);
    refContainer.push_back(p);
    addr = p.memPtr;
    arraySize = p.arraySize;
    isArray = p.isArray;
    p_details = findPtrInfo(addr);
    p_details -> refcount++;
    return addr;
    //from lhosszu

    // TODO: Implement operator==
    // LAB: Smart Pointer Project Lab

}
// Overload assignment of Pointer to Pointer.
template <class T, int size>
Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv){
    typename std::list<PtrDetails<T> >::iterator p;

    //from lhosszu
    p = findPtrInfo(addr);
    p -> refcount--;
    p = findPtrInfo(rv.addr);
    p -> refcount++;
    addr = rv.addr;
    return rv;
    //from lhosszu

    // TODO: Implement operator==
    // LAB: Smart Pointer Project Lab
    
}//DONE

// A utility function that displays refContainer.
template <class T, int size>
void Pointer<T, size>::showlist(){
    typename std::list<PtrDetails<T> >::iterator p;
    std::cout << "refContainer<" << typeid(T).name() << ", " << size << ">:\n";
    std::cout << "memPtr refcount value\n ";
    if (refContainer.begin() == refContainer.end())
    {
        std::cout << " Container is empty!\n\n ";
    }
    for (p = refContainer.begin(); p != refContainer.end(); p++)
    {
        std::cout << "[" << (void *)p->memPtr << "]"
             << " " << p->refcount << " ";
        if (p->memPtr)
            std::cout << " " << *p->memPtr;
        else
            std::cout << "---";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
// Find a pointer in refContainer.
template <class T, int size>
typename std::list<PtrDetails<T> >::iterator
Pointer<T, size>::findPtrInfo(T *ptr){
    typename std::list<PtrDetails<T> >::iterator p;
    // Find ptr in refContainer.
    for (p = refContainer.begin(); p != refContainer.end(); p++)
        if (p->memPtr == ptr)
            return p;
    return p;
}
// Clear refContainer when program exits.
template <class T, int size>
void Pointer<T, size>::shutdown(){
    if (refContainerSize() == 0)
        return; // list is empty
    typename std::list<PtrDetails<T> >::iterator p;
    for (p = refContainer.begin(); p != refContainer.end(); p++)
    {
        // Set all reference counts to zero
        p->refcount = 0;
    }
    collect();
}