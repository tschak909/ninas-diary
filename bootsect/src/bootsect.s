	.list off
	.include "atari.inc"

	.export start

	.segment "CODE"

	;; Boot header
	.byte $00		; Boot flags
	.byte $01		; # of sectors to load
	.byte $00		; run address
	.byte $07		; " "
	.byte $00		; init address
	.byte $07		; " "

	;; Start of program code
	;; Set color, set display list, and spin.
start:	
	lda #154
	sta COLOR0
	lda #69
	sta COLOR4
	lda #<dlist
	sta SDLSTL
	lda #>dlist
	sta SDLSTH
loop:	jmp loop
	
	.segment "RODATA"

	;; The boot message
dmsg:
	.byte 0,46,41,46,33,7,51,0,36,41,33,50,57,0,36,41,51,43,0,0
	;; The display list
dlist:
	.byte $70
	.byte $70
	.byte $70
	
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70
	.byte $70

	.byte $47
	.word dmsg
	.byte $41

	.res 63 		; Padding out to 128 bytes.
