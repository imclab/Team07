/*-----------------------------------------------------------------------------------
** demo of ble and accelermeter
** loovee 2013-6-18
** https://github.com/reeedstudio/xadow
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or (at your option) any later version.
**
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public
** License along with this library; if not, write to the Free Software
** Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
**--------------------------------------------------------------------------------*/
#include <Wire.h>
#include <SeeedOLED.h>

#include "xadow.h"

#include <avr/pgmspace.h>

static unsigned char EyeImage[] PROGMEM ={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3C, 0xFE, 0xFF, 0xFC, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xE0,
0xF8, 0xFC, 0xFC, 0x3C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x1C, 0x3C, 0x7C, 0x78, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0,
0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xF0, 0xF0, 0xF9, 0x7B, 0x7F, 0x3F, 0x3F, 0x1E, 0x9E,
0x9E, 0x9F, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,
0xE7, 0xCF, 0xCF, 0xCF, 0xCF, 0x8F, 0x9E, 0x1E, 0x1E, 0x3C, 0x3C, 0x78, 0x78, 0xF0, 0xE0, 0xE0,
0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x70, 0xF0, 0xE0, 0xE0, 0xE0, 0xE0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0xC0, 0xE0, 0xF1, 0x79, 0x3D,
0x3F, 0x1F, 0x8F, 0xC7, 0xE7, 0xE3, 0xF1, 0xF9, 0xF8, 0x7C, 0xBE, 0xFE, 0x7F, 0x3F, 0x1F, 0x1F,
0x0F, 0x07, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x03, 0x03, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F, 0x3E, 0x3C, 0x7C, 0xF8, 0xF1, 0xF1,
0xE3, 0xC7, 0x87, 0x8E, 0x1E, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x10, 0x30, 0x70, 0xF0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0xC1, 0xC3,
0xC3, 0xC3, 0x83, 0x03, 0x83, 0xC3, 0xF1, 0x39, 0x1D, 0x0F, 0x07, 0x83, 0xE1, 0xF0, 0xF8, 0xFC,
0x7E, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0xE1, 0xF8, 0x1E, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
0xFC, 0xF8, 0xF8, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03,
0x0F, 0x3F, 0xFF, 0xDF, 0x3F, 0x7E, 0xFC, 0xF8, 0xF0, 0xC0, 0x81, 0x01, 0x03, 0x02, 0x04, 0x04,
0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x41, 0x31, 0x0C, 0x06, 0x03, 0x81, 0xC0, 0xF0, 0xF8, 0xFE, 0x7F, 0x3F, 0x0F, 0x07, 0x03, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x03, 0xFF, 0x78, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F, 0x7F, 0xFE, 0xF8, 0xF0, 0xE0,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0C, 0x1F, 0x3F, 0x7F, 0xFF, 0xFB, 0xF1, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1F, 0x7C, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
0x3F, 0x3F, 0x1F, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0xC0, 0xF0, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC3, 0xE7, 0xEF,
0xFF, 0xFF, 0xFE, 0xFE, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x3E, 0x7C,
0x7C, 0xF8, 0xF0, 0xF0, 0xE0, 0xC0, 0xC0, 0x80, 0x81, 0x03, 0x07, 0x0E, 0x1C, 0x38, 0x30, 0x60,
0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0x60, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x83,
0x81, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0x7C, 0x7C, 0xBE, 0x1F, 0x0F, 0x0F, 0x07, 0x03,
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x01, 0x02, 0x00, 0x00,
0x00, 0x03, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x1F, 0x1F, 0x1E, 0x3F, 0x3C,
0x3C, 0x7C, 0x7D, 0x7F, 0x79, 0x7B, 0xFB, 0xF3, 0xF3, 0xF7, 0xF6, 0xF7, 0xF6, 0xF6, 0xF7, 0xF6,
0xF2, 0xFB, 0x7B, 0x7B, 0x7B, 0x79, 0x7D, 0x7D, 0x3C, 0x3C, 0x3E, 0x1E, 0x1F, 0x1F, 0x0F, 0x0F,
0x0F, 0x07, 0x07, 0x03, 0x03, 0x03, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

float lastXg = 0.0;
float lastYg = 0.0;
float lastZg = 0.0;

int dancing;

int looking;

#define ADDRACC         0x53

#define Register_ID     0
#define Register_2D     0x2D
#define Register_X0     0x32
#define Register_X1     0x33
#define Register_Y0     0x34
#define Register_Y1     0x35
#define Register_Z0     0x36
#define Register_Z1     0x37

void adxl_init()
{
    Wire.beginTransmission(ADDRACC);
    Wire.write(Register_2D);
    Wire.write(8);                                              // measuring enable
    Wire.endTransmission();                                     // stop transmitting
}

unsigned char readAcc(double *Xg, double *Yg, double *Zg)
{
    int X_out;
    int Y_out;
    int Z_out;
    Wire.beginTransmission(ADDRACC);                            // transmit to device
    Wire.write(Register_X0);
    Wire.write(Register_X1);
    Wire.endTransmission();
    Wire.requestFrom(ADDRACC,2);
    if(Wire.available()<=2)
    {
        int X0 = Wire.read();
        int X1 = Wire.read();
        X1=X1<<8;
        X_out=X0+X1;
    }
    //------------------Y
    Wire.beginTransmission(ADDRACC);                            // transmit to device
    Wire.write(Register_Y0);
    Wire.write(Register_Y1);
    Wire.endTransmission();
    Wire.requestFrom(ADDRACC,2);
    if(Wire.available()<=2)
    {
        int Y0 = Wire.read();
        int Y1 = Wire.read();
        Y1=Y1<<8;
        Y_out=Y0+Y1;
    }
    //------------------Z
    Wire.beginTransmission(ADDRACC);                            // transmit to device
    Wire.write(Register_Z0);
    Wire.write(Register_Z1);
    Wire.endTransmission();
    Wire.requestFrom(ADDRACC,2);
    if(Wire.available()<=2)
    {
        int Z0 = Wire.read();
        int Z1 = Wire.read();
        Z1=Z1<<8;
        Z_out=Z0+Z1;
    }
    *Xg=X_out/256.0;
    *Yg=Y_out/256.0;
    *Zg=Z_out/256.0;
}

void Show_eye(void)
{
 SeeedOled.drawBitmap(EyeImage,1024);   // 1024 = 128 Pixels * 64 Pixels / 8
}

void Close_eye(void)
{
  SeeedOled.clearDisplay();  
  
}

unsigned char dispBat(void)
{

    float Vabt = Xadow.getBatVol();
    cout << Vabt << endl;
//    SeeedOled.setTextXY(0,0);
//    SeeedOled.putString("VBat: ");
//    SeeedOled.setTextXY(0,6);
//    SeeedOled.putFloat(Vabt,2);
}

void vibrate(unsigned char OnOff)
{
    if(OnOff)
    {
        PORTB |= 0x04;
        PORTF |= 0x01;
    }
    else
    {
        PORTB &=~ 0x04;
        PORTF &=~ 0x01;
    }
}

void ADXL(void)
{

    double Xg, Yg, Zg;
    
    static float tempGL=0;
    static float tempGH=0;
    unsigned char vib=0;
    readAcc(&Xg, &Yg, &Zg);//get new Acc
    
    tempGL = Xg-1;
    tempGH = Xg+1;
    if((lastXg>tempGH)||(lastXg<tempGL))
    {
        lastXg=Xg;
      //  SeeedOled.setTextXY(1,0);
      //  SeeedOled.putString("X= ");
      //  SeeedOled.setTextXY(1,3);
      //  SeeedOled.putFloat(Xg);
      //  SeeedOled.putString("    ");
        vib|=0x01;
    }

    tempGL = Yg-1;
    tempGH = Yg+1;
    if((lastYg>tempGH)||(lastYg<tempGL))
    {
        lastYg=Yg;
      //  SeeedOled.setTextXY(2,0);
      //  SeeedOled.putString("Y= ");
      //  SeeedOled.setTextXY(2,3);
      //  SeeedOled.putFloat(Yg);
      //  SeeedOled.putString("    ");
        vib|=0x02;
    }

    tempGL = Zg-1;
    tempGH = Zg+1;
    if((lastZg>tempGH)||(lastZg<tempGL))
    {
        lastZg=Zg;
     //   SeeedOled.setTextXY(3,0);
     //   SeeedOled.putString("Z= ");
     //   SeeedOled.setTextXY(3,3);
     //   SeeedOled.putFloat(Zg);
     //   SeeedOled.putString("    ");
        vib|=0x04;
    }

    if(vib)
    {
        cout << "X = " << Xg << '\t';
        cout << "Y = " << Yg << '\t';
        cout << "Z = " << Zg << endl;

        Serial1.print("X = ");
        Serial1.print(Xg);
        Serial1.print(", Y = ");
        Serial1.print(Yg);
        Serial1.print(", Z = ");
        Serial1.println(Zg);
        vibrate(1);
    }
    delay(100);
    vibrate(0);
}

void setup(void)
{
    Wire.begin();

    SeeedOled.init();                               //initialze SEEED OLED display
    SeeedOled.clearDisplay();                       // clear the screen and set start position to top left corner

    Serial.begin(115200);
    Serial1.begin(38400);
    adxl_init();

  looking = 0;
    dancing = 0;
    
    DDRF |= 0x01;
    DDRB |= 0x04;                                   //vibrator io init
	
	Xadow.init();
}

void loop(void)
{
    static unsigned char count=0;

    unsigned char stateChg = Xadow.getChrgState();
    
    if (looking == 1)
    {
      
       delay(2000);
        SeeedOled.setHorizontalScrollProperties(Scroll_Left,0,7,Scroll_5Frames);
  
        delay(2000);
        SeeedOled.setHorizontalScrollProperties(Scroll_Right,0,7,Scroll_5Frames);
    }
    
  if(dancing == 1)
    {
       vibrate(1);
       delay(100);
       vibrate(0);  
       delay(100);      
    }
    else
    {
        vibrate(0);       
    }
  
  
    
    if(NOCHARGE == stateChg)
    {
        Xadow.redLed(LEDON);
    }
    else if(CHARGING == stateChg)
    {
        Xadow.redLed(LEDCHG);
    }
    else
    {
        Xadow.redLed(LEDOFF);
    }

    if(count>10)
    {
        count=0;
        dispBat();
    }
    count++;
    ADXL();
	
	BluetoothDtaProc();
	
}


bool cmpLvc(char *a, char *b, int len)
{
	if(!a || !b)return 0;
	for(int i = 0; i<len; i++)
	{
		if(a[i] == b[i])continue;
		else return 0;
	}
	return 1;
}
// you can send "LEDON" and "LEDOFF" to control the green LED on main board
void BluetoothDtaProc()
{
	char getDta 		= 0;
	unsigned char len 	= 0;
	char dta[20];
	while(Serial1.available())
	{
		char c = Serial1.read();
		
		dta[len++] = c;
		getDta = 1;
	}
	
	if(getDta)
	{
            Serial.print(dta);
              
                if(len == 4 && (cmpLvc(dta, "Look", len) || cmpLvc(dta, "look", len)))
		{  // make eye on Oled scroll side to side
                    SeeedOled.setHorizontalScrollProperties(Scroll_Right,0,7,Scroll_5Frames); //Set Scrolling properties to Scroll Right
                    SeeedOled.activateScroll();             // Activate Scrolling
                    looking = 1;    // flag to enable scrolling
                    
                }

                if(len == 3 && (cmpLvc(dta, "Are", len) || cmpLvc(dta, "are", len)))
		{  // Play "arh" pirate sound

                  digitalWrite(15,HIGH);
                  digitalWrite(16,HIGH);
                  delay(1000);
                  delay(1000);
                  delay(1000);
                  delay(1000);
                  delay(1000);
                  delay(1000);
                  delay(1000);
                  delay(1000);
                  digitalWrite(15,LOW);
                  digitalWrite(16,LOW); 
                }
                 if(len == 6 && (cmpLvc(dta, "Pirate", len) || cmpLvc(dta, "pirate", len)))
		{  // Play "arh" pirate sound and leave t play all sound

                  digitalWrite(15,HIGH);
                  digitalWrite(16,HIGH);
   
                }
                

 
                 if(len == 9 && (cmpLvc(dta, "Stop look", len) || cmpLvc(dta, "stop look", len)))
		{  // stop eye lookignnside to side
                    
                    SeeedOled.deactivateScroll();   //Disable scrolling
                    looking = 0;      // stop scroling in loop
                    SeeedOled.drawBitmap(EyeImage,1024);   // 1024 = 128 Pixels * 64 Pixels / 8          
                    
                }              
              
 if(len == 8 && (cmpLvc(dta, "Open eye", len) || cmpLvc(dta, "open eye", len)))
		{  // put imag of eye on OLED
                       Show_eye();
                }
                if(len == 9 && (cmpLvc(dta, "Close eye", len) || cmpLvc(dta, "close eye", len)))
		{  // OLED eye to blank for closed
                       Close_eye();
                }

                if(len == 4 && (cmpLvc(dta, "Wink", len) || cmpLvc(dta, "wink", len)))
		{  // Turn eye off fr 1/2 sec as a blink
                       delay(100);
                        SeeedOled.setBrightness(0);
                       delay(500);
                        SeeedOled.setBrightness(255);
                }


  		if(len == 11 && (cmpLvc(dta, "Dance start", len) || cmpLvc(dta, "dance start", len)))
		{  // turn on vibrator to make skeleton vibrate and dance
			Serial1.println("Dancing starting");
			//Xadow.greenLed(LEDON);
                        dancing = 1;

		}
  		if(len == 10 && (cmpLvc(dta, "Dance stop", len) || cmpLvc(dta, "dance stop", len)))
		{  // turn off vibrator
			Serial1.println("Dancing over");

                        dancing = 0; 

		}


		if(len == 2 && (cmpLvc(dta, "On", len) || cmpLvc(dta, "on", len)))
		{
			Serial1.println("ON");
			Xadow.greenLed(LEDON);
		}
		if(len == 3 && (cmpLvc(dta, "Off", len) || cmpLvc(dta, "off", len)))
		{
			Serial1.println("OFF");
			Xadow.greenLed(LEDOFF);
		}
		else 
		{
			Serial1.println("OK");
		}             
              
              
              
              
              
		getDta = 0;
	}
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
