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

# BOM (All prices are AUD)
| PCB designation | Name                               | Quantity | Product number / Website                                                                                                                                                                                                                                  | Unit price | Total price |
|-----------------|------------------------------------|-----------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------|--------------|
| XA1             | TinyPico                           | 1         | 392-TP-N-01                                                                                                                                                                                                                                                | $30.40      | $30.40       |
| R10,R4,R1,R7    | 3216 Metric 1000Ohm                | 4         | 704-MFBW1V3216-152-R                                                                                                                                                                                                                                      | $0.10       | $0.38        |
| R6,R12,R15,R9,R3,R13,R16,R14 | 3216 Metric 10000Ohm   | 8         | 652-CRT1206BY1002ELF                                                                                                                                                                                                                                      | $0.21       | $1.68        |
| R8,R5,R2,R11    | 3216 Metric 4700Ohm                | 4         | 603-RT1206BRD074K7L                                                                                                                                                                                                                                       | $0.19       | $0.74        |
| U1              | TCA9548APWR                        | 1         | 595-TCA9548APWR                                                                                                                                                                                                                                           | $3.65       | $3.65        |
| U2              | Dfplayer mini                      | 1         | [AliExpress Link](https://www.aliexpress.com/item/1005001417104130.html?src=google&pdp_npi=4%40dis!AUD!3.07!3.07!!!!!%40!12000016020958443!ppc!!!)                                                                                                         | $3.06       | $3.06        |
| SW12,SW3,SW1,SW9,SW2,SW8,SW5,SW10,SW6,SW7,SW11,SW4 | Cherry ULP SMD switches | 12 | [Reichelt Link](https://www.reichelt.de/de/en/shop/product/cherry_mx_ultra_low_profile_rgb_-_pushbutton_module-335040)                                                                                             | $2.66       | $31.92       |
| D8,D4,D2,D12,D6,D10,D7,D3,D5,D9,D11,D1 | Display_0.66in               | 12        | [BuyDisplay Link](https://www.buydisplay.com/i2c-white-0-66-inch-oled-display-module-64x48-arduino-raspberry-pi)                                                                                                   | $4.92       | $59.04       |
| —               | Battery                            | 1         | [AliExpress Link](https://www.aliexpress.com/p/tesla-landing/index.html?scenario=c_ppc_item_bridge&productId=4001029210544&_immersiveMode=true&withMainCard=true&src=google&aff_platform=true&isdl=y)                                                    | $12.39      | $12.39       |
| LS1             | Buzzer_12mm (6.5mm hole)           | 1         | MT-TH12-0126-RK                                                                                                                                                                                                                                           | $2.30       | $2.30        |
| ~               | **Overall cost (excluding shipping)** | ~         | ~                                                                                                                                                                                                                                                         | ~           | **$133.18**  |

