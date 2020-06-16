#ifndef LEPTON_I2C
#define LEPTON_I2C
int lepton_no();
void lepton_perform_ffc();
void lepton_ffc_start();
int lepton_ffc_status() ;
int lepton_temperature();
int lepton_auxtemperature();
float raw2Celsius(float);
void lepton_restart();
void lepton_hosya(float hosya_float);
#endif
