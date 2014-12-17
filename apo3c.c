#include <16F684.h>
#device adc=10

#FUSES INTRC_IO, NOMCLR, NOWDT, NOPROTECT, PUT, NOIESO, NOFCMEN, NOCPD
#use delay(clock=125000)


#use fast_io(a)
#use fast_io(c)

#define LED_STATUS  PIN_C5
#define VSENSE      PIN_C3
#define VSENSE_ADC  7
#define SW0         PIN_A1
#define SW1         PIN_A2
#define SW2         PIN_A0
#define SW3         PIN_A5
#define SW_OVERRIDE PIN_A4
#define SER_RX      PIN_A3
#define SER_TX      PIN_C1
#define POWER_CTRL  PIN_C4
#define ATE_SIGNAL  PIN_C0
#define VGOOD       PIN_C2

#define EE_LVD       0x00 /* low voltage disconnect */
#define EE_LVR       0x08 /* low voltage re-connect */
#define EE_DELAY     0x10 /* delay before LVD */
#define EE_SN        0x18 /* serial number */
#define EE_MODEL     0x1B /* model. 1=>APO3c 2=>APO3c24 (R1 = 49.9k) */


/*
todo:
	more intelligent LED indication
*/
#if 1
/*
For 24 volt solid state relay with R1=49.9k APO3C24 for cranes

EEPROM table for LVD, LVR, off delay, and serial number
generated by the following command:
./apo3c24_table 12.1 12.3 12.7 13.05 13.4 13.4 13.4 13.4 1 300 600 1200
*/
#rom 0x2100 = {
        0x01, 0x9d, 0x01, 0xa4, 0x01, 0xb1, 0x01, 0xbd, /* LVD = { 12.10 12.30 12.70 13.05 } volts */
        0x01, 0xc9, 0x01, 0xc9, 0x01, 0xc9, 0x01, 0xc9, /* LVR = { 13.40 13.40 13.40 13.40 } volts */
        0x00, 0x01, 0x01, 0x2c, 0x02, 0x58, 0x04, 0xb0, /* OFF DELAY = { 1 300 600 1200 } seconds */
        0x00, 0x00, 0x00, 0x02 } /* SERIAL NUMBER is always 2 for APO3C24 */

#endif

#if 0
/*
TESTING TABLE! 
EEPROM table for LVD, LVR, off delay, and serial number
generated by the following command:
./apo3c_table 11.8 12.1 12.7 13.05 12.4 12.3 12.9 13.4 1 10 20 30
*/
#rom 0x2100 = {
        0x02, 0xf2, 0x03, 0x05, 0x03, 0x2c, 0x03, 0x42, /* LVD = { 11.80 12.10 12.70 13.05 } volts */
        0x03, 0x18, 0x03, 0x12, 0x03, 0x38, 0x03, 0x58, /* LVR = { 12.40 12.30 12.90 13.40 } volts */
        0x00, 0x01, 0x00, 0x0a, 0x00, 0x14, 0x00, 0x1e, /* OFF DELAY = { 1 10 20 30 } seconds */
        0x00, 0x00, 0x00, 0x01 } /* SERIAL NUMBER is always 1 */
#endif

#if 1
/*
EEPROM table for LVD, LVR, off delay, and serial number
generated by the following command:
./apo3c_table 11.8 12.1 12.7 13.05 12.4 12.3 12.9 13.4 1 300 600 1200
*/
#rom 0x2100 = {
        0x02, 0xf2, 0x03, 0x05, 0x03, 0x2c, 0x03, 0x42, /* LVD = { 11.80 12.10 12.70 13.05 } volts */
        0x03, 0x18, 0x03, 0x12, 0x03, 0x38, 0x03, 0x58, /* LVR = { 12.40 12.30 12.90 13.40 } volts */
        0x00, 0x01, 0x01, 0x2c, 0x02, 0x58, 0x04, 0xb0, /* OFF DELAY = { 1 300 600 1200 } seconds */
        0x00, 0x00, 0x00, 0x01 } /* SERIAL NUMBER is always 1 */
#endif


#if 0
/*
EEPROM table for LVD, LVR, off delay, and serial number
generated by the following command:
./apo3c_table 11.5 11.75 12.0 12.25 12.0 12.25 12.5 12.6 1 300 600 1200

Settings for Sandia
*/

#rom 0x2100 = {
        0x02, 0xdf, 0x02, 0xef, 0x02, 0xff, 0x03, 0x0f, /* LVD = { 11.50 11.75 12.00 12.25 } volts */
        0x02, 0xff, 0x03, 0x0f, 0x03, 0x1f, 0x03, 0x25, /* LVR = { 12.00 12.25 12.50 12.60 } volts */
        0x00, 0x01, 0x01, 0x2c, 0x02, 0x58, 0x04, 0xb0, /* OFF DELAY = { 1 300 600 1200 } seconds */
        0x00, 0x00, 0x00, 0x01 } /* SERIAL NUMBER is always 1 */
#endif


#if 0
#define BRECO 1
/*
EEPROM table for LVD, LVR, off delay, and serial number
generated by the following command:
apo3c_table 12.00 12.05 12.10 12.20 12.5 12.6 0.00 0.00 600 300 0 0

this is specially for Breco

*/
#rom 0x2100 = {
        0x02, 0xff, 0x03, 0x02, 0x03, 0x05, 0x03, 0x0c, /* LVD = { 12.00 12.05 12.10 12.20 } volts */
        0x03, 0x1f, 0x03, 0x25, 0x00, 0x00, 0x00, 0x00, /* LVR = { 12.50 12.60 0.00 0.00 } volts */
        0x02, 0x58, 0x01, 0x2c, 0x00, 0x00, 0x00, 0x00, /* OFF DELAY = { 600 300 0 0 } seconds */
        0x00, 0x00, 0x00, 0x02 } /* SERIAL NUMBER is 2 for BRECO - generated 2014-01-14 */
#endif


#define ON_DELAY_SECONDS 5



/* 1 Hz flag to make decision */
int8 decide_now;

/* configuration globals */
int16 configuration_lvd;
int16 configuration_lvr;
int16 configuration_delay;



#int_timer0
void isr_timer0 (void) {
//	output_toggle(LED_STATUS);


	decide_now=1;
}

/* take the average of 8 ADC readings */
int16 read_adc_average(int8 channel) {
	int16 value;
	int8 i;

	set_adc_channel(channel); 
	value=0;
	for ( i=0 ; i<8 ; i++ ) {
		value += read_adc(); 
		delay_ms(20);
	}
	/* divide by 8 */
	value = value / 8;

	return value;
}

int16 read_eeprom_int16(int8 address) {
	return make16(read_eeprom(address),read_eeprom(address+1));
}

void get_threshold(void) {
	int8 sw;

	/* read our DIP switches */
	sw=!input(SW0);
	sw=sw<<1;
	sw |= !input(SW1);

	configuration_lvd = read_eeprom_int16(EE_LVD+sw*2);
	configuration_lvr = read_eeprom_int16(EE_LVR+sw*2);

	/* 
	check if we have an APO3c24. If we do, then we check voltage and determine if we have 12 volt or 24 volt battery.
	If 24 volts battery, , we double our LVD and LVR set points 
	*/
	if ( 2 == read_eeprom(EE_MODEL) && read_adc_average(VSENSE_ADC) > 615 ) {
		configuration_lvd *= 2;
		configuration_lvr *= 2;

		/* turn on LED for 900 milliseconds and then off for 100 ... next we will do normal startup LED flashes */
		restart_wdt();
		output_high(LED_STATUS);
		delay_ms(900);
		output_low(LED_STATUS);
		delay_ms(100);
	}



#ifdef BRECO
	sw=!input(SW2);
	configuration_lvr = read_eeprom_int16(EE_LVR+sw*2);
#endif
}

void get_delay(void) {
	int8 sw;

	/* read our DIP switches */
	sw=!input(SW2);
	sw=sw<<1;
	sw |= !input(SW3);

	configuration_delay = read_eeprom_int16(EE_DELAY+sw*2);

#ifdef BRECO
	sw=!input(SW3);
	configuration_delay = read_eeprom_int16(EE_DELAY+sw*2);
#endif
}



/* setup the PIC */
void init_hardware(void) {
	/* setup a very slow oscillator - apo3c draws 1.32mA */
	setup_oscillator(OSC_125KHZ);
	setup_wdt(WDT_OFF);

//	setup_wdt(WDT_2304MS);
//	setup_wdt(WDT_2304MS | WDT_ON);

	restart_wdt();

	/* setup analog to digital converter */
	setup_adc_ports(sAN7); /* battery input */
	setup_adc(ADC_CLOCK_INTERNAL);

	/* turn analog comparator off */
	setup_comparator(NC_NC_NC_NC);
	setup_vref(FALSE);

	/* set the direction of port_a */
	set_tris_a(0b00111111);
	/* setup pullups for switches (individually addressable) */
	port_a_pullups(0b00111111);
	/* set the direction of port_c */
	set_tris_c(0b00001001);

	/* setup our timer to be 1.048576 second */
	setup_timer_0(RTCC_INTERNAL|RTCC_8_BIT|RTCC_DIV_128);
	enable_interrupts(INT_TIMER0);
	enable_interrupts(GLOBAL);

	/* read our configuration from EEPROM */
	get_threshold();
	get_delay();

	/* initial values */
	output_low(POWER_CTRL);
	output_low(LED_STATUS);
	output_low(VGOOD);
	decide_now=1;
}



void main(void) {
	int8 i;
	int16 adc;

	int8  on_delay;
	int16 off_delay;
	int1 power;

	/* initialize hardware */
	init_hardware();


	on_delay=ON_DELAY_SECONDS;
	off_delay=configuration_delay;
	



	/* flash the LED 5 times on startup ... non-hysteresis APO3C firmware flashes 10 times on startup */
	for ( i=0 ; i<5 ; i++ ) {
		restart_wdt();
		output_high(LED_STATUS);
		delay_ms(200);
		output_low(LED_STATUS);
		delay_ms(200);
	}

	power=0;

	/* main loop */
	for ( ; ; ) {
		restart_wdt();

		/* actually flip the power relay */
		if ( 1==power || ! input(SW_OVERRIDE) ) {
			output_high(POWER_CTRL);
		} else {
			output_low(POWER_CTRL);
		}

		if ( decide_now ) {
			decide_now=0;

			adc=read_adc_average(VSENSE_ADC);
	
			if ( adc > configuration_lvd )
				output_high(VGOOD);
			else
				output_low(VGOOD);
	
	
			if ( adc > configuration_lvr ) {
				if ( on_delay > 0 ) {
					on_delay--;
				} else {
					power=1;
					output_low(LED_STATUS);
				}
			} else {
				on_delay = 5; /* 5 seconds before re-connecting */
			}
		
			if ( adc < configuration_lvd ) {
				if ( off_delay > 0 ) {
					off_delay--;
					output_high(LED_STATUS);
				} else {
					power=0;
					output_low(LED_STATUS);
				}
			} else {
				off_delay = configuration_delay;
			}
			restart_wdt();
		}
	}
}


#if 0
		/* test override switch */
		if ( input(SW_OVERRIDE) ) {
			output_low(POWER_CTRL);
		} else {
			output_high(POWER_CTRL);
		}
		continue;

		/* test voltage input circuitry and reading of threshold */
		if ( read_adc_average(VSENSE_ADC) > configuration_lvd ) {
			output_high(POWER_CTRL);
		} else {
			output_low(POWER_CTRL);
		}
		continue;

		/* test reading of delay */
		for ( ; ; ) {
			output_high(POWER_CTRL);
			for ( j=0 ; j<configuration_delay ; j++ ) {
				delay_ms(100);
			}
			output_low(POWER_CTRL);
			for ( j=0 ; j<configuration_delay ; j++ ) {
				delay_ms(100);
			}
		}
#endif
