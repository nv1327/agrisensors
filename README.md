# agrisensors
Arduino garden sensors

Read the Medium article to understand the hardware that goes along with the code.
https://medium.com/@n.vitebsky1327/how-to-create-a-fully-automated-garden-tool-with-arduino-in-under-30-min-61499b90c1f

Here's an excerpt:
"Since we’ll be doing temperature unit conversions, we’re going to need to import a library. This means that we will need to pull some code from the world of C++ that was already built by someone else. The math library lets us use math equations to convert between Kelvin, Celsius, and Fahrenheit. At the top of your code, type:

#include <math.h>

#include <LiquidCrystal.h>

This imports the math library and the library for using the LCD screen. Now, we’re going to initialize some variables to make coding a little less time consuming and a little more easy to look at. Under the previous, type:

const int pResistor = A0;

const double tResistor = A1;

const double mResistor = A2;

int light;

int temp;

int moisture;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

These are statements in coding that give certain values and names. The first one is named “pResistor,” and is a constant integer that is set equal to A0. A double is just another form of a data type in programming. The variables with no set value are created just to exist in the program. They don’t need values just yet. The LiquidCrystal statement creates an instance called “lcd” that tells the Arduino the LCD screen is connected to pins 12, 11, 5, 4, 3 and 2.
Now that all of the libraries and variables are out of the way, we can type the setup ( ). Type:

void setup() {

// set up the LCD’s number of columns and rows:

lcd.begin(16, 2);

pinMode(pResistor, INPUT);

pinMode(tResistor, INPUT);

pinMode(mResistor, INPUT);

}

This code is run only in the setup ( ) loop because it is all contained inside the curly braces { }. The lcd.begin statement sets up how many columns and rows the screen has (16 columns and 2 rows). The three pinMode statements use the variables we created above and basically tell the Arduino that the pins A0, A1 and A2 are input pins (Remember that pResistor, tResistor and mResistor are set to A0, A1 and A2 values). This method will only run once as our setup.
Now we can focus on the fun part. The loop ( ) method is what actually makes the pieces come together. This runs over and over as a loop until told to stop or change. Type:

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

temp = temp — 273.15; // Convert Kelvin to Celcius

temp = (temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit


lcd.print(temp);

lcd.setCursor(0,1);

if (moisture > 10) {

lcd.print(moisture);

}

else{

lcd.print(“0”);

}

lcd.setCursor(8,1);

lcd.print(light);

}

The loop ( ) begins with setting the “cursor” of the LCD screen to the top left. This expression lets the screen know where to start 
displaying stuff. Next, we set new variables such as light, temp, and moisture to analogInputs from the sensors. This works because all 
of the sensors we made are some form of resistor or depend solely on flow of electricity for input. The electricity flow is then inputted to the analog pins on the Arduino and we can use this code to give us some numbers. Next, we convert the temperature measurements from Kelvin to Celsius, and then Celsius to Fahrenheit (These may not be accurate due to the analog input. This is something you would have to scale to yourself). Furthermore, we use lcd.print to display our temperature, moisture, and light variables on the screen. The if-else loops are used to set some minimum values for the measurements on the screen.
The final code should look like:

#include <math.h>

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

// set up the LCD’s number of columns and rows:

lcd.begin(16, 2);

// Print a message to the LCD.

//lcd.print(“hello, world!”);

// pinmode(lcd, OUTPUT);

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

temp = temp — 273.15; // Convert Kelvin to Celcius

temp = (temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit

lcd.print(temp);

lcd.setCursor(0,1);

if (moisture > 10) {

lcd.print(moisture);

}

else{

lcd.print(“0”);

}


lcd.setCursor(8,1);

lcd.print(light);

}

Now you can upload the script to your Arduino. Stick the nails in the ground and congrats! You’ve made an agricultural tool using C++!

Please leave comments giving me ideas on how to improve this or what to make next. I’m considering applying some AI or deep learning to 
it next (I wish it was JavaScript). This spring, I’m also going to use this setup to communicate with a NodeMCU chip, which will relay the serial output of the sensors to a Node.js or a web server hosted on the Raspberry Pi Zero W. This will display live stats on a screen in my kitchen."
