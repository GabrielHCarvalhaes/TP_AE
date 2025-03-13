

import java.util.Random;
import java.util.Scanner;

public class Main {  
    public static void main(String[] args) {

        Random gerador = new Random();
        gerador.setSeed(4);
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();

        while (!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {       
            linha=substituindo(linha,gerador);
            System.out.println(linha);
            linha = sc.nextLine();
        }

        sc.close();
    }

    public static String substituindo(String linha, Random gerador){
        char[] linhaM= new char[linha.length()];
        char l1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26)), 
        l2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
        
        for(int i = 0; i < linha.length(); i++ ){

            if(linha.charAt(i) == l1 ){
    
                linhaM[i]= l2;
                
            }else{

              linhaM[i] = linha.charAt(i);

            }

        }

        return new String(linhaM);
    }   
}
