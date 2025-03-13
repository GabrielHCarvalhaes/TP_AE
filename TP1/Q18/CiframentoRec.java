
import java.util.Scanner;

public class CiframentoRec {
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();
    
        while(!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')){
    
            linha = cifrando(linha);
            System.out.println(linha);
            linha = sc.nextLine();
            
        }

        sc.close();
    }

    public static String cifrando(String linha){

        char[] cifra = new char[linha.length()];

        return cifrando(linha, 0, cifra);
    }

    private static String cifrando(String linha , int i, char[] cifra){
        if ((int) linha.charAt(i)> 31 && linha.charAt(i) < 127){
            int l = (int) linha.charAt(i) + 3;
            cifra[i] = (char)l;
        } else{
            cifra[i] = linha.charAt(i);
        } 

        if(i+1< linha.length()){
            cifrando(linha, i+1, cifra);
        }

        return new String(cifra);
    }
}
