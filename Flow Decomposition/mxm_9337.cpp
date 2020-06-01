#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

//Structure and CLasses to Hold the Vertices(Nodes)

//node structure
struct node {
	int vertex,currentFlow;
	struct node *nextVertex;
};

//Edge class
class Edge {
	public:
	int nextVertex, currentFlow;
};

//Node class
class Node {
	public:
	int currentVertex;
	int nextVertex[10000],currentFlow[10000];
};

// Values used for execution
bool stopFlag = false; //This flag is used to stop the loop after a cycle is detected.
bool fullBlackStopFlag = false;
int cycleStartNumberIndex=-1;
int cycleEndNumber=-1;
int globalArray[10000];
int totalFlow=0;
int lines=0;

// This function is used removeCycles from the given graph
void removeCycles(Node *n,int z,int vertices, bool *white,bool *grey, bool *black,string *path, int *totalVisitedNodes);

//This function is used to get all the augmenting paths by expanding Adjacency Lists
void expandAdjacencyLists(Node *n,int z,int vertices, bool *white,bool *grey, bool *black,string *path, int *totalVisitedNodes);

//Main function. Program execution starts here.
int main() {
	string filename = "";
	cout << "Enter Filename (input file should be in same directory): ";
	getline(cin, filename);
	string line,temp;
	int vertices , edges, spacePos;

	// Retrieve data from the file logic
	ifstream myfile(filename);
	getline(myfile,line);
	spacePos = line.find(" ");
	temp = line.substr(0,spacePos);   //substr(inclusive,exclusive)
	vertices = stoi(temp);
	spacePos = line.find(" ");
	temp =  line.substr(spacePos+1,line.length());
	edges = stoi(temp);
	int firstSpacePos, secondSpacePos, thirdSpacePos;
	int i,secondvertex;
	Node *n = new Node[vertices];
	int firstVertex=0;
	for(i=0;getline(myfile,line);i++) {
	firstSpacePos = line.find(" ");
	temp = line.substr(0,spacePos);
	firstVertex= stoi(temp);
	n[firstVertex].currentVertex = firstVertex; // Store the first vertex
	secondSpacePos = line.find(" ",firstSpacePos+1);
	temp = line.substr(firstSpacePos+1,secondSpacePos-firstSpacePos-1);
	secondvertex = stoi(temp);
	n[firstVertex].nextVertex[secondvertex] = secondvertex; // Store the second vertex
	thirdSpacePos = line.find(" ",secondSpacePos+1);
	temp = line.substr(secondSpacePos+1,line.length());
	n[firstVertex].currentFlow[secondvertex] = stoi(temp);  //Store the flow value
}

 // The below code checks if all the nodes are satisfying the INFLOW = OUTFLOW
 // condition or not
int inflow=0,outflow=0;
//Calculating inflow
for(int j=1;j<vertices-1;j++){
for(i=0;i<vertices-1;i++) {
  if(n[i].currentFlow[j]!=0) {
	  inflow += (n[i].currentFlow[j]);
  } }
}

//Calculating Outflow
for(int j=0;j<vertices-2;j++) {
for(i=0;i<vertices-1;i++)
{
  if(n[j].currentFlow[i]!=0)  {
	  outflow += n[j].currentFlow[i];
  }
}
}//for close

//Calculating total in flow and total out flow.
int j,totalInflow=0,totalOutflow=0;
for(j=0;j<vertices;j++) {
	if(n[0].currentFlow[j]!=0) {	totalOutflow+=n[0].currentFlow[j];	}
	if(n[j].currentFlow[vertices-1]!=0) {
		totalInflow+= n[j].currentFlow[vertices-1];	}
}

//Checking whether the flow is verified or not
if(totalInflow==totalOutflow) {
	cout<< "Verified flow is " << totalInflow << endl;
}
else { cout<< "Flow not conserved!"; //If flow isnt conserved then we exit
		exit(0); }

// Variables required for cycle detection
bool white[vertices],grey[vertices],black[vertices];
int z,start=0;
int list[100000];
list[0] = 0;
int l=1;
time_t timeStart = clock();
int totalVisitedNodes=0;
string path;

// Cycle detection logic
for(z=0;fullBlackStopFlag!=true;) {

	// Reinitialize the variables after every iteration
	totalVisitedNodes = 0;
	for(int t=0;t<vertices;t++){
		white[t]=true;
	}
	for(int t=0;t<vertices;t++){
		grey[t]=false;
	}
	for(int t=0;t<vertices;t++){
		black[t]=false;
	}
	if ((clock() - timeStart) / CLOCKS_PER_SEC >= 6) // time in seconds
					break;
	path = "";

	//Function Call to removeCycles() function.
		removeCycles(n,z,vertices,white,grey,black,&path,&totalVisitedNodes);

		stopFlag = false;
}//For end

//Re-initialized the variables to default values

for(int t=0;t<vertices;t++){
white[t]=true;
}
for(int t=0;t<vertices;t++){
grey[t]=false;
}
for(int t=0;t<vertices;t++){
black[t]=false;
}
z=0;
cout<< "Flow Decomposition: Edges ->\n";
path = "";

for(int t=0;t<vertices;t++) {
	path = "0->";
	for(int t=0;t<vertices;t++){
	white[t]=true;
	}
	for(int t=0;t<vertices;t++){
	grey[t]=false;
	}
	for(int t=0;t<vertices;t++){
	black[t]=false;
	}
	if(n[0].currentFlow[t]!=0) {
		expandAdjacencyLists(n,t,vertices,white,grey,black,&path,&totalVisitedNodes);
	} }
lines++;
cout <<lines <<": " <<"0->" + to_string(vertices-1) << ",  limiting edge 0->"+to_string(vertices-1)<< " has flow " << n[0].currentFlow[vertices-1] << endl ;
totalFlow += n[0].currentFlow[vertices-1];
cout<< "Total flow in decomposition: " << totalFlow << endl;
return 1;
}


// This function used DFS to search for cycles and then removes it after
// finding the cycle and then restarts the cycle detection process by calling
// the removeCycles() function. This is a recursive function.
void removeCycles(Node *n,int z,int vertices, bool *white,bool *grey, bool *black,string *path, int *totalVisitedNodes) {
int countBlack = 0;
for(int temp=0; temp<vertices;temp++) {
	if(black[temp]==true) {
		countBlack++;
	}
}
if(countBlack==vertices){
	fullBlackStopFlag = true;
	stopFlag = true;
	return;
}
	if(z==(vertices-1)){
		return; //We have reached till end without encountering any cycles
	}
	if(grey[z]==true) {
		cycleStartNumberIndex = (*path).find("->"+to_string(z)+"->");
		*path += to_string(z);
		cycleEndNumber = z;
		int gai=0;  //GLOBAL ARRAY INDEX (gai)
		string temp_path = (*path).substr(cycleStartNumberIndex,(*path).length());
		string delimiter = "->";
		size_t pos = 0;
		string token;
	while ((pos = temp_path.find(delimiter)) != string::npos) {
		try {
		token = temp_path.substr(0, pos);
		globalArray[gai] = stoi(token);
		gai++;
		temp_path.erase(0, pos + delimiter.length());
		}
		catch(std::invalid_argument e)
		{
			temp_path.erase(0, pos + delimiter.length());
			continue;
		}
	}
	int min = 9999; //We initialized a worst min value to start with
	int minIndex1=-1;
	int minIndex2=-1;
	for(int t1=0; t1<(gai-1);t1++) {
	int v1 = globalArray[t1]; //vertex1
	int v2 = globalArray[t1+1]; //vertex2
	int v1v2flow = n[v1].currentFlow[v2];
	if ( v1v2flow < min) {
			min = v1v2flow;
			minIndex1 = v1;
			minIndex2 = v2;
	}//if close
}

int v1v2flow = n[globalArray[gai-1]].currentFlow[globalArray[0]];
if(v1v2flow< min) {
	min = v1v2flow;
	minIndex1 = globalArray[gai-1];
	minIndex2 = globalArray[0];
}
cout<< "Cancel cycle of " << gai << " vertices,";
cout<< " limiting edge " << minIndex1 <<"->"<< minIndex2 << " has flow " << min << "\n";
for(int t1=0; t1<(gai-1);t1++)
{
	int v1 = globalArray[t1]; //vertex1
	int v2 = globalArray[t1+1]; //vertex2
	n[v1].currentFlow[v2]-=min;
}
int v1 = globalArray[gai-1];
int v2 = globalArray[0];
	n[v1].currentFlow[v2]-=min;
		stopFlag = true;
		return;
	}
	else if(black[z]==true){
		return;
	}
	else {
		*path = *path + to_string(z);
		*path += "->";
		white[z]=false;
		grey[z]=true;
		totalVisitedNodes+=1;
	}
	int i=0;
	for(i=0;i<vertices;i++)
	{
		if(n[z].currentFlow[i]!=0 and stopFlag== false){
			removeCycles(n,i,vertices,white,grey,black,path,totalVisitedNodes);  //CHECK THIS STATEMENT
		}
	}
	black[z] = true;
	grey[z] = false;
	string toErase = to_string(z)+"->";
	size_t found = (*path).find(toErase);
	size_t pos ;
while(found != std::string::npos){
size_t newFound  = (*path).find(toErase,found+1);
	if(newFound > (*path).length())
	{pos = found;
		break; } //previous found is the only index with the specied string
	else if(newFound < (*path).length() && newFound > found)
	{pos= newFound ;
	found = newFound;}  //There is a new position with specied string
}
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		(*path).erase(pos, toErase.length());
	}
	return;
}

// This function expands all possible paths and finds the least flow and
// subtracts that value in all the nodes in that path. This is a recursive function.
void expandAdjacencyLists(Node *n,int z,int vertices, bool *white,bool *grey, bool *black,string *path, int *totalVisitedNodes) {

if(black[z]==true){
	return;
}
		int i=0;
		if(z!=(vertices-1)){
		if(grey[z]!=true)
		{*path = *path + to_string(z);}
		else {return;}
		*path += "->";
		grey[z]=true;
	for(i=0;i<vertices;i++) {
		if(n[z].currentFlow[i]!=0){
			expandAdjacencyLists(n,i,vertices,white,grey,black,path,totalVisitedNodes);  //CHECK THIS STATEMENT
		}
	}
			*path+=to_string(vertices-1);
			int gai=0;  //GLOBAL ARRAY INDEX (gai)
			string temp_path = *path;
			string delimiter = "->";
			size_t pos = 0;
			string token;
		while ((pos = temp_path.find(delimiter)) != string::npos) {
			try {
			token = temp_path.substr(0, pos);
			globalArray[gai] = stoi(token);
			gai++;
			temp_path.erase(0, pos + delimiter.length());
			}
			catch(std::invalid_argument e)
			{
				temp_path.erase(0, pos + delimiter.length());
				continue;
			}
		}
		int min = 9999; //Contains the minimum flow value
		int minIndex1=-1;
		int minIndex2=-1;
	for(int t1=0; t1<(gai-1);t1++) {
		int v1 = globalArray[t1]; //vertex1
		int v2 = globalArray[t1+1]; //vertex2
		int v1v2flow = n[v1].currentFlow[v2];
		if ( v1v2flow < min) {
				min = v1v2flow;
				minIndex1 = v1;
				minIndex2 = v2;
		}//if close
	}
	if(min!=0) {
		lines++;
		cout << lines << ": " <<(*path)<< " , ";
		cout << " limiting edge " << minIndex1 <<"->"<< minIndex2 << " has flow " << min << "\n";
	}

	//We are calculating the total Flow in decomposition
	totalFlow+=min;
	for(int t1=0; t1<(gai-1);t1++) {
		int v1 = globalArray[t1]; //vertex1
		int v2 = globalArray[t1+1]; //vertex2
		n[v1].currentFlow[v2]-=min;
	}

	//Remove the visited node from the path
		string toErase = to_string(z)+"->"+to_string(vertices-1);
		// Search for the substring in main string
		size_t found = (*path).find(toErase);
		pos ;
	while(found != std::string::npos){
	size_t newFound  = (*path).find(toErase,found+1);
		if(newFound > (*path).length())
		{pos = found;
			break; } //previous found is the only index with the specied string
		else if(newFound < (*path).length() && newFound > found)
		{pos= newFound ;
		found = newFound;}  //There is a new position within specied string
	}
		if (pos != std::string::npos) {
			// If found then erase it from string
			(*path).erase(pos, toErase.length());
		}
}
	black[z] = true; // States that a node z is visited.
	return;
}
