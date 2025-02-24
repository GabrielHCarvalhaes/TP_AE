import java.util.Scanner;

public class Palindromo {
        public static void main(String[] args) {
            String linha;
            Scanner sc= new Scanner(System.in);
            linha = sc.nextLine();
            while (!linha.equals("FIM")) {
                
                int tam = linha.length();
                boolean ehPalindromo = analisando(tam, linha);
                if(ehPalindromo){
                    System.out.println("SIM");
                }else{
                    System.out.println("NAO");
                }
                linha = sc.nextLine();
            }

            sc.close();
        }
        
        public static boolean analisando(int tam, String linha){
            boolean ehPalindromo = true;
            int n = tam/2, tras = tam-1;
            for(int i = 0; i < n; i++, tras--){
                if(linha.charAt(i) != linha.charAt(tras)){
                    ehPalindromo = false;
                    i= n;
                }
            } 

            return ehPalindromo;
        }
    }
    