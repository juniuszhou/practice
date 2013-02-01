/*
it is an example to use sse instruction to do matrix multiply.
*/
void matMul( float result[4][4], float left[4][4], float right[4][4] )  
{  
    __asm  
    {  
        mov eax,left  
        mov edi,right  
        mov edx,result  
        movaps xmm4,[edi]  
        movaps xmm5,[edi+16]  
        movaps xmm6,[edi+32]  
        movaps xmm7,[edi+48]  
        mov edi,0  
        mov ecx,4  
l_:     movaps xmm0,[eax+edi]  
        movaps xmm1,xmm0  
        movaps xmm2,xmm0  
        movaps xmm3,xmm0  
        shufps xmm0,xmm0,00000000b  
        shufps xmm1,xmm1,01010101b  
        shufps xmm2,xmm2,10101010b  
        shufps xmm3,xmm3,11111111b  
        mulps xmm0,xmm4  
        mulps xmm1,xmm5  
        mulps xmm2,xmm6  
        mulps xmm3,xmm7  
        addps xmm2,xmm0  
        addps xmm3,xmm1  
        addps xmm3,xmm2  
        movaps [edx+edi],xmm3  
        add edi,16  
        loop l_  
    }  
} 


int main()
{
return 1;
}
