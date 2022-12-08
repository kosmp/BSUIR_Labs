.model SMALL
.stack 100h

.data        
max_number_of_digits_in_number EQU 7
number_of_lines EQU 5
number_of_columns EQU 6
number EQU 3276 
cr EQU 0Dh ;\r
lf EQU 0Ah ;\n
ASCII_zero EQU 30h
Ten EQU 10
twelve EQU 12
three EQU 3 

;-----Variables-----
crlf db lf,cr,'$'
line_number db 00h 
colum_number db 00h
max_lenght_buffer db max_number_of_digits_in_number
length_buffer db ? 
buffer db max_number_of_digits_in_number dup (' ')
buffer_matrix db number_of_lines*number_of_columns*max_number_of_digits_in_number+number_of_lines*3+1 dup ('$')
adress dw ? 
min_sum dd 00h 
sign_flag db 00h 
sum dd 00h
buffer_for_sum db twelve dup ('$')
;-----MESSAGE-----
message_task db "19.Enter a matrix of integers with a dimension of 5 * 6 elements. Find the column numbers with the minimum sum of elements.",lf,cr,'$'
message_remark db "Remark:range of matrix values from -32 768 to 32 767.",lf,cr,'$' 
message_input_numbers db "Input numbers." ,lf,cr,'$'
message_input_number1 db "matrix[",'$'
message_input_number2 db  "][",'$'
message_input_number3 db "] = ",'$'
message_invalid_input db "Invalid_input.",lf,cr,'$' 
message_repeat db "Input again:",lf,cr,'$'
message_void_input db "You have not entered anything.",lf,cr,'$'
message_overflow db "Overflow:",lf,cr,'$' 
message_colum_number db "Colum with min sum:",lf,cr,'$'
;-----Variables for matrix-----
matrix dw number_of_lines*number_of_columns dup (?)


;*****MACROS***** 
output_message MACRO message   ;Output message 
        mov dx,offset message
        mov ah,09h             ;Write at cursor position
        int 21h
ENDM


output_message1 MACRO adres   ;Output message 
        mov dx, adres
        mov ah,09h
        int 21h
ENDM

input_str MACRO max_length_str ;Input string 
        mov dx,offset max_length_str  
        mov ah,0Ah
        int 21h
        mov di,offset max_length_str	
ENDM

;-------------------------------------------------------------------------------------------------------------------
.code 


    Main:
          
        mov ax,@data
        mov ds,ax 
        mov es,ax 
        lea di,buffer_matrix
        mov adress,di
        mov ax,adress
        
        
        output_message message_task
        output_message message_remark
        
        call Input_numbers
        
        
        call crlf_str
        output_message buffer_matrix
        
         
        call Find_the_column_numbers_with_the_minimum_sum_of_elements
        
        
        call crlf_str
        output_message message_colum_number 
        output_message buffer_for_sum 
    
     Exit:  
        mov ax,4c00h
        int 21h 


;******PROCEDURS*****
crlf_str PROC                  ;Go to a new line
        mov dx, offset crlf
        mov ah, 09h
        int 21h  
        ret
crlf_str ENDP 


;--------------------
Input_numbers PROC
        xor cx,cx
        mov cl,number_of_lines 
        lea di,buffer_matrix
        
    matrix_i:
        push cx
        mov cl,number_of_columns
        mov colum_number,00h
        
        
    matrix_j:
        push cx
        call Input_number
        call crlf_str
        inc colum_number
        pop cx
        loop matrix_j
        
        mov di,adress 
        mov byte ptr[di],lf
        inc di
        mov byte ptr[di],cr
        inc di


        mov adress,di
        inc line_number 
        pop cx
        loop matrix_i
        
        mov di,adress 
        mov byte ptr [di],'$'
        ret
Input_numbers ENDP 


;---------------------------------------------------
Input_number PROC 
    Repiat_input:
    
        call Input_a_number_in_the_buffer
        

        xor bx,bx 
        xor dx,dx
        xor cx,cx
        mov cl,length_buffer
        xor ax,ax 
        lea si,buffer 
        mov bl,ten
        
     Number_calculation:  
        mov dl,byte ptr[si]
        cmp dl,'-'
        je Badge_mark   
        sub dx,ASCII_zero
        
        
        cmp cl,01h
        je Last_digit 
    
        add ax,dx 
        cmp ax,number
        ja Overflow
        mul bx
        jo Overflow 
        
     Badge_mark:
      inc si   
     Last_digit:
    
         
         loop Number_calculation 
 
        
         
         cmp sign_flag,01h
         jne  Positive_number
    
    Negative_number:
         not ax
         inc ax 
         
         not dx
         inc dx  
         
         add ax,dx
         jo Overflow
         jmp Writing_to_the_matrix 
         
         
     Positive_number:
         add ax,dx
         jo Overflow
         
         
     Writing_to_the_matrix:    
         lea si,matrix
         push ax
          
         xor dx,dx
         mov dl,number_of_columns
          
                        
         xor bx,bx 
         xor ax,ax
         mov al,line_number
         mul dl
         mov bl,colum_number
         add ax,bx
         shl ax,1 
         add si,ax
         pop ax                        
         mov es[si],ax
         
         
      Writing_to_the_buffer_matrix:
 
         mov di,adress
         lea si,buffer
         mov cl,length_buffer 
         rep movsb
         mov cl,max_number_of_digits_in_number 
         sub cl,length_buffer
         mov al,' '
         rep stosb
         mov adress,di
           
        
         
        jmp Exit_PROC_Input_number
    
    
     Overflow: 
     call crlf_str
        output_message message_overflow     
       jmp Repiat_input     
              
    Exit_PROC_Input_number:        
        
        
        ret
Input_number ENDP        
;---------------------------------------------------
Input_a_number_in_the_buffer PROC
             
    Input_number1:
        output_message message_input_number1
        mov ah,02h
        mov dl,line_number
        add dl,ASCII_zero
        int 21h
        output_message message_input_number2 
        mov dl,colum_number
        add dl,ASCII_zero
        mov ah,02h
        int 21h
        output_message message_input_number3
        input_str max_lenght_buffer
        cmp length_buffer,00h 
        je  Void_input
        
        
        xor cx,cx
        mov sign_flag,cl 
        mov cl,length_buffer
        lea si,buffer
        
        
      Check_buffer:
        mov al,byte ptr [si]
        call Check_symbol_by_digit
        
        
        cmp ah,00h
        je Invalid_input_digit
        cmp ah,02h
        je  Flag_sign
        
        
      Continue_check_buffer:   
        inc si
        loop Check_buffer
        mov byte ptr [si],' '

        jmp Exit_PROC_Input_a_number_in_the_buffer
        
         
    Invalid_input_digit:
        call crlf_str
        output_message message_invalid_input 
        jmp Repeat_input_number
        
         
    Void_input:    
        call crlf_str
        output_message message_void_input
        je Repeat_input_number
        
        
        
    Repeat_input_number:
        output_message message_repeat
        je  Input_number1 
        
        
    Flag_sign:
        mov sign_flag,01h 
        jmp Continue_check_buffer        
         
    Exit_PROC_Input_a_number_in_the_buffer:
        cmp al,'-'
        je Void_input
        ret
Input_a_number_in_the_buffer ENDP


;------------------------------------------------------------
Check_symbol_by_digit PROC
        mov ah,01h
        cmp al,'-'
        je Minus_sign
        cmp al,'0'
        jb Invalid_input
        cmp al,'9'
        jbe Exit_PROC_Check_symbol_by_digit
        
       
    Invalid_input:
        mov ah,00h
        jmp Exit_PROC_Check_symbol_by_digit
        
            
        
    Minus_sign:
        cmp cl,length_buffer
        jne Invalid_input
        mov ah,02h
           

    Exit_PROC_Check_symbol_by_digit:
        ret 
Check_symbol_by_digit ENDP        


;------------------------------------------------------------
Find_the_column_numbers_with_the_minimum_sum_of_elements PROC
        
        
        xor ax,ax
        mov colum_number,al  
        mov line_number,al
        lea si,buffer_for_sum
        xor cx,cx
        mov cl,number_of_columns
        xor ax,ax
        xor bx,bx
        xor dx,dx  
    Find_min_sum:
        
        mov line_number,00h    
        push cx
        mov cl,number_of_lines
        xor ax,ax
        mov sum[2],ax
        mov sum,ax
    Summa:
    
        lea di,matrix
        xor bx,bx
        xor ax,ax
        mov dl,number_of_columns
        
         
        
        mov al,line_number
        mul dl
        
        
        mov bl,colum_number
        
        
        add ax,bx
        shl ax,1 
        add di,ax 
        
        
        mov ax,es[di]
        xor bx,bx
        add ax,00h
        jns metka1
        not bx

        
        
        metka1:
        
        add sum,ax
        adc sum[2],bx
      
        
        inc line_number  
        loop Summa
        
           
         
         
        ;mov ax,sum
        pop cx  
        
        cmp cl,number_of_columns
        je Whrite_to_bufer 
        
        mov ax,word ptr sum[2]
        cmp ax,word ptr min_sum[2] 
        jl Less
        jg Metka
        mov ax,word ptr sum
        cmp ax,word ptr min_sum 
        jl Less
        je Equal
        
     Metka:
        inc colum_number
        loop Find_min_sum:
        
         
        inc si
        mov byte ptr [si],'$'
        jmp Exit_PROC_Find_the_column_numbers_with_the_minimum_sum_of_elements 
     
     
     Less:
        lea si,buffer_for_sum
        jmp Whrite_to_bufer 
     
     Equal:
        inc si
        mov byte ptr [si],' '
        inc si

               
    Whrite_to_bufer: 
    
    
        mov ax,word ptr sum[2]
        mov word ptr min_sum[2],ax
        mov ax,word ptr sum
        mov word ptr min_sum,ax
        
           
        mov dl,colum_number
        add dl,30h
        mov byte ptr [si],dl
        jmp Metka
    
    
    
  
Exit_PROC_Find_the_column_numbers_with_the_minimum_sum_of_elements:
        ret
Find_the_column_numbers_with_the_minimum_sum_of_elements ENDP
           

END Main