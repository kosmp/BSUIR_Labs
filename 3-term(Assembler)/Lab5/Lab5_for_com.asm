.model tiny
.code
    ORG 100h
    START:
    message db 'String of symbols!$'
        mov ah,9h
        mov dx,offset message
        int 21h
        mov ah,02h
        mov dx,0100h
        int 10h
        mov ah,9h
        mov dx,offset message
        int 21h               
        ret
end START    



