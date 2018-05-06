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
int acc_error=0;                         //We use this variable to only calculate once the Acc data error
float Acc_rawX, Acc_rawY, Acc_rawZ;    //Here we store the raw data read 

//Function prototypes

void setup();
void loop();
void setupAccel();
float readAccel();
String transmision(double accel1, double accel2, double accel3, double accel4);

//--------------------------------------

void setup() {
  Wire.begin();                           //begin the wire comunication 
  setupAccel();
  Serial.begin(115200);                     //Remember to set this same baud rate to the serial monitor  
  randomSeed(1);
}



void loop() {
  //Main cycle
    if(Serial.read()=='a'){
    readAccel();
    transmision(Acc_rawX,1,1,1);
    }
   delay(1); 
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
 
 float readAccel(){
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
  Acc_rawX=(Wire.read()<<8|Wire.read())/4096.0 ; //each value needs two registres
  Acc_rawY=(Wire.read()<<8|Wire.read())/4096.0 ;
  Acc_rawZ=(Wire.read()<<8|Wire.read())/4096.0 ; 
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
