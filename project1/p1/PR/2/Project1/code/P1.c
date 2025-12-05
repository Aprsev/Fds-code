#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

// Iterative version of Binary Search
int Iterative_Version_Of_Binary_Search(int a[],int N,int left,int right){
	int mid;
	while(left<=right){ // Keep searching as long as the left pointer is less than or equal to the right pointer
		mid=(left+right)/2;
		if (a[mid]==N) {
			return mid; // If the element is found at the middle index, return the index
		} 
		else if (a[mid]<N) {
			left=mid+1; // If the middle element is smaller, move the left pointer
		}
		else {
			right=mid-1; // If the middle element is larger, move the right pointer
		}
	}
	return -1;// Return -1 if the element is not found
}

// Recursive version of Binary Search
int Recursive_Version_Of_Binary_Search(int a[],int N,int left,int right){
	if (left>right){
		return -1; // Base case: if the left pointer is greater than the right, the element is not found
	}
	int mid=(left+right)/2;
	if (a[mid]==N) return mid; // If the element is found, return the index
	if (a[mid]<N){
		return Recursive_Version_Of_Binary_Search(a,N,mid+1,right); // If the middle element is smaller, search the right half recursively
	}
	else{
		return Recursive_Version_Of_Binary_Search(a,N,left,mid-1); // If the middle element is larger, search the left half recursively
	}
}

// Iterative version of Sequential Search
int Iterative_Version_Of_Sequential_Search(int a[],int N,int left,int right){
	int i;
	for (i=left;i<=right;i++){ // Loop through the array from left to right
		if (a[i]==N) {
			return i; // If the element is found, return the index
		}
	}
	return -1; // Return -1 if the element is not found
}

// Recursive version of Sequential Search
int Recursive_Version_Of_Sequential_Search(int a[],int N,int left,int right){
	if (left>right) return -1; // Base case: if the left pointer is greater than the right, the element is not found
	if (a[left]==N){
		return left; // If the element is found at the left pointer, return the index
	}
	return Recursive_Version_Of_Sequential_Search(a,N,left+1,right); // Recursive call by moving the left pointer to the right

}

// Function to allow the user to choose the search algorithm
void Function_choice(int (**Function)(int a[], int N, int left, int right),char *Func_Name){
	int choice;
	
	// Display the options for the user to choose the search algorithm
	printf("Choose search algorithm:\n");
	printf("0. exit\n");
    printf("1. Iterative version of Binary Search\n");
    printf("2. Recursive version of Binary Search\n");
    printf("3. Iterative version of Sequential Search\n");
    printf("4. Recursive version of Sequential Search\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    printf("\n");
    
    // Set the function pointer to the chosen search algorithm
    switch(choice){
    	case 1:{
    		*Function=Iterative_Version_Of_Binary_Search;
    		strcpy(Func_Name,"Iterative version of Binary Search");
			break;
		}
		case 2:{
			*Function=Recursive_Version_Of_Binary_Search;
    		strcpy(Func_Name,"Recursive version of Binary Search");
			break;
		}
		case 3:{
			*Function=Iterative_Version_Of_Sequential_Search;
    		strcpy(Func_Name,"Iterative version of Sequential Search");
			break;
		}
		case 4:{
			*Function=Recursive_Version_Of_Sequential_Search;
    		strcpy(Func_Name,"Recursive version of Sequential Search");
			break;
		}
		default :{
			exit(0); // Exit the program if the user input 0 or other invalid input
		}
	}
}

int main(){
	clock_t start,stop;
	double duration;
	int N,K,i,a[10005],cnt;
	char Func_Name[100];
	int (*Function)(int a[], int N, int left, int right);
	
	// Initialize the array with values from 0 to 10004
	for (i=0;i<10005;i++){
		a[i]=i;
	}
	
	while (1){
		Function_choice(&Function,Func_Name); // Get user's choice of algorithm
		printf("Enter list size (N): ");
		scanf("%d",&N); // Read the list size
		printf("Enter number of iterations (K): ");
		scanf("%d",&K); // Read the number of iterations
		
		// Start measuring time
		start=clock();
		for(i=0;i<K;i++){
			Function(a,N,0,N-1); // Call the chosen search algorithm
		}
		stop=clock(); // Stop measuring time
		
		duration=((double)(stop-start))/CLK_TCK;// Calculate total duration
		
		if (Function(a,N,0,N-1)!=-1){
			printf("Algorithm Error!\n"); // Check for any errors
		}
		else {
			// Print the results
			printf("%s: N=%d, K=%d, Ticks=%d, Total_time=%lf, Duration=%.12lf\n\n",Func_Name,N,K,stop-start,duration,duration/K);
		}
	}
	
	return 0;
}