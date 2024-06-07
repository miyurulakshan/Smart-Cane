#include <VibrationMotor.h>

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

Adafruit_MPU6050 mpu;


float accX_old = 0.0;
float accY_old = 0.0;
float accZ_old = 0.0;

const float fall_threshold = 10 ;


// LDR module
unsigned int ldrAnalog;  // analog input of the LDR_module
const int ambient_light = 8; //Vibration moter

const int vibration_motor = 13; //Vibration moter

const int trigPin_down = 12;  // Trigger of the down ultrasonic sensor
const int echoPin_down = 11;  // Echo of the down ultrasonic sensor
const int trigPin_up = 9;     // Trigger of the up ultrasonic sensor
const int echoPin_up = 10;   // Echo of the up ultrasonic sensor

const int buzzer = 7;   // Buzzer indication of falling




// globle Distance variables of the ultrasonic sensor
struct Distance {
  int distance_down;
  int distance_up;  
};

long duration_down;  // reflection duration of the ultrasonic wave - down
long duration_up;   //  reflection duration of the ultrasonic wave - up


VibrationMotor myVibrationMotor(vibration_motor);  // vibration moter function

void ambientLightSensor(void){ // Fall detection function

ldrAnalog = analogRead(A0);

// Prints the ldr value on the Serial Monitor - Tuning purpose to send the arduino cloud

Serial.println(ldrAnalog);  

if(ldrAnalog > 900 ){
  digitalWrite(ambient_light, HIGH);
}
else{
  digitalWrite(ambient_light, LOW);
}

}



Distance obstacalDetection(void){ // Obstacal detection function

  Distance result;

  //Down ultrasonic sensor
  // Clears the trigPin
  digitalWrite(trigPin_down, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_down, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_down, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_down = pulseIn(echoPin_down, HIGH);
  result.distance_down = duration_down * 0.034 / 2;


  //Up ultrasonic sensor
  digitalWrite(trigPin_up, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin_up, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_up, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_up = pulseIn(echoPin_up, HIGH);
  result.distance_up = duration_up * 0.034 / 2;


  // Prints the distance on the Serial Monitor - Tuning purpose to send the arduino cloud
  Serial.print("Distance_down:");
  Serial.print(result.distance_down);
  Serial.print(",");
  Serial.print("Distance_up:");
  Serial.println(result.distance_up);
  return result;



}



void fallDetection(void){ // Fall detection function
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate the magnitude of acceleration vector
  float accX = a.acceleration.x;
  float accY = a.acceleration.y;
  float accZ = a.acceleration.z;

  Serial.print(a.acceleration.x); 
  Serial.print(","); 
  Serial.print(a.acceleration.y); 
  Serial.print(","); 
  Serial.println(a.acceleration.z); 

  
  if (((abs(accX-accX_old)) >= fall_threshold) || ((abs(accY-accY_old)) >= fall_threshold) || ((abs(accZ-accZ_old)) >= fall_threshold) ) {
    
    digitalWrite(buzzer, HIGH);
    delay(5000);
    digitalWrite(buzzer, LOW);
;     
  }
  
  delay(100);

  accX_old = accX;
  accY_old = accY;
  accZ_old = accZ;


 }





void setup() {

  
  
  pinMode(vibration_motor, OUTPUT); // Sets the trigPin as an Output
  pinMode(buzzer, OUTPUT); // Sets the buzzer pin as an Output
  pinMode(ambient_light, OUTPUT); // Set ambient light led as an Output



  pinMode(trigPin_down, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_down, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin_up, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_up, INPUT); // Sets the echoPin as an Input

  Serial.begin(115200); // Starts the serial communication


  // MPU6050 configuration
    while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  
  //get the initial values of the mpu6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Calculate the magnitude of acceleration vector
  float accX_old = a.acceleration.x;
  float accY_old = a.acceleration.y;
  float accZ_old = a.acceleration.z;
  
  
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  Serial.println("MPU6050 Found!");


}


void loop() {

Distance values = obstacalDetection();
fallDetection();
ambientLightSensor();

if ( (values.distance_down < 92) || (values.distance_up <  83) ){ 
  myVibrationMotor.on();
}else{
  myVibrationMotor.off();
}

}

