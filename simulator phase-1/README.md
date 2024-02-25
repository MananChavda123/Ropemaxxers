# Ropemaxxers
For CO project


We started working on the project on 17th Feb.
17/02/2024
We made the basic structure of the core class.First we created public variables of pc,array of 32 registers x[32],etc.We added methods such as instructionFetch,instructionDecode and Execute.instructFetch is basically made for getting inpu,twe took one by one string input from the file and passed it to Instruction decode .In instructionDecode class,we took our string which is passed as a parameter and divided it into parts of a vector v(For e.g addi x12 x0 4 is split into 4 parts,v[0] = addi;v[1] = x12;v[2] = x0;v[3] = 4).After this,the function is passed to the execute function,in the execute function,v[0] is assigned as the opcode of that particular instruction.Then we put if and else if blocks for computation of different functions such as add,sub,addi,subi,muli,etc.We left functions such s lw,sw,jump for later dates.

19/02/2024
On this date,we made our next class that is processor class.In this class,we have declared variables such as clock
