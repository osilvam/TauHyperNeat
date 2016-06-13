#include <vector>
#include <stdlib.h>
#include <iostream>
#include <TAUHYPERNEAT>

#define INPUTS 4
#define OUTPUTS 4

using namespace std;
using namespace ANN_USM;

int main()
{
	srand (time(0));
	
	vector< double * > inputVector;
	vector< double * > outputVector;

	for(int i = 0; i < INPUTS; i++)
	{
		double * input = new double((100.0 - rand()%201)/100.0);
		double * output = new double(0.0);
		inputVector.push_back(input);
		outputVector.push_back(output);
	}

	TauHyperNeat tauhyperneat = TauHyperNeat(inputVector, outputVector, (char*)"tauhyperneat_config.json");

	tauhyperneat.createSubstrateConnections((char*)"genetic_encoding");

	tauhyperneat.evaluateSubstrateConnections();

	clog << endl;

	for(int i = 0; i < (int)inputVector.size(); i++)
		clog << "INPUT " << i << ":\t" << *inputVector.at(i) << endl;

	clog << endl;

	for(int i = 0; i < (int)outputVector.size(); i++)
		clog << "OUTPUT " << i << ":\t" << *outputVector.at(i) << endl;

	clog << endl;

	tauhyperneat.printConnectionFile((char*)"genetic_encoding");

	
	return 0;
}