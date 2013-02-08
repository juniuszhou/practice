int SequentialSelect(int *S, int num, int k)
{
if (num <= Q) return SortLessThanQ(S, num, k);
int cNum = num/Q + 1;
int *Medians = new int[cNum];
int i = 0;

for (int j = 0; j < num/Q; j++) {
    Medians[j] = SortSelect5(&S[i], 3); // find medians of subsequences
    i += Q;
}

int lastNum = num - (Q * (num / Q));

if (lastNum) {
    int lastQ = Q * (num / Q);
    Medians[cNum-1] = SortLessThanQ(&S[lastQ], lastNum, (lastNum+1)/2);
}
else cNum--;

int M = SequentialSelect(Medians, cNum, (cNum+1)/2);
int leg[3] = {0,0,0};
int *markS = new int[num];

CountAndMark(S, markS, num, M, leg);

if (leg[0] >= k) {
    int *sPack = new int[leg[0]];
    ArrayPack(S, sPack, num, markS, 0);
    //in smaller part, then recurse leg 0
    return SequentialSelect(sPack, leg[0], k);
}
else if ((leg[0] + leg[1]) >= k) return M;
else {
    int *sPack = new int[leg[2]];
    ArrayPack(S, sPack, num, markS, 2);
    //in bigger part, then recurse leg 2
    return SequentialSelect(sPack, leg[2], k-(leg[0]+leg[1]));
    }
}

void CountAndMark(int S[], int Marks[], int num, int median, int leg[3])
{
    for (int i = 0; i < num; i++) {
    if (S[i] < median) {Marks[i] = 0; leg[0]++;} //less than
    else if (S[i] > median) {Marks[i] = 2; leg[2]++;} // greater than
    else {Marks[i] = 1; leg[1]++;} // equal to
}

}
void ArrayPack(int S[], int sPack[], int num, int Marks[], int scanSym)
{
int j = 0;
for (int i = 0; i < num; i++)
if (Marks[i] == scanSym) sPack[j++] = S[i];
}



