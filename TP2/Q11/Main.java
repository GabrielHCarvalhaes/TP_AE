import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileInputStream;
import java.nio.charset.StandardCharsets;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

class Show{
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private Date date_added;
    private int release_year;
    private String rating;
    private String duration;
    private String[] listed_in;


    //CONSTRUTORES
    public Show(){
        this.show_id = "";
        this.type=  "";
        this.title = "";
        this.director = "";
        this.cast = new String[0];
        this.country = "";
        this.date_added = null;
        this.release_year = 0;
        this.rating = "";
        this.duration = "";
        this.listed_in = new String[0];
    }

    public Show( String show_id, String type, String title, String director, String[] cast, String country,
                 Date date_added, int release_year, String rating, String duration, String[] listed_in){
        
        this.show_id = show_id;
        this.type=  type;
        this.title = title;
        this.director = director;
        this.cast = cast;
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
        this.listed_in = listed_in;
    }

    //getters
    public String getShow_id() {
        return show_id;
    }

    public String getType() {
        return type;
    }

    public String getTitle() {
        return title;
    }

    public String getDirector() {
        return director;
    }

    public String[] getCast() {
        return cast;
    }

    public String getCountry() {
        return country;
    }

    public Date getDate_added() {
        return date_added;
    }

    public int getRelease_year() {
        return release_year;
    }

    public String getRating() {
        return rating;
    }

    public String getDuration() {
        return duration;
    }

    public String[] getListed_in() {
        return listed_in;
    }

    //setters
    public void setShow_id(String show_id) {
        this.show_id = show_id;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDirector(String director) {
        this.director = director;
    }

    public void setCast(String[] cast) {
        this.cast = cast;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public void setDate_added(Date date_added) {
        this.date_added = date_added;
    }

    public void setRelease_year(int release_year) {
        this.release_year = release_year;
    }

    public void setRating(String rating) {
        this.rating = rating;
    }

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public void setListed_in(String[] listed_in) {
        this.listed_in = listed_in;
    }


    //leitura
    public static void leiaShow(Show[] show) throws IOException, ParseException{
        
        BufferedReader file = new BufferedReader(new InputStreamReader(new FileInputStream("/tmp/disneyplus.csv"), StandardCharsets.UTF_8));

        file.readLine();

        String linha = "";
        while((linha = file.readLine()) != null){
            
            //show_id,type,title,director,cast,country,date_added,release_year,rating,duration,listed_in,description
            // 0   1       2                        3                            4               5          6            7     8      9       10                                              11
            //s1,Movie,A Spark Story,"Jason Steran, Leanne Dare","Apthon Corbin, Louis Gonzales",,"September 24, 2021",2021,TV-PG,88 min,Documentary,Two Pixar filmmakers strive to bring their uniquely personal SparkShorts visions to the screen.
            String[] divisao= linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");

            // Processa cada campo removendo as aspas externas
            for (int i = 0; i < divisao.length; i++) {
                divisao[i] = divisao[i].replaceAll("^\"|\"$", "").trim();
    
                // Tratamento especial para campos vazios representados como ",,"
                if (divisao[i].isEmpty() && linha.contains(",,")) {
                     divisao[i] = ""; 
                }
            }

            int index = Integer.parseInt(divisao[0].substring(1));
            --index;

            String[]cast = divisao[4].split(",\\s*");// removendo espaços depois da virgula e a virgula
            for(int i = 0; i <cast.length; i++){
                cast[i]=titleHasAspas(cast[i]);
            }
            ordenandoVetor(cast);
            if(divisao[3].isEmpty()){
                divisao[3]="NaN";
            }
            if(divisao[5].isEmpty()){
                divisao[5]="NaN";
            }
            Date date;
            if(!divisao[6].isEmpty()){
                SimpleDateFormat formatter = new SimpleDateFormat("MMMM dd, yyyy", Locale.ENGLISH);
                String data = divisao[6];
                date = formatter.parse(data);
            }else{
                date = null;
            }
            int ano = Integer.parseInt(divisao[7]);
            String[] listed = divisao[10].split(",\\s*"); 
            for(int i = 0; i <listed.length; i++){
                listed[i]=titleHasAspas(listed[i]);
            }
            ordenandoVetor(cast);

            show[index] = new Show(divisao[0], divisao[1], titleHasAspas(divisao[2]), divisao[3], cast,
                                    divisao[5], date, ano, divisao[8], divisao[9], listed);
        }

        file.close();

    }
    public static void ordenandoVetor(String[] ordenar){
        for(int i = 0; i < ordenar.length - 1; i++){
            for(int j = i+1; j <ordenar.length; j++){
                if(ehMaior(ordenar[i], ordenar[j])){
                    String tmp = ordenar[i];
                    ordenar[i] = ordenar[j];
                    ordenar[j]= tmp;
                }
            }
        }
    }
    
    public static String titleHasAspas(String title) {
        StringBuilder sb = new StringBuilder(title.length());
        boolean aspasAnterior = false;
    
        for(int i = 0; i < title.length(); i++) {
            char c = title.charAt(i);
            
            if(c != '"') {
                // Adiciona espaço apenas se:
                // 1. O caractere anterior era aspas
                // 2. O caractere atual não é espaço
                // 3. Não estamos no início da string
                if(aspasAnterior && c != ' ' && sb.length() > 0) {
                    sb.append(' ');
                }
                sb.append(c);
                aspasAnterior = false;
            } else {
                aspasAnterior = true;
            }
        }
        
        return sb.toString();
    }

    public static boolean ehMaior(String menor, String  maior ){
        boolean ehMaior = false;
        String[] str1 = menor.split(" "), str2 = maior.split(" ") ;
        if(str1[0].compareTo(str2[0]) > 0) {
            ehMaior = true;
        } else if(str1[0].compareTo(str2[0]) == 0) {
            if(str1.length > 1 && str2.length > 1) {
                if(str1[1].compareTo(str2[1]) > 0) {
                    ehMaior = true;
                }
            }
        }
        
        return ehMaior;
    }

    public void imprimir(){

        System.out.print("=> " + show_id + " ## " + title + " ## " + type + " ## " );

        if(director.isEmpty()){
            System.out.print("NaN" + " ## " + "[");
        }else{
            System.out.print( director + " ## " + "[");
        }

        if(cast.length == 1 && cast[0].isEmpty()){
            System.out.print("NaN" + "]");
        }else{
            for(int i = 0; i < cast.length-1;i++){
                System.out.print(cast[i] + ", ");
            }
            System.out.print(cast[cast.length-1] + "]");            
        }
        if (country.isEmpty()) {
            System.out.print(" ## " + "NaN" + " ## ");
        }else{
            System.out.print(" ## " + country + " ## ");
        }
        if(date_added == null){
            System.out.print("NaN" + " ## " + "[");
        }else{
            SimpleDateFormat formatter = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
            String data = formatter.format(date_added);
            System.out.print(data + " ## " );
        }

        System.out.print(release_year + " ## ");
        System.out.print(rating + " ## ");
        System.out.print(duration + " ## "+ "[");

        if(listed_in.length == 1 && listed_in[0].isEmpty()){
            System.out.println("NaN" + "]"+ "##");
        }else{
            for(int i = 0; i < listed_in.length-1;i++){
                System.out.print(listed_in[i] + ", ");
            }
            System.out.println(listed_in[listed_in.length-1] + "]" +" ##");            
        }

    }

    

}

public class Main {
    static Show[] show = new Show[1368];
    static int ids[] = new int[1368];
    
    public static void main(String[] args) throws IOException, ParseException {
        Scanner sc = new Scanner(System.in);
        Show.leiaShow(show);
        String linha = sc.next();
        int tam = 0;

        while (!linha.equals("FIM")) {
            int index = Integer.parseInt(linha.substring(1));
            ids[tam] = index;
            linha = sc.next();
            tam++;
        }
        
        countingSort(tam);

        for(int i = 0; i < tam; i++) {
            show[ids[i]-1].imprimir(); 
        }
    }

    public static void countingSort(int n) {
        // 1. Encontrar o ano mínimo e máximo
        int minYear = Integer.MAX_VALUE;
        int maxYear = Integer.MIN_VALUE;
        
        for (int i = 0; i < n; i++) {
            int year = show[ids[i]-1].getRelease_year();  
            if (year < minYear) minYear = year;
            if (year > maxYear) maxYear = year;
        }
        
        int range = maxYear - minYear + 1;
        
        // 2. Criar array de contagem e array auxiliar
        int[] count = new int[range];
        int[] output = new int[n];
        
        // 3. Contar a frequência de cada ano
        for (int i = 0; i < n; i++) {
            int year = show[ids[i]-1].getRelease_year();  
            count[year - minYear]++;
        }
        
        // 4. Calcular as posições cumulativas
        for (int i = 1; i < range; i++) {
            count[i] += count[i-1];
        }
        
        // 5. Construir o array de saída (ordenado por ano)
        for (int i = n-1; i >= 0; i--) {
            int year = show[ids[i]-1].getRelease_year(); 
            output[count[year - minYear] - 1] = ids[i];
            count[year - minYear]--;
        }
        
        // 6. Agora ordenar os empates (mesmo ano) por título
        int start = 0;
        for (int i = 1; i < n; i++) {
            int currentYear = show[output[i]-1].getRelease_year();  
            int prevYear = show[output[i-1]-1].getRelease_year();  
            
            if (currentYear != prevYear) {
                if (start < i-1) {
                    sortByTitle(output, start, i-1);
                }
                start = i;
            }
        }
        
        // Ordenar o último grupo
        if (start < n-1) {
            sortByTitle(output, start, n-1);
        }
        
        // 7. Copiar de volta para o array original
        System.arraycopy(output, 0, ids, 0, n);
    }

    // Método para ordenar por título (usando insertion sort para pequenos intervalos)
    private static void sortByTitle(int[] array, int start, int end) {
        for (int i = start + 1; i <= end; i++) {
            int key = array[i];
            int j = i - 1;
            
            while (j >= start && compareTitles(array[j], key) > 0) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    // Método para comparar apenas os títulos
    private static int compareTitles(int id1, int id2) {
        Show show1 = show[id1-1];
        Show show2 = show[id2-1];
        return show1.getTitle().toLowerCase()
               .compareTo(show2.getTitle().toLowerCase());
    }
    public static void swap(int i, int j) {
        int temp = ids[i];
        ids[i] = ids[j];
        ids[j] = temp;
    }
}
