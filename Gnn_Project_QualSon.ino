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
  unsigned long p, q, e, r, inverse, v;
  p = findLargePrimeNumber();
  do q = findLargePrimeNumber(); while(p == q);
  long n = p * q;
  do e = findLargePrimeNumber(); while(((p-1)*(q-1)) % e ==0);
  extendedEuclide(e,(p-1)*(q-1), &r, &inverse, &v);
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


void extendedEuclide(unsigned long a, unsigned long b, unsigned long* r, long* u, long* v){
  r = a;
  u = 1;
  v = 0;
  unsigned long rs = b, us = 0, vs = 1, q = 0;
  while(rs != 0){
    q = r/rs;
    r = rs;
    u = us;
    v = vs;
    rs = r - q*rs;
    us = u - q*us;
    vs = v - q*vs;
  }
}
