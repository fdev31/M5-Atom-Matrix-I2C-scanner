#include <M5Atom.h>
//#define BLINK_EACH_TURN

int  SDA_pin = G26;
int  SCL_pin = G32;

int SDA_ref = SDA_pin;
int SCL_ref = SCL_pin;

#define NORMAL_COLOR 0xaf0000
#define REVERSE_COLOR 0x00af00

// Alphabet {{{

char PROGMEM letters [][5*5] = {
    /* 0 */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1},
    /* 1 */
    {0, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0},
    /* 2 */
    {1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1},
    /* 3 */
    {1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1},
    /* 4 */
    {1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 0, 0, 1},
    /* 5 */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        1, 1, 1, 1, 1},
    /* 6 */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1},
    /* 7 */
    {1, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 1, 0, 0, 0,
        1, 0, 0, 0, 0},
    /* 8 */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1},
    /* 9 */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 1},
    /* A */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1},
    /* B */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1},
    /* C */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1},
    /* D */
    {1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 0},
    /* E */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1},
    /* F */
    {1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0},
    /* N */
    {1, 0, 0, 0, 1,
        1, 1, 0, 0, 1,
        1, 0, 1, 0, 1,
        1, 0, 0, 1, 1,
        1, 0, 0, 0, 1},
    /* R */
    {1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 0,
        1, 0, 0, 1, 0,
        1, 0, 0, 0, 1},
};

#define LETTER_N 16
#define LETTER_R 17

// }}}

void setup() 
{
    M5.begin(true, false, true);
}

int iterator=0;
int tmp;

void drawLetter(int index, int color) {
    char *c = letters[index];
    for (int i=0; i<5*5; i++) {
        M5.dis.drawpix(i, c[i]?color:0);
    }
}
void drawColor(int color) {
    for (int i=0; i<5*5; i++) {
        M5.dis.drawpix(i, color);
    }
}

int direction = 0;

void loop() 
{
    int address;
    int directionColor = direction?REVERSE_COLOR:NORMAL_COLOR;

    Wire.begin(SCL_pin, SDA_pin);
    drawColor(directionColor);

    /* rotate pins */
    if (direction) {
        SCL_pin = SDA_ref;
        SDA_pin = SCL_ref;
    } else {
        SCL_pin = SCL_ref;
        SDA_pin = SDA_ref;
    }

    for(address = 1; address < 127; address++ ) 
    {
        M5.update();
        if (M5.Btn.wasPressed()) {
            if(direction)
                drawLetter(LETTER_N, 0xAAAAAA);
            else
                drawLetter(LETTER_R, 0xAAAAAA);
            direction = !direction;
            delay(500);
        }
        Wire.beginTransmission(address);

        if(Wire.endTransmission() == 0) { /* All good! Print address */
            for (int n=0; n<2; n++) {
                drawLetter((address>>4)&0x0f, 0x00ff00);
                delay(1000);
                drawLetter(address&0x0f, 0x0000ff);
                delay(1000);
            }
            drawColor(0);
        }
        for (int i=0; i<5; i++) {
            M5.dis.drawpix(i*5 + ((address-1/10)%5), 0);
            M5.dis.drawpix(i*5 + ((address/10)%5), directionColor);
        }
        delay(5);
    }

#ifdef BLINK_EACH_TURN
    for (int n=0; n<3; n++)  {
        drawColor(0x00ff00);
        delay(10);
        drawColor(0xffffff);
        delay(10);
        drawColor(0);
        delay(10);
    }
#endif
}

