

/*!
* @file Heartrate.h
* @brief Heartrate.h detailed description for Heartrate.cpp 
*
*  This is written for the heart rate sensor the company library. Mainly used for real 
*  time measurement of blood oxygen saturation, based on measured values calculate heart rate values.
* 
* @author linfeng(490289303@qq.com)
* @version  V1.0
* @date  2015-12-24
*/

#ifndef __HEARTRATE__H
#define __HEARTRATE__H
          

#include "Arduino.h"


#define ANALOG_MODE 0
#define DIGITAL_MODE 1


#define SAMPLE_NUMBER 100


class Heartrate
{
public:
    Heartrate(char mode) { mode_ = mode; }
	char maxNumber(unsigned char count);
	void minNumber(unsigned char count);
	unsigned int analogGetRate(void);
	unsigned int digitalGetRate(void);
	unsigned int getRate(void);
	unsigned int getValue(unsigned char pin,unsigned char count);	
	
private:	
	
	unsigned char mode_;	
	unsigned char valueCount_;
	unsigned char valueFlag;	
	
};

#endif

/******************************************************************************
  Copyright (C) <2015>  <linfeng>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  Contact: 490289303@qq.com
 ******************************************************************************/
 
 