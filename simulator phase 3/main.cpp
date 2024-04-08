#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include<math.h>
#include <cmath>
#include <algorithm>
using namespace std;

class core {
public:
    long long int x[32];
    int na=0;
    int destination,value; 
    int pc, size, t;
    bool isStall, isStall1;
    int stalls;
    int clock1;
    int predictorCorrect;
    int predictorIncorrect;
    map<int, int> predictorTable;
    int instructionCount;
    vector <string> v1,v2;
    vector<string> newmemory;
    string instruction;
    vector<string> decodedinstruction;
    std::string filename1;
    map<string, int> mnew;
    int latency,cacheMissRate,hitRate;
    long long int address;
    bool hit,isMemoryOperation;
    
    core(const std::string& filename) : filename1(filename), pc(0), size(0), predictorCorrect(0), predictorIncorrect(0) {
        pc = 0;
        latency = 1;
        stalls = 0;
        cacheMissRate = 0;
        hitRate = 0;
        t=0;
        instructionCount=0;
        clock1 = 0;
        isStall = false;
        isStall1 = false;
        destination=0;
        value=0;
        ifstream infile(filename1);
        string t;
        instruction="temp";
        for (int i = 0; i < size; ++i) {
            predictorTable[i] = 2;
        }
        for (int i = 0; i < 32; i++) {
            x[i] = 0;
        }
        while (getline(infile, t)) {
            newmemory.push_back(t);
            pc = pc + 1;
            string newi = "";
            for (char c : t) {
                if (c == ':') {
                    mnew.insert({ newi, pc });
                }
                else {
                    newi = newi + c;
                }
            }
        }
        size = pc;
        infile.close();
        pc = 0;
    }
    string independentInstructionFetch() {
        if (pc >= newmemory.size()) {
            return ""; 
        }
        else{
        string instruction = newmemory[pc];
        // cout<<instruction<<endl;
        instructionCount++;
        pc++;
        return instruction;
        }  
    }
    
    vector<string> independentInstructionDecode(string& instruction) {
        vector<string> v;
        if(detectDataHazardStall()){
            isStall1 = true;
        }
        if(instruction.empty()){
        }
        else{
            string token;
            for (char c : instruction) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v.push_back(token);
            }   
        }
    return v;
    }
    vector<string> independentInstructionDecode1(string& instruction) {
        vector<string> v;
        if(detectDataHazardStall1()){
            isStall1 = true;
        }
        if(instruction.empty()){
        }
        else{
            string token;
            for (char c : instruction) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v.push_back(token);
            }   
        }
    return v;
    }
bool detectDataHazardStall() {
    if(pc+1 < newmemory.size()){
    string nextInstruction = newmemory[pc];
    string nextInstruction1 = newmemory[pc+1];
    vector<string> v1,v2;

        if(nextInstruction.empty()){

        }
        else{
            string token;
            for (char c : nextInstruction) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v1.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v1.push_back(token);
            }
        }
            string opcode = v1[0];
    if (opcode == "add" || opcode == "sub" || opcode == "addi" || opcode == "slli" || opcode == "srli" ){
        int rd = stoi(v1[1].substr(1));    
        // cout<<rd;
        v1.clear();
        if(nextInstruction1.empty()){
        }
        else{
            string token;
            for (char c : nextInstruction1) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v1.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v1.push_back(token);
            }
        }
            if (v1[0] == "add" || v1[0] == "sub"){
                if(rd == stoi(v1[1].substr(1)) || rd == stoi(v1[2].substr(1)) ||  rd == stoi(v1[3].substr(1))){
                    isStall = true;
                    stalls=stalls+2;
                    return true;
                }
            }
            else if (v1[0] == "lw" || v1[0] == "sw"){
                if(rd == stoi(v1[1].substr(1)) ){
                    isStall = true;
                    stalls=stalls+2;
                    return true;
                }
            }
            else if (v1[0] == "addi" || v1[0] == "slli" || v1[0] == "srli"){
                if(rd == stoi(v1[1].substr(1)) ||  rd == stoi(v1[2].substr(1))){
                    isStall = true;
                    stalls=stalls+2;
                    return true;
                }
            }
        }
    }
    return false; 
}
bool detectDataHazardStall1() {
    if(pc+1 < newmemory.size()){
    string nextInstruction = newmemory[pc];
    string nextInstruction1 = newmemory[pc+1];
    vector<string> v1,v2;

        if(nextInstruction.empty()){

        }
        else{
            string token;
            for (char c : nextInstruction) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v1.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v1.push_back(token);
            }
        }
            string opcode = v1[0];
    if (opcode == "add" || opcode == "sub" || opcode == "addi" || opcode == "slli" || opcode == "srli" ){
        int rd = stoi(v1[1].substr(1));    
        // cout<<rd;
        v1.clear();
        if(nextInstruction1.empty()){
        }
        else{
            string token;
            for (char c : nextInstruction1) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v1.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v1.push_back(token);
            }
        }
            if (v1[0] == "add" || v1[0] == "sub"){
                if(rd == stoi(v1[1].substr(1)) || rd == stoi(v1[2].substr(1)) ||  rd == stoi(v1[3].substr(1))){
                    isStall = true;
                    stalls=stalls+1;
                    return true;
                }
            }
            else if (v1[0] == "lw" || v1[0] == "sw"){
                if(rd == stoi(v1[1].substr(1)) ){
                    isStall = true;
                    stalls=stalls+1;
                    return true;
                }
            }
            else if (v1[0] == "addi" || v1[0] == "slli" || v1[0] == "srli"){
                if(rd == stoi(v1[1].substr(1)) ||  rd == stoi(v1[2].substr(1))){
                    isStall = true;
                    stalls=stalls+1;
                    return true;
                }
            }
        }
    }
    return false; 
}

bool detectMemoryHazardStall() {
    clock1++;
    if(pc+1 < newmemory.size()){
    string nextInstruction = newmemory[pc];
    string nextInstruction1 = newmemory[pc+1];
    vector<string> v1,v2;
        // cout<<"decode"<<nextInstruction;
        // cout<<"decode"<<nextInstruction1;
        // cout<<endl;S
        if(nextInstruction.empty()){

        }
        else{
            string token;
            for (char c : nextInstruction) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v1.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v1.push_back(token);
            }
        }
            string opcode = v1[0];
            // cout<<opcode;
        if (opcode == "lw" || opcode == "sw"){
        int rd = stoi(v1[1].substr(1));    
        // cout<<rd;
        v1.clear();
        if(nextInstruction1.empty()){
        }
        else{
            string token;
            for (char c : nextInstruction1) {
                if (c != ' ') {
                    token += c;
                }
                else {
                    v1.push_back(token);
                    token.clear();
                }
            }
            if (!token.empty()) {
                v1.push_back(token);
            }
        }
            if (v1[0] == "add" || v1[0] == "sub"){
                if(rd == stoi(v1[1].substr(1)) || rd == stoi(v1[2].substr(1)) ||  rd == stoi(v1[3].substr(1))){
                    isStall = true;
                    stalls=stalls+3;
                    return true;
                }
            }
            else if (v1[0] == "lw" || v1[0] == "sw"){
                if(rd == stoi(v1[1].substr(1)) ){
                    isStall = true;
                    stalls=stalls+3;
                    return true;
                }
            }
            else if (v1[0] == "addi" || v1[0] == "slli" || v1[0] == "srli"){
                if(rd == stoi(v1[1].substr(1)) ||  rd == stoi(v1[2].substr(1))){
                    isStall = true;
                    stalls=stalls+3;
                    return true;
                }
            }
        }
    }
    return false; 
}
void independentExecute1(vector<string>& v,int *memory){
    map<string, long long int> n;
    string addressAdder="";
    string temp="";
    int t=0;
    int offset=0;
    if(v.empty()){

    }
    else{
        string opcode = v[0];
        if (opcode == "add" || opcode == "sub" || opcode == "addi" || opcode == "slli" || opcode == "srli") {
            int rd = stoi(v[1].substr(1));
            int rs1 = stoi(v[2].substr(1));
            if (opcode == "add") {
                x[rd] = x[rs1] + x[stoi(v[3].substr(1))];
            } else if (opcode == "sub") {
                x[rd] = x[rs1] - x[stoi(v[3].substr(1))];
            } else if (opcode == "addi") {
                x[rd] = x[rs1] + stoi(v[3]);
            } else if (opcode == "slli") {
                x[rd] = x[rs1] << stoi(v[3]);
            } else if (opcode == "srli") {
                x[rd] = x[rs1] >> stoi(v[3]);
            }
            v.clear();
        } 

        else if (opcode == "bne" || opcode == "beq" || opcode == "bgt" || opcode == "blt" || opcode == "bge" || opcode == "ble") {
            int rd = stoi(v[1].substr(1));
            int rs1 = stoi(v[2].substr(1));
            string label = v[3];
            if ((opcode == "bne" && x[rd] != x[rs1]) ||
                (opcode == "beq" && x[rd] == x[rs1]) ||
                (opcode == "bgt" && x[rd] > x[rs1]) ||
                (opcode == "blt" && x[rd] < x[rs1]) ||
                (opcode == "bge" && x[rd] >= x[rs1]) ||
                (opcode == "ble" && x[rd] <= x[rs1])) {
                isStall=true;
                stalls++;
                pc = mnew[label];
            }
            v.clear();
        }

    else if(opcode == "j" || opcode == "jump"){
        string label;
        label = v[1];
        isStall=true;
        stalls++;
        v.clear();
        jump(label);
        return;
    } 
    if(opcode==".data") {
        pc = pc - 1;
            while(pc < newmemory.size() && newmemory[pc] != ".text"){                
                string line1 = newmemory[pc];
                // cout<<line1;
                string opcode1, opcode2;
                std::istringstream iss1(line1);
                iss1 >> opcode1 >>opcode2;              
                // cout<<opcode1<<" "<<opcode2;
                if(opcode2==".word"){
                    int count=0;
                    int x;
                    int memsize = 0;
                    for(int i=0; i<1024; i++){
                        if(i==0){
                             long long int lang = reinterpret_cast< long long int>(memory);
                        }
                        if(memory[i]!=0){
                            memsize++;
                        }

                    }
                    while(iss1 >> x){ 
                        memory[count] = x;
                        count++;
                    }
                }
                pc++;
            }    
        } 
    }
    v2 = v;
    v.clear();
}

void independentExecute(vector<string>& v,int *memory){
    // cout<<"execute";
    for(int i=0;i<v.size();i++){
        // cout<<v[i];
    }
    // cout<<endl;
    map<string, long long int> n;
    string addressAdder="";
    string temp="";
    int t=0;
    int offset=0;
    if(v.empty()){

    }
    else{
        string opcode = v[0];
        if (opcode == "add" || opcode == "sub" || opcode == "addi" || opcode == "slli" || opcode == "srli") {
            int rd = stoi(v[1].substr(1));
            destination = rd;
            int rs1 = stoi(v[2].substr(1));
            if (opcode == "add") {
                value = x[rs1] + x[stoi(v[3].substr(1))];
            } else if (opcode == "sub") {
                value = x[rs1] - x[stoi(v[3].substr(1))];
            } else if (opcode == "addi") {
                value = x[rs1] + stoi(v[3]);
            } else if (opcode == "slli") {
                value = x[rs1] << stoi(v[3]);
            } else if (opcode == "srli") {
                value = x[rs1] >> stoi(v[3]);
            }
            v.clear();
        } 

        else if (opcode == "bne" || opcode == "beq" || opcode == "bgt" || opcode == "blt" || opcode == "bge" || opcode == "ble") {
            int rd = stoi(v[1].substr(1));
            int rs1 = stoi(v[2].substr(1));
            string label = v[3];
            if ((opcode == "bne" && x[rd] != x[rs1]) ||
                (opcode == "beq" && x[rd] == x[rs1]) ||
                (opcode == "bgt" && x[rd] > x[rs1]) ||
                (opcode == "blt" && x[rd] < x[rs1]) ||
                (opcode == "bge" && x[rd] >= x[rs1]) ||
                (opcode == "ble" && x[rd] <= x[rs1])) {
                isStall=true;
                stalls++;
                pc = mnew[label];
            }
            v.clear();
        }

    else if(opcode == "j" || opcode == "jump"){
        string label;
        label = v[1];
        isStall=true;
        stalls++;
        v.clear();
        jump(label);
        return;
    } 
    if(opcode==".data") {
        pc = pc - 1;
            while(pc < newmemory.size() && newmemory[pc] != ".text"){                
                string line1 = newmemory[pc];
                // cout<<line1;
                string opcode1, opcode2;
                std::istringstream iss1(line1);
                iss1 >> opcode1 >>opcode2;              
                // cout<<opcode1<<" "<<opcode2;
                if(opcode2==".word"){
                    int count=0;
                    int x;
                    int memsize = 0;
                    for(int i=0; i<1024; i++){
                        if(i==0){
                             long long int lang = reinterpret_cast< long long int>(memory);
                        }
                        if(memory[i]!=0){
                            memsize++;
                        }

                    }
                    while(iss1 >> x){ 
                        memory[count] = x;
                        count++;
                    }
                }
                pc++;
            }    
        } 
    }
    v1 = v;
    v.clear();
}
bool isBranchInstruction(const string instruction) {
    return instruction.size() >= 2 && instruction[0] == 'b' && isalpha(instruction[1]);
}
int getCurrentPC() {
    return pc; 
}
bool getActualBranchOutcome(const string instruction) {
    return true;
}


void independentMemory(vector<string> &v,int memory[]){
    if(v2.empty()){

    }
    else{
            // cout<<"memory";
    // for(int i=0;i<v.size();i++){
    //     cout<<v[i];
    // }
    // cout<<endl;
    // map<string, long long int> n;
            if (isBranchInstruction(v[0])) {
            int pc = getCurrentPC(); 
            bool actualOutcome = getActualBranchOutcome(v[0]); 
            bool predictedOutcome = predictBranch(pc); 
            updatePredictor(pc, actualOutcome); 
            if (predictedOutcome == actualOutcome) {
                predictorCorrect++;
            } else {
                predictorIncorrect++;
            }
        }
    string addressAdder="";
    string temp="";
    int t=0;
    int offset=0;
    string opcode = v2[0];
    if (opcode == "lw") {
        // cout<<v[2]<<endl;
        int rd = stoi(v2[1].substr(1));
        addressAdder=v2[2];
              if(!isdigit(v2[2][0])){
                
                    x[rd] =  reinterpret_cast< long long int>(memory);
                    isMemoryOperation = true;
                    address = x[rd];
                    // cout<<x[rd]<<endl;
                }
                else{
        for(char d : addressAdder){
            if(isdigit(d)){
                temp+=d;
            }
            else{
                break;
            }
        }
        offset = stoi(temp);
        temp="";
        for(char d : addressAdder){
            if(d=='x'){
                temp+=d;
                t=1;
            }
            if(t==1){
               if(isdigit(d)){
                    temp+=d;
                } 
            }
        }
        int rs1 = stoi(temp.substr(1));
        int* array_ptr = reinterpret_cast<int*>(x[rs1]+offset);
        x[rd] = *array_ptr;
        isMemoryOperation = true;
        address = *array_ptr;
        // cout<<" "<<x[rd]<<" "<<x[rs1]+offset<<endl;
                }

        temp="";t=0;
    } 
    else if (opcode == "la") {
        int rd = stoi(v[1].substr(1));
        addressAdder=v[2];
              if(!isdigit(v2[2][0])){
                
                    x[rd] =  reinterpret_cast< long long int>(memory);
                    // cout<<x[rd]<<endl;
                }
                else{
        for(char d : addressAdder){
            if(isdigit(d)){
                temp+=d;
            }
            else{
                break;
            }
        }
        offset = stoi(temp);
        temp="";
        for(char d : addressAdder){
            if(d=='x'){
                temp+=d;
                t=1;
            }
            if(t==1){
               if(isdigit(d)){
                    temp+=d;
                } 
            }
        }
        int rs1 = stoi(temp.substr(1));
            
        int* array_ptr = reinterpret_cast<int*>(x[rs1]+offset);
        x[rd] = *array_ptr;
        // cout<<" "<<x[rd]<<" "<<x[rs1]<<endl;
                }

        temp="";t=0;
    } 
    else if (opcode == "sw") {
         int rd = stoi(v2[1].substr(1));
        addressAdder = v2[2];
        for (char d : addressAdder) {
            if (isdigit(d)) {
                temp += d;
            } else {
                break;
            }
        }
        offset = stoi(temp);
        temp = "";
        for (char d : addressAdder) {
            if (d == 'x') {
                temp += d;
                t = 1;
            }
            if (t == 1) {
                if (isdigit(d)) {
                    temp += d;
                }
            }
        }
        int rs1 = stoi(temp.substr(1));
        int* memory_ptr = reinterpret_cast<int*>(x[rs1] + offset);
        isMemoryOperation = true;
        address = *memory_ptr;
        *memory_ptr = x[rd];
        temp = "";
        t = 0;
    }
    v2.clear();
    return;  
    }

}

void independentWriteBack(){
    // cout<<"write back";
    // cout<<endl;
    x[destination] = value;
    destination = 0;
    value = 0;
    v2 = v1;
    v1.clear();
    return;
}
    bool predictBranch(int pc) {
        int prediction = predictorTable[pc];
        return (prediction >= 2);
    }
    void updatePredictor(int pc, bool actualOutcome) {
        int& prediction = predictorTable[pc];
        if (actualOutcome) {
            if (prediction < 3) {
                prediction++;
            }
        } else {
            if (prediction > 0) {
                prediction--;
            }
        }
    }
int one_cycle(int memory[]){
    if(detectMemoryHazardStall()){
        if(instruction.empty()){
            t++;
        if(t == 4){
            return 1;
            }                 
        }  
            independentMemory(decodedinstruction,memory);
            independentWriteBack();       
            independentExecute(decodedinstruction,memory);   
            decodedinstruction = independentInstructionDecode(instruction);
            instruction =  independentInstructionFetch(); 

            independentMemory(decodedinstruction,memory);
            independentWriteBack();       
            decodedinstruction = independentInstructionDecode(instruction);  
    }
    else{
        if(instruction.empty()){
            t++;
            if(t == 4 + stalls){
                return 1;
            }         
        }
        independentMemory(decodedinstruction,memory);
        independentWriteBack();   
        independentExecute(decodedinstruction,memory);
            if(!isStall){    
            decodedinstruction = independentInstructionDecode(instruction);
        }
        if(!instruction.empty()){
            instruction =  independentInstructionFetch();
        }
            
    
    }
        isStall1=false;
        isStall=false;
}
    int one_cycle1(int memory[]){
    if(detectMemoryHazardStall()){
        if(instruction.empty()){
            t++;
        if(t == 1){
            return 1;
            }                 
        }  
            independentMemory(decodedinstruction,memory);    
            independentExecute1(decodedinstruction,memory);   
            decodedinstruction = independentInstructionDecode1(instruction);
            instruction =  independentInstructionFetch(); 

            independentMemory(decodedinstruction,memory);
            decodedinstruction = independentInstructionDecode1(instruction);  
    }
    else{
        if(instruction.empty()){
            t++;
            if(t == 4 + stalls){
                return 1;
            }         
        }
        independentMemory(decodedinstruction,memory);
        independentExecute1(decodedinstruction,memory);
        if(!isStall){    
            decodedinstruction = independentInstructionDecode1(instruction);
        }
            instruction =  independentInstructionFetch();
    }
        isStall1=false;
        isStall=false;
}

    void jump(const string& label) {
        isStall=true;
        pc = mnew[label];
    }
    void getPredictorStatistics(int& correct, int& incorrect) {
        correct = predictorCorrect;
        incorrect = predictorIncorrect;
    }
};

// Define Cache Block structure
struct CacheBlock {
    bool valid;
    int tag;
    vector<int> data;
    int accessTime; // For LRU and MRU
};

class Cache {
private:
    int cacheSize;
    int blockSize;
    int associativity;
    bool replacement_policy;
    
    int numSets;
    
    vector<vector<CacheBlock>> cache;

public:
int accessLatency;
int memoryAccess;
    int misses;
    Cache(int size, int bSize, int assoc, int latency) 
        : cacheSize(size), blockSize(bSize), associativity(assoc), accessLatency(latency) {
        numSets = cacheSize / (blockSize * associativity);
        memoryAccess = 0;
        misses = 0;
       replacement_policy = true;//for LRU and false for MRU
        cache.resize(numSets, vector<CacheBlock>(associativity, {false, -1, vector<int>(blockSize, 0), 0}));
    }

    // Access cache to read/write data
    bool accessCache(int address, bool isWrite, vector<int>& data) {
        int setIndex = (address / blockSize) % numSets;
        int tag = address / (blockSize * numSets);
        memoryAccess++;

        // Search for the block in the cache
        for (int i = 0; i < associativity; ++i) {
            if (cache[setIndex][i].valid && cache[setIndex][i].tag == tag) {
                // Cache hit
                cache[setIndex][i].accessTime = memoryAccess; // Update access time
                if (isWrite) {
                    cache[setIndex][i].data = data; // Update cache block data if it's a write operation
                } else {
                    data = cache[setIndex][i].data; // Read data from cache
                }
                return true;
            }
        }
        // Cache miss
        insertBlock(address, data);
        misses++;
        return false;
    }

    // Insert block into cache
    void insertBlock(int address, vector<int>& data) {
        int setIndex = (address / blockSize) % numSets;
        int tag = address / (blockSize * numSets);

        // Find an empty slot or evict a block based on a replacement policy
        int emptySlot = -1;
        for (int i = 0; i < associativity; ++i) {
            if (!cache[setIndex][i].valid) {
                emptySlot = i;
                break;
            }
        }

        if (emptySlot != -1) {
            // Found an empty slot
            cache[setIndex][emptySlot].valid = true;
            cache[setIndex][emptySlot].tag = tag;
            cache[setIndex][emptySlot].data = data;
            cache[setIndex][emptySlot].accessTime = memoryAccess; // Update access time
        } else {
            // Implement replacement policy here (LRU or MRU)
           int replaceIndex = -1;
            if (replacement_policy) {
                // Find the least recently used block
                int minAccessTime = numeric_limits<int>::max();
                for (int i = 0; i < associativity; ++i) {
                    if (cache[setIndex][i].accessTime < minAccessTime) {
                        minAccessTime = cache[setIndex][i].accessTime;
                        replaceIndex = i;
                    }
                }
            } else {
                // Find the most recently used block
                int maxAccessTime = numeric_limits<int>::min();
                for (int i = 0; i < associativity; ++i) {
                    if (cache[setIndex][i].accessTime > maxAccessTime) {
                        maxAccessTime = cache[setIndex][i].accessTime;
                        replaceIndex = i;
                    }
                }
            }

            // Evict the block based on the replacement policy (LRU or MRU)
            cache[setIndex][replaceIndex].valid = true;
            cache[setIndex][replaceIndex].tag = tag;
            cache[setIndex][replaceIndex].data = data;
            cache[setIndex][replaceIndex].accessTime = memoryAccess; // Update access time
        }
    }

    // Get access latency
    
    // Get access latency
    int getAccessLatency() {
        return accessLatency;
    }
};

class processor {
private:
    std::vector<core> cores;
    int *memory;
    int clock;
    Cache cache;
    vector<string> decodedInstruction;
    vector<int> data;
    bool isMemoryOperation;
public:

    processor(const vector<string>& filenames, int cacheSize, int blockSize, int associativity, int cacheLatency, int memoryLatency): cache(cacheSize, blockSize, associativity, cacheLatency) {
        memory = new int[1024];
        cores.push_back(core("C:/Users/Manan/Desktop/Manan/test5.txt"));//choose path from the provided files
        cores.push_back(core("C:/Users/Manan/Desktop/Manan/test5.txt"));//choose path from the provided files
        clock = 0;      
    }

void independentRun() {
    bool core0_finished = false;
    bool core1_finished = false;

    while (!core0_finished || !core1_finished) {
        if (!core0_finished) {
            isMemoryOperation = cores[0].isMemoryOperation;
            if(isMemoryOperation){
                if(!cache.accessCache(cores[0].address,false,data)){cache.accessLatency = cache.accessLatency+50;}
                }
                cores[0].isMemoryOperation = false;  
            if(isMemoryOperation){}          
            int* address = reinterpret_cast<int*>(&cores[0].newmemory[cores[0].pc]);
            // cout<<*address<<endl;
            if(!cache.accessCache(*address,false,data)){cache.accessLatency = cache.accessLatency+50;}
            if (cores[0].one_cycle(memory) == 1) {
                core0_finished = true;
            }
        }

        if (!core1_finished) {
            isMemoryOperation = cores[1].isMemoryOperation;
            if(isMemoryOperation){
                if(!cache.accessCache(cores[1].address,false,data)){cache.accessLatency = cache.accessLatency+50;}
                }
                cores[1].isMemoryOperation = false;
            int* address = reinterpret_cast<int*>(&cores[1].newmemory[cores[1].pc]);
            // cout<<*address<<endl;
            if(!cache.accessCache(*address,false,data)){cache.accessLatency = cache.accessLatency+50;}
            if (cores[1].one_cycle(memory + 512) == 1) {
                core1_finished = true;
            }
        }
        clock++;
    }

    for (int i = 0; i < 1024; ++i) {
        cout << memory[i] << " ";
    }
    cout<<endl;
        cout<<"the no. of clock cycle for first program is:"<<cores[0].clock1<<endl;
        cout<<"the no. of Stalls for first program is:"<<cores[0].stalls<<endl;
        cout<<"the no. of IPC for first program is:"<<(float)cores[0].instructionCount/(cores[0].clock1+cache.accessLatency)<<endl;
        cout<<cache.accessLatency<<endl<<cache.misses<<endl<<cache.memoryAccess<<endl;
                cout<<"Miss rate:"<<((float)cache.misses/(float)cache.memoryAccess)*100<<endl;

        cout<<endl;
        for(int i =0;i<32;++i){
            cout<<cores[0].x[i]<<" ";
        }
        cout << endl;
        for (int i = 0; i < 32; ++i) {
            cout << cores[1].x[i] << " ";
        }
        cout<<endl;
        cout << "the no. of clock cycle for second program is:" << cores[1].clock1 << endl;
        cout << "the no. of Stalls for second program is:" << cores[1].stalls<<endl;
        cout<<"the no. of IPC for first program is:"<<(float)cores[1].instructionCount/(cores[1].clock1+cache.accessLatency)<<endl;
}
    void independentRun1() {
    bool core0_finished = false;
    bool core1_finished = false;

    while (!core0_finished || !core1_finished) {
        if (!core0_finished) {
            isMemoryOperation = cores[0].isMemoryOperation;
            if(isMemoryOperation){
                if(!cache.accessCache(cores[0].address,false,data)){cache.accessLatency = cache.accessLatency+50;}
                }
                cores[0].isMemoryOperation = false;
            int* address = reinterpret_cast<int*>(&cores[0].newmemory[cores[0].pc]);
            // cout<<*address<<endl;
            if(!cache.accessCache(*address,false,data)){cache.accessLatency = cache.accessLatency+50;}
            if (cores[0].one_cycle1(memory) == 1) {
                core0_finished = true;
            }
        }

        if (!core1_finished) {
            isMemoryOperation = cores[1].isMemoryOperation;
            if(isMemoryOperation){
                if(!cache.accessCache(cores[1].address,false,data)){cache.accessLatency = cache.accessLatency+50;}
                }
                cores[1].isMemoryOperation = false;
            int* address = reinterpret_cast<int*>(&cores[0].newmemory[cores[1].pc]);
            // cout<<*address<<endl;
            if(!cache.accessCache(*address,false,data)){cache.accessLatency = cache.accessLatency+50;}
            if (cores[1].one_cycle1(memory + 512) == 1) {
                core1_finished = true;
            }
        }
        clock++;
    }

    for (int i = 0; i < 1024; ++i) {
        cout << memory[i] << " ";
    }
    cout<<endl;
        cout<<"the no. of clock cycle for first program is:"<<cores[0].clock1<<endl;
        cout<<"the no. of Stalls for first program is:"<<cores[0].stalls<<endl;
        cout<<"the no. of IPC for first program is:"<<(float)cores[0].instructionCount/(cores[0].clock1+cache.accessLatency);
        // cout<<cache.accessLatency<<endl<<cache.misses<<endl<<cache.memoryAccess<<endl;
        cout<<"Miss rate:"<<((float)cache.misses/(float)cache.memoryAccess)*100<<endl;
        cout<<endl;
        for(int i =0;i<32;++i){
            cout<<cores[0].x[i]<<" ";
        }
        cout << endl;
        for (int i = 0; i < 32; ++i) {
            cout << cores[1].x[i] << " ";
        }
        cout<<endl;
        cout << "the no. of clock cycle for second program is:" << cores[1].clock1 << endl;
        cout << "the no. of Stalls for second program is:" << cores[1].stalls<<endl;
        cout<<"the no. of IPC for first program is:"<<(float)cores[1].instructionCount/(cores[1].clock1+cache.accessLatency);
    }
};

int main() {
    vector<string> filenames = {"C:/Users/Manan/Desktop/Manan/test5.txt", "C:/Users/Manan/Desktop/Manan/test5.txt"};
    processor p(filenames, 1024, 64, 4, 10, 50);
    int address = 1024; // Example address
    bool isWrite = false; // Read operation
    vector<int> data;
    int n;
    cout << "choose 1 for program with data forwarding"<<endl;
    cout << "choose 0 for program without data forwarding"<<endl;
    cin >> n;
    if(n == 1){
        p.independentRun1(); // Start the execution of the processor
    }
    else if(n == 0){
        p.independentRun(); // Start the execution of the processor
    }
    else{
        cout<<"what about 0 and 1 is that you don't understand.";
    }
    
    return 0;
}
