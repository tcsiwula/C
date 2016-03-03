/*
    Attained        Max 
***Daxpy***             
Correct input of data on the main thread    1   /   1   
Correct division of work among the threads  1   /   1   
Correct calculation by the threads  0   /   1   Loop iterates 1 time too many; should be iterator < loc_n_stop, not <=
Correct output by the main thread   1   /   1   
                
***Global sum***                
Bitmask starts at p >> 1    1   /   1   
Correct loop test   1   /   1   
Sendrecv and sum += temp    1   /   1   
Correct update to bitmask   1   /   1   
                
Total   7   /   8   
*/