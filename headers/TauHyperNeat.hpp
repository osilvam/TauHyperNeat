#ifndef TAUHYPERNEAT_H
#define TAUHYPERNEAT_H

#include <NEAT>
#include "Substrate.hpp"
#include "CPPNInputs.hpp"
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define TAUHYPERNEAT_DATANUMBER 4

using namespace std;
/**
 * \namespace ANN_USM
 * \brief Dedicated to artificial intelligence development in Santa María University.
 */
namespace ANN_USM{
	/**
	 * \class TauHyperNeat
	 * \brief The TauHyperNeat class is used to implement a neuroevolution method called TauHyperNeat.
	 */
	class TauHyperNeat
	{
		// Vector of aditional cppn inputs
		vector < CPPNInputs > AditionalCPPNInputs;

		//Threshold that determine the creation for an connection
		double connection_threshold;

		//Indicated if the connections were created successfully
		bool okConnections;

	public:

		Substrate * substrate;/**< hyperNeat substrate */

		/**
		 * \brief Constructor with parameters.
		 * \param inputs Input vector.
		 * \param outputs Output vector.
		 * \param hyperneat_info_file Json file.
		 */
		TauHyperNeat(vector < double * > inputs, vector < double * > outputs, char * config_file);

		/**
		 * \brief Destructor.
		 */
		~TauHyperNeat();

		/**
		 * \brief Extract all TauHyperNeat information of json string.
		 * \param hyperneat_info json string.
		 */
		void hyperNeatJsonDeserialize(string hyperneat_info);

		/**
		 * \brief Create all substrate connections according to CPPN-NEAT result.
		 * \param organism Organism of CPPN-NEAT that will create connections in the substrate.
		 * \return The return value is true if the creation of connections was successful and false if it was not.
		 */
		bool createSubstrateConnections(Genetic_Encoding * organism);

		/**
		 * \brief Create all substrate connections according to CPPN-NEAT result.
		 * \param Path to the organism of CPPN-NEAT that will create connections in the substrate.
		 * \return The return value is true if the creation of connections was successful and false if it was not.
		 */
		bool createSubstrateConnections(char * path);

		/**
		 * \brief Allows to obtain the final TauHyperNeat outputs.
		 * \return The return value is true if the evaluation of connections was successful and false if it was not.
		 */
		bool evaluateSubstrateConnections();
		
		/**
		 * \brief This functions allows obtain the file with th information of all conections of all substrate nodes.
		 * \param organism Organism of CPPN-NEAT that will create connections in the substrate.
		 */
		void printConnectionFile(Genetic_Encoding * organism, const char fileName[] = "TauHyperNeat_Connections.txt");

		/**
		 * \brief This functions allows obtain the file with th information of all conections of all substrate nodes.
		 * \param Path to the organism of CPPN-NEAT that will create connections in the substrate.
		 */
		void printConnectionFile(char * path, const char fileName[] = "TauHyperNeat_Connections.txt");
	};
}
#endif