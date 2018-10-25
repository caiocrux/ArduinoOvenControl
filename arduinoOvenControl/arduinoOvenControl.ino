enum SEG7 {
  SEG_A = 2,
  SEG_B,
  SEG_C,
  SEG_D,
  SEG_E,
  SEG_F,
  SEG_G,
  SEG_DP} display_7;

enum Button {
  BUTTON_ON_OFF_MICROWAVE= 9,
  BUTTON_OPEN_CLOSE_MICROWAVE,
  BUTTON_INCREASE_TIMER,
  BUTTON_DECREASE_TIMER
}button;

enum LED {
	LED_OVEN_ON_OFF=0,
  	LED_OPEN_CLOSE
}leds;

typedef enum states {
    WAITING,
    COOKING,
    UPDATE_DISPLAY
} _state;
//declaração das variaveis globais
int BUZZER_PIN = A0;
int C_FREQUENCY = 261; // valor par o buzzer emitir a nota Dó
int VALUE_TO_SET_IN_DISPLAY=0;
int UPDOWN_DISPLAY = false;
_state fsm_state = WAITING; // estado inicial fsm
//declaração dos protitpos de função
void Set_Display(int number);
void Update_Display(bool UpDown);
void Active_buzzer(void);

void setup()
{
  for(int i = SEG_A; i <= SEG_DP;i++){ 
 	 pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }
  for(int i = BUTTON_ON_OFF_MICROWAVE; i <= BUTTON_DECREASE_TIMER;i++){ 
 	 pinMode(i, INPUT_PULLUP);
  }
  for(int i = LED_OVEN_ON_OFF; i <= LED_OPEN_CLOSE;i++){ 
 	 pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }
  pinMode(BUZZER_PIN,OUTPUT);
  digitalWrite(LED_OPEN_CLOSE,HIGH); // door is closed
  Set_Display(0);


}

void loop() {
  switch(fsm_state) { // start of switch case  	
    //do instructions in WAITING
    case WAITING:
    	if( digitalRead(BUTTON_INCREASE_TIMER) == HIGH){
          fsm_state = UPDATE_DISPLAY;
          UPDOWN_DISPLAY = true;
          break;
    	}
       	if( digitalRead(BUTTON_DECREASE_TIMER) == HIGH){
          fsm_state = UPDATE_DISPLAY;
          UPDOWN_DISPLAY = false;
          break;
    	}
    	if( (digitalRead(BUTTON_ON_OFF_MICROWAVE) == HIGH) & (digitalRead(LED_OPEN_CLOSE) == HIGH) ){
          fsm_state = COOKING;
          digitalWrite(LED_OVEN_ON_OFF,HIGH);
          break;
        }
    	if(digitalRead(BUTTON_OPEN_CLOSE_MICROWAVE) == HIGH){
    	  fsm_state = WAITING;
          digitalWrite(LED_OPEN_CLOSE, !digitalRead(LED_OPEN_CLOSE));

        }
    break;
    //do instructions in COOKING
    case COOKING:
    	if(VALUE_TO_SET_IN_DISPLAY > 0) {
          	Update_Display(false);
          	delay(1000);
        }
    	else {
          	Active_buzzer();
          	digitalWrite(LED_OVEN_ON_OFF,LOW);
			fsm_state = WAITING;
          	break;
        }
    	if(digitalRead(BUTTON_OPEN_CLOSE_MICROWAVE) == HIGH){
    		fsm_state = WAITING;
                digitalWrite(LED_OVEN_ON_OFF,LOW);
		digitalWrite(LED_OPEN_CLOSE,LOW);
          break;
        }
        if(digitalRead(BUTTON_ON_OFF_MICROWAVE) == HIGH){
    		fsm_state = WAITING;
                digitalWrite(LED_OVEN_ON_OFF,LOW);
		digitalWrite(LED_OPEN_CLOSE,HIGH);
          break;
        }
    break;
    //do instructions in UPDATE_DISPLAY
    case UPDATE_DISPLAY:
    	fsm_state = WAITING;
    	Update_Display(UPDOWN_DISPLAY);
    break;
    //default:
    
  } // end of switch
  delay(300);
}// end of loop()
void Active_buzzer(void) {
  tone(BUZZER_PIN,C_FREQUENCY); //   
  delay(500);
  noTone(BUZZER_PIN);
}
void Update_Display(bool UpDown){
  
  if (UpDown == HIGH) {
    VALUE_TO_SET_IN_DISPLAY++;
    if (VALUE_TO_SET_IN_DISPLAY > 9){
    	VALUE_TO_SET_IN_DISPLAY = 0;
    }
  }
  else  {
    VALUE_TO_SET_IN_DISPLAY--;
    if (VALUE_TO_SET_IN_DISPLAY < 0){
    	VALUE_TO_SET_IN_DISPLAY = 9;
    }
  }
  Set_Display(VALUE_TO_SET_IN_DISPLAY);
}
void Set_Display(int number) {
  
  switch(number){
    
  	case 1:
	    digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_C, HIGH);
    	digitalWrite(SEG_A, LOW);
    	digitalWrite(SEG_D, LOW);
    	digitalWrite(SEG_E, LOW);
    	digitalWrite(SEG_F, LOW);
    	digitalWrite(SEG_G, LOW);
  	break;
    
    case 2:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_G, HIGH);
    	digitalWrite(SEG_D, HIGH);
    	digitalWrite(SEG_E, HIGH);
    	digitalWrite(SEG_F, LOW);
        digitalWrite(SEG_C, LOW);    	
  	break;
    
    case 3:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_G, HIGH);
    	digitalWrite(SEG_C, HIGH);
    	digitalWrite(SEG_D, HIGH);
    	digitalWrite(SEG_E, LOW);
    	digitalWrite(SEG_F, LOW);	
  	break;
    
    case 4:
    	digitalWrite(SEG_F, HIGH);
       	digitalWrite(SEG_G, HIGH);
        digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_C, HIGH);
    	digitalWrite(SEG_A, LOW);
    	digitalWrite(SEG_D, LOW);
    	digitalWrite(SEG_E, LOW);
    		
  	break;
    
    case 5:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_F, HIGH);
   	 	digitalWrite(SEG_G, HIGH);	
    	digitalWrite(SEG_C, HIGH);	
    	digitalWrite(SEG_D, HIGH);
   		digitalWrite(SEG_B, LOW);
    	digitalWrite(SEG_E, LOW);
    		
  	break;
    case 6:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_F, HIGH);
   	 	digitalWrite(SEG_G, HIGH);	
    	digitalWrite(SEG_C, HIGH);	
    	digitalWrite(SEG_D, HIGH);
   		digitalWrite(SEG_E, HIGH);
		digitalWrite(SEG_B, LOW);
    	
  	break;
    
    case 7:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_C, HIGH);	
    	digitalWrite(SEG_G, LOW);
    	digitalWrite(SEG_D, LOW);
    	digitalWrite(SEG_E, LOW);
    	digitalWrite(SEG_F, LOW);	
  	break;
    
    case 8:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_G, HIGH);
    	digitalWrite(SEG_C, HIGH);
    	digitalWrite(SEG_D, HIGH);
    	digitalWrite(SEG_E, HIGH);
    	digitalWrite(SEG_F, HIGH);	
  	break;
    
    case 9:
    	digitalWrite(SEG_A, HIGH);
	    digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_G, HIGH);
    	digitalWrite(SEG_C, HIGH);
    	digitalWrite(SEG_D, HIGH);
    	digitalWrite(SEG_F, HIGH);
    	digitalWrite(SEG_E, LOW);
  	break;
    default:
    	digitalWrite(SEG_B, HIGH);
    	digitalWrite(SEG_C, HIGH);
    	digitalWrite(SEG_F, HIGH);
    	digitalWrite(SEG_E, HIGH);
       	digitalWrite(SEG_A, HIGH);
    	digitalWrite(SEG_D, HIGH);
    	digitalWrite(SEG_G, LOW);
 }

}

