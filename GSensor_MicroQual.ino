//-----------------------------------------------------------------------------
//
// Sensor Measurement (Signal from microphone).
//
//  Read the comments and understand the program.
//  Replace the “????” with a suitable value before running the program.
//
// Step-1 : Goto ##TAG##1 Set the sensor pin and determine SAMPLE_FREQ and SIZE_BUFF
// Step-2 : Goto ##TAG##2 read and understand the sampling function
//						  Il ne faut rien modifier
// Step-3 : Goto ##TAG##3 Translate your Matlab program to calculate the mean power
//						  and signal frequency
// Step-5 : Goto ##TAG##4 Complete the main program Sensor_Measure()
//-----------------------------------------------------------------------------

#include    "Gnx_Project_QualSon.h"


// ##TAG##1 deb
#define		SENSOR_PIN	PD_3

// Define the sampling parameters
//---------------------------------------------------------------
//	Choose the sampling frequency : integer value in KHz (example 10 for 10 KHz)
#define		SAMPLE_FREQ		5000

//	Sampling period in micro-secondes for project with microphone
#define		SAMPLE_PERIOD	(1000/SAMPLE_FREQ)

//	Choose the size of samples buffer
// Depending on your project, determine the number to have 
// the desired recording duration		/* value between 1000 and 4000	*/
#define		SIZE_BUFF		5000

//	Signal samples Buffer 
float	Buffer_Sample[SIZE_BUFF];
// Buffer of Instantaneous power
float	Power_Inst[SIZE_BUFF];

// Nombre d'echantillons correspondant K
#define		LEN_K	(SAMPLE_FREQ*5)

#define		SIZE_AUTOCORR	(SIZE_BUFF/2)

// Buffer of autocorrelztion
float	Buff_AutoCorr[SIZE_AUTOCORR];
// ##TAG##1 end



void	Read_Samples(void);
float	myPowerEstimation(void);
short	myPowerFiltrage( void);


// ##TAG##4 deb
// You must determine the power measured with no Signal
// this is the low level value in the below line
#define		LOW_LEVEL	 200	

short	Sensor_Measure(void)
//-----------------------------------------------------
// Main Fonction 
//-----------------------------------------------------
{
	// Déclaration de variables
	float SignalPower;		// puissance du Son
	float PowerOver2K;		// pourcentage de puissance au dela de 2 KHz
	short SigPenible;

	Serial.println(" ");
	Serial.println("--- Signal Power Measurement ---");

	// call function : get buffer samples of signal

	// call function : get power signal
	// SignalPower = ...

	// Display the result
	Serial.print(" Power = ");		Serial.println(SignalPower);
	if (SignalPower < LOW_LEVEL) {
		// Power is too low = no signal
		// display an explicit message and turn on the white LED
    
    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_B, HIGH);
    digitalWrite(PIN_LED_G, HIGH);
		SigPenible = -1;	
	}
	else {
		// acceptable power
		// display an explicit message and turn on the green LED
		// Calcul de la puissance apres 2 KHz
		//PowerOver2K = ...

		// Determiner si le signal est penible 
		// SigPenible = 0 => acceptable, ( > 0 ) => niveau de penibilite
		// SigPenible = ......	
	}
	return SigPenible;
}
// ##TAG##4 end


// ##TAG##3 deb
float	myPowerEstimation(void)
//------------------------------------------------------------------------------
//	Read signal and compute mean power
//------------------------------------------------------------------------------
{
	float power;
	// add some local variables
	float  ech, pwr_sum, sumfen, pval, val_moy;
	short  n, k, szfen;

	power = 0;
	// center the signal : <signal> = <signal> - ????
	//
	// compute mean power
	// Calcul de la puissance instantannée en floatant
	pwr_sum = 0.0;    pval = 0.0;
	for (n = 0; n < LEN_K; n++) {
		sumfen = 0.0;	szfen = n + LEN_K;
		// .........
		// pval = 
		Power_Inst[n] = pval;
		pwr_sum = pwr_sum + pval;
	}
	for (n = LEN_K; n < (SIZE_BUFF - LEN_K); n++) {
		sumfen = 0.0;	szfen = (2*LEN_K) + 1;
		// .........
		// pval = 
		Power_Inst[n] = pval;
		pwr_sum = pwr_sum + pval;
	}
	for (n = SIZE_BUFF - LEN_K; n < SIZE_BUFF; n++) {
		sumfen = 0.0;	szfen = SIZE_BUFF - n + LEN_K;
		// .........
		// pval = 
		Power_Inst[n] = pval;
		pwr_sum = pwr_sum + pval;
	}
	// calculer la puissance moyenne
	power = pwr_sum / SIZE_BUFF;
	return power;
}


short	myPowerFiltrage(void)
//------------------------------------------------------------------------------
//	compute signal frequency Power : par Filtrage
//------------------------------------------------------------------------------
{
	short freqSig;

	freqSig = 0;
	// Implement Signal processing algorithm and

	return freqSig;
}
// ##TAG##3 end


// ##TAG##2 deb
void	Sensor_Init(void)
//-----------------------------------------------------
// Initialization function 
//-----------------------------------------------------
{
	// Serial port baud rate = 9600 bauds
	Serial.begin(9600);
	// Initialize the sensor input as an analog input
	pinMode(SENSOR_PIN, INPUT);
}

#define		ADC_MAX_VDD		3.3
#define		ADC_MAX_NUM		4096

void	Read_Samples(void)
//------------------------------------------------------------------------------
// Do Not modify this function. Read and understand
//------------------------------------------------------------------------------
{	float val_float;
	short idx_sample, val_integer;		unsigned long curtime, nextime;

	// See help of 'micros()' function in Energia
	// compute next sampling time (nextime)
	nextime = micros() + SAMPLE_PERIOD;
	idx_sample = 0;
	while (idx_sample < SIZE_BUFF) {
		// wait time of next sample (nextime)
		do {
			curtime = micros();
		} while (curtime < nextime);
		// read sample
		val_integer = analogRead(SENSOR_PIN);
		val_float = ((float)val_integer*ADC_MAX_VDD)/ADC_MAX_NUM;
		Buffer_Sample[idx_sample] = val_float;
		idx_sample++;
		// update next sample time
		nextime += SAMPLE_PERIOD;
	}
	return;
}
// ##TAG##2 end
