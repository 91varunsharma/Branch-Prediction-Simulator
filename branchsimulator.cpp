
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>
#include <stdio.h>
#include <map>

using namespace std;
//access state:
#define SN 00 // Strong Not Taken
#define WN 01 // Weak Not Taken
#define WT 10 // Weak Taken
#define ST 11 // Strong Taken



string getBits(bitset<32> addr, unsigned long counter_index_bits)
{
    string stringAddr = addr.to_string();
    string bits;
    bits = stringAddr.substr(32-counter_index_bits, counter_index_bits);

    return bits;
}

vector<unsigned long> counter(unsigned long indexRow)
{
    vector<unsigned long> myCounter;

    for (unsigned long i=0; i<indexRow; i++)
        {
            myCounter[i]= ST;
        }

    return myCounter;
}


int main(int argc, char* argv[]){


    ifstream params;
    unsigned long counter_index_bits;
    params.open(argv[1]);

        while (!params.eof())  // read config file
        {
            params >> counter_index_bits;

        }

    unsigned long indexRow = (unsigned long)pow(2, counter_index_bits);

    vector<unsigned long> saturating_counter(indexRow, ST);

    int BranchState = 0;
    unsigned long Misses=0;


        ifstream traces;
        ofstream tracesout;
        string outname;
        outname = string(argv[2]) + ".out";

        traces.open(argv[2]);
        tracesout.open(outname.c_str());

        string line;
        string accesstype;  // the Read/Write access type from the memory trace;
        string xaddr;       // the address from the memory trace store in hex;
        unsigned int addr;  // the address from the memory trace store in unsigned int;
        bitset<32> accessaddr; // the address from the memory trace store in the bitset;

        if (traces.is_open() && tracesout.is_open()) {
            while (getline(traces, line)) {

                istringstream iss(line);

                if (!(iss >> xaddr >> accesstype)) { break; }

               stringstream saddr(xaddr);
                saddr >> std::hex >> addr;

                accessaddr = bitset<32>(addr);

                
                string counterbits = getBits(accessaddr, counter_index_bits);
                char *ptr;
                long bits = strtol(counterbits.c_str(), &ptr, 2);
                

                unsigned long BranchState=0;

                if (accesstype.compare("1") == 0)
                {

                            if (saturating_counter[bits]==ST || saturating_counter[bits]==WT){

                                saturating_counter[bits]=ST;
                                BranchState=1;
                            }

                            else if (saturating_counter[bits]==WN){

                                saturating_counter[bits]=ST;
                                BranchState=0;
                            }

                            else if (saturating_counter[bits]==SN){

                                saturating_counter[bits]=WN;
                                BranchState=0;
                            }

                }

                 else if (accesstype.compare("0") == 0) {

                            if (saturating_counter[bits]==WN || saturating_counter[bits]==SN){

                                saturating_counter[bits]=SN;
                                BranchState=0;
                            }

                            else if (saturating_counter[bits]==WT){

                                saturating_counter[bits]=SN;
                                BranchState=1;
                            }

                            else if (saturating_counter[bits]==ST){

                                saturating_counter[bits]=WT;
                                BranchState=1;
                            }

                }

        if (((accesstype.compare("1") == 0)&& BranchState==0) || ((accesstype.compare("0") == 0)&& BranchState==1))

         {
                    Misses=Misses+1;
          }

                tracesout << BranchState
                          << endl;

            }
            traces.close();
            tracesout.close();
        } else cout << "\n Unable to open trace or traceout file ";



    return 0;
}
