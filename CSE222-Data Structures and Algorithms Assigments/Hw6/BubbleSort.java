public class BubbleSort extends SortAlgorithm {

	public BubbleSort(int input_array[]) {
		super(input_array);
	}
	
    @Override
    public void sort() {
        //This loop iterates through the every element one by one.
        for(int i = 0; i < arr.length - 1; i++){
            //isSwapped variable hold the value of "is swap occured in this step", if swap not occured this means this array is sorted right now.
            boolean isSwapped = false; 
            
            //This loop iterates through the subarray which is limited with "i" value. 
            for(int j = 0; j < arr.length - i - 1; j++){
                //The bubbled consecutive elements will be swapped to put greater element at the end.
                if(arr[j] > arr[j + 1]){
                    swap(j, j+1); //If smaller indexed element is greater this bubbled pair will swapped to put greater element at the end.
                    isSwapped = true; //If swap is occured this means for this iteration array wasnt sorted.
                }
                comparison_counter++; //The comparison_counter will be incremented for each bubled pair comparison. 
            }
            
            if(!isSwapped){ //If isSwapped is false that means for this iteration array was sorted and no need to continue to sort.
                break;
            }
        }
    }
    
    
    @Override
    public void print() {
    	System.out.print("Bubble Sort\t=>\t");
    	super.print();
    }
}
