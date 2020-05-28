#include <math.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>


double results;   //This Stores the sum of 1/(1-a) , 1/(1-b) , 1/(1-c) and so on..
double tempres=0;  //This store the temporary results i.e., 1/(1-a) or 1/(1-b) and all their sum is stored in results
double pow(double x, double y);   //This is the power function



/*
The below two functions addCombination and generateCombination are taken from the below
Link: https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/

These functions have been modified for the current project but the overall skeleton code is taken 
from the above link.

*/


// Program to add all combination of size r in 
// an array of size n 
void addCombination(double arr[], int n, int r, 
					int index, double data[], int i); 



// This function generates all combinations of 
// size r in arr[] of size n. This function mainly 
// uses addCombination() 
void generateCombination(double arr[], int n, int r) 
{ 
	// A temporary array to store all combination 
	// one by one 
	double data[r]; 

	// Print all combination using temprary array 'data[]' 
	addCombination(arr, n, r, 0, data, 0); 
} 


/* arr[] ---> Input Array 
n	 ---> Size of input array 
r	 ---> Size of a combination to be printed 
index ---> Current index in data[] 
data[] ---> Temporary array to store current combination 
i	 ---> index of current element in arr[]	 */
void addCombination(double arr[], int n, int r, int index, 
					double data[], int i) 
{ 
  int j=0;
	// Current cobination is ready, print it 
	if (index == r) { 
		tempres = 0;
		for (j = 0; j < r; j++) 
        {
          tempres += data[j];
        }	
      	results = results + (1/(1-tempres));
		
		return; 
	} 

	// When no more elements are there to put in data[] 
	if (i >= n) 
		return; 

	// current is included, put next at next location 
	data[index] = arr[i]; 
	addCombination(arr, n, r, index + 1, data, i + 1); 

	// current is excluded, replace it with next 
	// (Note that i+1 is passed, but index is not 
	// changed) 
	addCombination(arr, n, r, index, data, i + 1); 
} 




/*
The below two functions findCeil and myRand are taken from the following link:
https://www.geeksforgeeks.org/random-number-generator-in-arbitrary-probability-distribution-fashion/
*/


//This function is used to find the ceil for the given elements in the array
int findCeil(int arr[], int r, int l, int h) 
{ 
    int mid; 
    while (l < h) 
    { 
         mid = l + ((h - l) >> 1);  // Same as mid = (l+h)/2 
        (r > arr[mid]) ? (l = mid + 1) : (h = mid); 
    } 
    return (arr[l] >= r) ? l : -1; 
} 
  
// The main function that returns a random number from arr[] according to 
// distribution array defined by freq[]. n is size of arrays. 
int myRand(int arr[], int freq[], int n) 
{ 
    // Create and fill prefix array 
    int prefix[n], i; 
    prefix[0] = freq[0]; 
    for (i = 1; i < n; ++i) 
        prefix[i] = prefix[i - 1] + freq[i]; 
  
    // prefix[n-1] is sum of all frequencies. Generate a random number 
    // with value from 1 to this sum 
    int r = (rand() % prefix[n - 1]) + 1; 
  
    // Find index of ceiling of r in prefix arrat 
    int indexc = findCeil(prefix, r, 0, n - 1); 
    return arr[indexc]; 
} 
 


// Main program to execute the given functionality 
int main() 
{ 
	int coupons,sum;   //coupons stores number of coupons and sum is used in the PART-2 to store the number of coupons in each simultion

	printf("\nEnter number of coupons:");
	scanf("%d",&coupons);       //Store the number of coupons specied by the user
	
	int frequencies[coupons];    //Array to store frequencies
	double arr[coupons];        //Array to store Probabilities
	int total=0.0;
	printf("Enter Frequency of each coupon:\n");
	int i;
  for(i=0;i<coupons;i++)    //Store the frequencies in the array
	{
	    scanf("%d",&frequencies[i]);
	    total+=frequencies[i];
	
    }

	for(i=0;i<coupons;i++)    //Loop to calculate the probability of each of the coupon
	{
	    arr[i]=((double)frequencies[i]/total);  
	}
	

  //Set of variables to store partial result in each phase of the program execution
	int r = coupons-1; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	double combination_res = 0;
	double product=0;
	double final_result=0;   //This is the variable which stores the final result
	int flag;
  int q;      //This is the same q used in the formula provided in the project document
	for(q=0; q<=r;q++ )    //Outer loop that calculates the formula specified in the document provided by professor
    {
			flag = 0;
      results = 0;
			combination_res=0;
      generateCombination(arr, n, q);             //This Funciton generates the 1/(1-a) , 1/(1-b) , 1/(1-c) and so on.. and sums each of them  and stores the result in the results.
    
      product = pow(-1,coupons-1-q);   //Temp variable to store the value of (-1)^(m-1-q) according to the Lab assignment 1 document provided by the professor
      product*=results;   //This product is multiplied by results. This can be visualized as (-1)*(1/(1-a) + 1/(1-b) + 1/(1-c))
      final_result += product;   //All these partial results are summed up and stored in the final_result variable
    }
    
    printf("\nTheoretically predicted # of soap boxes = %lf ",final_result);



		//========================================PART2=============================================

	 int seed=0;
   int empirical=0;
	 
	 printf("\nEnter # of iterations for empirical:\n");
   scanf("%d",&empirical);

   printf("Enter seed:\n");
   scanf("%d",&seed);

   /* Intializes random number generator */
   srand(seed);
   int couponsCollected[coupons];
   int noCouponInEachItr[empirical];
 
	int couponarr[coupons];

for(i=0;i<coupons;i++)   //This generates the coupon numbers from 1 to coupons 
{
    couponarr[i] = i+1;
}

  n = sizeof(couponarr) / sizeof(couponarr[0]); 



    int iterations = 0;
    int tempval=0;

     while(iterations<empirical) {   //While the number of iteration < Empirical i.e., 0 to empirical
       tempval = 0;
       for(i=0;i<=coupons;i++)
       {
           couponsCollected[i]=0;    //Initially all the coupons are 0 i.e., We dont have any coupons during the start of simulation
       }
       
       
      while(1){  
          tempval++;
          sum=0;
      if( 1 ) 
      { int t;
          for(t=0;t<=coupons;t++)     //Loop to calculate the number of collected coupons in the current simulation
          {
              if(couponsCollected[t]==1)
              {
                    sum+=1;       
              }
          }
          
          if(sum==coupons) //If all the coupons are collected then stop the iteration and break the loop
            {
                break;   
            }
      }//OUTER IF CLOSE
      
      int number = myRand(couponarr, frequencies, n);   //Generating  a random number using the given coupon array and the frequencies for each element
      
      couponsCollected[number] = 1;   //Whenever we collect a coupon we set that index to 1. This is done to indicate that we collected a coupon.
      }
      
      
      noCouponInEachItr[iterations] = tempval-1;     //Number Of coupons In each Iteration is stored in the Array "noCouponInEachItr"
      iterations++;
      
   }
   
   
   float mean=0;
   
   for(i=0;i<empirical;i++)
   {
       mean+=noCouponInEachItr[i];   //Calculation the total of all the coupons in all the iterations.
   }
  mean = (mean/empirical);   
   printf("Empirically predicted # of soap boxes = %f\n", mean);

	 return 0; 
} 


