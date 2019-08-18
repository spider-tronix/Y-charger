#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
int k=1;
int i=0,j=0,x=0;
uint32_t packet;
uint32_t checksum,header=0b10110011,message=0b11110001;
uint32_t data,preamble=0b11111111111;

uint32_t parity(uint32_t a){
int b=0;
uint32_t c;
for(int i=0;i<8;i++){
//Serial.println(b);
if(a&0b00000001){
b++;
}
a>>=1;
}

if(b%2==0)
c=0b100000000;
else
c=0;
return c;
  
}



int main()
{
Serial.begin(9600);
DDRD=0b11111000;
DDRB=0xff;
PORTD=0xff;
PORTB=0xff;

TCNT1=0;
OCR1A=400;
TIMSK1=1<<OCIE1A;

EIMSK=1<<INT0;
EICRA=(1<<ISC00);
sei();

checksum=header^message;
checksum=checksum|parity(checksum);
checksum<<=1;
checksum=checksum|0b10000000000;

message=message|parity(message);
message<<=1;
message=message|0b10000000000;
//var_code=data;
//packet=parity(header);
//
header=header|parity(header);
header<<=1;
header=header|0b10000000000;


while(1){
//Serial.println(header,BIN);
}


}

ISR(INT0_vect){

PORTB^=0xff;

if((!(EICRA&0b00000010))&&j==0){

if(x==0){
data=preamble;}

if(data&0x01)
EICRA=(1<<ISC00);
else
EICRA=(1<<ISC01)|(1<<ISC00);

data>>=1;
x++;

if(x==11){
data=header;
}
else if(x==22){
data=message;
}
else if(x==33)
data=checksum;

else if(x==44){
//x=0;
}

j++;


}

else if((!(EICRA&0b00000010))&&j==1){
j=0;
if(x==44){
x=0;
//i++;
TCCR1B=(1<<CS12)|(1<<CS10)|(1<<WGM12); 
EIMSK &=!(1<<INT0);
x=0;
while(TCNT1<5){;
}
PORTB^=0xff;

}
}

else{

if(x==0){
data=preamble;}

if(data&0b00000001)
EICRA=(1<<ISC00);
else
EICRA=(1<<ISC01)|(1<<ISC00);
data>>=1;
x++;


if(x==11){
data=header;

}
else if(x==22){
data=message;
}
else if(x==33)
data=checksum;

else if(x==44){
//x=0;
}

}
}

ISR(TIMER1_COMPA_vect){
    EIMSK|=1<<INT0;
    TCCR1B=0;
}
