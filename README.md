# Metaheurystyka - Subset sum problem

Mamy zbior licz calkowitych. Probujemy sprawdzic czy sumujac jakies liczby ze zbiory jestes w stanie uzyskac wynik jaki chcemy.
Przykladowo chcemy uzyskac wynik 0 ze zbioru {-7,-3,-2,9000,5,8}. Zwroci true poniewaz {-3, -2, 5} suma tych liczb da nam 0. Koniec.
I druga strone {-2, -3, 4, 5} i wynik 8. False.


### Subset Sum
Klasa przyjmuje dwa argumentu do konstruktowa (wektor zbioru liczb, oraz szukanej sumy)
Program sam stworzy te argumenty, wystarczy w pliku data w pierwszym wierku podac zbior liczb oddzielonych spacja,
a w drugiej podac szukana sume.

Metody tej klasy to

```bash
getDeterministicBestHillClimb
```

```bash
getDeterministicRandomHillClimb
```

```bash
getTabuSearch
```

```bash
getSimulatedAnnealing
```

```bash
getGeneticAlgorithm
```

### HillClimbing

Klasa ta przyjmuje dwa argumenty w konstruktorze, wektor zbioru liczb, oraz szukana sume.
Posiada dwie publiczne metody:

```bash
getDeterministicRandomHillClimb
```

```bash
getDeterministicBestHillClimb
```

Algorytm w obu przypadkach rozpoczyna dzialanie tak samo.
Generuje wszystkie mozliwe kombinacje (podzbiory) w postacji 0, 1 w zaleznosci od dlugosci wektora zbioru liczb.
Nastepnie wybiera losowy podzbior, tworzy dla niego siasiadow i wykonuje ten schemat
az skonczy sie ilosc iteracji.
Dzialanie jest nastepujece:

##### getDeterministicRandomHillClimb
    
Znajdz pierwszego lepszego siasiad, zakoncz szukanie, wygeneruj nowych siasiodow dla nowo znalezionego zbioru,
i znowu znajdz pierwszego lepszego.

##### getDeterministicBestHillClimb

Z kolei "best" przeleci wszystkich siasiadow, znajdzie najlepszego, i tak samo jak w przypadku "random" powtarza proces.


### TabuSearch

Przed powstaniem klasy, wykonywany jest HillClimbing -> getDeterministicBestHillClimbing, 
aby dodac pierwsze rozwiazanie do listy tabu.
Klasa przyjmuje dwa wymagane argumenty oraz jeden opcjonalny
Wymagane jest podanie  wektor zbioru liczb oraz punkt startowy (w tym przypadku z getDeterministicBestHillClimbing)
Opcjonalnym jest podanie wielkosci tabu, jesli nie zostanie ona poda petla dziala dopoki nie skoncza sie mozliwosci
