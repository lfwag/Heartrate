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

#include "Heartrate.h"

Heartrate heartrate(DIGITAL_MODE); ///< ANALOG_MODE or DIGITAL_MODE

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned int rateValue;
  static unsigned char count;
  static unsigned int value[SAMPLE_NUMBER];  ///< Initializes the value of sampling points
  value[count]=heartrate.getValue(A1,count); ///< A1 foot sampled values
  count++;
  if(count>=SAMPLE_NUMBER)count=0;  
  rateValue = heartrate.getRate(); ///< Get heart rate value 
  if(rateValue)
  {
    Serial.println(rateValue);
  }  
  delay(20);
}

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
 
 
