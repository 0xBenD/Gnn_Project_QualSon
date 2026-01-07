//------------------------------------------------------------------------------------
// Gnn_Project_QualSon.c
// 
//------------------------------------------------------------------------------------

#include    "Gnx_Project_QualSon.h"
#include    "OLedAffi_MyLogo.h"



void setup()
//----------------------------------------------------
//----------------------------------------------------
{
    Serial.begin(9600);
    pinMode(PIN_LED_R,  OUTPUT);
    pinMode(PIN_LED_G,  OUTPUT);
    pinMode(PIN_LED_B,  OUTPUT);

    pinMode(PIN_POTAR,  INPUT);
    pinMode(PIN_BOUTON, INPUT);

    delay(1000);

    digitalWrite(PIN_LED_R, HIGH);
    digitalWrite(PIN_LED_B, LOW);
    digitalWrite(PIN_LED_G, LOW);

    Serial.println("+++ INIT AOLED  Debut  ++++");
    AOLED_InitScreen();
    Serial.println("+++ INIT AOLED Fin    ++++");
    
    //delay(2000);
    //AOLED_DisplayImage((char*)Gnn_myLogo);
   
    Sensor_Init();

    digitalWrite(PIN_LED_R, LOW);
    delay(1000);
}

void loop()
//----------------------------------------------------
//----------------------------------------------------
{
	short  etat, SigPenible;

    etat = digitalRead(PIN_BOUTON);
    if (etat == 0) {        // bouton appuye
        while (1) {
            etat = digitalRead(PIN_BOUTON);
            if (etat == 1)  // attendre que le bouton soit relache
                break;
        }
        SigPenible = Sensor_Measure();
        // afficher les resultats
		//  SigPenible = -1 -> Pas de signal
		// SigPenible = 0 => acceptable, ( > 0 ) => niveau de penibilite
    }
sortie:
    delay(1000);
}



void RSA(){
  unsigned long p, q;
  p = findLargePrimeNumber();
  do q = findLargePrimeNumber(); while(p == q);
}

unsigned long findLargePrimeNumber(){
  randomSeed(analogRead(5));
  long nb;
  while (true){
    nb = random(pow(2,14),pow(2,15));
    if (nb%2 == 0) break;
    bool cond = true;
    for(long i = 3; i < sqrt(nb); i+=2){
      if(nb%i == 0){
        cond = false;
        break;
      }
      if(cond) break;
    }
  }
  return nb;
  
}
