/** Arduino library: SCP1000
 *
 * Copyright 2011 Nicolas Herment
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SCP1000_H
#define SCP1000_H

#include "WProgram.h"

class SCP1000 {
public:
	unsigned long getTemperature();
	unsigned long getPressure();
	void update();
	void init();

private:

	char rev_in_byte;
	int temp_in;
	unsigned long pressure_lsb;
	unsigned long pressure_msb;
	unsigned long temp_pressure;
	unsigned long pressure;

	float tempC;

	char spi_transfer(volatile char data);
	char read_register(char register_name);
	unsigned long read_register16(char register_name);
	void write_register(char register_name, char register_value);

};
#endif;