 .global send_one
 .global send_zero
 .global send_ret
 .global read_buttons

 #define PORTD 0x0B
 #define DDRD 0x0A
 #define PIND 0x09
 #define PINA 0x20
 #define DDRA 0x01
 #define PORTB 0x05
 #define DDRB 0x04

 ; This code is used to set the ones, zeroes and ret signal for the signals sent to the neopixels.
 ; Send_one = 12 clock cycles, send_zero = 8 clock cycles, send_ret = 44 clock cycles
 ; ldi, out, nop, dec, brne (branch not taken) = 1 clk / brne (branch taken) = 2 clk / ret = 4 clk

 send_one:
	ldi r19, 0b11111111

	out PORTB, r19
	out PORTD, r19
	nop
	nop
	ldi r18, 0b00000000
	nop
	out PORTB, r18
	out PORTD, r18
	
	ret

 send_zero:
	ldi r18, 0b11111111
	out PORTB, r18
	out PORTD, r18
	ldi r18, 0b00000000
	out PORTB, r18
	out PORTD, r18

	ret

 send_ret:
	ldi r18,0b00000000
	out PORTB, r18
	out PORTD, r18
	
	ldi r19, 20
		loop1:
			ldi r18, 10
			loop2:
				dec r18
				brne loop2
			dec r19
			brne loop1
			
	ret