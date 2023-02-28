# Prim's Algorithm OpenGL Demo
The project uses the basic primitives defined in openGL library to demonstrate a type of Greedy Algorithm through visualisation.
It takes the number of nodes as input followed by a matrix representing the graph. You can choose to the position the nodes anywhere within the window and see the graphical representation of the graph and generate a minimum spanning tree for the given input graph.

### Algorithm
In computer science, Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph. This means it finds a subset of the edges that forms a tree that includes every vertex, where the total weight of all the edges in the tree is minimized. The algorithm operates by building this tree one vertex at a time, from an arbitrary starting vertex, at each step adding the cheapest possible connection from the tree to another vertex.
The algorithm may informally be described as performing the following steps:
 1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
 2. Grow the tree by one edge: of the edges that connect the tree to vertices not yet in the
    tree, find the minimum- weight edge, and transfer it to the tree. 
 3. Repeat step 2 (until all vertices are in the tree).

### Steps to run the project
1. To execute the code make sure you have installed OpenGL (freeglut or whatever) and also the necessary Compiler.
2. LINUX USERS
Open the directory where the code cgv1_linux.cpp is stored and execute the following commands:
```
 $ gcc cgv1_linux.cpp -lGLU -lGL -lglut -lm -Wno-write-strings
 $ ./a.out 
```
WINDOWS USERS: 
Install codeblocks to Execute cgv1.cpp
3. Follow the procedure as shown in the screenshots available in the report enclosed
