
#include <math.h>
/*
double Thermistor(int RawADC) {
 int Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}
*/
const int pResistor = A0;
const double tResistor = A1;
const double mResistor = A2;
int light;
int temp;
int moisture;


//include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
//  pinmode(lcd, OUTPUT);
  pinMode(pResistor, INPUT);
  pinMode(tResistor, INPUT);
  pinMode(mResistor, INPUT);

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  light = analogRead(pResistor);
  temp = analogRead(tResistor);
  moisture = analogRead(mResistor);
  moisture = moisture*3;
  
  temp =log(10000.0/(1024.0/temp-1));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
  temp = temp - 273.15;            // Convert Kelvin to Celcius
  temp = (temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  
  
  lcd.print(temp);
  lcd.setCursor(0,1);
  if (moisture > 10) {
      lcd.print(moisture);
  }
  else{
    lcd.print("0");
  }

  lcd.setCursor(8,1);
  lcd.print(light);

//start with Serial.begin(9600);
//use Serial.print(degreesC); and Serial.print(degreesF);
//also use lightLevel = map(lightLevel, 0, 1023, 0, 255);
//then lightLevel = constrain(lightLevel, 0, 255);
//maybe use push buttons to change display from Celsius to Fahrenheit and more



}
