#include <bits/stdc++.h>
using namespace std;
///sequence IONHAKEBDLMFPCJG
int ins_cnt = 0;
int ln_cnt = 0;
map<string,string> opcode;
map<string,string> registers;

void initialize()
{
    opcode.insert(pair<string,string>("sll","0"));
    opcode.insert(pair<string,string>("bneq","1"));
    opcode.insert(pair<string,string>("beq","2"));
    opcode.insert(pair<string,string>("ori","3"));
    opcode.insert(pair<string,string>("add","4"));
    opcode.insert(pair<string,string>("nor","5"));
    opcode.insert(pair<string,string>("and","6"));
    opcode.insert(pair<string,string>("addi","7"));
    opcode.insert(pair<string,string>("subi","8"));
    opcode.insert(pair<string,string>("sw","9"));
    opcode.insert(pair<string,string>("lw","a"));
    opcode.insert(pair<string,string>("andi","b"));
    opcode.insert(pair<string,string>("j","c"));
    opcode.insert(pair<string,string>("sub","d"));
    opcode.insert(pair<string,string>("srl","e"));
    opcode.insert(pair<string,string>("or","f"));

    registers.insert(pair<string,string>("$zero","0"));
    registers.insert(pair<string,string>("$t0","1"));
    registers.insert(pair<string,string>("$t1","2"));
    registers.insert(pair<string,string>("$t2","3"));
    registers.insert(pair<string,string>("$t3","4"));
    registers.insert(pair<string,string>("$t4","5"));
    registers.insert(pair<string,string>("$sp","6"));
}

int main() {
    initialize();
    string line = "";
    map<string,string> labels;
    ifstream test ("test.txt");
    while( getline(test ,line)) {
        ln_cnt++;
        istringstream ss(line);
        string inst[4];
        int i = 0;
        while (getline(ss, inst[i], ' ')) {i++;}
        for (i = 0; i < 4; i++)
        {
            cout<<inst[i]<<" ";
        }
        cout<<endl;
        i=0;
    }
    cout<<ln_cnt<<endl;
    return 0;
}
