#ifndef CPPNINPUTS_H
#define CPPNINPUTS_H

#include <cmath>
#include <vector>
#include <cstring>

using namespace std;
/**
 * \namespace ANN_USM
 * \brief Dedicated to artificial intelligence development in Santa María University.
 */
namespace ANN_USM{
	/** 
	 * \class CPPNInputs.
	 * \brief The class CPPNInputs is used to create cppn inputs.
	 */
	class CPPNInputs
	{
		double bias;/**< bias value. If the input corresponds to bias input, this variable store a bias input value. */
		char * type;/**< type poiter. Corresponds to char array with the input type name. */
		/**
		 * \brief Function that point to other function corresponding to type name.
		 * \note The function pointed corresponding to type name must be implemented in this class.
		 * \param point Vector of coordenate of each node, source and target.
		 * \return A function pointer return.
		 */
		double (CPPNInputs::*function)(vector < double > point);
		/**
		 * \brief Bias function.
		 * \param point Vector of coordenate of each node, source and target.
		 * \return Bias value.
		 */
		double Bias(vector < double > point);
		/**
		 * \brief Radius function of source node.
		 * \param point Vector of coordenate of each node, source and target.
		 * \return Radius value of source node.
		 */
		double Radius1(vector < double > point);
		/**
		 * \brief RAdius function of target node.
		 * \param point Vector of coordenate of each node, source and target.
		 * \return Radius value of target node.
		 */
		double Radius2(vector < double > point);	
		/**
		 * \brief Euclidian distance  function.
		 * \param point Vector of coordenate of each node, source and target.
		 * \return Euclidian distance value among source and target node.
		 */
		double EuclidianDistance(vector < double > point);	
		//double user_custom(vector<double> points);
	public:
		/**
		 * \brief Constructor.
		 * \param type Char array with the input type name.
		 * \param bias If the input corresponds to bias input, this variable store a bias input value.
		 */
		CPPNInputs(char type[], double bias = 0.0);
		/**
		 * \brief Destructor
		 */
		~CPPNInputs();		
		/**
		 * \brief Eval function.
		 * Eval the function corresponding to type name.
		 * \param point Vector of coordenate of each node, source and target.
		 * \return Returned value of function corresponding to type name.
		 */
		double Eval(vector < double > point);
		/**
		 * \brief Get cppn input type name.
		 * \return Char array with type name.
		 */
		char * GetType();
	};
}

#endif