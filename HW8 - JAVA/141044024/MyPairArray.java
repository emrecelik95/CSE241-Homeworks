@SuppressWarnings("unchecked")          // warningleri ignore et                      

public class MyPairArray <F,S> {
    public F first[];       // ilk eleman arrayi
    public S second[];      // ikinci eleman arrayi

    
    MyPairArray(int capacity){
        this.first = (F[])new Object[capacity];     // yer alma
        this.second = (S[])new Object[capacity];    // yer alma
    }

    
    
    public void swap(int ind1,int ind2){
        F tmpFirst = first[ind1];           // gecici degiskene at
        S tmpSecond = second[ind2];         //gecici degiskene at
    
        first[ind1] = first[ind2];
        second[ind1] = second[ind2];
                                            // swap et
        first[ind2] = tmpFirst;
        second[ind2] = tmpSecond;
    }
    
    public String toString(int i)           // verilen indisteki pairi yaz
    {
        return (first[i] + "," + second[i]);
    }
    
    public boolean isEqual(int ind1,int ind2)   // iki indisteki pairler eşit mi ?
    {
        return (first[ind1].equals(first[ind2]) && second[ind1].equals(second[ind2]));
    }
    
}
