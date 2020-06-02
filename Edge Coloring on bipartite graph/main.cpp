/*

Name: Mohith Marisetti
ID: 1001669337
Language: C++
Task: Project 3 (Edge Coloring)

*/


#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

class Node {
	public:
    int currentVertex;
	int nextVertex[10000];
};

void printLeftRightMatrices(int leftvertices,int rightvertices,int** leftFreeMatrix,int **rightFreeMatrix);


int main() {
	string filename = "";
	cout << "Enter Filename (input file should be in same directory): ";
	getline(cin, filename);
	string line,temp;
	int leftvertices , rightvertices, edges;

    int firstSpacePos, secondSpacePos, thirdSpacePos, spacePos;

	// Retrieve data from the file logic
	ifstream myfile(filename);
	getline(myfile,line);
	spacePos = line.find(" ");
	temp = line.substr(0,spacePos);   //substr(inclusive,exclusive)
	leftvertices = stoi(temp);
	secondSpacePos = line.find(" ",spacePos+1);
	temp =  line.substr(spacePos+1,secondSpacePos-spacePos-1);
	rightvertices = stoi(temp);
    thirdSpacePos = line.find(" ",secondSpacePos+1);
	temp =  line.substr(secondSpacePos+1,thirdSpacePos-secondSpacePos-1);
	edges = stoi(temp);
    
	
	int i,secondvertex;
	Node *n = new Node[leftvertices];
	int firstVertex=0;
	for(i=0;getline(myfile,line);i++) 
    {
	
    firstSpacePos = line.find(" ");
	temp = line.substr(0,spacePos);
	firstVertex= stoi(temp);
	n[firstVertex].currentVertex = firstVertex; // Store the first vertex
	secondSpacePos = line.find(" ",firstSpacePos+1);
	temp = line.substr(firstSpacePos+1,secondSpacePos-firstSpacePos-1);
	secondvertex = stoi(temp);
	n[firstVertex].nextVertex[secondvertex] = 9999; // We store 9999 to indicate there is a path from firstvertex to secondvertex
    }

   int **leftFreeMatrix = new int*[leftvertices];

    for(int t=0;t<leftvertices;t++){
        leftFreeMatrix[t] =  new int[rightvertices];
    }

   int **rightFreeMatrix = new int*[rightvertices];
    for(int t=0;t<rightvertices;t++){
        rightFreeMatrix[t] =  new int[rightvertices];
    }


    for (int t=0;t<leftvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
            leftFreeMatrix[t][t2]=10101;  //Some random number to indicate that the vertex is still empty
        }    
    }

    for (int t=0;t<rightvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
            rightFreeMatrix[t][t2]=10101;  //Some random number to indicate that the vertex is still empty
        }    
    }

    /*
    //Both are Testing for loop 
    for (int t=0;t<leftvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
            cout << leftFreeMatrix[t][t2] << "  ";  //Some random number to indicate that the vertex is still empty
        }    
        cout << endl ;
    }

    cout << endl ;

    for (int t=0;t<rightvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
           cout << rightFreeMatrix[t][t2] << "  " ;  //Some random number to indicate that the vertex is still empty
        }    
        
        cout << endl ;
    }
    */
    int count=0;
    for (int t=0;t<leftvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
            if (n[t].nextVertex[t2] == 9999){ // 9999 Means there is a path from vertex t to vertex t2
                count = 0;
                for (int t3=0; t3<rightvertices ;t3++){
                    /*
                    if ((t==1) && (t2==1)) {
                        cout << "LEFT VALUE at 1-1" <<leftFreeMatrix[t][t3] <<endl;
                        cout << "Right VALUE at 1-1" <<leftFreeMatrix[t][t3] <<endl;
                    }
                    cout << "\n\n"; 
                    */
                  
                    if ((leftFreeMatrix[t][t3] == 10101) && (rightFreeMatrix[t2][t3] == 10101)) { //10101 refers to a location in the matrix being free. If either of the location is not free we go to the next location in the same row.
                            rightFreeMatrix[t2][t3] = t; // t used as color to that location
                            leftFreeMatrix[t][t3] = t3;
                            cout << "\n Case 1: (" << t << " " << t2 << ") gets color " << t3 ;//<<endl;
                            //printLeftRightMatrices(leftvertices,rightvertices,leftFreeMatrix,rightFreeMatrix);
                            break;
                    }//if close
                    else {
                        count++;
                    }

                    if (count==rightvertices){  //Case 2 logic
                                     //cout << "\nEntered case 2 logic" << endl;
                        //cout << "\n Case2: ";
                                     //cout << "The t3 value for which this problem occurred is " << t3 <<endl;
                       //Case 2 logic
                       int r = t2;
                       int temp2 = t3;
                       int a=0;
                       int b=0;
                       int a_temp=0;
                       int b_temp = 0;
                                        

                        for(int z=0;z<rightvertices;z++){
                            if(leftFreeMatrix[t][z]==10101 && a_temp==0)
                            {a = z;
                            a_temp=99;}
                            if(rightFreeMatrix[t2][z]==10101 && b_temp==0)
                            {b = z;
                            b_temp=99;}
                        
                        }

                                                 

                       int temp_r = 0;
                       int tempcount = 0;
                       int breakCount = 0;
                       while(true) { 
                        
                        /*
                        if(breakCount>=2){
                            break;
                        }

                        */
                        

                        if(rightFreeMatrix[r][a]!=10101 && tempcount%2==0)
                        {
                            if(r==rightFreeMatrix[r][a])
                            {
                                breakCount++;
                            }
                            if( breakCount<=1)
                            {   //cout << "Before Updation: r = " << r << endl;
                                temp_r = rightFreeMatrix[r][a];
                                //cout << "Value of temp_r = " << temp_r <<endl;
                                rightFreeMatrix[r][a] = 10101;
                                //cout << "Just Updated the value of rightFreeMatrix["<<r<<"]["<<a<<"] = " << rightFreeMatrix[r][a] << endl;
                                rightFreeMatrix[r][b] = temp_r;
                                //cout << "Just Updated the value of rightFreeMatrix["<<r<<"]["<<b<<"] = " << rightFreeMatrix[r][b] << endl ;
                                r = temp_r;
                                //cout << "Just Updated the value of r = " << r<< endl;

                            }
                           
                         tempcount+=1;
                        }
                        else if(tempcount%2==0 && rightFreeMatrix[r][a]==10101)
                        {
                            break;
                        }
                        
                        if(rightFreeMatrix[r][b]!=10101 && tempcount%2!=0) 
                        {
                            if (r==rightFreeMatrix[r][b]) {
                                breakCount++;
                            }
                             if(breakCount<=1)
                            {
                                                          //cout << "Before Updation: r = " << r<< endl;
                                temp_r = rightFreeMatrix[r][b];
                                                          //cout << "Value of temp_r = " << temp_r <<endl;
                                rightFreeMatrix[r][b] = 10101;
                                                           //cout << "Just Updated the value of rightFreeMatrix["<<r<<"]["<<b<<"] = " << rightFreeMatrix[r][b] << endl;
                                rightFreeMatrix[r][a] = temp_r;
                                                          //cout << "Just Updated the value of rightFreeMatrix["<<r<<"]["<<a<<"] = " << rightFreeMatrix[r][a] << endl;
                                r = temp_r;
                                                           // cout << "Just Updated the value of r = " << r<< endl;

                            }
                            
                         tempcount+=1;
                        }
                        else if(rightFreeMatrix[r][b]==10101 && tempcount%2!=0) {
                            break;
                        }
                      
                       }//infinite loop
                       

                     if ((leftFreeMatrix[t][a] == 10101) && (rightFreeMatrix[t2][a] == 10101)) { //10101 refers to a location in the matrix being free. If either of the location is not free we go to the next location in the same row.
                            rightFreeMatrix[t2][a] = t; // t used as color to that location
                            leftFreeMatrix[t][a] = t2;
                            cout << "\n Case 2: (" << t << " " << t2 << ") gets color " << a ;
                            cout << ", a = "<<a << ", swaps with b = " << b;
                            cout << ", r : "<< r ;
                            //printLeftRightMatrices(leftvertices,rightvertices,leftFreeMatrix,rightFreeMatrix);
                            break;
                    }//if close




                   }//Case 2 Logic close

                     

                }//Inner most for loop
                
            }
        }    
        
    }

//printLeftRightMatrices(leftvertices,rightvertices,leftFreeMatrix,rightFreeMatrix);

bool temp2[1000];
int tmp=0;
 for (int t=0;t<rightvertices;t++)
    {
        for(int x=0;x<rightvertices;x++)
        {
            temp2[x]=false;
        }

        for (int t2=0;t2<rightvertices;t2++)
        {
           if (rightFreeMatrix[t][t2]!=10101)
           {
               //finalFreeMatrix[t][tmp] = t2;
               //finalFreeMatrix[t][t2] = 100;   //MAtrix has a value
               //cout <<rightFreeMatrix[t][t2] << endl;
               temp2[rightFreeMatrix[t][t2]] = true;  // True means that node is filled 
           }
           else
           {
               //finalFreeMatrix[t][t2] = t2; //MAtrix has an empty value at t2(i.e., t2 color is unused)
               //cout << rightFreeMatrix[t][t2] << endl; 
               temp2[t2] = false;  // False means that node is empty
           }
        }

         for (int t2=0;t2<rightvertices;t2++)
        {
           if (rightFreeMatrix[t][t2]==10101)
           {
               for(int x=0;x<rightvertices ;x++)
               {
                   if(temp2[x] == false){
                       temp2[x]=true;
                       rightFreeMatrix[t][t2] = x;
                       break;
                   }
               }
           }
        }

    }

cout << endl;

//printLeftRightMatrices(leftvertices,rightvertices,leftFreeMatrix,rightFreeMatrix);


  for (int t=0;t<leftvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
           for (int t3=0; t3<rightvertices;t3++)
           {
               if(rightFreeMatrix[t][t3]==t2)
               {
                    cout << " " <<t << " " << t2 << " " << t3  << endl;
               }
               else 
               {
                    //Do nothing
               }
           }
        }    
    }



    

} //main close



void printLeftRightMatrices(int leftvertices,int rightvertices,int** leftFreeMatrix,int **rightFreeMatrix) {

        for (int t=0;t<leftvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
            cout << leftFreeMatrix[t][t2] << "  ";  //Some random number to indicate that the vertex is still empty
        }    
        cout << endl ;
    }

    cout << endl ;

    for (int t=0;t<rightvertices;t++)
    {
        for (int t2=0;t2<rightvertices;t2++)
        {
           cout << rightFreeMatrix[t][t2] << "  " ;  //Some random number to indicate that the vertex is still empty
        }    
        
        cout <<endl ;
    }
}