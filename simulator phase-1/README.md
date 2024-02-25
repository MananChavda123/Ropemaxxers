# Ropemaxxers
For CO project


We started working on the project on 17th Feb.
17/02/2024
We made the basic structure of the core class.First we created public variables of pc,array of 32 registers x[32],etc.We added methods such as instructionFetch,instructionDecode and Execute.instructFetch is basically made for getting inpu,twe took one by one string input from the file and passed it to Instruction decode .In instructionDecode class,we took our string which is passed as a parameter and divided it into parts of a vector v(For e.g addi x12 x0 4 is split into 4 parts,v[0] = addi;v[1] = x12;v[2] = x0;v[3] = 4).After this,the function is passed to the execute function,in the execute function,v[0] is assigned as the opcode of that particular instruction.Then we put if and else if blocks for computation of different functions such as add,sub,addi,subi,muli,etc.We left functions such s lw,sw,jump for later dates.

19/02/2024
On this date,we made our next class that is processor class.In this class,we have declared variables such as clock,memory,etc and also decided to make a run class to execute both cores but for now,we just limited ourselves on making  of a single core.

23/02/2024
Then we decided to shift to the main part,our goal of today was to design memory functions such as lw,sw,etc.It was tiring to find the logic of it because we required a function such that it stores the address of the memory in the register and we required other register to find the value of the memory whose address was stored. Then , we found a inbuilt funtion(reinterpret cast) such that it can store the address of register in long long int. and other function (reinterpret cast<int *>) so that it can access the value stored in register.Thus, completing the workload of lw and sw.We also decided to work on jump function but couldn't meet the deadline.

24/02/2024
today our main goal was to find the logic of jump function,we tried manyy ways for it but still couldn't get the logic.Atlast,we came to know that we we were doing the whole function calling wrong.So,we adjusted the function calling to a different way.At first,we were calling Run() from the processor,from that processor calls instuctionfetch() from the core and then we made it to call all functions like a chain.Like this:
processor p;
p.run();
processor class:
run(){
core.InstructionFetch();
}
now in the core class:
Class core(){
InsructionFetch(){
//code 
InstructionDecode();
}
InstructionDecode(){
//code
execute();
}
execute(){
//code
if(opcode == jump){
//code
InstructionFetch();
}
So,this was our first logic.it can run for normal functions without loop.But for looping functions,it can't break and moves on in an infinite loop.So,we decided to make it like this which is like our final code:
processor p;
p.run();
processor class:
run(){
 while (!instruction.empty()) {
            vector<string> decodedInstruction = core[0].independentInstructionDecode();
            core.independentExecute();
            instruction = core].independentInstructionFetch();
            }
}
now in the core class:
Class core(){
IndependentInsructionFetch(){
//code 
**Direct calling from the instructionFetch removed instead now InstructionDecode is called from processor class as IndependentInstructionDecode**
}
IndependentInstructionDecode(){
//code
**Direct calling from the instructionDecode removed instead now execute is called from processor class as Independentexecute**

}
independentexecute(){
//code
if(opcode == jump){
//code
**Same above process applied here**
}
By resolving this error,we mostly completed the logic part of our code and made a simulator for a single core.The thing which was left was adding another core and adding code snippets for cases of".data" and ".text" handling.

25/02/2024
We added another core to our processor and it successfully executed in 2 or 3 trials.For this we divided memory section into 2 parts for both the cores.Memory[0 to 512] for core[0] and memory[512-1024] for core[1].Then,we decide the logic of .data,.text function and then we were done with the project.
