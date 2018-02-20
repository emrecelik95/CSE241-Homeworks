
public interface Bigram<T>
{
    // interface in gerekli methodları
    public void readFile(String filename) throws MyException;
    public int numGrams();
    public int numOfGrams(T big1,T big2);
    public String toString();
    
}