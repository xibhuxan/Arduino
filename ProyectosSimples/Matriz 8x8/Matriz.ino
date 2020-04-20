/*
 * Show messages on an 8x8 led matrix (cathode rows),
 * scrolling from right to left.
 *
 * Pinouts & code by Andrew
 * see http://arduino.pastebin.com/f35fdf323
 * see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1203747843/13#13
 */

// pin[xx] on led matrix connected to nn on Arduino (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9, 8, 7, 6};
// (for some reason I ended up with different pinouts that Andrew's)

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06], pins[11], pins[15], pins[16]};

// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1], pins[7], pins[2], pins[5]};

// Letter definitions based on 5 bit-wise columns (5 x 7 font)
#define SP {0, 0, 0, 0, 0}
#define EX {0, 125, 0, 0, 0}  // !

#define A {31, 36, 68, 36, 31}
#define B {127, 73, 73, 73, 54}
#define C {62, 65, 65, 65, 34}
#define D {127, 65, 65, 34, 28}
#define E {127, 73, 73, 65, 65}
#define F {127, 72, 72, 72, 64}
#define G {62, 65, 65, 69, 38}
#define H {127, 8, 8, 8, 127}
#define I {0, 65, 127, 65, 0}
#define J {2, 1, 1, 1, 126}
#define K {127, 8, 20, 34, 65}
#define L {127, 1, 1, 1, 1}
#define M {127, 32, 16, 32, 127}
#define N {127, 32, 16, 8, 127}
#define O {62, 65, 65, 65, 62}
#define P {127, 72, 72, 72, 48}
#define Q {62, 65, 69, 66, 61}
#define R {127, 72, 76, 74, 49}
#define S {50, 73, 73, 73, 38}
#define T {64, 64, 127, 64, 64}
#define U {126, 1, 1, 1, 126}
#define V {124, 2, 1, 2, 124}
#define W {126, 1, 6, 1, 126}
#define X {99, 20, 8, 20, 99}
#define Y {96, 16, 15, 16, 96}
#define Z {67, 69, 73, 81, 97}

int dispSpeed = 20;      // Constrols scroll speed (1 minimum, way too fast)
byte bit[8] = {128, 64, 32, 16, 8, 4, 2, 1}; // Used for bit comparisons
byte colVals[8] = {0, 0, 0, 0, 0, 0, 0, 0};  // Hold display columns (initaly blank)

// Define display string here
const int charNum = 13;        // Number of letters in display string
byte string[charNum][5] = {A,S,T,R,O,SP,N,O,O,B,I,E,SP};

void setup() {
  Serial.begin(9600);     // for troubleshooting
  for (int i = 1; i <= 16; i++) {   // sets the pins as output
    pinMode(pins[i], OUTPUT); }
  for (int col = 0; col < 8; col++) {    // set up cols and rows
    digitalWrite(cols[col], HIGH);  }
  for (int row = 1; row < 8; row++) {
    digitalWrite(rows[row], HIGH);
  }
  Serial.println(availableMemory());     // 670 bytes for charNum = 15
}

void loop() {

  for (int ltr = 0; ltr < charNum; ltr++){// For each letter in string array
    for (int y = 0; y < 6; y++){     // For each columin in letter + one space
 shiftLeft();    // shifts display columns left
 if (y < 5){
   colVals[7] = string[ltr][y]; }    // add new letter column on right
 else {colVals[7] = 0; }   // or empty space between
 for (int x = 0; x < dispSpeed; x++){// loop to refresh display x times ton control scrolling
   display();
 }
    }
  }
}


void shiftLeft(){
 for (int x = 0; x < 7; x++){
   colVals[x] = colVals[x + 1];
 }
}


void display() {

   for (int col = 0; col < 8; col++){
    for (int row = 0; row < 8; row++){
 if (colVals[col] & bit[row]){
   digitalWrite(rows[row], HIGH);}
 }
    digitalWrite(cols[col], LOW);  // Turn on column
    delay(1);  // Delay for POV
    for (int row = 0; row < 8; row++){
 digitalWrite(rows[row], LOW);
    }
    digitalWrite(cols[col], HIGH);  // And off
  }
}

// this function will return the number of bytes currently free in RAM
// written by David A. Mellis
// based on code by Rob Faludi http://www.faludi.com
int availableMemory() {
  int size = 1024;
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL);
  free(buf);
  return size;
}
 
