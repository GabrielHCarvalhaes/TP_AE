
import java.util.Scanner;

public class Is {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();

        while(!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')){


            boolean verifica = soVogais(linha);
            resposta(verifica);

      
            verifica = soConsoantes(linha);
            resposta(verifica);

       
            verifica = ehInteiro(linha);
            resposta(verifica);

   
            if(verifica){
                System.out.println("SIM");
            }else{
                verifica = ehReal(linha);
                if(verifica){
                    System.out.println("SIM");
                }else{
                    System.out.println("NAO");
                }
            }
              
           linha = sc.nextLine();
        }

    }

    public static boolean ehReal(String linha){
        boolean v= true;
        int contadorSeparador=0;
        for(int i=0; i < linha.length(); i++){
            char l = linha.charAt(i);
            if(!(l >= '0' && l <= '9') && l != '.' && l != ','){
                v=false;
                i=linha.length();
            }

            if(l == '.' || l == ','){
                contadorSeparador++;
            }

            if(contadorSeparador > 1){
                v=false;
                i=linha.length();
            }
        }

        return v;
    }

    public static boolean ehInteiro(String linha){
        boolean v= true;

        for(int i=0; i < linha.length(); i++){
            int l = (int) linha.charAt(i);
            if(l < 48 || l > 57) {
                v=false;
                i=linha.length();
            }
        }
        return v;
    }

    public static Boolean soConsoantes(String linha){

        boolean v= true;

        for(int i=0; i < linha.length(); i++){
            if( ((linha.charAt(i) >= 'A' && linha.charAt(i) <= 'Z') || (linha.charAt(i) >= 'a' && linha.charAt(i) <= 'z'))){
                if(linha.charAt(i) == 'A' || linha.charAt(i) == 'a' || linha.charAt(i) == 'E' || linha.charAt(i) == 'e'
                || linha.charAt(i) == 'I' || linha.charAt(i) == 'i' || linha.charAt(i) == 'O' || linha.charAt(i) == 'o'
                || linha.charAt(i) == 'U' || linha.charAt(i) == 'u'){
                    v=false;
                    i=linha.length();  
                }
            }else{
                v=false;
                i=linha.length(); 
            }
        }

        return v;
    }

    public static Boolean soVogais(String linha){
        boolean v= true;

        for(int i=0; i < linha.length(); i++){

            if(!(linha.charAt(i) == 'A' || linha.charAt(i) == 'a' || linha.charAt(i) == 'E' || linha.charAt(i) == 'e'
            || linha.charAt(i) == 'I' || linha.charAt(i) == 'i' || linha.charAt(i) == 'O' || linha.charAt(i) == 'o'
            || linha.charAt(i) == 'U' || linha.charAt(i) == 'u')){
              v=false;
              i=linha.length();  
            }

        }

        return v;
    }


    public static void resposta(boolean certo){

        if(certo){
            System.out.print("SIM ");
        }else{
            System.out.print("NAO ");
        }
    }
}
