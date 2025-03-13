import java.util.Scanner;

public class Ciframento {


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String linha = sc.nextLine();
       
        while (!ehFIM(linha)) {   
            linha = cifrando(linha);
            System.out.println(linha);
            linha = sc.nextLine();
        }

        sc.close();
    }

    public static boolean ehFIM(String linha) {
        return linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M';
    }    
    
    public static String cifrando(String linha){
        int[] lin = new int[linha.length()];
        char[] cifra = new char[linha.length()];
        for(int i =0 ; i < linha.length(); i++){
            if ((int) linha.charAt(i)> 31 && linha.charAt(i) < 127){
                lin[i]= (int) linha.charAt(i) + 3;
                cifra[i] = (char)lin[i];
            } else{
                cifra[i] = linha.charAt(i);
            } 
        }
        
        return new String(cifra);
    }

}
