//Name: Abdulla Sakallah                        Student ID: 1001846204

//Complilation Instructions on Omega:-

// gcc aws6204.c
// ./a.out < data.txt

#include <stdio.h>
#include <stdlib.h>


//creating a struct to hold values of times for washer,dryer and storing the index and the key to the smallest value.
typedef struct wd
{
    int key; //smallest keys
    int w; // times of washers
    int d; // times of dryer
    int index; //index per each dryer and washer
} wd;

wd * basket; //array of structs 
int size; //size of array


//This function takes two integers as parameters and returns 1 if they are less and 0 if not
int isLessThan(int a,int b)
{
    int ret = 0;
    if(a<b)
    {
        ret = 1;
    }

    return ret;
}

//This function is used in quick sort, and it compares two elements
int compare (const void * x, const void * y)
{
   return  *(int*)x > *(int*)y;
}

//This function gets the smallest key values and does the qsort()
//======================
//Global variables USED: 
//======================
//basket, size
void sortTimes()
{
    int i=0;

    for(i=0;i<size;i++)
    {
        if(isLessThan(basket[i].w, basket[i].d))
        {
            basket[i].key = basket[i].w;
        }
        else if(!isLessThan(basket[i].w, basket[i].d))
        {
            basket[i].key = basket[i].d;

        }
        else
        {
            basket[i].key = basket[i].w;

        }
    }

    qsort(basket,size,sizeof(wd),compare);





}
//This function perform Johnson's Rule without taking any parameters and returns a wd pointer of the struct to print out the result,
//and this function doesn't return anything
//======================
//Global variables USED: 
//======================
//basket, size
wd * johnsonRule(void)
{
    int i=0,k=0,j=0;
    int n = size-1;

    wd * jon = (wd*) malloc(sizeof(wd)*size);

    for(i=0; i<size; i++)
    {
        if(isLessThan(basket[i].w, basket[i].d) || basket[i].w == basket[i].d)
        {
            if(&jon[k]!=NULL)
            {

                jon[k] = basket[i];
                k++;
            }
            
        }
                
        else if(!isLessThan(basket[i].w, basket[i].d))
        {
            if(&jon[size-j-1]!=NULL)
            {
                jon[size-j-1] = basket[i];
                j++;
            }
        }

    }


    return jon; //returning a struct pointer holding values that had Johnson Rule applied to them
}

//This function reads input from file, it doesn't take any parameters and it doesn't return anything
//======================
//Global variables USED: 
//======================
//basket, size
void getInput(void)
{
    int i=0;
    
    scanf("%d",&size);

    basket = malloc(sizeof(wd)*size);
    

    

    for(i=0; i<size; i++)
    {
        scanf("%d %d",&basket[i].w,&basket[i].d);
        basket[i].index = i;
    }


    sortTimes(); //getting the smaller key value between the 2 machines to perform qsort()

}

//This function takes a struct pointer and prints out the result of the Johnson Rule with doing calculations on how to get 
//the dryend times and the makespan with indicating if there are any gaps and it doesn't return anything
//======================
//Global variables USED: 
//======================
//size
void printResult(wd *p)
{
    int i=0;
    int washStart[size];
    int washEnd[size];
    int washCounter=0;

    int dryStart[size];
    int dryEnd[size];
    int dryCounter=0;

    washStart[0] = 0;
    washEnd[0] = p[0].w;
    washCounter = 0;

    dryStart[0] = washEnd[0];
    dryEnd[0] = washEnd[0] + p[0].d;
    dryCounter = p[0].w;
    
    printf("%d %d %d %d %d\n",p[i].index,p[i].w,p[i].d,washCounter,dryCounter);

    for(i=1; i<size; i++)
    {
        washStart[i] = washEnd[i-1];
        washEnd[i] = washStart[i] + p[i].w; 
        washCounter += p[i-1].w;

        dryStart[i] = dryEnd[i-1];
        dryEnd[i] = dryStart[i] + p[i].d; 
        dryCounter += p[i-1].d;


        if(isLessThan(dryEnd[i-1],washEnd[i])) // Checking to see if there's a gap
        {
            dryStart[i] = washEnd[i];
            dryEnd[i] = dryStart[i] + p[i].d;
            dryCounter += washEnd[i] - dryEnd[i-1];

            printf("dryer gap from %d to %d\n",dryEnd[i-1],washEnd[i]);
        }
        
        printf("%d %d %d %d %d\n",p[i].index,p[i].w,p[i].d,washCounter,dryCounter);


    }

    printf("makespan is: %d\n",dryEnd[i-1]); //getting makespan

    free(p); //freeing memory

}

//==**main starts here**==
int main(int argc,char ** argv)
{
    getInput(); //Reading input from file and adjusting it to work in Johnson's Rule
    wd * p = johnsonRule(); //Performing the Johnson's Rule
    printResult(p); //Printing the result of the Johnson's Rule
    free(basket); //freeing space of basket
}
