import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Scanner;

public class Arquivo {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int numLidos = sc.nextInt();

        // Consome a quebra de linha deixada pelo nextInt() para evitar problemas na leitura posterior
        sc.nextLine();

        // Tenta abrir (ou criar) um arquivo de acesso aleatório chamado "Doubles.txt" para leitura e escrita
        try (RandomAccessFile file = new RandomAccessFile("Doubles.txt", "rw")) {

            // Loop para ler os números da entrada e escrevê-los no arquivo
            for (int i = 0; i < numLidos; i++) {
                double num; 
                String linha = sc.nextLine(); 
                num = Double.parseDouble(linha);

                file.writeDouble(num);
            }

            // Loop para ler os números do arquivo em ordem inversa e exibi-los na tela
            for (int i = numLidos - 1; i >= 0; i--) {
                // Posiciona o ponteiro do arquivo no início do i-ésimo número double
                // Cada double ocupa 8 bytes, então o offset é i * 8
                file.seek(i * 8);
                double num = file.readDouble();

                if (num == (int) num) {
                    System.out.println((int) num);
                } else {
                    System.out.println(num); 
                }
            }

        } catch (IOException erro) {
            
        } finally {
          
            sc.close();
        }
    }
}