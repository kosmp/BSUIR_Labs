code SEGMENT para USE16 PUBLIC 'code'
    ASSUME CS:code, DS:data, SS:stack
    START:
        mov ax,data
        mov ds,ax 
        mov ah,9h
        mov dx,offset message
        int 21h
        mov ah,02h   ; function 02h
        mov dx,0100h ; set cursor row and col in console
        int 10h
        mov ah,9h
        mov dx,offset message
        int 21h  
        ; To successfully exit the program we need to put 4c in ah.
        ; To return code 0 we need to put 0 in al
        mov ax,4c00h
        int 21h
code ends

data SEGMENT para USE16 PUBLIC 'data'
    message db 'String of symbols!$'
data ends

stack SEGMENT para USE16 STACK 'stack'
    db 256 DUP(?)
stack ends

end START