//Where is the led connected
//-pin? green led  =0 | blue led =7| red led=14
//-port? green led = B| blue led = B|red led=B

#define PERIPH_BASE 0x40000000UL   //check "memory map" in Reference manual
#define AHB1_OFFSET 0x20000UL
#define AHB1PEPRIPH_BASE PERIPH_BASE+AHB1_OFFSET
#define GPIOB_OFFSET 0x400UL
#define GPIOB_BASE AHB1PEPRIPH_BASE+GPIOB_OFFSET //0x40020400 --GPI0B_BASE addr

#define RCC_OFFSET 0x3800UL //
#define RCC_BASE AHB1PEPRIPH_BASE+RCC_OFFSET //0x40023800 -- RCC_BASE addr

#define AHB1EN_R_OFFSET 0x30UL // (RCC_AHB1ENR) in RM

#define RCC_AHB1EN_R (*(volatile unsigned int *) (RCC_BASE+AHB1EN_R_OFFSET))


//Refer GPIO port mode register in RM
#define MODER_OFFSET  0x00UL

#define GPIOB_MODE_R   (*(volatile unsigned int *) (GPIOB_BASE+MODER_OFFSET))


//Refer RCC_AHB1ENR in RM doc for before value assignment
#define GPIOB_CLK_EN (1U<<1) // 0000 0000 0000 0000 0000 0000 0000 0010


// refer GPIO port output data register  in RM doc
#define ODR_OFFSET 0x14UL
#define GPIOB_OD_R   (*(volatile unsigned int *) (GPIOB_BASE+ODR_OFFSET))
//

#define USER_LED1_MODER (1U<<0)
#define USER_LED2_MODER (1U<<14)
#define USER_LED3_MODER (1U<<28)


#define USER_LED1 (1U<<0) //GREEN LED
#define USER_LED2 (1U<<7) //BLUE LED
#define USER_LED3 (1U<<14) //RED LED


int main(void)
{

	//Enable clock access to PORTB

	RCC_AHB1EN_R |= GPIOB_CLK_EN;

	//Configure led pins as output pins

	GPIOB_MODE_R |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

	while(1)
	{
		/*Turn ON all LEDs*/
		GPIOB_OD_R ^= 	USER_LED1 ;

		for(int i=0; i<900000; i++);

		GPIOB_OD_R ^= USER_LED2  ;

		for(int i=0; i<900000; i++);

		GPIOB_OD_R ^= USER_LED3  ;

		for(int i=0; i<900000; i++);

	}

}




