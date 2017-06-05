// Klaudia C - 14.12.2016

import static java.lang.Integer.max;
import java.util.Scanner;
import java.util.Locale;

public class Source{
    static int N;  // liczba slow
    static int[] x; // liczby wyszukiwan dla konkretnego slowa
    static int[] y; // liczby wyszukiwan dla zestawu slow
    static String[] words;
    static long[][] c; // tablica kosztow drzewa 
    static int[][] w; // sumy czastkowe x i y
    static int[][] r; // korzen poddrzewa
    
    static void print(int i, int j, int d){
        if(i == j) // jestesmy w lisciu
            return;
        int k = r[i][j]; // punkt podzialu (korzen)
        print(i, k - 1, d + 2);
        for(int p = 0; p < d; p++)
            System.out.print(".");
        System.out.println(words[k]);
        print(k, j, d + 2);
    }
    
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        
        int Z = scan.nextInt();
        scan.nextLine();
        for(int z = 0; z < Z; z++){
            String data = scan.nextLine();
            String splitData[] = data.split("[^0-9]+");
            N = Integer.parseInt(splitData[1]);
            x = new int[N + 1];
            y = new int[N + 1];
            words = new String[N + 1];
            y[0] = Integer.parseInt(splitData[2]); // liczba wyszukiwan
            for(int n = 1; n <= N; n++){ // bo indeksujemy od 1
                data = scan.nextLine();
                String names[] = data.split("[^a-zA-Z]+");
                String numbers[] = data.split("[^0-9]+");
                
                if(names[0].length() == 0)
                    words[n] = names[1];
                else
                    words[n] = names[0];
                x[n] = Integer.parseInt(numbers[1]);
                y[n] = Integer.parseInt(numbers[2]);
            }
            
            c = new long[N + 1][N + 1];
            w = new int[N + 1][N + 1];
            r = new int[N + 1][N + 1];
            for(int n = 0; n <= N; n++){
                c[n][n] = 0; // jednoelementowe drzewa
                w[n][n] = y[n];
                r[n][n] = n;
            }
            for(int d = 1; d <= N; d++){ // sprawdzanie zakresow o okreslonej dlugosci
                for(int i = 0, j = d; j <= N; i++, j++){ // przejscie na zakresie i, j
                    w[i][j] = w[i][j - 1] + x[j] + y[j]; // dolozenie wartosci z poddrzewa
                    
                    int mink; // indeks optymalnego korzenia
                    long minc = 1000000000000L; // optymalny koszt
                    for(int k = mink = max(r[i][j - 1], i + 1); k <= r[i + 1][j]; k++){
                        if(minc > c[i][k - 1] + c[k][j]){ // jesli znaleziono bardziej optymalny korzen
                            minc = c[i][k - 1] + c[k][j];
                            mink = k;
                        }                        
                    }
                    r[i][j] = mink;
                    c[i][j] = minc + w[i][j];
                }
            }
            print(0, N, 1);
            double D = ((double)c[0][N])/w[0][N];
            System.out.format(Locale.ENGLISH,"%.4f%n", D);
        }
    }
}
