public class QuickSort extends SortAlgorithm {

	public QuickSort(int input_array[]) {
		super(input_array);
	}
	
    private int partition(int[] array, int start, int end){
        int pivot = array[end]; // The last element choosed as pivot element initiallly.
        int i = start - 1; //Auxillary index to swap the smaller elements with greater elements based on pivot element.
        
        //This loop iterates through start to end-1.
        for(int j = start; j < end; j++){
            //To make sure that the greater elements than pivot element set after the smaller elements, checking the pivot and current "j" indexed element and 
            //if pivot is greater than current element than swap current element with "i" indexed element which is greater than pivot. 
            if(array[j] < pivot){
                i++;
                swap(i, j);
            }
            comparison_counter++; //Increment the comparision_counter for each iteration 
        }
        
        //After the loop finished pivot element will be put to the index "i" because before the index "i" all elements is smaller and after that all elements is greater.
        i++;
        swap(i, end);
    
        return i; //Return pivot index which separate the array into to parts.
    }
    

    private void sort(int[] array, int start, int end){
        //As the base case, if end index less than start index then return.
        if(end <= start){
            return;
        }

        // By using partition method the pivot index will be found.
        int pivot = partition(array, start, end);
        //By using the pivot point, the subarrays that are limited by pivot will be sorted.
        sort(array, start, pivot-1);
        sort(array, pivot+1, end);
    }

    @Override
    public void sort() {
    	sort(arr, 0, arr.length-1); //The actual sort method will be called.
    }

    @Override
    public void print() {
    	System.out.print("Quick Sort\t=>\t");
    	super.print();
    }
}
