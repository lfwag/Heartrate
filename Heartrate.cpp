#include "Heartrate.h"

unsigned int value[SAMPLE_NUMBER]={0}; ///< Initialize sampling point value

/*!
* @brief Get a sample
*
* @brief  Get a sample
*
* @return unsigned int
*/ 
unsigned int Heartrate::getValue(unsigned char pin,unsigned char count)
{
	valueCount_ = count;
	value[valueCount_] = analogRead(pin); 
	return(value[count]);
}

/*!
* @brief Points to a valid node of the wave rise
*
* @brief  When the sampling point value increased 4 times in a row, considered to be a heartbeat
*
* @return char
*/ 

char Heartrate::maxNumber(unsigned char count)
{
	unsigned int temp1,temp2;
	for(int i=0;i<4;i++){
		if(count<i){
			temp1 = SAMPLE_NUMBER+count-i;
		}else{
			temp1 = count-i;
		}
		if(count<i+1){
			temp2 = SAMPLE_NUMBER+(count-1)-i;
		}else{
			temp2 = (count-1)-i;
		}		
		if(value[temp1]<=value[temp2])return(0);
	}
	if(valueFlag){
		valueFlag=1;
		return(0);
	}else{
		valueFlag=1;
		return(1);
	}	
}

/*!
* @brief Waveform down processing
*
* @brief  When the sample values decreased four times in a row, clear the heartbeat
*
* @return void
*/ 

void Heartrate::minNumber(unsigned char count)
{
	unsigned int temp1,temp2;
	for(int i=0;i<4;i++){
		if(count<i){
			temp1 = SAMPLE_NUMBER+count-i;
		}else{
			temp1 = count-i;
		}
		if(count<i+1){
			temp2 = SAMPLE_NUMBER+(count-1)-i;
		}else{
			temp2 = (count-1)-i;
		}		
		if(value[temp1]>=value[temp2])return;
	}
	valueFlag = 0;
	
}


/*!
* @brief Get heart rate value
*
* @brief  Sample ten times in a row beating heart rate value is computed
*
* @return unsigned int
*/ 

unsigned int Heartrate::analogGetRate(void)
{

	static unsigned char timeFlag;
	static unsigned long sampleTime[10];
	unsigned long valueTime_;
	minNumber(valueCount_);
	if(maxNumber(valueCount_))
	{
		sampleTime[timeFlag]=millis();
		
		unsigned char timeFlagMax = timeFlag;
		unsigned char timeFlagMin;
		if(timeFlag){
			timeFlagMin = timeFlag-1;
		}else{
			timeFlagMin = 9;
		}
		for(int i=0;i<9;i++){
			if((sampleTime[timeFlagMax]-sampleTime[timeFlagMin])<270 || (sampleTime[timeFlagMax]-sampleTime[timeFlagMin])>2000){
				timeFlag++;
				if(timeFlag>=10)timeFlag=0;
				return(0);
			}
			if(timeFlagMax){
				timeFlagMax--;
			}else{
				timeFlagMax = 9;
			}
			if(timeFlagMin){
				timeFlagMin--;
			}else{
				timeFlagMin = 9;
			}				
		}
		
		
		unsigned long Arrange[9]={0};
		unsigned char timeFlag_ = timeFlag++;
		for(int i=0;i<9;i++){
			if(timeFlag_){	
				Arrange[i] = sampleTime[timeFlag_]-sampleTime[timeFlag_-1];	
				timeFlag_--;				
			}else{
				Arrange[i] = sampleTime[0]-sampleTime[9];
				timeFlag_ = 9;
			}						
		}
		unsigned long Arrange_=0;
		for(int i=8;i>0;i--){
			for(int j=0;j<i;j++)
			if(Arrange[j]>Arrange[j+1]){
				Arrange_ = Arrange[j];
				Arrange[j] = Arrange[j+1];
				Arrange[j+1] = Arrange_;
			}
		}
		Arrange_ = 0;
		for(int i=2;i<=6;i++){
			Arrange_ += Arrange[i];
		}		

		if((Arrange[6]-Arrange[2])>100){
			return(0);
		}	
		
		valueTime_ = 300000/Arrange_;///<60*1000*(6-1)	
		return((unsigned int)valueTime_);
	}	
	return(0);
}

/*!
* @brief Get heart rate value
*
* @brief  Sample ten times in a row beating heart rate value is computed
*
* @return unsigned int
*/ 

unsigned int Heartrate::digitalGetRate(void)
{

	static unsigned char timeFlag;
	static unsigned long sampleTime[10];
	unsigned long valueTime_;
	unsigned char count_;
	
	if(valueCount_){
		count_ = valueCount_-1;
	}else{
		count_ = SAMPLE_NUMBER-1;
	}
	if((value[valueCount_]>1000)&&(value[count_]<20)){
		sampleTime[timeFlag]=millis();	
		
		unsigned char timeFlagMax = timeFlag;
		unsigned char timeFlagMin;
		if(timeFlag){
			timeFlagMin = timeFlag-1;
		}else{
			timeFlagMin = 9;
		}
		for(int i=0;i<9;i++){
			if((sampleTime[timeFlagMax]-sampleTime[timeFlagMin])<270 || (sampleTime[timeFlagMax]-sampleTime[timeFlagMin])>2000){
				timeFlag++;
				if(timeFlag>=10)timeFlag=0;
				return(0);
			}
			if(timeFlagMax){
				timeFlagMax--;
			}else{
				timeFlagMax = 9;
			}
			if(timeFlagMin){
				timeFlagMin--;
			}else{
				timeFlagMin = 9;
			}				
		}
		
		unsigned long Arrange[9]={0};
		unsigned char timeFlag_ = timeFlag++;
		for(int i=0;i<9;i++){
			if(timeFlag_){	
				Arrange[i] = sampleTime[timeFlag_]-sampleTime[timeFlag_-1];	
				timeFlag_--;				
			}else{
				Arrange[i] = sampleTime[0]-sampleTime[9];
				timeFlag_ = 9;
			}						
		}
		unsigned long Arrange_=0;
		for(int i=8;i>0;i--){
			for(int j=0;j<i;j++)
			if(Arrange[j]>Arrange[j+1]){
				Arrange_ = Arrange[j];
				Arrange[j] = Arrange[j+1];
				Arrange[j+1] = Arrange_;
			}
		}
		Arrange_ = 0;
		for(int i=2;i<=6;i++){
			Arrange_ += Arrange[i];
		}		
	
		if((Arrange[6]-Arrange[2])>100){
			return(0);
		}	
		
		valueTime_ = 300000/Arrange_;///<60*1000*(6-1)
		return((unsigned int)valueTime_);

	}else{
		return(0);
	}
}

/*!
* @brief Get heart rate value
*
* @brief  Sample ten times in a row beating heart rate value is computed
*
* @return unsigned int
*/ 
unsigned int Heartrate::getRate(void)
{
	if(mode_ == DIGITAL_MODE){
		return(digitalGetRate());
	}else{
		return(analogGetRate());
	}
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
 

    
