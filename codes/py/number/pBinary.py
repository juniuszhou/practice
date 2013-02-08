import os
def reverseBinary():
    
    x := (x and $55555555) shl  1 or (x and $AAAAAAAA) shr  1;
    x := (x and $33333333) shl  2 or (x and $CCCCCCCC) shr  2;
    x := (x and $0F0F0F0F) shl  4 or (x and $F0F0F0F0) shr  4;
    x := (x and $00FF00FF) shl  8 or (x and $FF00FF00) shr  8;
    x := (x and $0000FFFF) shl 16 or (x and $FFFF0000) shr 16;
