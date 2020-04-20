
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9 // Configurable, see typical pin layout above
#define SS_PIN 10 // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	lcd.init();
	lcd.backlight();

	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);

	Serial.begin(9600); // Initialize serial communications with the PC
	while (!Serial)
		;							   // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();					   // Init SPI bus
	mfrc522.PCD_Init();				   // Init MFRC522
	mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop()
{
	// Look for new cards
	if (mfrc522.PICC_IsNewCardPresent())
	{
		escribirLCD("Abierto         ");
	}
	else
	{
		escribirLCD("Cerrado         ");
	}

	// Select one of the cards
	if (!mfrc522.PICC_ReadCardSerial())
	{
		return;
	}

	// Dump debug info about the card; PICC_HaltA() is automatically called
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

void escribirLCD(String s)
{

	delay(1);
	lcd.setCursor(0, 0);
	lcd.print(s);
	delay(1);
}
