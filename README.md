# Branch-Prediction-Simulator
It simulates a simple branch predictor with a 2-bit saturating counter. You are provided with a text file containing a trace of branch instructions consisting of the PC at which each branch occurs, and whether the branch is Taken or Not Taken. 
Your goal is write code to evaluate the performance of a 2-bit saturating counter based branch predictor on this trace. Your output file indicates, for each branch in the trace, whether it was predicted as Taken or Not Taken. 

# Branch Predictor Architecture
The design consists of 2^m 2-bit saturating counters indexed using m LSBs of each branch instruction. Each 2-bit saturating predictor starts in the 11 (Predict Taken with High Confidence) state and is updated as per the finite state machine. The value of m is specified in a config file config.txt. 

# Config File
The config file config.txt contains a single line with the value of m. The largest value of m is 32 (for 32 bit PCs).

# Trace File
The trace file, trace.txt, contains one branch per line. Each line has the PC for the corresponding branch (in hex format) followed by a single bit indicating Taken (1) or Not Taken (0). A sample trace file is provided.  

# Output Format
The output from the simulator is a file trace.txt.out that has one line per branch. Each line has a single bit which indicates whether that branch was predicted as Taken (1) or Not Taken (0).

The simulator outputs a file trace.txt.out in the same directory.

The branch misprediction rate as a function of m with m varying from 10 to 20 is also calculated.
 

