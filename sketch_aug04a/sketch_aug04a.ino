const int 
PWM_A   = 3,
DIR_A   = 12,
BRAKE_A = 9,
SNS_A   = A0;


void setup() {
  // Configure the A output
  pinMode(11, OUTPUT);  // Brake pin on channel A
  pinMode(3, OUTPUT);    // Direction pin on channel A

    pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin


  // Open Serial communication
  //Serial.begin(9600);
  //Serial.println("Motor shield DC motor Test:\n");
}

void loop() {

 motor_output(11, HIGH, 255);

delay(3000);

while(1);
}
 

