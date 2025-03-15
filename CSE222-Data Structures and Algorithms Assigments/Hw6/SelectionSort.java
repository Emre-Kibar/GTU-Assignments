public class SelectionSort extends SortAlgorithm {

	public SelectionSort(int input_array[]) {
		super(input_array);
	}

    @Override
    public void sort() {
        //This loop iterates through every indeces one by one.
        for(int i = 0; i < arr.length - 1; i++){
            int minIndex = i; //The minimum element in each iteration will be initialize as current element.
            //This loop iterates the the remaining elements which comes after the current element. 
            for(int j = i+1; j < arr.length; j++){
                //The minimum element will be found in this if statement within the searched part of array.
                if(arr[j] < arr[minIndex]){
                    minIndex = j; //minIndex will be updated.
                }
                comparison_counter++; //The comparison_counter will be incremented for each minIndex check. 
            }
            //The minIndex element will be swapped the current element to put smaller elements to the beginning of the array.
            swap(i, minIndex); 
        }
    }

    @Override
    public void print() {
    	System.out.print("Selection Sort\t=>\t");
    	super.print();
    }
}
