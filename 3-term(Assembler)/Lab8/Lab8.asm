.model small

.stack 100h

.data    
readedTotal           dw  0
writedTotal           dw  0

maxCMDSize equ 127
cmd_size              db  ?
cmd_text              db  maxCMDSize + 2 dup(0)
sourcePath            db  maxCMDSize + 2 dup(0) 
;sourcePath            db  "text.txt", 0
       
                      
sourceID              dw  0
                      
maxWordSize           equ 50
buffer                db  maxWordSize + 2 dup(0)
                            
spaceSym              db  " ","$"                            
                            
spaceSymbol           equ ' '
newLineSymbol         equ 0Dh
returnSymbol          equ 0Ah
tabulation            equ 9
endl                  equ 0
                      
startText             db  "Program is started",                                               '$'
badCMDArgsMessage     db  "Bad command-line arguments. Only 1 argument required: source path",'$'
badSourceText         db  "Cannot open source file",                                          '$'
fileNotFoundText      db  "File not found",                                                   '$'
errorClosingSource    db  "Cannot close source file",                                         '$' 
errorWritingText      db  "Error writing to file",                                            '$'
endText               db  "Program is ended",                                                 '$'
errorReadSourceText   db  "Error reading from source file",                                   '$'
EOF                   db  0

period                equ 2
currWordStartingValue equ 0
currWordIndex         db  currWordStartingValue	;

.code  

println MACRO info          
	push ax                 
	push dx                 
                            
	mov ah, 09h             ; input command
	lea dx, info            ; load to dx message "info"
	int 21h                 ; call interruption for input
                            
	mov dl, 0Ah             ; symbol of new line
	mov ah, 02h             ; output command
	int 21h                 ; interruption 
                            
	mov dl, 0Dh             ; symbol of string beginning  
	mov ah, 02h             
	int 21h                 
                            
	pop dx                  
	pop ax                       
ENDM

main:
	mov ax, @data           ; load  data
	mov es, ax              
                            
	xor ch, ch              ; ch = 0
	mov cl, ds:[80h]		; offset for work with command line
	mov cmd_size, cl 		; cmd_size -- length of command line
	mov si, 81h            
	lea di, cmd_text        ; load to di offset of the text from cmd 
	rep movsb               ; load to ES:DI byte from DS:SI
                            
	mov ds, ax              ; load data to ds
                            
	println startText       
                            
	call parseCMD           ; call procedure of parsing cmd
	cmp ax, 0               
	jne endMain				; if ax != 0 -- error in procedure, jump to endMain
                            
	call openFiles          ; call procedure, which opens file
	cmp ax, 0               
	jne endMain				
                        
	call processingFile     ; main procedure for processing data 
	cmp ax, 0                
	jne endMain				
                            
	call closeFiles         ; finish processing data, call procedure of closing file
	cmp ax, 0               
	jne endMain				
                            
endMain:                    
	println endText         
                            
	mov ah, 4Ch             ; load to ah code of finishing work
	int 21h                 


cmpWordLenWith0 MACRO textline, is0Marker       ;  compare string with zero, 1st parameter - string, 2nd - condition of jump if zero
	push si                                     
	                                           
	lea si, textline                            ; si = offset of string we measure length
	call    strlen                              ; call proc of searching length textline
	                                            
	pop si                                      
	cmp ax, 0                                   
	je is0Marker                               
ENDM                                                                           
                                                 

parseCMD PROC                                  
	push bx                                     
	push cx                                     
	push dx                                  
                                                ; cl - size of cmd
	mov cl, cmd_size                            
	xor ch, ch                                  
                                                
	lea si, cmd_text                            ; si - offset of data from cmd
	                                                                                                      
	lea di, buffer                              ; di - offset of buffer for data processing
	call rewriteAsWord                                                                                     
                                                                                                           
	lea di, sourcePath                          ; di - offset of sourcePath
	call rewriteAsWord                          
                                                
	cmpWordLenWith0 sourcePath, badCMDArgs      ; if sourcePath is empty - error
	;checkTxt        sourcePath, badCMDArgs
                                                 
	lea di, buffer                               
	call rewriteAsWord                          
                                                
	cmpWordLenWith0 buffer, argsIsGood          ; check if parameters correct
                                                ; correct - argsIsGood
badCMDArgs:                                     
	println badCMDArgsMessage                   
	mov ax, 1                                   
                                                
	jmp endproc                                
                                               
argsIsGood:                                    
	mov ax, 0                                   
endproc:                                        
	pop dx                                      
	pop cx                                      
	pop bx                                      
	ret	                                        
ENDP

;cx - length of cmd
;result - rewrite parameter from cmd 
rewriteAsWord PROC              
	push ax                     
	push cx                     
	push di                     
	                            
loopParseWord:                  
	mov al, ds:[si]             ; al - current symbol
	
	cmp al, spaceSymbol         
    je isStoppedSymbol                                           
	cmp al, newLineSymbol       
	je isStoppedSymbol          ; if symbol is
	cmp al, tabulation          ; shift tabulation 0Ah, 0Dh or \0
	je isStoppedSymbol          ; then it is end of the word
	cmp al, returnSymbol        
	je isStoppedSymbol                                                  ;
	cmp al, endl                
	je isStoppedSymbol          
                                
	mov es:[di], al             
                                
	inc di                      
	inc si                      
                                
	loop loopParseWord          
isStoppedSymbol:                
	mov al, endl          
	mov es:[di], al             
	inc si                      
                                
	pop di                      
	pop cx                      
	pop ax                      
	ret                         
ENDP   

strlen PROC                    
	push bx                     
	push si                     
	                            
	xor ax, ax                  
                                
    startCalc:                  
	    mov bl, ds:[si]         
	    cmp bl, endl            
	    je endCalc              
                                
	    inc si                  
	    inc ax                  
	    jmp startCalc           
	                            
    endCalc:                    
	pop si                      
	pop bx                      
	ret                         
ENDP                            

openFiles PROC                  
	push bx                     
	push dx                     
	
	
	
	push si                                     
	                                            
	lea si, sourcePath                          
	call    strlen                              
	    
	xor si, si         
	mov si, ax 
	sub si, 1                   
	        
	cmp sourcePath[si], 't' 
	jne checkTxt_Error     
	
	sub si, 1
	
	cmp sourcePath[si], 'x' 
	jne checkTxt_Error    
	
	sub si, 1
	
	cmp sourcePath[si], 't' 
	jne checkTxt_Error   
	
	sub si, 1
	
	cmp sourcePath[si], '.' 
	jne checkTxt_Error
	                    
	jmp checkTxt_OK                    
	checkTxt_Error: 
	pop si
	jmp badOpenSource       
	       
	checkTxt_OK:                                            
	pop si  
	
                                
	mov ah, 3Dh			        
	mov al, 02h			        
	lea dx, sourcePath          
	mov cx, 00h			       
	int 21h                     
                                
	jb badOpenSource	        
                                
	mov sourceID, ax	        
                               
	mov ax, 0			        
	jmp endOpenProc		        
                                
badOpenSource:                  
	println badSourceText       
	cmp ax, 02h                 
	jne errorFound              
                                
	println fileNotFoundText    
                                
	jmp errorFound              
                                                            
errorFound:                     
	mov ax, 1                   
endOpenProc:                    
	pop dx                      
	pop bx                     
	ret                         
ENDP                            

closeFiles PROC                 
	push bx                     
	push cx                     
                                
	xor cx, cx                  
                                
	mov ah, 3Eh                 
	mov bx, sourceID            
	int 21h                     
                                
	jnb goodCloseOfSource		
                                
	println errorClosingSource  
	                            
	inc cx 			            ; now it is a counter of errors
                                
goodCloseOfSource:                       
	mov ax, cx 		            
                                
	pop cx                      
	pop bx                      
	ret                         
ENDP                            

setPosInFileTo MACRO symbolsInt, symbols;
	push ax                     
	push bx                     
	push cx                     
	push dx                     
                                
	mov ah, 42h                 
	xor al ,al 			        
	mov cx, symbolsInt           
	mov dx, symbols			    
	int 21h                     
                                
	pop dx                      
	pop cx                      
	pop bx                      
	pop ax                      
ENDM 

divCurrWordIndex MACRO          
	mov al, currWordIndex      
	xor ah, ah                  
                                
	push bx                    
	mov bl, period              
	div bl                      
	pop bx                      
	mov currWordIndex, ah      
                                
	cmp ah, 0                  
	je movToSkip                
	jmp movToWrite              
                                
ENDM                            

processingFile PROC                     
	push ax                             
	push bx                             
	push cx                             
	push dx                             
	push si                             
	push di                             
                                        
	mov bx, sourceID                    
	setPosInFileTo 0,0                  
                                        
    call readFromFile                   
	                                    
	cmp ax, 0                           
	je finishProcessing                 
                                        
	lea si, buffer                      
	lea di, buffer                      
	mov cx, ax					        
	xor dx, dx                         
                                       
loopProcessing:                         
	                                    
                   ;                    
writeDelimsAgain:                       
	call writeDelims                    
	add dx, bx                          
	cmp ax, 0                          
	je notNewLine                       
                                        ; 
                                        
	mov bl,currWordStartingValue        
	mov currWordIndex, bl              
                                        
notNewLine:                             
	call checkEndBuff                   
	cmp ax, 2                           
	je finishProcessing                 
	cmp ax, 1                          
	je writeDelimsAgain                 
                                        
	divCurrWordIndex                   
                                        
movToWrite:                             
	call writeWord                      
	add dx, bx                          
	call checkEndBuff                   
	cmp ax, 2                           
	je finishProcessing                 
	cmp ax, 1                           
	je movToWrite                       
                                       
	jmp endWriteSkip                   
                                        
movToSkip:                              
	call skipWord                       
	call checkEndBuff                   
	cmp ax, 2                          
	je finishProcessing                
	cmp ax, 1                           
	je movToSkip                        
                                        
	jmp endWriteSkip                     
                                        
endWriteSkip:                           
	push dx                             
	mov dl, currWordIndex               
	inc dl                              
	mov currWordIndex, dl 	           
	pop dx                              
                                        
	jmp loopProcessing                  
                                        
finishProcessing:                       
    mov bx, sourceID                                         
                                        
    setPosInFileTo 0,writedTotal        
                                        
    xor ax,ax                           
    mov ah, 40h                         
    mov bx, sourceID                   
    mov cx, 0h                          
    int 21h                             
                                        
	pop di                              
	pop si                              
	pop dx                              
	pop cx                              
	pop bx                              
	pop ax                              
	ret                                 
ENDP                                    

ParseWordAndJumpIfDelimTo MACRO marker    
    cmp al, spaceSymbol                
    je marker                                                            
	cmp al, newLineSymbol               
	je marker                           
	cmp al, tabulation                  
	je marker                           
	cmp al, returnSymbol                
	je marker                                                                   
	cmp al, endl                        
	je marker                           
                                        
ENDM                                    

;ds:si - offset to byte source (will change)
;es:di - offset to byte destination (will change)
;cx - max length (will change)
writeDelims PROC                        
	push dx                            
	xor bx, bx                         
	xor dx, dx                         
                                        
startWriteDelimsLoop:                   
	mov al, ds:[si]                     
	                                    
	cmp al, spaceSymbol                
    je isDelim                          
                                       
	cmp al, newLineSymbol               
	je isNewLineSymbol                 
                                        
	cmp al, tabulation                 
	je isDelim                          
                                        
	cmp al, returnSymbol                
	je isNewLineSymbol                  
                                        
	cmp al, endl                        
	je isDelim                          
                                                                               ;
	jmp isNotDelim                      
                                        
isNewLineSymbol:                        
	inc dx                              
isDelim:                                
	movsb                               
	inc bx                              
	loop startWriteDelimsLoop           
                                        
isNotDelim:                             
	mov ax, dx                         
                                        
	pop dx                              
	ret                                 
ENDP                                                    

;ds:si - offset, where we will find (will change)
;es:di - offset, where word will be (will change)
writeWord PROC                      
	push ax                         
	xor bx, bx                     
                                    
loopParseWordWW:                    
	mov al, ds:[si]                
	
	ParseWordAndJumpIfDelimTo isStoppedSymbolWW
                                    
	movsb                           
	inc bx                          
	loop loopParseWordWW            
                                    
isStoppedSymbolWW:                  
	pop ax                          
	ret                             
ENDP

;ds:si - offset, where we will find (will change)
skipWord PROC
	push ax
	xor bx, bx
	
loopParseWordSW:
	mov al, ds:[si]
	
	ParseWordAndJumpIfDelimTo isStoppedSymbolSW

	inc si
	inc bx
	loop loopParseWordSW

isStoppedSymbolSW:
	pop ax
	ret
ENDP  

;reads to buffer maxWordSize symbols
readFromFile PROC                   
	push bx                         
	push cx                         
	push dx                        
                                   
	mov ah, 3Fh                    
	mov bx, sourceID               
	mov cx, maxWordSize             
	lea dx, buffer                 
	int 21h                         
                                    
	jnb goodRead					
                                    
	println errorReadSourceText     
	mov ax, 0                       
                                    
goodRead:                              
    add readedTotal, ax                                
	pop dx                          
	pop cx                          
	pop bx                          
	ret                             
ENDP                                

;RES: ax - number of writed bytes
writeToFile PROC                      
	push bx                           
	push cx                           
	push dx                           
	                                 
	mov bx, sourceID                  
	setPosInFileTo 0, writedTotal     
	                                  
	add writedTotal, cx                                       
	                ;                 
	mov ah, 40h                       
	mov bx, sourceID                  
	lea dx, buffer                   
	int 21h                          
                                      
	jnb goodWrite					 
                                      
	println errorWritingText          
	mov ax, 0                         
                                      
goodWrite:                            
    mov bx, sourceID                                   
    setPosInFileTo 0, readedTotal     
                                      
	pop dx                            
	pop cx                            
	pop bx                            
	ret                               
ENDP                                  

checkEndBuff PROC               
	cmp cx, 0                   
	jne notEndOfBuffer          
                               
	cmp dx, 0                   
	je skipWrite                
	                           
	mov cx, dx                 
	call writeToFile            
                                
skipWrite:                      
	call readFromFile           
	cmp ax, 0                   
	je endOfProcessing          
                                
	lea si, buffer              
	lea di, buffer              
	mov cx, ax					
	
	xor dx, dx                  
                                
	mov ax, 1                   
	ret                         
                                
endOfProcessing:                
	mov ax, 2                   
	ret                         
                                
notEndOfBuffer:                 
	mov ax, 0                   
	ret                         
ENDP                            

end main