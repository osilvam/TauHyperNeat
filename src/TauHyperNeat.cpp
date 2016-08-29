#ifndef TAUHYPERNEAT_CPP
#define TAUHYPERNEAT_CPP

#include "TauHyperNeat.hpp"

using namespace ANN_USM;

TauHyperNeat::TauHyperNeat(vector < double * > inputs, vector < double * > outputs, char * config_file)
{
	// ============================= READING JSON FILE ============================= //
	ifstream file;
	file.open(config_file);
	string hyperneat_info((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	// ============================================================================= //	

	substrate = new Substrate(inputs,outputs);
	
	hyperNeatJsonDeserialize(hyperneat_info);	
}

TauHyperNeat::~TauHyperNeat()
{
	free(substrate);
	vector<CPPNInputs>().swap(AditionalCPPNInputs);
}

void TauHyperNeat::hyperNeatJsonDeserialize(string hyperneat_info)
{
	int dataNumber = 0;

	char str[(int)hyperneat_info.size()];
	strcpy(str, hyperneat_info.c_str());
	const char delimeters[] = "{\"\t\n:,[ ]}";
	char *pch = strtok(str, delimeters);
	
	if(!strcmp(pch,(char *)"n_AditionalCPPNInputs"))
	{
		dataNumber++;

		pch = strtok(NULL, delimeters);
		int n_AditionalCPPNInputs = atoi(pch);
		pch = strtok(NULL, delimeters);

		if(!strcmp(pch,(char *)"AditionalCPPNInputs"))
		{
			dataNumber++;

			for(int i = 0; i < n_AditionalCPPNInputs; i++)
			{
				pch = strtok(NULL, delimeters);		
				if (!strcmp(pch,(char *)"BIAS"))
				{	
					char * aux = pch;
					pch = strtok(NULL, delimeters);						
					AditionalCPPNInputs.push_back(CPPNInputs(aux, atof(pch)));
				}else																
					AditionalCPPNInputs.push_back(CPPNInputs(pch));
			}						
			pch = strtok(NULL, delimeters);					
		}
	}
	
	if(!strcmp(pch,(char *)"connection_threshold"))
	{
		dataNumber++;

		pch = strtok(NULL, delimeters);
		connection_threshold = atof(pch);
		pch = strtok(NULL, delimeters);
	}
	if (!strcmp(pch,(char *)"Substrate"))
	{	
		dataNumber++;

		pch = strtok(NULL, delimeters);
		pch = substrate->SJsonDeserialize(pch);
	}

	if(dataNumber != TAUHYPERNEAT_DATANUMBER)
	{
		cerr << "TAUHYPERNEAT ERROR:\tThe hyperneat config file is not correct" << endl;
		exit(0);
	}

	clog << "TAUHYPERNEAT:\tSuccessful serialization" << endl;
}

bool TauHyperNeat::createSubstrateConnections(Genetic_Encoding * organism)
{
	okConnections = false;

	if(substrate->GetLayersNumber() == 0)
	{
		cerr << "TAUHYPERNEAT ERROR:\tDoes not exist any substrate initialized" << endl;
		return false;
	}

	if(2*(substrate->GetLayersNumber() - 1) != organism->getNEATOutputSize())
	{
		cerr << "TAUHYPERNEAT ERROR:\tThe layout number does not correspond to the cppn output number" << endl;
		return false;
	}

	for(int i = 0; i < substrate->GetLayersNumber()-1; i++)
	{				
		substrate->ClearSpatialNodeInputs(i+1);

		for(int j = 0; j < substrate->GetLayerNodesNumber(i); j++)
			for(int k = 0; k < substrate->GetLayerNodesNumber(i+1); k++)
			{
				vector < double > cppn_inputs;
				vector < double > cppn_output;
				vector < double > c1 = (substrate->GetSpatialNode(i,j))->GetCoordenates();
				vector < double > c2 = (substrate->GetSpatialNode(i+1,k))->GetCoordenates();
				cppn_inputs.insert(cppn_inputs.end(), c1.begin(), c1.end());
				cppn_inputs.insert(cppn_inputs.end(), c2.begin(), c2.end());

				for(int c = 0; c < (int)AditionalCPPNInputs.size(); c++)
					cppn_inputs.push_back(AditionalCPPNInputs.at(c).Eval(cppn_inputs));
				
				cppn_output = organism->eval(cppn_inputs);

				if(abs(cppn_output.at(i*2)) > connection_threshold)
					(substrate->GetSpatialNode(i+1,k))->AddInputToNode(substrate->GetSpatialNode(i,j), cppn_output.at(i*2), cppn_output.at(i*2 + 1));				
			}
	}		
	
	for(int i = 0; i < substrate->GetLayersNumber(); i++)
		for(int j = 0; j < substrate->GetLayerNodesNumber(i); j++)
			if((substrate->GetSpatialNode(i,j))->GetNodeType() == 2 && (substrate->GetSpatialNode(i,j))->ActiveNode())
			{
				okConnections = true;
				//clog << "TAUHYPERNEAT:\tConnections successfully created" << endl;
				return true; 
			}

	cerr << "TAUHYPERNEAT ERROR:\tDoes not exist any active output node" << endl;
	return false;
	
}

bool TauHyperNeat::createSubstrateConnections(char * path)
{
	Genetic_Encoding * organism = new Genetic_Encoding();
	organism->load(path);

	return createSubstrateConnections(organism);	
}

bool TauHyperNeat::evaluateSubstrateConnections()
{
	if(substrate->GetLayersNumber() == 0){
		cerr << "TAUHYPERNEAT ERROR:\tDoes not exist any substrate initialized" << endl;
		return false;
	}

	if(!okConnections) 
	{
		cerr << "TAUHYPERNEAT ERROR:\tDoes not exist any active output node" << endl;
		return false;
	}

	for(int i = 0; i < substrate->GetLayersNumber(); i++)
		substrate->EvaluateSpatialNode(i);

	return true;
}

void TauHyperNeat::printConnectionFile(Genetic_Encoding * organism, const char fileName[])
{
	if(!createSubstrateConnections(organism))
	{
		cerr << "TAUHYPERNEAT ERROR:\tThe connection file can not be printed" << endl;
		return;
	}

	ofstream myfile (fileName);

	if(myfile.is_open())
	{
		myfile << substrate->getSubstrateConnectionString() << endl;
	}
	else
	{
		cerr << "TAUHYPERNEAT ERROR:\tUnable to create the file: " << fileName << endl;
		return;
	}

	myfile.close();

	clog << "TAUHYPERNEAT:\tTauHyperNeat connection file was printed successfully" << endl;
}

void TauHyperNeat::printConnectionFile(char * path, const char fileName[])
{
	Genetic_Encoding * organism = new Genetic_Encoding();
	organism->load(path);

	printConnectionFile(organism, fileName);
}

#endif