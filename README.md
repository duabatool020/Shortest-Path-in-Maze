# Shortest-Path-in-Maze
Writing a C++ program to find shortest path in a maze(maze can be represented in
the form of binary rectangular matrix).<br>
[ 1 1 1 1 1 0 0 1 1 1 ]<br>
[ 0 1 1 1 1 1 0 1 0 1 ]<br>
[ 0 0 1 0 1 1 1 0 0 1 ]<br>
[ 1 0 1 1 1 0 1 1 0 1 ]<br>
[ 1 1 1 1 1 0 0 1 1 1 ]<br>
[ 0 1 1 1 1 1 0 1 0 1 ]<br>
[ 0 0 1 0 1 1 1 0 0 1 ]<br>
[ 1 0 1 1 1 0 1 1 0 1 ]<br>
Also find shortest path’s length from given source to destination. 
<br>First determining that the path could be constructed or not (the path can only be constructed out of
cells having value 1) and keeping in mind that only one step can be taken in one of
the four directions, shortest path from the given source to destination can be
calculated by only taking valid moves.<br><br>
The Data Structures used to Solve this problem are Tree and Queue
