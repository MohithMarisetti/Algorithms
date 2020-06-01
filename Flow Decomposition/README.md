
Goals:
1.	Review of network flow concepts.
2.	Review of depth-first search.
3.	Understanding of flow decomposition.

Requirements:
1.	Write (and test) a C/C++ program to extract a flow decomposition from a provided flow.  Your program must compile and execute on at least one of OMEGA or Visual Studio.
	The input to your program will be:
a.	n and m, the number of vertices and edges.    and  .
b.	m lines, each giving an edge:  tail, head, flow.  Vertices are numbered 0 . . . n - 1.  The source is vertex 0.  The sink is vertex n - 1.  The flow will be positive.  Inverse pairs of edges will not appear in the input.  The source will never be the head of an edge.  Likewise, the sink will never be the tail of an edge.  Finally, the edges will be sorted lexicographically by tails, then heads.

The output from your program will be:
a.	The total verified flow.  If there is an issue with flow conservation, your program should terminate.
b.	For each cycle that is found, output the limiting edge and the amount of the flow that is cancelled.
c.	The S-T paths in the flow decomposition.  Besides listing each path of vertices and its contribution to flow, your program should also indicate an edge on each S-T path that is cancelled down to zero flow.

2.	Submit your C/C++ code on Blackboard before 3:45 p.m. on April 10.  Please provide only source code files without compressing/zipping.  Be sure to include comments regrading how to compile and execute your code.
Getting Started:

1.	You may use existing code for the depth-first search, but be sure to give appropriate credit.
2.	Flow decomposition is discussed in Notes 9 (page 6).
3.	Do not use an adjacency matrix.  Use adjacency lists.
4.	Network flow code is not needed for implementing this assignment.
