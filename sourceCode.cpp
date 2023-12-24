#include <bits/stdc++.h>

using namespace std;

struct instruction{
    string type;
    string r1;
    string r2;
    string r3;
};
string alias(string x){
    if(x == "zero," || x == "zero"){
        return "x0,";
    }
    else if (x == "ra," || x == "ra")
    {
        return "x1,";
    }
    else if (x == "sp," || x == "sp")
    {
        return "x2,";
    }
    else if (x == "gp," || x == "gp")
    {
        return "x3,";
    }
    else if (x == "tp," || x == "tp")
    {
        return "x4,";
    }
    else if (x == "t0," || x == "t0")
    {
        return "x5,";
    }
    else if (x == "t1," || x == "t1")
    {
        return "x6,";
    }
    else if (x == "t2," || x == "t2")
    {
        return "x7,";
    }
    else if (x == "s0," || x == "s0" || x == "fp," || x == "fp")
    {
        return "x8,";
    }
    else if (x == "s1," || x == "s1")
    {
        return "x9,";
    }
    else if (x == "a0," || x == "a0")
    {
        return "x10,";
    }
    else if (x == "a1," || x == "a1")
    {
        return "x11,";
    }
    else if (x == "a2," || x == "a2")
    {
        return "x12,";
    }
    else if (x == "a3," || x == "a3")
    {
        return "x13,";
    }
    else if (x == "a4," || x == "a4")
    {
        return "x14,";
    }
    else if (x == "a5," || x == "a5")
    {
        return "x15,";
    }
    else if (x == "a6," || x == "a6")
    {
        return "x16,";
    }
    else if (x == "a7," || x == "a7")
    {
        return "x17,";
    }
    else if (x == "s2," || x == "s2")
    {
        return "x18,";
    }
    else if (x == "s3," || x == "s3")
    {
        return "x19,";
    }
    else if (x == "s4," || x == "s4")
    {
        return "x20,";
    }
    else if (x == "s5," || x == "s5")
    {
        return "x21,";
    }
    else if (x == "s6," || x == "s6")
    {
        return "x22,";
    }
    else if (x == "s7," || x == "s7")
    {
        return "x23,";
    }
    else if (x == "s8," || x == "s8")
    {
        return "x24,";
    }
    else if (x == "s9," || x == "s9")
    {
        return "x25,";
    }
    else if (x == "s10," || x == "s10")
    {
        return "x26,";
    }
    else if (x == "s11," || x == "s11")
    {
        return "x27,";
    }
    else if (x == "t3," || x == "t3")
    {
        return "x28,";
    }
    else if (x == "t4," || x == "t4")
    {
        return "x29,";
    }
    else if (x == "t5," || x == "t5")
    {
        return "x30,";
    }
    else if (x == "t6," || x == "t6")
    {
        return "x31,";
    }
    return x;
}

struct instruction parsing(struct instruction m){
    if (m.type != "ld" && m.type != "lw" && m.type != "lb" && m.type != "lh" && m.type != "lbu" && m.type != "lhu" && m.type != "lwu" && m.type != "sw" && m.type != "sd" && m.type != "sh" && m.type != "sb" )
            {
                m.r3 = m.r3 + ",";
            }
            else{
                int i = 0,j;
                while (1)
                {
                    if(m.r2.substr(i,1) == ")"){
                        break;
                    }
                    if( m.r2.substr(i,1) == "("){
                       j = i;   
                    }
                    i++;
                }
                m.r2 = m.r2.substr(j+1,i-j-1) + ",";
            }
            return m;
}
int main(){
    ifstream input1("compArchInput.txt");
    ifstream input2("compArchInput.txt");
    ofstream output("compArchOutput.txt");

    if(!input1){
        cout << "No such file" <<endl;
    }
    else{
        
        int nopCounter1 = 0;
        int nopCounter2 = 0;
        int cycles = 0;
        string a ; 
        string b ; 
        string c ; 

        getline(input1,a);
        getline(input1, b);

        output << "NO FORWARDING -\n\n" << a << endl;
        struct instruction last;
        struct instruction secLast;
        while (getline(input1,c))
        {   
            istringstream x(a);
            struct instruction m;
            x >> m.type >> m.r1 >> m.r2 >> m.r3;
            m = parsing(m);

            istringstream y(b);
            struct instruction n;
            y >> n.type >> n.r1 >> n.r2 >> n.r3;
            n = parsing(n);
            
            istringstream z(c);
            struct instruction o;
            z >> o.type >> o.r1 >> o.r2 >> o.r3;
            o = parsing(o);

            m.r1 = alias(m.r1);
            m.r2 = alias(m.r2);
            m.r3 = alias(m.r3);
            n.r1 = alias(n.r1);
            n.r2 = alias(n.r2);
            n.r3 = alias(n.r3);
            o.r1 = alias(o.r1);
            o.r2 = alias(o.r2);
            o.r3 = alias(o.r3);

            if(m.type != "sd" && m.type != "sw"  && m.type != "sh" && m.type != "sb"){
                if(n.type !=  "sd" && n.type != "sw"  && n.type != "sh"  && n.type != "sb" ){
                    if(m.r1 == n.r2 || m.r1 == n.r3){
                        if(m.r1 != "x0"){
                            if (nopCounter1 == 0)
                            {
                                output << "NOP\nNOP\n";
                                cycles += 2;
                                nopCounter2 = 1;
                            }
                            else if(nopCounter1 == 1){
                                output << "NOP\n";
                                cycles += 1;
                                nopCounter2 = 1;
                            }
                        }    
                    }
                }
                else{
                    if(m.r1 == n.r1 || m.r1 == n.r2){
                        if(m.r1 != "x0,"){
                            if (nopCounter1 == 0)
                            {
                                output << "NOP\nNOP\n";
                                cycles += 2;
                                nopCounter2 = 1;
                            }
                            else if(nopCounter1 == 1){
                                output << "NOP\n";
                                cycles += 1;
                                nopCounter2 = 1;
                            } 
                        }   
                    }
                }
            }
            
            output << b << endl;
            nopCounter1 = 0;
            if(m.type != "sd" && m.type != "sw" && m.type != "sh" && m.type != "sb"){
                if(o.type != "sd" && o.type != "sw" && o.type != "sh" && o.type != "sb"){
                    if(m.r1 == o.r2 || m.r1 == o.r3){

                        if(m.r1 != "x0,"){
                            if (nopCounter2 == 0)
                            {
                                output << "NOP\n";
                                cycles += 1;
                                nopCounter1 = 1;
                            }
                        }
                    }
                }
                    else{
                        if(m.r1 == o.r1 || m.r1 == o.r2){
                            if(m.r1 != "x0,"){
                                if (nopCounter2 == 0)
                                {   

                                    output << "NOP\n";
                                    cycles += 1;
                                    nopCounter1 = 1;
                                }
                            }
                    }
                    }
            }
            nopCounter2 = 0;
            a = b;
            b = c;
            cycles++;
        }
            
        istringstream x(a);
            x >> secLast.type >> secLast.r1 >> secLast.r2 >> secLast.r3;
            secLast = parsing(secLast);

            istringstream y(b);
            y >> last.type >> last.r1 >> last.r2 >> last.r3;
            last = parsing(last);
            getline(input1, b);

            secLast.r1 = alias(secLast.r1);
            secLast.r2 = alias(secLast.r2);
            secLast.r3 = alias(secLast.r3);
            last.r1 = alias(last.r1);
            last.r2 = alias(last.r2);
            last.r3 = alias(last.r3);

        if(secLast.type != "sd" && secLast.type != "sw" && secLast.type != "sh" && secLast.type != "sb"){
                if(last.type !=  "sd" && last.type != "sw" && secLast.type != "sh" && secLast.type != "sb"){
                    if(secLast.r1 == last.r2 || secLast.r1 == last.r3){
                        if(secLast.r1 != "x0,"){
                            if (nopCounter1 == 0)
                            {
                                output << "NOP\nNOP\n";
                                cycles += 2;
                            }
                            else if (nopCounter1 == 1)
                            {
                                output << "NOP\n";
                                cycles += 1;
                            }
                            

                        }    
                    }
                }
                else{
                    if(secLast.r1 == last.r1 || secLast.r1 == last.r2){
                        if(secLast.r1 != "x0,"){

                            if (nopCounter1 == 0)
                            {
                                output << "NOP\nNOP\n";
                                cycles += 2;
                            }
                            else if (nopCounter1 == 1)
                            {
                                output << "NOP\n";
                                cycles += 1;
                            }
                        }  
                    }
                }
            }
        output << b << endl;
        output << "\nTotal: " << cycles+6 << " cycles\n" <<endl;

        output <<"FORWARDING\n"<<endl;
        if(!input2){
            cout << "No such file" <<endl;
        }
        else{
            int cycles = 0;
            string a ; 
            string b ;

            getline(input2, a);
            output << a << endl;
            while (getline(input2, b))
            {
                istringstream x(a);
                struct instruction m;
                x >> m.type >> m.r1 >> m.r2 >> m.r3;
                m = parsing(m);
                
                istringstream y(b);
                struct instruction n;
                y >> n.type >> n.r1 >> n.r2 >> n.r3;

                n = parsing(n);

                m.r1 = alias(m.r1);
                m.r2 = alias(m.r2);
                m.r3 = alias(m.r3);
                n.r1 = alias(n.r1);
                n.r2 = alias(n.r2);
                n.r3 = alias(n.r3);

                if ((m.type == "ld" ||  m.type == "lw" ||  m.type == "lb" ||  m.type == "lh" ||  m.type == "lbu" ||  m.type == "lhu" ||  m.type == "lwu" ) && (n.type != "sd" &&  n.type != "sw" &&  n.type != "sh" &&  n.type != "sb") )
                {
                    if (m.r1 == n.r2 || m.r1 == n.r3)
                    {   
                        if(m.r1 != "x0,"){
                            output << "NOP" <<endl;
                            cycles ++;
                        }
                    }    
                }
                else if ((m.type == "ld" ||  m.type == "lw" ||  m.type == "lb" ||  m.type == "lh" ||  m.type == "lbu" ||  m.type == "lhu" ||  m.type == "lwu" ) && (n.type == "sd" ||  n.type == "sw" ||  n.type == "sh" ||  n.type == "sb"))
                {
                    if (m.r1== n.r2)
                    {
                        if(m.r1 != "x0,"){
                            output << "NOP" << endl;
                            cycles++;
                        }
                    }    
                }
                output << b << endl;
                cycles ++;
                a = b;
            }
            output << "\nTotal: " << cycles + 5 << " cycles"<<endl;    
        }

    }
}
