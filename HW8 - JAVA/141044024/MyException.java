import java.lang.Exception;

@SuppressWarnings("serial")          // warningleri ignore et                      


public class MyException extends Exception{ //Exception dan miras al
    private final String error;             // parametreyle ilkenecek hata mesajı
    
    MyException(String err){    // string hata al
        error = err;            // error u ilklendir 
    }
    
    @Override
    public String toString(){   // erroru dondur
        return error;
    }
}
