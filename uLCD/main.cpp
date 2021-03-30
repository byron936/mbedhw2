// R = 270ohm, C = 561nF, cutoff_freq = 1050Hz
// S = 1 + 0 + 8 + 0 + 6 + 0 + 0 + 3 + 4 = 2
#include "mbed.h"

#include "uLCD_4DGL.h"

DigitalIn but1(D13);
DigitalIn but2(D12);
DigitalIn but3(D11);

AnalogOut aout(D7);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

EventQueue queue(32 * EVENTS_EVENT_SIZE);

Thread t;

int n = 0;
int flag = 1;

void display()
{
    if (n == 0)
    {
        uLCD.cls();
        uLCD.textbackground_color(RED);
        uLCD.printf("\n950Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
        uLCD.printf("\n1050Hz\n");
        uLCD.printf("\n1150Hz\n");
    }
    else if (n == 1)
    {
        uLCD.cls();
        uLCD.printf("\n950Hz\n");
        uLCD.textbackground_color(RED);
        uLCD.printf("\n1050Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
        uLCD.printf("\n1150Hz\n");
    }
    else if (n == 2)
    {
        uLCD.cls();
        uLCD.printf("\n950Hz\n");
        uLCD.printf("\n1050Hz\n");
        uLCD.textbackground_color(RED);
        uLCD.printf("\n1150Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
    }
}

void pl()
{
    n--;
    n = (n + 3) % 3;
    printf("up\n");
    queue.call(display);
}

void mi()
{
    n++;
    n = (n + 3) % 3;
    printf("down\n");
    queue.call(display);
}
void sel()
{
    flag = 0;
    printf("select\n");
    queue.call(display);
}

int main()
{
    uLCD.background_color(0xFFFFFF);
    uLCD.cls();
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.color(BLUE);
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    display();
    while (flag == 1)
    {
        if (but1.read() == 1)
            pl();
        else if (but2.read() == 1)
            mi();
        else if (but3.read() == 1)
            sel();
        ThisThread::sleep_for(250ms);
    }
    int freq = 1050;
    if (n == 0)
        freq = 950;
    else if (n == 1)
        freq = 1050;
    else if (n == 2)
        freq = 1150;
    while (1)
    {
        for (float i = 0.0f; i < 1.0f; i += 0.08f)
        {
            aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
            //ThisThread::sleep_for(20ms);
        }
        for (float i = 1.0f; i > 0; i -= 0.02f)
        {
            aout = i;
            //printf("aout = %f volts\n", aout.read() * 3.3f);
            //ThisThread::sleep_for(80ms);
        }
    }
}
