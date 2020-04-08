## Points to be considered while designing the inverter circuit

## General notations
1. m <sub>a</sub> = Vcontrol/Vtri
2. m <sub>f</sub> = Fs/Fi, where Fs is switching frequency

## Considering that Fi is high for our system,  m <sub>f</sub> will be kept small to reduce losses.

### 2 types possible
	1. modified sine wave
	2. true sine wave

### True sine wave:
	-  bridge inverter configuration
	-  unipolar sine PWM
		1. use of 5 mosfets only one high frequency
		2. one having PWM signal
		3. other in bridge configuration with 50hz sqaure wave
		4. switching loss is minimised because only one mosfets is switching very fast other at lower frequency

	-  bipolar
   	        1 Amplitude of fundamental harmonic V <sub>a0</sub> =m <sub>a</sub> * Vd/2
		2. Harmonics  frequency fh = (j*m <sub>f</sub> + or - k)* fi
		3. m <sub>f</sub> has to be odd to eliminate even harmonics.
		4. since m <sub>f</sub> is small, both the signals have to be synchronised which is the case cause we will be using MCU to generate the PWM signals 
		5. use of 4 mosfets all in high frequency
		6. all in bridge configuration
		7. switching loss is high
		for sine pwm
		technique 1: (standard)
			give SPWM signal to all the mosfets

		technique 2: (have to test the practically)
			give the SPWM signal to only upper two mosfets others two at sine wave frequency
			heating and loss distribution is unequal

- Square wave inverters have more efficiency than pure sine wave inverters on account of poor switching losses
- efficiency in case of wireless power system will be similar both the inverters but the square wave inverter can give more output power.
- for reducing the switching loss zero voltage switching has to be employed for pure sine wave inverter.

### key feature
	- need to have maximum power point tracking mechanism
	- ability to prevent the inrush current

### Some useful components:
	Gate driver IC:
		TLP 250:
			both opto-coupler and amplifier both in one package
