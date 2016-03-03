/*
*Linked List*               
Test 1  1   /   2   
Test 2  1   /   2   
Test 3  1   /   2   
Test 4  1   /   2   
                
*MPI*               
Correctly handle the case when there's only 1 process.  2   /   2   
Correctly compute dest process rank when p > 1. 0   /   2   dest should be next higher process (rank + 1, not rank - 1)
Use MPI_ANY_SOURCE or correctly compute the source process rank when p > 1. 0   /   2   source should be next lower rank process (rank - 1, not rank + 1)
Correctly send, receive, and print the greeting when p > 1. 0   /   2   Incorrect dest and source
                
Total   6   /   16
*/  