/* http://www.youtube.com/c/electronoobs
 * 
 * This is an example where we configure te data of the MPU6050
 * and read the Acceleration data and print it to the serial monitor
 * 
 * Arduino pin    |   MPU6050
 * 5V             |   Vcc
 * GND            |   GND
 * A4             |   SDA
 * A5             |   SCL
 */
 
//Includes
#include <Wire.h>

//Variables
int acc_error         =0;                         //We use this variable to only calculate once the Acc data error
long double Acc_rawX1 = 0, Acc_rawX2 = 0, Acc_rawX3 = 0 , Acc_rawX4=0; 
float Acc_rawY, Acc_rawZ;                         //Here we store the raw data read 

//Function prototypes

void setup();
void loop();
void setupAccel();
double readAccel();
String transmision(double accel1, double accel2, double accel3, double accel4);
int pin1 = 5, pin2 = 2, pin3 = 3, pin4 = 4;
char Letra='c';
//--------------------------------------

void setup() {
  //Setup of pins starts
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  //-------------------
  //Pins are initialized to make shure there is no accelerometer tuned on
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  digitalWrite(pin4,HIGH);
  
  //-------------------
  Wire.begin();                           //begin the wire comunication 
  //Initialices accelerometer by accelerometer
    digitalWrite(pin1,LOW);
    setupAccel();
    digitalWrite(pin1,HIGH);
    //-----------------------
    digitalWrite(pin1,HIGH);
    digitalWrite(pin2,LOW);
    //setupAccel();
    //-----------------------
    digitalWrite(pin2,HIGH);
    digitalWrite(pin3,LOW);
    //setupAccel();
    //-----------------------
    digitalWrite(pin3,HIGH);
    digitalWrite(pin4,LOW);
    //setupAccel();
    digitalWrite(pin4,HIGH);
    
  Serial.begin(115200);                   //Remenber to set this same baud rate to the serial monitor  
  randomSeed(millis());
}



void loop() {
  //Main cycle
//Serial.print('a');
  Letra = Serial.read();
    if(Letra=='a'){
      //Modo real
      //------Read accelerometer No 1-------
      digitalWrite(pin4,HIGH);
      digitalWrite(pin1,LOW);
      delayMicroseconds(60);
      Acc_rawX1 = readAccel();
      Acc_rawX2 = 0;
      Acc_rawX3 = 0;
      Acc_rawX4 = 0;
      //Acc_rawX4 = random(100); 
      //------Read accelerometer No 2-------
      /*digitalWrite(pin1,HIGH);
      digitalWrite(pin2,LOW);
      delayMicroseconds(40);
      
    
      //------Read accelerometer No 3-------
      digitalWrite(pin2,HIGH);
      digitalWrite(pin3,LOW);
      delayMicroseconds(40);
      Acc_rawX3 = readAccel();

      //------Read accelerometer No 4-------
      digitalWrite(pin3,HIGH);
      digitalWrite(pin4,LOW);
      delayMicroseconds(40);
      Acc_rawX4 = readAccel();
      */
    transmision(Acc_rawX1,Acc_rawX2,Acc_rawX3,Acc_rawX4);
    } 
   if(Letra=='b'){
;   Acc_rawX1 = 0.01*random(100)-0.5;
    Acc_rawX2 = 0.01*random(100)-0.5;
    Acc_rawX3 = 0.01*random(100)-0.5;
    Acc_rawX4 = 0.01*random(100)-0.5;
    transmision(Acc_rawX1,Acc_rawX2,Acc_rawX3,Acc_rawX4);
    }
    
   delayMicroseconds(60);
  }

 
 //Declares all the functions needed in order to excute the code
 
 void setupAccel(){
  // This function initializes the IMU sensor
  Wire.beginTransmission(0x68);           //begin, Send the slave adress (in this case 68)              
  Wire.write(0x6B);                       //make the reset (place a 0 into the 6B register)
  Wire.write(0x00);
  Wire.endTransmission(true);             //end the transmission
  
  Wire.beginTransmission(0x68);           //Start communication with the address found during search.
  Wire.write(0x1C);                       //We want to write to the ACCEL_CONFIG register
  Wire.write(0x10);                       //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true); 
 
  }
 
double readAccel(){
  double LAcc_rawX;
  Wire.beginTransmission(0x68);     //begin, Send the slave adress (in this case 68) 
  Wire.write(0x3B);                 //Ask for the 0x3B register- correspond to AcX
  Wire.endTransmission(false);      //keep the transmission and next
  Wire.requestFrom(0x68,6,true);    //We ask for next 6 registers starting withj the 3B  
  /*We have asked for the 0x3B register. The IMU will send a brust of register.
  * The amount of register to read is specify in the requestFrom function.
  * In this case we request 6 registers. Each value of acceleration is made out of
  * two 8bits registers, low values and high values. For that we request the 6 of them  
  * and just make then sum of each pair. For that we shift to the left the high values 
  * register (<<) and make an or (|) operation to add the low values.
  If we read the datasheet, for a range of+-8g, we have to divide the raw values by 4096*/    
  LAcc_rawX = (Wire.read()<<8|Wire.read())/4096.0 ;
  return LAcc_rawX;

}

  String transmision(double accel1, double accel2, double accel3, double accel4) {
  Serial.print(accel1);
  Serial.print(' ');
  Serial.print(accel2);
  Serial.print(' ');
  Serial.print(accel3);
  Serial.print(' ');
  Serial.println(accel4);
}
