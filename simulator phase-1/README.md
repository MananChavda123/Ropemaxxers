# Ropemaxxers
For CO project
We started working on the project on 17th Feb.
17/02/2024
Havish made the basic structure of the core class.First we created public variables of pc,array of 32 registers x[32],etc.We added methods such as instructionFetch,instructionDecode and Execute.instructFetch is basically made for getting inpu,twe took one by one string input from the file and passed it to Instruction decode .In instructionDecode class,we took our string which is passed as a parameter and divided it into parts of a vector v(For e.g addi x12 x0 4 is split into 4 parts,v[0] = addi;v[1] = x12;v[2] = x0;v[3] = 4).Then we assigned 
