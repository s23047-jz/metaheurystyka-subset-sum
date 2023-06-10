# Metaheurystyka - Subset sum problem

Mamy zbior licz calkowitych. Probujemy sprawdzic czy sumujac jakies liczby ze zbiory jestes w stanie uzyskac wynik jaki chcemy.
Przykladowo chcemy uzyskac wynik 0 ze zbioru {-7,-3,-2,9000,5,8}. Zwroci true poniewaz {-3, -2, 5} suma tych liczb da nam 0. Koniec.
I druga strone {-2, -3, 4, 5} i wynik 8. False.


### Subset Sum
Klasa przyjmuje dwa argumentu do konstruktowa (wektor zbioru liczb, oraz szukanej sumy)
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

Klasa ta obejmuje dwie publiczne metody

```bash
getDeterministicRandomHillClimb
```

```bash
getDeterministicBestHillClimb
```

