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

```bash
getGeneticAlgorithmElite
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
Klasa przyjmuje dwa wymagane argumenty zbiór liczb oraz oraz jeden opcjonalny
Wymagane jest podanie  wektor zbioru liczb oraz punkt startowy (w tym przypadku z getDeterministicBestHillClimbing)
Opcjonalnym jest podanie wielkosci tabu, jesli nie zostanie ona poda petla dziala dopoki nie skoncza sie mozliwosci.
Dodaniem możliwości cofania sprawia, że algorytm znajdzie wszystkie możliwe rozwiązania.

Aby wywołać algorytm należy wywołać metodę:

```bash
getTabuSearch
```

### SimulatedAnnealing

Algorytm symulowanego wyżarzania, klasa przyjmuje 4 wymagane argumenty, wektor zbioru liczb, szukana suma, 
funkcja z temperaturą (która z czasem będzie się zmniejszać) , oraz na końcu ilośc iteracji.

Działanie algorytmu jest praktycznie takie same jak w algorytmie wspinaczkowym getDeterministicRandomHillClimb, 
jedyna róznica jest taka, że w momencie gdy sąsiad nie jest bliżej od poczatkowego losowego rozwiazania, 
wykonuje się warunek który akceptuje gorsze rozwiazanie (podobnie jak tabu) tylko w tym przypadku mamy 
prawdopodobną akceptację gorszego rozwiązania, która jest zależna od temperatury oraz od bierzącego rozwiązania.
Nawiazanie algorytmu do kowola, wytwarzającego miecz, trzeba odpowiednio schłodzić miecz, aby nie pękł.

Wywołanie algorytmu:

```bash
getSimulatedAnnealing
```

### Algorytm genetyczny

Ostatni algorytm z projektu. Algorytm genetyczny przyjmuje 5 argumentów z czego ostatni nie jest wymagany.
4 wymagane argument to wektor zbioru liczb, szukana suma, wielkość populacji oraz ilość iteracji.
Opcjonalnym argumentem jest wybranie metody krzyżowania, jeśli nie zostanie ona podoba wykona się krzyżowanie 
z jedym przedziałem (do wyboru jest jeszcze z dwoma). Do wyboru są dwa wywołania bez elite i z elitą.

bez elity
```bash
getGeneticAlgorithm
```

z elitą
```bash
getGeneticAlgorithmElite
```

W obu przypadkach algorytm działą tak samo, wytwarza pierwsza losową populacje (w zależności od jej podanej wielkości) 
Następnie tworzy ruletkę wyboru osobników do krzyżowania populacji.Im (moim problemie) osobnik jest bliżej szukanej 
sumy ma największe szanse wyboru. Przeprowadziłem skalowanie osobników, dzięki czemu nie zależnie od wielkości liczb,
ustali wartość siły procentową osobnika, która potem doda taką ilość kopi osobnika do ruletki.
Np osobnika uzyskał wynik 19%, to do ruletki zostanie dodane 19 kopii tego osobnika. Należy pamiętać, że osobnik 
może zostać wybrany kilka razy do krzyżowania. Wybieramy osobniki, które zostaną skrzyżowane.

Nastepnie dzieli populacje na pary, i krzyżuje je. Prawdopodobieństwo mutacji jest 1% dla każdego dziecka osobnika. 
Na końcu zastępuje bieżącą populację nową populacją, która jest wynikiem krzyżowania. Po wszystkich powtarzamy proces 
tworzenia ruletki i krzyżowania populacji bazując już na aktualnej populacji (nie tworzymy nowej losowej). 

W przypadku z rozwiązania z elita schemat jest praktycznie taki sam z dwama różnicami. Pierwsze to na początku każdej, 
iteracji, przed krzyżowaniem, wybieramy dwoch najlepszych osobników i dodajemy ich do tabeli najlepszych wyborów.
Następnie dokonujemy krzyżowań, mutacji i na końcu przed zakończeniem iteracji, w nowej populacji usuwamy dwa najsłąbsze 
osobniki i zastępuje je dwoma z elity.

Oba algorytmy zakończą działanie po wykonaniu ilości iteracji lub jeśli w bieżącej populacji znajdzie osobnika którego 
suma zbioru jest równa szukanej sumie.