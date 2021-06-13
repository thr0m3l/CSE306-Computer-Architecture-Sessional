#include <bits/stdc++.h>
using namespace std;
///sequence IONHAKEBDLMFPCJG
int ins_cnt = 0; ///to count number of instructions that each label points to in first iteration
int ln_cnt = 0;
int is_rtype =0;///to count line numbers in second iteration
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

string makehex(string s)
{
    stringstream ss;
    if(s[0]=='-')
    {
        s = s.substr(1,s.size());
        int d = 256- stoi(s);
        ss<<hex<<d;
    }
    else ss<<hex<<stoi(s);
    string result(ss.str());
    if (result.size()==1 && is_rtype==0) result = "0"+result;
    return result;
}

int main() {
    initialize();
    string line = "",label;
    map<string,int> labels;
    ifstream test ("test.txt");

    while(getline(test,line))
    {
        if(line[line.size()-1]==':')
        {
            label = line.substr(0,line.size()-1);
            //cout<<label<<" goto ins "<<ins_cnt<<endl;
            labels.insert(pair<string,int>(label, ins_cnt));
        }
        else if(line!="")
            ins_cnt++;
    }

    test.close();
    ifstream test1 ("test.txt");
    ofstream codefile("machine_code.txt");
    codefile<<"v2.0 raw"<<endl;

    while( getline(test1 ,line)) {

        istringstream ss(line);
        string inst[4],code;
        int i = 0;
        while (getline(ss, inst[i], ' ')) {i++;}
        for (i = 0; i < 4; i++)
        {
            //cout<<inst[i]<<" ";
        }
        //cout<<endl;
        i=0;
        if(inst[0][inst[0].size()-1]!=':')
        {
            if(inst[0]=="add"||inst[0]=="sub"||inst[0]=="and"||inst[0]=="or"||inst[0]=="nor")
            {
                ln_cnt++;
                inst[1] = inst[1].substr(0,inst[1].size()-1);
                inst[2] = inst[2].substr(0,inst[2].size()-1);

                code = opcode[inst[0]]+registers[inst[2]]+registers[inst[3]]+registers[inst[1]]+"0";
                //cout<<code<<endl;
                codefile<<code<<endl;
            }

            if(inst[0]=="sll"||inst[0]=="srl")
            {
                is_rtype =1;
                ln_cnt++;
                inst[1] = inst[1].substr(0,inst[1].size()-1);
                inst[2] = inst[2].substr(0,inst[2].size()-1);

                code = opcode[inst[0]]+"0"+registers[inst[2]]+registers[inst[1]]+makehex(inst[3]);
                //cout<<code<<endl;
                codefile<<code<<endl;
                is_rtype =0;
            }

            if(inst[0]=="addi"||inst[0]=="subi"||inst[0]=="andi"||inst[0]=="ori"||inst[0]=="nori")
            {
                ln_cnt++;
                inst[1] = inst[1].substr(0,inst[1].size()-1);
                inst[2] = inst[2].substr(0,inst[2].size()-1);

                code = opcode[inst[0]]+registers[inst[2]]+registers[inst[1]]+ makehex(inst[3]);
                //cout<<code<<endl;
                codefile<<code<<endl;
            }

            if(inst[0]=="lw"||inst[0]=="sw")
            {
                ln_cnt++;
                inst[1] = inst[1].substr(0,inst[1].size()-1);
                inst[2] = inst[2].substr(0,inst[2].size()-1);

                string offset = inst[2].substr(0,inst[2].find('('));
                string reg = inst[2].substr(inst[2].find('(')+1,inst[2].size());

                code = opcode[inst[0]]+registers[reg]+registers[inst[1]]+makehex(offset);
                //cout<<code<<endl;
                codefile<<code<<endl;
            }

            if(inst[0]=="j")
            {
                ln_cnt++;

                code = opcode[inst[0]]+ makehex(to_string(labels[inst[1]]))+"00";
                //cout<<code<<endl;
                codefile<<code<<endl;
            }

            if(inst[0]=="beq"||inst[0]=="bneq")
            {
                ln_cnt++;
                inst[1] = inst[1].substr(0,inst[1].size()-1);
                inst[2] = inst[2].substr(0,inst[2].size()-1);

                int offset = labels[inst[3]]-ln_cnt-1;

                code = opcode[inst[0]]+registers[inst[2]]+registers[inst[1]]+ makehex(to_string(offset));
                cout<<ln_cnt<<" "<<offset<<endl;
                cout<<code<<endl;
                codefile<<code<<endl;
            }

        }
    }
    cout<<ln_cnt<<endl;
    return 0;
}
