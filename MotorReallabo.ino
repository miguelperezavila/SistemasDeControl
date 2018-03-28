#include <DueTimer.h>

int channel0 = 0;
int channel1 = 1;

int dutyCicle = 50;
int dutyCicle0 = 0;
int Encoder0 = 3;
int Encoder1 = 7;
long pulses = 0;

int interrupt = 0;
int i = 0;
int j;
int values[1201];

DueTimer timerssito = DueTimer(1);
DueTimer timerssitoShit = DueTimer(2);
DueTimer timerssitoMotor = DueTimer(3);
void setup() {
  //delay(1000);
  Serial.begin(250000);
  pwmInitialised(channel0,4,34922,0);
  pwmInitialised(channel1,4,34922,0);
  pwmPIODisabled();
  
  timerssito.attachInterrupt(printValues);
  timerssito.setFrequency(1000);
  timerssitoShit.attachInterrupt(interruptValues);
  timerssitoShit.setPeriod(1201000);
  timerssitoMotor.attachInterrupt(stopMotor);
  timerssitoMotor.setPeriod(600000);
  //Serial.println("Iniciamos serial\n");
  delay(1000);
 
  pinMode(Encoder0,INPUT);
  pinMode(Encoder1,INPUT);
  delay(1000);

  attachInterrupt(digitalPinToInterrupt(Encoder0), countPulse, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Encoder1), countPulse, CHANGE);
  timerssito.start();
  timerssitoShit.start();
  timerssitoMotor.start();
  pwmInitialised(channel0,4,34922,100);
  pwmInitialised(channel1,4,34922,0);
  //Serial.println("Inicializados");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(values[i]);
  if(interrupt == 1){
    for( j = 0;j<1201;j = j + 1){
   //Serial.println("aqui");
   String space = " ";
   String jota = String(j);
   
   String cero = String(000000);
   String definitive = jota +'.'+ cero+cero+cero+cero+cero+cero + space + values[j]+ '.' + cero+cero+cero+cero+cero+cero;
    Serial.println(definitive);
   // delay(100);
  
  }
  interrupt=0;
  }
}

void pwmInitialised(short channel, short preescaler, int frecuency, int dutyCycle){
  
  pmc_enable_periph_clk (PWM_INTERFACE_ID) ;
  PWMC_ConfigureChannel (PWM, channel, preescaler, 0, 0) ;
  
  int period = ((84000000)*4)/(frecuency * 2 * preescaler);
  PWMC_SetPeriod (PWM, channel, period) ;
  PWMC_SetDutyCycle (PWM, channel, dutyCycle*period/100) ;
  PWMC_EnableChannel (PWM, channel) ;
}

void pwmPIODisabled(){

    PIOC->PIO_PDR = 1<<2;
    PIOC->PIO_IDR = 1<<2;
    PIOC->PIO_ABSR |=1<<2;

    PIOC->PIO_PDR = 1<<4;
    PIOC->PIO_IDR = 1<<4;
    PIOC->PIO_ABSR |=1<<4;
}

void countPulse(){
  pulses= pulses +1;
}

void printValues(){
  if(interrupt != 1){
  values[i] = pulses;
  i = i+1;
  }
}
void interruptValues(){
  interrupt = 1;
  //pwmInitialised(channel0,4,34922,0);
 // pwmInitialised(channel1,4,34922,0);

  //detachInterrupt(digitalPinToInterrupt(Encoder0));
  //detachInterrupt(digitalPinToInterrupt(Encoder1));

    timerssito.stop();
  timerssitoShit.stop();
}

void stopMotor(){
    pwmInitialised(channel0,4,34922,0);
  pwmInitialised(channel1,4,34922,0);
}

