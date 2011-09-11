/** Arduino library for manipulating numbers
 *
 * @license Apache License Version 2.0
 * @author Nicolas Herment
 * nherment@gmail.com
 */

#include "WProgram.h"
#include "Number.h"


void Number::minValue(double* array, int arrayLength, double* minVal) {
    *minVal = array[0];
    for(int i=1 ; i < arrayLength ; i++) {
        *minVal = min(array[i], *minVal);
    }
}

void Number::maxValue(double* array, int arrayLength, double* maxVal) {
    *maxVal = array[0];
    for(int i=1 ; i < arrayLength ; i++) {
        *maxVal = max(array[i], *maxVal);
    }
}
