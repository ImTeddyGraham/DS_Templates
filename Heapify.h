#ifndef QUALITY_HEAP
#define QUALITY_HEAP

template<typename T>
class heap {
    public:
        void heapify(T *a[], int index=0);
        T* pop(T *a[]);
        heap(int c = 0, int l = 0, bool m = true) : capacity(c), last_index(l), minheap(m){};

        int capacity; //  TOTAL SPACE 
        int last_index; //  SPACE IN USE 
        bool minheap; //  HEAP TYPE
};
//  THIS FUNCTION TAKES IN AN ARRY OF POINTERS AND TURNS IT INTO A BINARY HEAP
template<typename T>
void heap<T>::heapify(T *arr[], int curr_index) {
    //  OUT OF BOUNDS
    if (curr_index < 0 || last_index < 2*curr_index+1 ) {
        return;
    }
    
    //  DEFAULTS TO LEFT; ALWAYS IN BOUNDS
    T *min_or_max = arr[2*curr_index+1];
    int swap_index = 2*curr_index+1;

    //  IF RIGHT CHILD IS IN RANGE
    if (2*curr_index+2 <= last_index) {
        // FINDS MAX OR MIN CHILD, HOLDS IN TEMP 
        if (minheap) { //  FINDING MIN
            if (arr[2*curr_index+2]->priority < arr[2*curr_index+1]->priority) {
                min_or_max = arr[2*curr_index+2];
                swap_index = 2*curr_index+2;
            }
        } else { //  FINDING MAX
            if (arr[2*curr_index+1]->priority < arr[2*curr_index+2]->priority) {
                min_or_max = arr[2*curr_index+2];
                swap_index = 2*curr_index+2;
            }
        }
    }

    //  COMPARE MAX OR MIN CHILD TO PARENT
    //  SWAPS IF NECESSARY AND VERIFIES PARENTS ARE STILL IN HEAP ORDER 
    if (minheap) {
        if (min_or_max->priority < arr[curr_index]->priority) {
            arr[swap_index] = arr[curr_index];
            arr[curr_index] = min_or_max;
            heapify(arr, (curr_index-1)/2);
        }
    } else {
        if (arr[curr_index]->priority < min_or_max->priority){
            arr[swap_index] = arr[curr_index];
            arr[curr_index] = min_or_max;
            heapify(arr, (curr_index-1)/2);
        }
    }
    heapify(arr, ++curr_index);
}

template<typename T>
T* heap<T>::pop(T* arr[]){
    if (last_index < 0 || capacity < 1) {
        //Going to ommit this for the time being
        // throw ()
    }
    //  SWAPS VALUES TO ENSURE NO MEMORY LEAKS 
    T *temp = arr[0];
    arr[0] = arr[last_index--];
    arr[last_index+1] = temp;

    //  ENSURES HEAP PROPERTY IS MAINTAINED 
    heapify(arr);
    return temp;
}

#endif