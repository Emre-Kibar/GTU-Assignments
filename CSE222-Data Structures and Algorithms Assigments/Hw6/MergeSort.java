public class MergeSort extends SortAlgorithm {
	
	public MergeSort(int input_array[]) {
		super(input_array);
	}
	
	private void merge(int[] array, int[] leftArr, int[] rightArr){
        int leftArrLength = array.length / 2;
        int rightArrLength = array.length - leftArrLength;
        int resultIndex = 0 , leftArrIndex = 0, rightArrIndex = 0;
        
        //While there are elements in each subarrays, the smaller elements will be put to the main array.
        while(leftArrIndex < leftArrLength && rightArrIndex < rightArrLength){
            if(leftArr[leftArrIndex] < rightArr[rightArrIndex]){
                array[resultIndex++] = leftArr[leftArrIndex++];
            }else{
                array[resultIndex++] = rightArr[rightArrIndex++];
            }
            comparison_counter++; // For each comparison between left and right array,comparison_counter will be incremented.
        }

        //If there are remaining characters in the subarrays they will be put the main array directly.
        while (leftArrIndex < leftArrLength) {
            array[resultIndex++] = leftArr[leftArrIndex++];
        }
        while (rightArrIndex < rightArrLength) {
            array[resultIndex++] = rightArr[rightArrIndex++];
        }
    }

    private void sort(int[] array){
        int length = array.length;
        if(array == null || length <= 1){ //As a recursive function,the base cases are like that. 
            return;
        }

        //The array will be separeted into two part for each recursive step.
        int mid = length / 2;
        int[] leftArr = new int[mid];
        int[] rightArr = new int[length - mid];

        //The left and right arrays are filled using the main array.
        for(int i = 0; i < mid; i++){
            leftArr[i] = array[i];
        }
        for(int i = mid; i < length; i++){
            rightArr[i-mid] = array[i];
        }

        //To sort the left and right parts of the main array, the sort function called recursively.
        sort(leftArr);
        sort(rightArr);

        // After left and right part sorted,by using merge function the main array will be filled orderly.
        merge(array, leftArr, rightArr); 
    }
    
    @Override
    public void sort() {
    	sort(arr);
    }
    
    @Override
    public void print() {
    	System.out.print("Merge Sort\t=>\t");
    	super.print();
    }
}
