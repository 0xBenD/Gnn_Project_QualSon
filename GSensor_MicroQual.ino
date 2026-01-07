//-----------------------------------------------------------------------------
//
// Sensor Measurement (Signal from microphone).
//
//  Read the comments and understand the program.
//  Replace the “????” with a suitable value before running the program.
//
// Step-1 : Goto ##TAG##1 Set the sensor pin and determine SAMPLE_FREQ and SIZE_BUFF
// Step-2 : Goto ##TAG##2 read and understand the sampling function
//              Il ne faut rien modifier
// Step-3 : Goto ##TAG##3 Translate your Matlab program to calculate the mean power
//              and signal frequency
// Step-4 : Goto ##TAG##4 Complete the main program Sensor_Measure()
//-----------------------------------------------------------------------------

#include    "Gnx_Project_QualSon.h"


// ##TAG##1 deb
#define   SENSOR_PIN  PD_3

// Define the sampling parameters
//---------------------------------------------------------------
//  Choose the sampling frequency : integer value in KHz (example 10 for 10 KHz)
#define   SAMPLE_FREQ   10

//  Sampling period in micro-secondes for project with microphone
#define   SAMPLE_PERIOD (1000/SAMPLE_FREQ)

//  Choose the size of samples buffer
// Depending on your project, determine the number to have 
// the desired recording duration   /* value between 1000 and 4000  */
#define   SIZE_BUFF 2500



// Nombre d'echantillons correspondant K
#define   LEN_K (SAMPLE_FREQ*5)

#define   SIZE_AUTOCORR (SIZE_BUFF/2)
// Buffer of autocorrelztion
float Buff_AutoCorr[SIZE_AUTOCORR];
// ##TAG##1 end



void  Read_Samples(float Buffer_Sample[SIZE_BUFF]);
float myPowerEstimation(float Buffer_Sample[SIZE_BUFF]);
short myPowerFiltrage( void);


// ##TAG##4 deb
// You must determine the power measured with no Signal
// this is the low level value in the below line
#define   LOW_LEVEL   30

short Sensor_Measure(void)
//-----------------------------------------------------
// Main Fonction 
//-----------------------------------------------------
{
  // Déclaration de variables
  float SignalPower;    // puissance du Son
  float PowerOver2K;    // pourcentage de puissance au dela de 2 KHz
  short SigPenible;
  // Signal samples Buffer 
  float Buffer_Sample[SIZE_BUFF];

  Serial.println(" ");
  Serial.println("--- Signal Power Measurement ---");

  // call function : get buffer samples of signal
  // call function : get power signal
  SignalPower = myPowerEstimation(Buffer_Sample);

  // Display the result
  Serial.print(" Power = ");    Serial.println(SignalPower);
  if (SignalPower < LOW_LEVEL) {
    // Power is too low = no signal
    // display an explicit message and turn on the white LED
    SigPenible = -1;  // Pas de signal
  }
  else {
    // acceptable power
    // display an explicit message and turn on the green LED
    // Calcul de la puissance apres 2 KHz
    //PowerOver2K = 100*(SignalPower - myPowerFiltrage(SignalPower))/SignalPower;
    
    // Determiner si le signal est penible 
    // SigPenible = 0 => acceptable, ( > 0 ) => niveau de penibilite
    // SigPenible = ......  
  }
  return SigPenible;
}
// ##TAG##4 end


// ##TAG##3 deb
float myPowerEstimation(float Buffer_Sample[SIZE_BUFF])
//------------------------------------------------------------------------------
//  Read signal and compute mean power
//------------------------------------------------------------------------------
{
  float power;
  // add some local variables
  float  ech, pwr_sum, sumfen, pval, val_moy;
  short  n, k, szfen;
 // Buffer of Instantaneous power
float Power_Inst[SIZE_BUFF];


  power = 0;
  // center the signal : <signal> = <signal> - 0 (no continuous component)
  //
  // compute mean power
  // Calcul de la puissance instantannée en floatant
  pwr_sum = 0.0;    pval = 0.0;
  for (n = 0; n < LEN_K; n++) {
    sumfen = 0.0; szfen = n + LEN_K;
    for(int j = 0; j < szfen; j++){
      sumfen += pow(Buffer_Sample[j],2);
    }
    pval = sumfen / szfen;
    Power_Inst[n] = pval;
    pwr_sum = pwr_sum + pval;
  }
  for (n = LEN_K; n < (SIZE_BUFF - LEN_K); n++) {
    sumfen = 0.0; szfen = (2*LEN_K) + 1;
    for(int j = n - LEN_K; j < n + LEN_K; j++){
      sumfen += pow(Buffer_Sample[j],2);
    }
    pval = sumfen / szfen;
    Power_Inst[n] = pval;
    pwr_sum = pwr_sum + pval;
  }
  for (n = SIZE_BUFF - LEN_K; n < SIZE_BUFF; n++) {
    sumfen = 0.0; szfen = SIZE_BUFF - n + LEN_K;
    for(int j = SIZE_BUFF - LEN_K; j < LEN_K; j++){
      sumfen += pow(Buffer_Sample[j],2);
    }
    pval = sumfen / szfen;
    Power_Inst[n] = pval;
    pwr_sum = pwr_sum + pval;
  }
  // calculer la puissance moyenne
  power = pwr_sum / SIZE_BUFF;
  return power;
}


short myPowerFiltrage(void)
//------------------------------------------------------------------------------
//  compute signal frequency Power : par Filtrage
//------------------------------------------------------------------------------
{
  short freqSig;

  freqSig = 0;
  // Implement Signal processing algorithm and

  return freqSig;
}
// ##TAG##3 end


// ##TAG##2 deb
void  Sensor_Init(void)
//-----------------------------------------------------
// Initialization function 
//-----------------------------------------------------
{
  // Serial port baud rate = 9600 bauds
  Serial.begin(9600);
  // Initialize the sensor input as an analog input
  pinMode(SENSOR_PIN, INPUT);
}

#define   ADC_MAX_VDD   3.3
#define   ADC_MAX_NUM   4095

void  Read_Samples(float Buffer_Sample[SIZE_BUFF])
//------------------------------------------------------------------------------
// Do Not modify this function. Read and understand
//------------------------------------------------------------------------------
{ float val_float;
  short val_integer;    unsigned long curtime, nextime;

  // See help of 'micros()' function in Energia
  // compute next sampling time (nextime)
  nextime = micros() + SAMPLE_PERIOD;
  for(short idx_sample = 0; idx_sample < SIZE_BUFF; idx_sample++){
    // wait time of next sample (nextime)
    do {
      curtime = micros();
    } while (curtime < nextime);
    // read sample
    val_integer = analogRead(SENSOR_PIN);
    val_float = ((float)val_integer*ADC_MAX_VDD)/ADC_MAX_NUM;
    Buffer_Sample[idx_sample] = val_float;
    // update next sample time
    nextime += SAMPLE_PERIOD;
  }
  return;
}
// ##TAG##2 end
