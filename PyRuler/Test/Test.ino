
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  digitalWrite(4, HIGH); 
  digitalWrite(5, HIGH); 
  digitalWrite(6, HIGH); 
  digitalWrite(7, HIGH);   
  
  delay(1000);                       // wait for a second
  
  digitalWrite(4, LOW);    
  digitalWrite(5, LOW);    
  digitalWrite(6, LOW);    
  digitalWrite(7, LOW);    
  
  delay(1000);                       // wait for a second
}
