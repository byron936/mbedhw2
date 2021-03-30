# mbedhw2
In this homework, I do the following things:
1. display the frequency list on uLCD
2. generate triangle waveform
3. sampling this waveform
4. Do the fourier transform

(1) In the first step, I use three buttons to control my uLCD. The top of it is up, the middle of it is down, the last one is select. When the frequency is chosen, the frequency will have green highlight, and when you select it, the frequency will get red highlight.

![](https://i.imgur.com/gtUE4pt.jpg)
![](https://i.imgur.com/G0cjmM7.jpg)

(2) In the second step, I use the running time of for loop to generate the triangle waveform. Since sleep_for() only allow values greater than 1ms, I can not use sleep_for() function to generate it.I choose 550Hz, 1050Hz, and 1550Hz as my frequencies, since my cutoff frequency is 1050Hz.

Here are the results:

550Hz
![](https://i.imgur.com/YXjSlYc.png)

1050Hz
![](https://i.imgur.com/H03YVVb.png)

1550Hz
![](https://i.imgur.com/rJZInWz.png)

(3) In the third part of the homework, I sample the waveform by using sleep_for() function. I take a sample by 1ms. However, the timer shows that I run this code for 6s. Therefore, I have to divide my sample frequency by 6, which is 166.66Hz. 

(4) For the last one, I just copy the code from the previous lab, and I got the fourier transform at matlabplot.

Here are the results:

550Hz
![](https://i.imgur.com/6ahlRBZ.png)

1050Hz
![](https://i.imgur.com/Dbtf0l3.png)

1550Hz
![](https://i.imgur.com/wjIclY1.png)

During this homework2, I think that I choose a wrong capacitor and resistor so that my cutoff frequency being too high. This causes me difficulty on this homework. The period of my waveform is too fast, and the sample rating can not as high as the frequency * 2. Maybe next time I should spend more time on calculating the proper value of each element.
