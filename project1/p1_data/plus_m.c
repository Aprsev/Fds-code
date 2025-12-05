# include<stdio.h>
# include<stdlib.h>                         //For the random function
# include<time.h>
clock_t start1,stop1,start2,stop2;          //To record the start and end time of functions
double duration1,duration2;                 //duration1 to count the time of function1,duration2 to count the time of function2
int ticks1,ticks2;

int* generate_array_of_n(int n,int max_num);//A function to generate random data for functions
void print_list(int* arr,int n);                  //A function to print the list member out to help find a proper sum input

int brute_force_search(int* arr,int sum,int n);            //Definition of function1
int div_con(int* arr,int sum,int left_p,int right_p,int count);            //Definition of function2

int main(void){
    // int n,max_num;                          //n represents the size of data,max_sum represents the integers won't be larger than it
    // printf("Please input the size and max of the number(split them with a space):");
    // scanf("%d %d",&n,&max_num);             //Input manual to contrl different situation
    int* arr;                               //The target arr
    int res1,res2;                          //res1,res2 to note whether the function find the a and b
    int n_val[9] = {1000,5000,10000,20000,40000,60000,80000,100000,1000000};
    int max_num_val[8] = {1000,5000,10000,20000,40000,60000,80000,100000};
    for (int k = 0;k < 8; k++){
        for (int q = 0;q < 9;q++){
            int n = n_val[q];
            int max_num = max_num_val[k];
            arr = generate_array_of_n(n,max_num);   //Generate the random array
            printf("The random array generate successfully!\n");
                                                    //Show the generate step process well
            // printf("If you want to see the detail numbers , please enter number 1(or will skip it)!!!only use it when N is quite small:");
            // int flag;                               //Use a flag to check if the tester want to see the array 
            // scanf("%d",&flag);                      
            // if(flag == 1){                          //If you want to see the randomly generated array input 1 or input any number else
            //     print_list(arr,n);                  //Print the whole list
            // }

            int sum;                               //Take the targeted sum of algorithm

            srand((unsigned int)time(NULL));        //Initialize rand seed
            start1 = clock();                       //Mark the starting time of function1
            for (int i = 0; i < 10000; i++){        //Please change loop number if needed
                int k = rand() % n;                 //To ensure the sum is working,I choose to randomly select 2 element to calculate the sum 
                int j = rand() % n;
                sum = arr[k] + arr[j];
                res1 = brute_force_search(arr, sum, n); //Get the return result
            }       //Operate the function1 for K times(I'll set it without input)
            stop1 = clock();                          //Mark the starting time of function2
            ticks1 = (int)(stop1-start1);             //Calculate the running ticks
            duration1 = ((double)(stop1 -start1))/CLK_TCK;//Calculate the running time

            start2 = clock();                       //Mark the starting time of function2(actually all the same below)
            for (int i = 0; i < 10000; i++){        //Please change loop number if needed
                int k = rand() % n;                 //Same in function1
                int j = rand() % n;
                sum = arr[k] + arr[j];
                res2 = div_con(arr, sum, 0, n-1,i);//Get the return result
            }
            stop2 = clock();
            ticks2 = (int)(stop2-start2);
            duration2 = ((double)(stop2 -start2))/CLK_TCK;//Calculate the running time 

            if (res1 == 1 && res2 == 1){           //Check if both find the a and b
                //Print the ticks and duration of the two functions
                printf("%d and %d:\n",n,max_num);
                printf("The operation of  function1(Brute-force) is: %e (s)and %d ticks\n",duration1,ticks1);
                printf("The operation of function2(Divide and conquer) is: %e (s)and %d ticks\n",duration2,ticks2);
                                                //Print out the result
            }else if(res1 != 1){
                printf("Function1 failed");        //If function1 failed
            }else if(res2 != 1){
                printf("Function2 failed");        //If function2 failed
            }else{
                printf("Both failed");             //If both failed
            }
        }
    }
    return 0;
}

int* generate_array_of_n(int n,int max_num){
    int* arr = (int*)malloc(n * sizeof(int));//Create a new array to contain numbers
    if(arr == NULL){                       //Check the location
        printf("Memory allocation failed\n");
        exit(1);                            //If malloc failed exit the program
    }
    srand((unsigned int)time(NULL));       //Initialize random seeds
    for (int i = 0;i < n;i++){
        arr[i] = rand() % (max_num+1);     //Use % to contrl the numbers are no more than max_num
    }
    return arr;
}

void print_list(int* arr,int n){        //Print the array randomly generated
    for (int i = 0;i < n;i++){          //Go through all integers
        printf("%d ",arr[i]);
        if (i % 30 == 29)               //30 integers each line
            printf("\n");
    }
}

int brute_force_search(int* arr,int sum,int n){
    int res = 0;                        //Mark if the function find the answer
    for (int i = 0;i < n;i++){          //Go through every possible group
        for (int j = i+1;j < n;j++){
            if (arr[i] + arr[j] == sum){//Check the sum
                res = 1;
                return res;             //Target found
            }
        }
    }
    return res;                         //Target not found
}
int div_con(int* arr,int sum,int left_p,int right_p,int count){
    int res = 0;                        //Mark if the function find the answer
    if((right_p - left_p) > 20){        //Only start brute-force searching when subset is smaller than 20
        int mid = (right_p + left_p)/2; //Find the mid index
        int res_left,res_right;         //Mark result of left and right part search
        res_left = div_con(arr, sum, left_p, mid, count);
        if(res_left == 1){              //Check if there's answer in the left half first
            res = 1;                    //If answer found in the left half,skip right half and return til the main function
            return res;
        }
        res_right = div_con(arr, sum, mid, right_p, count);
        if(res_right == 1){             //If there's no answer in the left half,then check the right half
            res = 1;                    //Same above
            return res;
        }
    }
    for(int i = left_p;i < right_p;i++){//When the size of subset is small enough,deploy brute search
        for(int j = i+1;j < right_p;j++){
            if(arr[i] + arr[j] == sum){
                res = 1;
                return res;             //Target found
            }
        }
    }
    
    return res;                         //Target not found
}
