/** Arduino library: Helper class for Number related manipulations
 *
 * @author Nicolas Herment
 * nherment@gmail.com
 */
#ifndef NUMBER_H
#define NUMBER_H

#include "WProgram.h"

class Number {
public:
	static void minValue(double* array, int arrayLength, double* minVal);
	static void maxValue(double* array, int arrayLength, double* maxVal);

};
#endif;