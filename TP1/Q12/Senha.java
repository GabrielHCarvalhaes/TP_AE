import java.util.Scanner;

public class Senha {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        String linha = sc.nextLine();
       
        // Entra em um loop que continua até que a linha de entrada seja "FIM"
        while (!(linha.length() == 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {
            
            // Chama a função validandoSenha para verificar se a senha é válida
            boolean ehValida = validandoSenha(linha);
            
            // Se a senha for válida, imprime "SIM", caso contrário, imprime "NAO"
            if (ehValida) {
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }
            
            linha = sc.nextLine();
        }


        sc.close();
    }

    // Função que valida a senha de acordo com as regras especificadas
    public static boolean validandoSenha(String senha){
        boolean ehValida = false;
        
        // Verifica se a senha tem pelo menos 8 caracteres
        if(senha.length() >= 8){
            boolean temMaiuscula= false, temMinuscula = false, temCaracEspecial= false; 
            
            // Percorre cada caractere da senha
            for(int i = 0; i < senha.length(); i++){

                // Verifica se o caractere atual é uma letra maiúscula
                if(!temMaiuscula){
                    if(senha.charAt(i) >= 'A' && senha.charAt(i) <= 'Z' ){
                        temMaiuscula = true;
                    }
                }   

                // Verifica se o caractere atual é uma letra minúscula
                if(!temMinuscula){
                    if(senha.charAt(i) >= 'a' && senha.charAt(i) <= 'z' ){
                        temMinuscula = true;
                    }
                }   

                // Verifica se o caractere atual é um caractere especial (não alfanumérico)
                if(!temCaracEspecial){
                    if(((int) senha.charAt(i) >= 33 && (int) senha.charAt(i) <= 47) || ((int) senha.charAt(i) >= 58 && (int) senha.charAt(i) <= 64 ||
                    ((int) senha.charAt(i) >= 91 && (int) senha.charAt(i) <= 96) || ((int) senha.charAt(i) >= 123 && (int) senha.charAt(i) <= 126))){
                        temCaracEspecial = true;
                    }
                }   

                // Se a senha contiver pelo menos uma letra maiúscula, uma letra minúscula e um caractere especial, ela é considerada válida
                if (temCaracEspecial && temMaiuscula && temMinuscula) {
                    ehValida = true;
                    i = senha.length();
                }
            }
        }

        return ehValida;
    }
}