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
    bool isArray = false; // true if pointing to array     //added = false
    /* If memPtr is pointing to an allocated
       array, then arraySize contains its size */
    unsigned arraySize; // size of array
    // Here, mPtr points to the allocated memory.
    // If this is an array, then size specifies
    // the size of the array.


    //from lhosszu
    PtrDetails(T *ptr, unsigned int size = 0){ 

        // TODO: Implement PtrDetails

        this -> memPtr = ptr;
        this -> refcount = 1;
        this -> arraySize = size;
        if(size > 0){
            isArray = true;
        }
    }  //from lhosszu
};



// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template <class T>  //this line is needed before every function built
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    // TODO: Implement operator==
    //I added this
    return (ob1.memPtr == ob2.memPtr);

}