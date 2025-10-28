# WHY ArmBoard?
We have all been there (well I have at least). Your friend says something funny, goofy, or pretty much anything and you think to yourself "I wish I could play a sound effect IRL, that would inject a lot of humour into this situation". Whether that be a generic laughing track or some obscure in joke, I believe on-demand audio add depth to any situation.

The issue we face as a society is that despite having phones which can play any sound imaginable the process of play a sound on a phone is clunky and time consuming. You must pull out and unlock your phone, look up the audio, find the correct version, wait for it to load, and then finally you can play a sound. The issue here being that this possess is time consuming, and many of these jokes/situations are time dependant.

It is clear from this that the need for a more convenient method of playing audio is required. And what could be more convenient than big buttons strapped to your wrist. It is always within arms reach, literally!  That is why I decided to create the ArmBoard, as an audio solution for the masses.


# How does it work?
The main system is comprised of 3 main parts, the esp32, the screen buttons, and the Dfplayer mini. Each of these systems have multiple sub components and functions. 

The esp32 is the brains of the operations, the TinyPico I have opted to use is optimal due to its small form factor and high number of GPIO pins. Allowing for the control of many differant components within a miniture package.

The screen buttons are made up of two distinct components, the screen and the buttons. The screens I have used are 0.66in two tone OLED displays. These are cheap, small, and bright. I have chosen to use the breakout board version of the screens as it simplifys soldering an circutry. The buttons I have chosen are the cherry MX ultra low profile. Unfortunatly these switches can only be bought from two suppliers, one in china and one in germany, they are also quite pricey. Depsite this I have still used them because of their incredibly thin form factor. 
The TinyPico does not have enough GPIO pins for each switch to have its own, as such I have arrange the switches into 4 sets of 3 switches. Each switch has a differant value resistor attatched to it (1000, 4700, and 10,000 ohm). As such, when pressed each switch in each set will produce a differant voltage. This reduces the number of Inputs needed on the TinyPico from 12 GPIO pins to just 4 analogue inputs. 
The TinyPico communicates to the Displays over I2C. Each display only supports 2 I2C addresses, as such I have had to use an I2C multiplexer to create 6 discrete I2C lines. For this task I have used the TCA9548APWR, a common I2C multiplexer. This takes one I2C line and 3 GPIO pins as input. The I2C lines carry the signal and the GPIO lines select the output using binary where each GPIO represents one digit.

Finally, the sound system consists of a DFplayer mini and a small 0.5w speaker. The DFplayer is a premade mp3 player board, the TinyPico uses a UART connection to select from mp3 files stored on an sd card within the DFplayer. The DFplayer, which incorporates a DAC, amp, and SD card, then outputs that sound signal to the speaker.

# Images
PCB:

<img width="1069" height="374" alt="image" src="https://github.com/user-attachments/assets/f92577ed-8b56-477e-8a1a-b9140d3c5e58" />

Schematic:

<img width="926" height="519" alt="image" src="https://github.com/user-attachments/assets/cc3fcf6b-2e91-4f67-b697-c6ceb786485a" />

3d Models:

<img width="584" height="413" alt="image" src="https://github.com/user-attachments/assets/ff929104-47d6-4991-bc89-1fdf9856bac5" />
<img width="652" height="305" alt="image" src="https://github.com/user-attachments/assets/19294d89-660a-43fa-90e7-4c5c68b6e976" />
