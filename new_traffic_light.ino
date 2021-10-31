struct State{
	uint8_t out;
	uint32_t wait;
	uint8_t next[4];
};
typedef struct State SType;
#define goN 0
#define waitN 1
#define goE 2
#define waitE 3

SType FSM[4] = {
	{0x21, 3000, {goN, waitN, goN, waitN}}, //goN
	{0x22, 500, {goE, goE, goE, goE}}, //waitN
	{0x0C, 3000, {goE, goE, waitE, waitE}}, //goE
	{0x14, 500, {goN, goN, goN, goN}}  //waitE
};
uint8_t initState; 

int main(){
	uint8_t input;

  DDRC |= 0x3F;
  DDRD &= ~(0x03);
	initState = waitE;
	
	while(1){
	PORTC = FSM[initState].out;
	delay(FSM[initState].wait);
	input = ~(PORTD & 0x03);
	initState = FSM[initState].next[input];
	}
}
