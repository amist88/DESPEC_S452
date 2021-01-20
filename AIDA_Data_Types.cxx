#include "AIDA_Data_Types.h"


ADCDataItem::ADCDataItem(){

	fee64ID 	  = -1;  				//Top 6 bit of chIdentity (22:27) are FEE64 number
	channelID 	  = -1;				//Bottom 6 bits of chIdentity (16:21) are channel number
	real_channelID 	  = -1;				//Bottom 6 bits of chIdentity (16:21) are channel number
	adcRange 	  = -1;				//Bit 28 - Veto bit used as ADC range
	adcData 	  = -1; 				//Bits 0:15 of Word 0 is ADC data
	timestamp 	  = -1;				//Word 1, bits 0:27 - Timestamp LSB
	front_back	  = -1;
	layer_number	  = -1;
	calibrated_energy = -1;
	dataType = 0;
	ADC_Data = 0;
	timestampLSB = 0;
	sampleLength = 0;
}
void ADCDataItem::Set_Decay_Data(int* pdata, ULong64_t AIDA_Time_Base){

	//ADC_Data = *pdata;

	
	channelID = (*pdata >> 16) & 0xFFF;				//Bottom 6 bits of chIdentity (16:21) are channel number
	fee64ID   = (channelID >> 6) & 0x3F;           //Top 6 bit of chIdentity (22:27) are FEE64 number
	channelID &=0x3F;
	adcRange  = (*pdata >> 28 ) & 0x0001;			//Bit 28 - Veto bit used as ADC range
	adcData   = (*pdata & 0xFFFF); 				//Bits 0:15 of Word 0 is ADC data

	//ADC_Data = *pdata++;

	timestampLSB = (*pdata++ & 0x0FFFFFFF);			//Word 1, bits 0:27 - Timestamp LSB
	timestamp = (AIDA_Time_Base + timestampLSB)*10;		// Added to Timestamp base (x10 to convert to nanoseconds)
	
	/*fee64ID 	= Decay_Header_1->FEE64;  	//Top 6 bit of chIdentity (22:27) are FEE64 number
	channelID 	= Decay_Header_1->Ch_ID;	//Bottom 6 bits of chIdentity (16:21) are channel number
	adcRange 	= 0;				//Bit 28 - Veto bit used as ADC range
	adcData 	= Decay_Header_1->ADC_Data; 	//Bits 0:15 of Word 0 is ADC data
	timestamp 	= AIDA_Time_Base + Decay_Header_2->timestampLSB;		//Word 1, bits 0:27 - Timestamp LSB
	*/
	
}

void ADCDataItem::Set_Implant_Data(int* pdata, ULong64_t AIDA_Time_Base){

	//ADC_Data = *pdata;

	fee64ID   = (*pdata >> 22) & 0x003F;  			//Top 6 bit of chIdentity (22:27) are FEE64 number
	channelID = (*pdata >> 16) & 0x003F;				//Bottom 6 bits of chIdentity (16:21) are channel number
	adcRange  = (*pdata >> 28 ) & 0x0001;			//Bit 28 - Veto bit used as ADC range
	adcData   = (*pdata & 0xFFFF); 				//Bits 0:15 of Word 0 is ADC data
	
	//ADC_Data = *pdata++;

	timestampLSB = (*pdata++ & 0x0FFFFFFF);			//Word 1, bits 0:27 - Timestamp LSB
	timestamp = (AIDA_Time_Base + timestampLSB)*10;		// Added to Timestamp base (x10 to convert to nanoseconds)


	/*fee64ID 	= Decay_Header_1->FEE64;  	//Top 6 bit of chIdentity (22:27) are FEE64 number
	channelID 	= Decay_Header_1->Ch_ID;	//Bottom 6 bits of chIdentity (16:21) are channel number
	adcRange 	= 1;				//Bit 28 - Veto bit used as ADC range
	adcData 	= Decay_Header_1->ADC_Data; 	//Bits 0:15 of Word 0 is ADC data
	timestamp 	= AIDA_Time_Base + Decay_Header_2->timestampLSB;		//Word 1, bits 0:27 - Timestamp LSB
	*/
}

void ADCDataItem::SetTimestamp(ULong64_t newTimestamp){
	timestamp = newTimestamp;
}


double ADCDataItem::get_calibrated_energy(){
	return calibrated_energy;
}


ULong64_t ADCDataItem::GetTimestamp(){
	return timestamp;
}
int ADCDataItem::GetFEE64ID(){
	return fee64ID;
}
unsigned int ADCDataItem::GetADCRange(){
	return adcRange;
}
unsigned int ADCDataItem::GetChannelID(){
	return channelID;
}
unsigned int ADCDataItem::GetRealChannelID(){
	return real_channelID;
}
unsigned int ADCDataItem::GetADCData(){
	return adcData;
}
void ADCDataItem::SetADCRange(short range){
	adcRange = range;
}
void ADCDataItem::SetCalEnergy(double energyIn){
	calibrated_energy = energyIn;
}
void ADCDataItem::SetRealChannelID(int channelIDIn){
	real_channelID = channelIDIn;
}
void ADCDataItem::SetFront_Back(int x_y){
	front_back = x_y;

}
void ADCDataItem::SetLayer(int layer){
    layer_number = layer;
}

int ADCDataItem::GetFront_Back(){

	return front_back;

}
int ADCDataItem::GetLayer(){
    
	return layer_number;

}
void ADCDataItem::Print_Event(){
    
    cout<<"AIDA Event Variables: "<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"fee64ID 		= "<<fee64ID<<endl;
    cout<<"channelID 		= "<<channelID<<endl;
    cout<<"Real channelID       = "<<real_channelID<<endl;
    cout<<"adcRange 		= "<<adcRange<<endl;
    cout<<"Energy 		= "<<adcData<<endl;
    cout<<"Calibarated Energy 	= "<<calibrated_energy<<endl;
    cout<<"timestamp 		= "<<timestamp<<endl;
    cout<<"Front/Back 		= "<<front_back<<endl;
    cout<<"layer_number         = "<<layer_number<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<endl;
    

}

/*CalibratedADCDataItem::CalibratedADCDataItem(){};
CalibratedADCDataItem::CalibratedADCDataItem(ADCDataItem &adcDataItem){
	energy = adcDataItem.GetADCData();
	timestamp = adcDataItem.GetTimestamp();
	#ifdef DEB_CALIBRATOR
		//std::cout << "\nadcDataItem " << adcDataItem.GetADCData() << " - Non-calibratedItem " << energy << std::endl;
		//std::cout << "\nadcDataItem " << adcDataItem.GetTimestamp() << " - Non-calibratedItem " << timestamp << std::endl;
		#endif
};
void CalibratedADCDataItem::BuildItem(ADCDataItem &adcDataItem){
	energy = adcDataItem.GetADCData();
	timestamp = (adcDataItem.GetTimestamp())*10;	//Convwerts the timestamp to nanoseconds
	#ifdef DEB_CALIBRATOR
		//std::cout << "\nadcDataItem " << adcDataItem.GetADCData() << " - Non-calibratedItem " << energy << std::endl;
		//std::cout << "\nadcDataItem " << adcDataItem.GetTimestamp() << " - Non-calibratedItem " << timestamp << std::endl;
		#endif	
}
void CalibratedADCDataItem::SetDSSD(short dssdIn){
	dssd = dssdIn;
	return;
}
void CalibratedADCDataItem::SetSide(short sideIn){
	side = sideIn;
	return;
}
void CalibratedADCDataItem::SetStrip(short stripIn){
	strip = stripIn;
	return;
}
void CalibratedADCDataItem::SetADCRange(short adcRangeIn){
	adcRange = adcRangeIn;
	return;
}
void CalibratedADCDataItem::SetEnergy(double EnergyIn){
	energy = EnergyIn;
	return;
}
void CalibratedADCDataItem::SetTimestamp(unsigned long timestampIn){
	timestamp = timestampIn;
	return;
}
short CalibratedADCDataItem::GetDSSD() const{
	return dssd;
}
short CalibratedADCDataItem::GetSide() const{
	return side;
}
short CalibratedADCDataItem::GetStrip() const{
	return strip;
}
short CalibratedADCDataItem::GetADCRange() const{
	return adcRange;
}
double CalibratedADCDataItem::GetEnergy() const{
	return energy;
}
unsigned long CalibratedADCDataItem::GetTimestamp() const{
	return timestamp;
}

bool CalibratedADCDataItem::operator<(const CalibratedADCDataItem &dataItem) const{
	return dssd < dataItem.GetDSSD() || (dssd == dataItem.GetDSSD() && side < dataItem.GetSide())
			|| (dssd == dataItem.GetDSSD() && side == dataItem.GetSide() && strip < dataItem.GetStrip());
}
Cluster::Cluster(){
	dssd = -5;
	side = -5;
	stripMin = -5;
	stripMax = -5;
	Energy = -5;
	timestampMin = 0;
	timestampMax = 0;
	clusterMultiplicity = -5;
	eventMultiplicity = -5;
};
Cluster::Cluster(CalibratedADCDataItem &dataItem){
	dssd = dataItem.GetDSSD();
	side = dataItem.GetSide();
	stripMin = dataItem.GetStrip();
	stripMax = stripMin;
	Energy = dataItem.GetEnergy();
	adcRange = dataItem.GetADCRange();
	timestampMin = dataItem.GetTimestamp();
	timestampMax = timestampMin;
	clusterMultiplicity = 1;
	eventMultiplicity = 0;
}
void Cluster::AddEventToCluster(CalibratedADCDataItem dataItem){

	unsigned long timestampIn = dataItem.GetTimestamp();
	short stripIn = dataItem.GetStrip();


	if(timestampMin == 0 || timestampMax == 0){
		timestampMin = timestampIn;
		timestampMax = timestampIn;
	}
	else if(timestampIn < timestampMin){
		timestampMin = timestampIn;
	}
	else if(timestampIn > timestampMax){
		timestampMax = timestampIn;
	}
	else if(timestampIn == timestampMin || timestampIn == timestampMax){}

	if(stripIn < stripMin){
		stripMin = stripIn;
	}
	else if (stripIn > stripMax && stripMax != -5){
		stripMax = stripIn;
	}
	else if (stripMin == -5 || stripMax == -5){
		stripMin = stripIn;
		stripMax = stripIn;
	}
	if(clusterMultiplicity == -5){

		dssd = dataItem.GetDSSD();
		side = dataItem.GetSide();
		Energy = 0;
		adcRange = dataItem.GetADCRange();
		clusterMultiplicity = 0;
	}
	Energy += dataItem.GetEnergy();
	clusterMultiplicity++;
}
void Cluster::ResetCluster(){
	dssd = -5;
	side = -5;
	stripMin = -5;
	stripMax = -5;
	Energy = -5;
	timestampMin = 0;
	timestampMax = 0;
	clusterMultiplicity = -5;
	eventMultiplicity = -5;
}
short Cluster::GetDSSD() const{
	return dssd;
}
short Cluster::GetSide() const{
	return side;
}
short Cluster::GetStrip() const{
	return stripMax;
}
short Cluster::GetStripMin() const{
	return stripMin;
}
short Cluster::GetADCRange() const{
	return adcRange;
}
double Cluster::GetEnergy() const{
	return Energy;
}
unsigned long Cluster::GetTimestampMin() const{
	return timestampMin;
}
unsigned long Cluster::GetTimestampMax() const{
	return timestampMax;
}
short Cluster::GetSize() const{
	return clusterMultiplicity;
}
short Cluster::GetMultiplicity() const{
	return eventMultiplicity;
}
unsigned long Cluster::GetTimestampDifference(unsigned long timestampIn) const{
	unsigned long timestampDifMin;
	unsigned long timestampDifMax;

	timestampDifMin = abs(timestampMin-timestampIn);
	timestampDifMax = abs(timestampMax-timestampIn);

	if(timestampDifMin < timestampDifMax){
		return timestampDifMin;
	}
	else if(timestampDifMax < timestampDifMin){
		return timestampDifMax;
	}
	else if( timestampDifMin == timestampDifMax && timestampMin != 0){
		return timestampDifMin;
	}
	else if( timestampMin == 0){
		return 0;
	} 
	else{
		return 0;
	}
}
void Cluster::SetMultiplicity(short multiplicity){
	eventMultiplicity = multiplicity;
}*/


