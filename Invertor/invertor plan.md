## Points to be considered while designing the invertor circuit

### 2 types possible
	1. modified sine wave
	2. true sine wave

### True sine wave:
	-  bridge invertor configuration
	-  unipolar sine PWM 
		1. use of 5 mosfets only one high frequency
		2. one having PWM signel
		3. other in bridge configuration with 50hz sqaure wave
		4. switching loss is minimised because only one mosfets is switching very fast other at lower frequency
	
	-  bipolar
		1. use of 4 mosfets all high frequency
		2. all in bridge configuration 
		3. switching loss is high
		for sine pwm
		techique 1:
			give SPWM signel to all the mosfets
		
		techique 2:
			give the SPWM signal to only upper two mosfets others two at sine wave frequency
			heating and loss distribution is unequal
		
	



### Some useful components:
	Gate driver IC:
		TLP 250:
			both opto-coupler and amplifier both in one package
		
	

