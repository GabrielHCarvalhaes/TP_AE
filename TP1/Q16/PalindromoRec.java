import java.util.Scanner;

public class PalindromoRec{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();
        while(!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M' )){
            ehPalindromo(linha);
            linha= sc.nextLine();
        }

    }

    public static void ehPalindromo(String linha){
        boolean ehPalindromo = true;
        ehPalindromo=analisando(linha,0, linha.length()/2, linha.length()-1);
        if(ehPalindromo){
            System.out.println("SIM");
        }else{
            System.out.println("NAO");
        }
    }

    public static boolean analisando(String linha, int i, int n, int atras){
        boolean ehPalindromo= true;
        if(i<n && i < atras){
            if(linha.charAt(i) != linha.charAt(atras)){
                ehPalindromo = false;
                i= n;
            }
            if (ehPalindromo) {
                ehPalindromo = analisando(linha, i+1, n, atras-1);
            }
        } 

        return ehPalindromo;
    }

}