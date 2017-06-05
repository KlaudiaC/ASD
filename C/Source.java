// Klaudia C - 30.11.2016

import static java.lang.Math.min;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;

public class Source{
    static int ccCounter; // wartosc spojnej skladowej
    static int[] tIn; // lista czasow wejscia
    static int tCounter; // czas wejscia
    static int[] low; // lista sciezek wstecznych
    static int[][] graph;
    static int d; // rozmiar grafu
    static ArrayList<ArrayList<Integer>> ccList; // lista spojnych skladowych
    static ArrayList cc; // zbior spojnych skladowych
    static ArrayList<ArrayList<Integer>> dccList; // lista dwospojnych skladowych
    static ArrayList<ArrayList<Integer>> bList; // lista mostow
    static ArrayList<Integer> apList; // lista puntow artykulacji
    static int[] stack; // stos wierzcholkow
    static int top;
    
    public static void dfs(int v, int p){ // wierzcholek i jego rodzic
        tIn[v] = ++tCounter;
        low[v] = tIn[v];  // low nie moze byc wiekszy
        cc.add(v); // dokladamy wierzcholek danej spojnej skladowej
        stack[top++] = v;
        
        int childCount = 0;
        boolean isAp = false; // czy jest to wierzcholek rozdzielajacy
        
        for(int i = 0; i < graph[v].length; i++){ // przeglad listy sasiedztwa
            int w = graph[v][i]; // sprawdzane dziecko
            
            if(w == p) // pominiecie ojca, bo tam juz bylismy
                continue;
            if(tIn[w] == 0){
                childCount++; // liczba dzieci = liczba wywolan dfs
                dfs(w, v); // zejscie nizej
                low[v] = min(low[v], low[w]);
                
                if(low[w] >= tIn[v]){ // sprawdzenie, czy nastapilo wyjscie z dwuspojnej skladowej
                    ArrayList dcc = new ArrayList(); // pojedyncza podwojna skladowa
                    isAp = true; // ojciec to punkt artykulacji
                    
                    int x;
                    do{ // ustalanie dwuspojnych skladowych
                        x = stack[--top];
                        dcc.add(x + 1);
                    }while(x != w);
                    dcc.add(v + 1);
                    Collections.sort(dcc);
                    if(dcc.size() == 2) // sprawdzenie, czy jest ona mostem
                        bList.add(dcc);
                    else
                        dccList.add(dcc);
                }
            }
            else
                low[v] = min(low[v], tIn[w]);
        }
        if(p == -1 && childCount <= 1) // jestesmy w korzeniu z najwyzej jednym dzieckiem
            isAp = false;
        if(isAp)
            apList.add(v);
    }
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        
        for(int i = 0; i < n; i++){ // petla zestawow
            ccList = new ArrayList();
            dccList = new ArrayList();
            bList = new ArrayList();
            apList = new ArrayList();
            tCounter = 0;
            ccCounter = 0;
            top = 0;
            int s = scan.nextInt();
            tIn = new int[s];
            low = new int[s];
            graph = new int[s][];
            stack = new int[s];
            
            for(int j = 0; j < s; j++){ // petla grafu
                d = scan.nextInt();
                graph[j] = new int[d];
                
                for(int k = 0; k < d; k++){ // petla listy wierzcholkow
                    int x = scan.nextInt();
                    graph[j][k] = x - 1; // -1, bo indeksowanie jest od zera
                }
            }
        
            for(int j = 0; j < s; j++){
                if(tIn[j] != 0) // jak niezerowy, to znaczy ze tu bylismy
                    continue;
                cc = new ArrayList();
                ccList.add(cc);
                ccCounter++;
                dfs(j, -1); // -1, bo nie ma ojca na poczatku
                Collections.sort(cc);
            }

            System.out.print(ccList.size() +":");  // wypisanie spojnych skladowych
            if(ccList.size() > 0){
                for(int j = 0; j < ccList.size(); j++){
                    for(int k = 0; k < ccList.get(j).size() - 1; k++)
                        System.out.print((int)ccList.get(j).get(k) + 1 +",");
                    System.out.print((int)ccList.get(j).get(ccList.get(j).size() - 1) + 1 +";");
                }
            }
            System.out.println();
                
            Collections.sort(dccList, new Comparator<ArrayList<Integer>>(){
                public int compare(ArrayList<Integer> o1, ArrayList<Integer> o2){
                        return o1.get(0).compareTo(o2.get(0));
                    }
                }
            );
            System.out.print(dccList.size() +":"); // wypisanie dwuspojnych skladowych
            if(dccList.size() > 0){
                for(int j = 0; j < dccList.size(); j++){
                    for(int k = 0; k < dccList.get(j).size() - 1; k++)
                        System.out.print(dccList.get(j).get(k) +",");
                    System.out.print(dccList.get(j).get(dccList.get(j).size() - 1) + ";");
                }
            }
            System.out.println();
            
            Collections.sort(bList, new Comparator<ArrayList<Integer>>(){
                public int compare(ArrayList<Integer> o1, ArrayList<Integer> o2){
                    int result = 0;
                    for(int i = 0; i <= o1.size() - 1 && result == 0; i++)
                        result = o1.get(i).compareTo(o2.get(i));
                    return result;
                }
            });
            System.out.print(bList.size() +":"); // wypisanie mostow
            if(bList.size() > 0){
                for(int j = 0; j < bList.size(); j++)
                    System.out.print(bList.get(j).get(0) +"-" +bList.get(j).get(1) +";");
            }
            System.out.println();
            
            Collections.sort(apList, new Comparator<Integer>(){
                public int compare(Integer o1, Integer o2){
                        return o1.compareTo(o2);
                    }
                }
            );
            System.out.print(apList.size() +":"); // wypisanie wierzcholkow rozdzielajacych
            if(apList.size() > 0){
                for(int j = 0; j < apList.size(); j++)
                    System.out.print((apList.get(j) + 1) +";");
            }
            System.out.println();
        }
    }
}
