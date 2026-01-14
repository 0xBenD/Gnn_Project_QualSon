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

    char password[19] = "5N6ctfYVVlod2QFwp";
    //char password[19] = "DeZLO2rqdvgyUzWp"; to check if XOR works
    char key[19] = "DeZLO2rqdvgyUzWpV";
    etat = digitalRead(PIN_BOUTON);
    if (etat == 0) {        // bouton appuye
        while (1) {
            etat = digitalRead(PIN_BOUTON);
            if (etat == 1)  // attendre que le bouton soit relache
                break;
        }
        SigPenible = Sensor_Measure();
        char InfoSig[3] ="0";
        //char InfoSig[3] ="V";
        // afficher les resultats
		//  SigPenible = -1 -> Pas de signal
		// SigPenible = 0 => acceptable, ( > 0 ) => niveau de penibilite
    strcat(password,InfoSig);
    for(int i = 0; i < 19; i++) password[i] = password[i]^key[i];
    Serial1.print(password);
    }
    delay(1000);
}
