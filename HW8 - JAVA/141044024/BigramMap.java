import java.io.*;
import java.util.HashMap;
import java.util.Scanner;
import java.util.InputMismatchException;

@SuppressWarnings("unchecked")          // warningleri ignore et                      

public class BigramMap<T> implements Bigram<T>  // interface implement et
{
    private int dataType;               // veritipi
    private HashMap<Integer,Object> map = new HashMap<>();  // keyi integer,valuesi object olam map
    
    public BigramMap(int type)     // type alıp dataType ilklendiren constructor
    {
        setDataType(type);
    }
    
    // 
    @Override
    public void readFile(String filename) throws MyException
    {
        File file = new File(filename); 
        
        try 
        {
            Scanner input = new Scanner(file);   
            
            if(!input.hasNext())                    // dosya boş kontrolü
                throw new MyException("File can't be empty!");
            
            for(int i = 0 ; input.hasNext() ; ++i){   // dosya sonuna kadar dongu
                if(getDataType() == 1)                // tipe göre oku
                    map.put(i,input.nextInt());
                else if(getDataType() == 2)           
                    map.put(i,input.next());
                else if(getDataType() == 3)
                    map.put(i,input.nextDouble());
                else                                    // dataType excepitonu
                    throw new MyException("Datatype must be 1,2 or 3,please set it!");
            }
            
            if(numGrams() < 1)    // bigram için eleman sayısı şartı
                throw new MyException("File must contain more than 1 element");
        }
        catch (FileNotFoundException ex)        // dosya yoksa yakala
        {
            throw new MyException("File is not exist!");    // kendi clasımı fırlattım
        }
        catch (InputMismatchException ex) // dosya okumada problem çıkarsa yakala
        {
            throw new MyException("File is not in the correct format!"); // kendi clasım fırlattım
        }
    }

    // eleman sayısı - 1 = bigram sayısı
    @Override
    public int numGrams()
    {
        return map.size() - 1 ;
    }
    
    // bigramın kaç kez olduğuna ardışık indislerde bak ve sayısını dondur
    @Override
    public int numOfGrams(T big1,T big2)
    {
        int count = 0;
        for(int i = 0;i < numGrams() ; ++i)
            if(map.get(i).equals(big1) && map.get(i + 1).equals(big2))
                ++count;
        
        return count;
    }
    
    // azalarak bigramları tekrar sayılarına göre yazdır
    @Override
    public String toString()
    {
        String out = "";                // çıktı degiskeni
        MyPairArray<Object,Object> bigs = new MyPairArray<>(numGrams()); // kendi yazdığım pair array clasım
        boolean sameExist;          
        
        for(int i = 0 ; i < numGrams() ; ++i) // bigramları pair arrayine doldur
        { 
            bigs.first[i] = map.get(i);
            bigs.second[i] = map.get(i + 1);
        }
        
        //tekrar sayısına göre bigramları pair arrayinde sırala
        for(int i = 0 ; i < numGrams() ; ++i) 
            for(int j = i + 1 ; j < numGrams() - 1; ++j)
            {
                if(numOfGrams((T)bigs.first[i],(T)bigs.second[i]) < 
                   numOfGrams((T)bigs.first[i],(T)bigs.second[i]))
                    bigs.swap(i, j);
            }
        // çıktının doldurulması
        for(int i = 0 ; i < numGrams() ; ++i)
        {
            sameExist = false;          
            for(int j = i - 1; j >= 0 ; --j) // kendinden öncekilere bak
            {
                if(bigs.isEqual(i,j)) // pair önceden yazıldıysa bir daha yazmamak için
                {
                    sameExist = true;
                    j = -1;
                }
            }
            if(!sameExist)  // eğer hiç yazılmadıysa bigramı ve tekrar sayısını bas alt satıra geç
                out += bigs.toString(i) + " : " 
                + numOfGrams((T)bigs.first[i],(T)bigs.second[i]) + " times" + "\n";
            
        }
            
        return out;
    }
    
// dataType setter getter (belki dışardan degistirilmek istenir)    
    public void setDataType(int value)
    {
        dataType = value;
    }
    
    public int getDataType()
    {
        return dataType;
    }

}   
