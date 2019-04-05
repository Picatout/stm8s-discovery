/********************************************************************************/
/*                                 STM8A/S                                      */
/*                       AN3143 audio software codec                            */
/*                              README text file                                */
/*                                 V1.0.0                                       */
/*                                                                              */
/********************************************************************************/
/* THE PRESENT FIRMWARE, WHICH IS FOR GUIDANCE ONLY, AIMS AT PROVIDING CUSTOMERS*/
/* WITH CODING INFORMATION REGARDING THEIR PRODUCTS SO THEY CAN SAVE            */
/* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY       */
/* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING */
/* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE    */
/* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.       */
/********************************************************************************/

This file explains how to use the code attached to the AN3143.

The firmware project is developed in STVD using Cosmic and Raisonance STM8 compiler.
It could be simply ported to any other development environment and C compiler.

/********************************************************************************/
	HW requirements
/********************************************************************************/

The audio software codec firmware is developed to run on STM8/128k Eval board - MB631.
To configure HW enviroment check the following steps
1) JP14 to position 1-2
2) JP4 short
3) set the RV 2 to middle position (volume)
4) connect headphones to CN7 or use onboard speaker

The filtered PWM audio output is available on test point TP5. To allow dual PWM output
connect resistor of 300k between PC3 and TP5.

/********************************************************************************/
	Storing audio data on uSD Card
/********************************************************************************/

Please, follow the instructions in the AN3143 to create compressed audio data stream 
(xyz.ima file) in IMA ADPCM format by using SOX command line application. You can use 
cockoo.ima file attached to this project for reference.
Then you have to use hexa editor (HxD, http://mh-nexus.de) to open the ima file and 
save it on uSD card inserted in card reader connected to your PC by using command 
"Open disk" from menu "Extras". Make sure that you have unchecked the "Open As Readonly"
tick box. Then copy the content of ima file to uSD card and save it.
Put the uSD card to MB631 eval board.

/********************************************************************************/
	Start demo
/********************************************************************************/

To download the code into the MCU, the user must use STVP or the 'light programmer' 
in STVD or run a code from debug session.
When the code is executed it should play several times sound of cuckoo bird. The sound 
samples are stored in ADPCM audio stream - file "cuckoo.c".