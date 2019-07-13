// This class defines an element that is stored      //I completed.  removed dash from begin of line
// in the garbage collection information list.
//
template <class T>
class PtrDetails
{
  public:
    unsigned refcount; // current reference count
    T *memPtr;         // pointer to allocated memory
    /* isArray is true if memPtr points
to an allocated array. It is false
otherwise. */
    bool isArray; // true if pointing to array
    /* If memPtr is pointing to an allocated
array, then arraySize contains its size */
    unsigned arraySize; // size of array
    // Here, mPtr points to the allocated memory.
    // If this is an array, then size specifies
    // the size of the array.

    PtrDetails(void)
    {
        // TODO: Implement PtrDetails
    }
};
// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>  //this line is needed before every function built
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    // TODO: Implement operator==
    //I added
    return (ob1.memPtr == ob2.memPtr);
}

template <class T, int size> //this line is needed before every function built
Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv){
    typename std::list<PtrDetails<T> >::iterator p;
}

//Collect garbage.  Returns true if at least one object was freed.
template <class T, int size>  //this line is needed before every function built
bool Pointer<T, size>::collect(){
    bool memfreed = false;
    typename std::list<PtrDetails<T> >::iterator p;
    do{
        //Scan refContainer looking for unreferenced pointers.
        for (p = refContainer.begin(); p != refContainer.end(); p++){
            //TODO: Implement collect()
            //If in-use, skip.

            //Remove unused entry from refContainer.

            //Free memory unless the Pointer is null.

            //Restart the search.
            break;
        }

    } while (p != refContainer.end());
    return memfreed;
}

//Destructor for Pointer.
template <class T, int size>  //this line is needed before every function built.
Pointer<T, size>::~Pointer(){
    typename std::list<PtrDetails<T> >::iterator p;
    p = findPtrInfo(addr);

    //TODO:  Finalize Pointer destructor
    //decrement ref count

    refcount--;  //I added

    //Collect garbage when a pointer goes out of scope

    //For real use, you might want to collect unused memory less frequently,
    //such as after refContainer has reached a certain size, after a certain number of Pointers
    //have gone out of scope, or when memory is low.
}

