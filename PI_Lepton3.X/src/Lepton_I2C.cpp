#include <stdio.h>
#include "Lepton_I2C.h"
#include "leptonSDKEmb32PUB/LEPTON_SDK.h"
#include "leptonSDKEmb32PUB/LEPTON_SYS.h"
#include "leptonSDKEmb32PUB/LEPTON_Types.h"
#include "leptonSDKEmb32PUB/LEPTON_AGC.h"
#include "leptonSDKEmb32PUB/LEPTON_OEM.h"
//*******

#include "leptonSDKEmb32PUB/LEPTON_RAD.h"
//*******
bool _connected;

LEP_CAMERA_PORT_DESC_T _port;
LEP_SYS_FPA_TEMPERATURE_KELVIN_T fpa_temp_kelvin;
LEP_SYS_AUX_TEMPERATURE_KELVIN_T aux_temp_kelvin;
//***
LEP_OEM_PART_NUMBER_T aho;
//***
//LEP_SYS_CUST_SERIAL_NUMBER_T_PTR sysSerialNumber;
LEP_RESULT result;





int lepton_connect() {
	int res = (int)LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
	_connected = true;
	return res;
}
int lepton_no(){
	char aa[32];
	//int  *aap;
	if(!_connected)lepton_connect();
	result = ((LEP_GetOemFlirPartNumber(&_port, &aho)));
	printf("LEPTON SerialNo: %s, code %d\n", &aho, result);
	sprintf(aa,"%s",&aho);
		printf("Lepton No=%c%c\n",aa[6],aa[7]);
	if (aa[6]=='7' && aa[7]=='1') return 1;  //lepton3.5
	else if (aa[6]=='2' && aa[7]=='6') return 2; //lepton3.0
	else return 2;
}
int lepton_temperature(){
	if(!_connected)
		lepton_connect();
	result = ((LEP_GetSysFpaTemperatureKelvin(&_port, &fpa_temp_kelvin)));
//	printf("FPA temp kelvin: %i, code %i\n", fpa_temp_kelvin, result);
	
//	LEP_GetSysCustSerialNumber( &_port,sysSerialNumber );
//	printf("lepto no: %s\n", sysSerialNumber);
	
	
	
	return (fpa_temp_kelvin);
}
int lepton_auxtemperature(){
    if(!_connected)
        lepton_connect();
    result = ((LEP_GetSysAuxTemperatureKelvin(&_port, &aux_temp_kelvin)));
//    printf("FPA temp kelvin: %i, code %i\n", fpa_temp_kelvin, result);
    
//    LEP_GetSysCustSerialNumber( &_port,sysSerialNumber );
//    printf("lepto no: %s\n", sysSerialNumber);
    
    
    
    return (aux_temp_kelvin);
}
float raw2Celsius(float raw){
	float ambientTemperature = 25.0;
	float slope = 0.0217;
	return slope*raw+ambientTemperature-177.77;
}

void lepton_perform_ffc() {
    printf("performing FFC...\n");
    if(!_connected) {
        int res = lepton_connect();
        if (res != 0) {
            //check SDA and SCL lines if you get this error
            printf("I2C could not connect\n");
            printf("error code: %d\n", res);
        }
    }
}

void lepton_ffc_start() {
    printf(" FFC Start...\n");

        result =LEP_RunSysFFCNormalization(&_port);
        if (result != 0) {
            //check SDA and SCL lines if you get this error
            printf("I2C could not connect\n");
            printf("error code: %d\n", result);
        }
    }
int lepton_ffc_status() {
//printf(" FFC Start...\n");
    LEP_SYS_STATUS_E ffc_s;
    result =LEP_GetSysFFCStatus(&_port,&ffc_s);
    return ffc_s;

}
void lepton_restart() {
	if(!_connected) {
		int res = lepton_connect();
		if (res != 0) {
			//check SDA and SCL lines if you get this error
			printf("I2C could not connect\n");
			printf("error code: %d\n", res);
		}
	}
	printf("*********************** restarting *************************\n");
	int res = (int)LEP_RunOemReboot(&_port);
/*
	if(res != 0) {
		printf("restart unsuccessful with error: %d\n", res);
	} else {
		printf("restart successful!\n");
	}
*/
}

void lepton_hosya(float hosya_float) {
   //  printf("HOSYAritu= %f\n",hosya_float);
    LEP_RAD_FLUX_LINEAR_PARAMS_T_TAG hosya_x;  //OK
    int hosya_int=hosya_float*8192;
   //  printf("HOSYAritu= %i\n",hosya_int);
    hosya_x.sceneEmissivity=hosya_int;//放射率97％7946に設定（100%で8192）
    hosya_x.TBkgK       =2951;
    hosya_x.tauWindow   =8192;
    hosya_x.TWindowK    =2951;
    hosya_x.tauAtm      =8192;
    hosya_x.TAtmK       =2951;
    hosya_x.reflWindow  =0;
    hosya_x.TReflK      =2951;

  
    result = LEP_SetRadFluxLinearParams(&_port,  hosya_x);
    
    //printf("LEPTON HOSYA: %d\n",result);
    /*
    LEP_RAD_FLUX_LINEAR_PARAMS_T_PTR *fluxParamsPtr;
    result = LEP_GetRadFluxLinearParams(&_port,  &hosya_x);
    printf("LEPTON hosyaritu 1: %d, code %d\n", hosya_x.sceneEmissivity, result);
    printf("LEPTON hosyaritu 2: %d, code %d\n", hosya_x.TBkgK);
    printf("LEPTON hosyaritu 3: %d, code %d\n", hosya_x.tauWindow);
    printf("LEPTON hosyaritu 4: %d, code %d\n", hosya_x.TWindowK);
    printf("LEPTON hosyaritu 5: %d, code %d\n", hosya_x.tauAtm);
    printf("LEPTON hosyaritu 6: %d, code %d\n", hosya_x.TAtmK);
    printf("LEPTON hosyaritu 6: %d, code %d\n", hosya_x.reflWindow);
    printf("LEPTON hosyaritu 6: %d, code %d\n", hosya_x.TReflK );
*/
           
}
