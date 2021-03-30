// R = 270ohm, C = 561nF, cutoff_freq = 1050Hz
// S = 1 + 0 + 8 + 0 + 6 + 0 + 0 + 3 + 4 = 2
#include "mbed.h"

#include "uLCD_4DGL.h"

using namespace std::chrono;

DigitalIn but1(D13);
DigitalIn but2(D12);
DigitalIn but3(D11);

AnalogOut aout(D7);

AnalogIn ain(A0);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

EventQueue queue(32 * EVENTS_EVENT_SIZE);

Timer ti;
Thread t;
Thread t2;

float ADCdata[1000];
int n = 0;
int flag = 1;

void display_s()
{
    if (n == 0)
    {
        uLCD.cls();
        uLCD.textbackground_color(RED);
        uLCD.printf("\n50Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
        uLCD.printf("\n1050Hz\n");
        uLCD.printf("\n1550Hz\n");
    }
    else if (n == 1)
    {
        uLCD.cls();
        uLCD.printf("\n550Hz\n");
        uLCD.textbackground_color(RED);
        uLCD.printf("\n1050Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
        uLCD.printf("\n1550Hz\n");
    }
    else if (n == 2)
    {
        uLCD.cls();
        uLCD.printf("\n550Hz\n");
        uLCD.printf("\n1050Hz\n");
        uLCD.textbackground_color(RED);
        uLCD.printf("\n1550Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
    }
}

void display()
{
    if (n == 0)
    {
        uLCD.cls();
        uLCD.textbackground_color(GREEN);
        uLCD.printf("\n550Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
        uLCD.printf("\n1050Hz\n");
        uLCD.printf("\n1550Hz\n");
    }
    else if (n == 1)
    {
        uLCD.cls();
        uLCD.printf("\n550Hz\n");
        uLCD.textbackground_color(GREEN);
        uLCD.printf("\n1050Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
        uLCD.printf("\n1550Hz\n");
    }
    else if (n == 2)
    {
        uLCD.cls();
        uLCD.printf("\n550Hz\n");
        uLCD.printf("\n1050Hz\n");
        uLCD.textbackground_color(GREEN);
        uLCD.printf("\n1550Hz\n");
        uLCD.textbackground_color(0xFFFFFF);
    }
}
void pl()
{
    n--;
    n = (n + 3) % 3;
    //printf("up\n");
    queue.call(display);
}

void mi()
{
    n++;
    n = (n + 3) % 3;
    //printf("down\n");
    queue.call(display);
}
void sel()
{
    flag = 0;
    //printf("select\n");
    queue.call(display_s);
}
void generate_wave()
{
    if (n == 0)
        while (1)
        {
            for (int i = 0; i < 48; i += 1)
            {
                aout = float(i) / 48.000;
            }
            for (int i = 192; i > 0; i -= 1)
            {
                aout = float(i) / 192.000;
            }
        }
    else if (n == 1)
        while (1)
        {
            for (int i = 0; i < 25; i += 1)
            {
                aout = float(i) / 25.000;
            }
            for (int i = 100; i > 0; i -= 1)
            {
                aout = float(i) / 100.000;
            }
        }
    else if (n == 2)
        while (1)
        {
            for (int i = 0; i < 17; i += 1)
            {
                aout = float(i) / 17.000;
            }
            for (int i = 68; i > 0; i -= 1)
            {
                aout = float(i) / 68.000;
            }
        }
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

    t2.start(generate_wave);
    //ti.start();
    for (int i = 0; i < 1000; i++)
    {
        ADCdata[i] = ain;
        ThisThread::sleep_for(1ms);
    }
    //ti.stop();
    //auto s = chrono::duration_cast<chrono::seconds>(ti.elapsed_time()).count();
    //printf("Timer time: %llu s\n", s);
    //time:6s
    for (int i = 0; i < 1000; i++)
    {
        printf("%f\r\n", ADCdata[i]);
    }
    ThisThread::sleep_for(10000ms);
}
