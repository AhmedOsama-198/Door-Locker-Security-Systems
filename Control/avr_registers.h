 /******************************************************************************
 *
 * Module: REGISTERS
 *
 * File Name: avr_registers.h
 *
 * Description: Header file for the AVR REGISTERS MAPPING
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/


#ifndef AVR_REGISTERS_H_
#define AVR_REGISTERS_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef union{
	uint8 Byte;
	struct{
		uint8 C_Bit:1;
		uint8 Z_Bit:1;
		uint8 N_Bit:1;
		uint8 V_Bit:1;
		uint8 S_Bit:1;
		uint8 H_Bit:1;
		uint8 T_Bit:1;
		uint8 I_Bit:1;
	}Bits;
}STATUS_Reg_Type;


typedef union{
	uint16 Byte;
	struct{
		uint8 BIT0: 1;
		uint8 BIT1: 1;
		uint8 BIT2: 1;
		uint8 BIT3: 1;
		uint8 BIT4: 1;
		uint8 BIT5: 1;
		uint8 BIT6: 1;
		uint8 BIT7: 1;
		uint8 BIT8: 1;
		uint8 BIT9: 1;
		uint8 BIT10: 1;
		uint8 BIT11: 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
	}Bits;
}STACK_POINTER_Type;


typedef union{
	uint8 Byte;
}TIMER0_OCR0_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 IVCE_bit: 1;
		uint8 IVSEL_bit: 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 INT2_bit: 1;
		uint8 INT0_bit: 1;
		uint8 INT1_bit: 1;
	}Bits;
}GICR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 INTF2_bit: 1;
		uint8 INTF0_bit: 1;
		uint8 INTF1_bit: 1;
	}Bits;
}GIFR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 TOIE0_bit: 1;
		uint8 OCIE0_bit: 1;
		uint8 TOIE1_bit: 1;
		uint8 OCIE1B_bit: 1;
		uint8 OCIE1A_bit: 1;
		uint8 TICIE1_bit: 1;
		uint8 TOIE2_bit: 1;
		uint8 OCIE2_bit: 1;
	}Bits;
}TIMSK_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 TOV0_bit: 1;
		uint8 OCF0_bit: 1;
		uint8 TOV1_bit: 1;
		uint8 OCF1B_bit: 1;
		uint8 OCF1A_bit: 1;
		uint8 ICF1_bit: 1;
		uint8 TOV2_bit: 1;
		uint8 OCF2_bit: 1;
	}Bits;
}TIFR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 SPMEN_bit: 1;
		uint8 PGERS_bit: 1;
		uint8 PGWRT_bit: 1;
		uint8 BLBSET_bit: 1;
		uint8 RWWSRE_bit: 1;
		uint8 : 1;
		uint8 RWWSB_bit: 1;
		uint8 SPMIE_bit: 1;
	}Bits;
}SPMCR_Reg_Type;



typedef union{
	uint8 Byte;
	struct{
		uint8 TWIE_bit: 1;
		uint8 : 1;
		uint8 TWEN_bit: 1;
		uint8 TWWC_bit: 1;
		uint8 TWSTO_bit: 1;
		uint8 TWSTA_bit: 1;
		uint8 TWEA_bit: 1;
		uint8 TWINT_bit: 1;
	}Bits;
}TWCR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 ISC00_bit: 1;
		uint8 ISC01_bit: 1;
		uint8 ISC10_bit: 1;
		uint8 ISC11_bit: 1;
		uint8 SM0_bit: 1;
		uint8 SM1_bit: 1;
		uint8 SM2_bit: 1;
		uint8 SE_bit: 1;
	}Bits;
}MCUCR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 PORF_bit: 1;
		uint8 EXTRF_bit: 1;
		uint8 BORF_bit: 1;
		uint8 WDRF_bit: 1;
		uint8 JTRF_bit: 1;
		uint8 : 1;
		uint8 ISC2_bit: 1;
		uint8 JTD_bit: 1;
	}Bits;
}MCUCSR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 CS00_bit: 1;
		uint8 CS01_bit: 1;
		uint8 CS02_bit: 1;
		uint8 WGM01_bit: 1;
		uint8 COM00_bit: 1;
		uint8 COM01_bit: 1;
		uint8 WGM00_bit: 1;
		uint8 FOC0_bit: 1;
	}Bits;
}TIMER0_TCCR0_Type;


typedef union{
	uint8 Byte;
}TIMER0_TCNT0_Type;


typedef union{
	uint8 Byte;
}OSCCAL_OCDR_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 PSR10_bit: 1;
		uint8 PSR2_bit: 1;
		uint8 PUD_bit: 1;
		uint8 ACME_bit: 1;
		uint8 : 1;
		uint8 ADTS0_bit: 1;
		uint8 ADTS1_bit: 1;
		uint8 ADTS2_bit: 1;
	}Bits;
}SFIOR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 WGM10_bit: 1;
		uint8 WGM11_bit: 1;
		uint8 FOC1B_bit: 1;
		uint8 FOC1A_bit: 1;
		uint8 COM1B0_bit: 1;
		uint8 COM1B1_bit: 1;
		uint8 COM1A0_bit: 1;
		uint8 COM1A1_bit: 1;
	}Bits;
}TIMER1_TCCR1A_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 CS10_bit: 1;
		uint8 CS11_bit: 1;
		uint8 CS12_bit: 1;
		uint8 WGM12_bit: 1;
		uint8 WGM13_bit: 1;
		uint8 : 1;
		uint8 ICES1_bit: 1;
		uint8 ICNC1_bit: 1;
	}Bits;
}TIMER1_TCCR1B_Type;


typedef union{
	uint16 Byte;
}TIMER1_TCNT1_Type;


typedef union{
	uint16 Byte;
}TIMER1_OCR1A_Type;


typedef union{
	uint16 Byte;
}TIMER1_OCR1B_Type;


typedef union{
	uint16 Byte;
}TIMER1_ICR1_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 CS20_bit: 1;
		uint8 CS21_bit: 1;
		uint8 CS22_bit: 1;
		uint8 WGM21_bit: 1;
		uint8 COM20_bit: 1;
		uint8 COM21_bit: 1;
		uint8 WGM20_bit: 1;
		uint8 FOC2_bit: 1;
	}Bits;
}TIMER2_TCCR2_Type;


typedef union{
	uint8 Byte;
}TIMER2_TCNT2_Type;


typedef union{
	uint8 Byte;
}TIMER0_OCR2_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 TCR2UB_bit: 1;
		uint8 OCR2UB_bit: 1;
		uint8 TCN2UB_bit: 1;
		uint8 AS2_bit: 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
	}Bits;
}ASSR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 WDP0_bit: 1;
		uint8 WDP1_bit: 1;
		uint8 WDP2_bit: 1;
		uint8 WDE_bit: 1;
		uint8 WDTOE_bit: 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
	}Bits;
}WDTCR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 UBRRH_bits: 4;
		uint8 : 3;
		uint8 URSEL_bit: 1;
	}Bits;
}UBRRH_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 UCPOL_bit: 1;
		uint8 UCSZ0_bit: 1;
		uint8 UCSZ1_bit: 1;
		uint8 USBS_bit: 1;
		uint8 UPM0_bit: 1;
		uint8 UPM1_bit: 1;
		uint8 UMSEL_bit: 1;
		uint8 URSEL_bit: 1;
	}Bits;
}UCSRC_Reg_Type;


typedef union{
	uint16 Byte: 10;
}EEAR_Reg_Type;


typedef union{
	uint8 Byte;
}EEDR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 EERE_bit: 1;
		uint8 EEWE_bit: 1;
		uint8 EEMWE_bit: 1;
		uint8 EERIE_bit: 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
	}Bits;
}EECR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 Bit0:1;
		uint8 Bit1:1;
		uint8 Bit2:1;
		uint8 Bit3:1;
		uint8 Bit4:1;
		uint8 Bit5:1;
		uint8 Bit6:1;
		uint8 Bit7:1;
	}Bits;
}GPIO_Reg_Type;


typedef union{
	uint8 Byte;
}SPDR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 SPI2X_bit: 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 : 1;
		uint8 WCOL_bit: 1;
		uint8 SPIF_bit: 1;
	}Bits;
}SPSR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 SPR0_bit: 1;
		uint8 SPR1_bit: 1;
		uint8 CPHA_bit: 1;
		uint8 CPOL_bit: 1;
		uint8 MSTR_bit: 1;
		uint8 DORD_bit: 1;
		uint8 SPE_bit: 1;
		uint8 SPIE_bit: 1;
	}Bits;
}SPCR_Reg_Type;


typedef union{
	uint8 Byte;
}UDR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 MPCM_bit: 1;
		uint8 U2X_bit: 1;
		uint8 PE_bit: 1;
		uint8 DOR_bit: 1;
		uint8 FE_bit: 1;
		uint8 UDRE_bit: 1;
		uint8 TXC_bit: 1;
		uint8 RXC_bit: 1;
	}Bits;
}UCSRA_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 TXB8_bit: 1;
		uint8 RXB8_bit: 1;
		uint8 UCSZ2_bit: 1;
		uint8 TXEN_bit: 1;
		uint8 RXEN_bit: 1;
		uint8 UDRIE_bit: 1;
		uint8 TXCIE_bit: 1;
		uint8 RXCIE_bit: 1;
	}Bits;
}UCSRB_Reg_Type;


typedef union{
	uint8 Byte;
}UBRRL_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 ACIS0_bit: 1;
		uint8 ACIS1_bit: 1;
		uint8 ACIC_bit: 1;
		uint8 ACIE_bit: 1;
		uint8 ACI_bit: 1;
		uint8 ACO_bit: 1;
		uint8 ACBG_bit: 1;
		uint8 ACD_bit: 1;
	}Bits;
}ACSR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 MUX0_bit: 1;
		uint8 MUX1_bit: 1;
		uint8 MUX2_bit: 1;
		uint8 MUX3_bit: 1;
		uint8 MUX4_bit: 1;
		uint8 ADLAR_bit: 1;
		uint8 REFS0_bit: 1;
		uint8 REFS1_bit: 1;
	}Bits;
}ADMUX_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 ADPS0_bit: 1;
		uint8 ADPS1_bit: 1;
		uint8 ADPS2_bit: 1;
		uint8 ADIE_bit: 1;
		uint8 ADIF_bit: 1;
		uint8 ADATE_bit: 1;
		uint8 ADSC_bit: 1;
		uint8 ADEN_bit: 1;
	}Bits;
}ADCSRA_Reg_Type;


typedef union{
	uint16 Byte;
}ADC_Reg_Type;


typedef union{
	uint8 Byte;
}TWDR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 TWGCE_bit: 1;
		uint8 TWA0_bit: 1;
		uint8 TWA1_bit: 1;
		uint8 TWA2_bit: 1;
		uint8 TWA3_bit: 1;
		uint8 TWA4_bit: 1;
		uint8 TWA5_bit: 1;
		uint8 TWA6_bit: 1;
	}Bits;
}TWAR_Reg_Type;


typedef union{
	uint8 Byte;
	struct{
		uint8 TWPS0_bit: 1;
		uint8 TWPS1_bit: 1;
		uint8 : 1;
		uint8 TWS3_bit: 1;
		uint8 TWS4_bit: 1;
		uint8 TWS5_bit: 1;
		uint8 TWS6_bit: 1;
		uint8 TWS7_bit: 1;
	}Bits;
}TWSR_Reg_Type;


typedef union{
	uint8 Byte;
}TWBR_Reg_Type;


/*******************************************************************************/




/*******************************************************************************
 *                               Definitions                             *
 *******************************************************************************/


#define SREG_REG (*(volatile STATUS_Reg_Type*)0x5F)
#define SP_REG (*(volatile STACK_POINTER_Type*)0x5D)
#define OCR0_REG (*(volatile TIMER0_OCR0_Type*)0x5C)
#define GICR_REG (*(volatile GICR_Reg_Type*)0x5C)
#define GIFR_REG (*(volatile GIFR_Reg_Type*)0x5A)
#define TIMSK_REG (*(volatile TIMSK_Reg_Type*)0x59)
#define TIFR_REG (*(volatile TIFR_Reg_Type*)0x58)
#define SPMCR_REG (*(volatile SPMCR_Reg_Type*)0x57)
#define TWCR_REG (*(volatile TWCR_Reg_Type*)0x56)
#define MCUCR_REG (*(volatile MCUCR_Reg_Type*)0x55)
#define MCUCSR_REG (*(volatile MCUCSR_Reg_Type*)0x54)
#define TCCR0_REG (*(volatile TIMER0_TCCR0_Type*)0x53)
#define TCNT0_REG (*(volatile TIMER0_TCNT0_Type*)0x52)
#define OSCCAL_OCDR_REG (*(volatile OSCCAL_OCDR_Type*)0x51)
#define SFIOR_REG (*(volatile SFIOR_Reg_Type*)0x50)
#define TCCR1A_REG (*(volatile TIMER1_TCCR1A_Type*)0x4F)
#define TCCR1B_REG (*(volatile TIMER1_TCCR1B_Type*)0x4E)
#define TCNT1_REG (*(volatile TIMER1_TCNT1_Type*)0x4C)
#define OCR1A_REG (*(volatile TIMER1_OCR1A_Type*)0x4A)
#define OCR1B_REG (*(volatile TIMER1_OCR1B_Type*)0x48)
#define ICR1_REG (*(volatile TIMER1_ICR1_Type*)0x46)
#define TCCR2_REG (*(volatile TIMER2_TCCR2_Type*)0x45)
#define TCNT2_REG (*(volatile TIMER2_TCNT2_Type*)0x44)
#define OCR2_REG (*(volatile TIMER0_OCR2_Type*)0x43)
#define ASSR_REG (*(volatile ASSR_Reg_Type*)0x42)
#define WDTCR_REG (*(volatile WDTCR_Reg_Type*)0x41)
#define UBRRH_REG (*(volatile UBRRH_Reg_Type*)0x40)
#define UCSRC_REG (*(volatile UCSRC_Reg_Type*)0x40)
#define EEAR_REG (*(volatile EEAR_Reg_Type*)0x3E)
#define EEDR_REG (*(volatile EEDR_Reg_Type*)0x3D)
#define EECR_REG (*(volatile EECR_Reg_Type*)0x3C)
#define PORTA_REG (*(volatile GPIO_Reg_Type*)0x3B)
#define DDRA_REG (*(volatile GPIO_Reg_Type*)0x3A)
#define PINA_REG (*(volatile GPIO_Reg_Type*)0x39)
#define PORTB_REG (*(volatile GPIO_Reg_Type*)0x38)
#define DDRB_REG (*(volatile GPIO_Reg_Type*)0x37)
#define PINB_REG (*(volatile GPIO_Reg_Type*)0x36)
#define PORTC_REG (*(volatile GPIO_Reg_Type*)0x35)
#define DDRC_REG (*(volatile GPIO_Reg_Type*)0x34)
#define PINC_REG (*(volatile GPIO_Reg_Type*)0x33)
#define PORTD_REG (*(volatile GPIO_Reg_Type*)0x32)
#define DDRD_REG (*(volatile GPIO_Reg_Type*)0x31)
#define PIND_REG (*(volatile GPIO_Reg_Type*)0x30)
#define SPDR_REG (*(volatile SPDR_Reg_Type*)0x2F)
#define SPSR_REG (*(volatile SPSR_Reg_Type*)0x2E)
#define SPCR_REG (*(volatile SPCR_Reg_Type*)0x2D)
#define UDR_REG (*(volatile UDR_Reg_Type*)0x2C)
#define UCSRA_REG (*(volatile UCSRA_Reg_Type*)0x2B)
#define UCSRB_REG (*(volatile UCSRB_Reg_Type*)0x2A)
#define UBRRL_REG (*(volatile UBRRL_Reg_Type*)0x29)
#define ACSR_REG (*(volatile ACSR_Reg_Type*)0x28)
#define ADMUX_REG (*(volatile ADMUX_Reg_Type*)0x27)
#define ADCSRA_REG (*(volatile ADCSRA_Reg_Type*)0x26)
#define ADC_REG (*(volatile ADC_Reg_Type*)0x24)
#define TWDR_REG (*(volatile TWDR_Reg_Type*)0x23)
#define TWAR_REG (*(volatile TWAR_Reg_Type*)0x22)
#define TWSR_REG (*(volatile TWSR_Reg_Type*)0x21)
#define TWBR_REG (*(volatile TWBR_Reg_Type*)0x20)


/********************************************************************************/


#endif /* AVR_REGISTERS_H_ */
