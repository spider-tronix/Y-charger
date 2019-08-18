#include<avr/io.h>
#include<avr/interrupt.h>

int k=1,flag1=0,bitstats=1,pstats=0;
int i=0,j=0,x=0,bitcount=0,bytestats=1,pcount=0;
uint16_t data=0;
uint8_t header,message,checksum;
uint8_t dummy_header,dummy_message;

uint16_t pcheck(uint16_t a){

int b=0;
int c;
for(int i=0;i<10;i++){
if(a&0x01){
b++;
}
a>>=1;
}

if(b%2==0)
c=1;
else
c=0;

return c;  
}


int main()
{
Serial.begin(9600);
DDRD=0b11110000;
DDRB=0xff;
PORTB=0;
PORTD=0xff;

TCCR0A=1<<WGM01;
TCNT0=0;
OCR0A=150;


EICRA=(1<<ISC10);
EIMSK=1<<INT1;
sei();

while(1){

Serial.print(dummy_header,BIN); 
Serial.print(" , ");
Serial.println(dummy_message,BIN);
}

}

ISR(INT1_vect){

TCCR0B=(1<<CS01)|(1<<CS00);
//EICRA=1<<ISC10;
if(pstats==0){
//i++;
  if(TCNT0>50&&TCNT0<75){
//i++;
    pcount++;
    TCNT0=0;
  }
  else{
//i++;
    if(TCNT0>100&&TCNT0<150){
//i++;
      if(pcount>=8){     //*
//i++;
        pstats=1;
        pcount=0;
        bitcount=1;
      }
    }
    else{
      pstats=0;
      pcount=0;
    }
    TCNT0=0;
  }
}

else{
//i++;
  if(bitstats==1){

  if(TCNT0>100&&TCNT0<150){
    //PORTB^=0xff;
    if(flag1==1){
      data|=0b10000000000;
      data>>=1;
      bitstats=1;
      bitcount++;
      TCNT0=0;
      flag1=0;
      PORTB=0xff;
      
      if(bitcount==11){
        //j++;
        if(pcheck(data)==1){
          //j++;
          data=data&0b0011111111;
          dummy_header=data;
        }
        else{ 
          //j++;
          header=0;
          bitstats=0;
        }
        data=0;
      }
      
      else if(bitcount==22){
        //j++;
        if(pcheck(data)==1){
          //j++;
          data=data&0b0011111111;
          dummy_message=data;
        }
        else{ 
          //j++;
          message=0;
          bitstats=0;
        }
        data=0;
      }
      
      else if(bitcount>=33){
        //j++;
        pstats=0;
        if(pcheck(data)==1){
          //j++;
          data=data&0b0011111111;
          checksum=data;
          if(checksum==(dummy_header^dummy_message)){
            header=dummy_header;
            message=dummy_message;
          }
          else{
            header=0;
            message=0;
            checksum=0;
          }
        }
        else{ 
          //j++;
          checksum=0;
          bitstats=0;
        }
        bitcount=0;
        data=0;
      }
    
    }
    
    else{
      data|=0;   //can be removed 
      data>>=1;
      TCNT0=0;
      bitstats=1;
      bitcount++;
      PORTB&=0;
      
      if(bitcount==11){
        //j++;
        if(pcheck(data)==1){
          //j++;
          data=data&0b0011111111;
          dummy_header=data;
        }
        else{ 
          //j++;
          header=0;
          bitstats=0;
        }
        data=0;
      }
      
      else if(bitcount==22){
        //j++;
        if(pcheck(data)==1){
          //j++;
          data=data&0b0011111111;
          dummy_message=data;
        }
        else{ 
          //j++;
          message=0;
          bitstats=0;
        }
        data=0;
      }
      
      else if(bitcount>=33){
       // j++;
        pstats=0;            
        if(pcheck(data)==1){
          //j++;
          data=data&0b0011111111;
          checksum=data;
          if(checksum==(dummy_header^dummy_message)){
            header=dummy_header;
            message=dummy_message;
            }
          else{
            header=0;
            message=0;
            checksum=0;
          }
        }
        else{ 
          //j++;
          checksum=0;
          bitstats=0;
        }
        bitcount=0;
        data=0;
      }
    }
  }
  
  else{
    if(TCNT0>50&&TCNT0<75){
    flag1=1;
    //PORTB^=0xff;
    }
    else {
    //j++;
    bitstats=0;
    }
  }
}

else{
  //j++;
  data=0;
  bitcount++;
  if(bitcount>=33){
  bitstats=1;
  bitcount=0;
  pstats=0;
  }
}

}
//PORTB=data;

}
