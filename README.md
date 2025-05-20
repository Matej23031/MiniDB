# MiniDB

MiniDB je jednostavna, ali robusna **dretveno-sigurna memorijska baza ključ-vrijednost** implementirana u C++-u, uz **REST API sloj** u Node.js-u. Projekt služi kao demonstracija end‑to‑end rješenja za prijavu na poziciju Database Engineering Intern u startupu Farseer.

## Tehnologije

* **C++17**: jezgra baze podataka, `Database` klasa
* **std::unordered\_map**: internetsko spremište parova ključ-vrijednost
* **std::shared\_mutex** + **std::unique\_lock**/**std::shared\_lock**: dretvena sigurnost
* **Node.js** + **Express**: REST API
* **helmet**, **morgan**: sigurnosni i logging middleware
* **Catch2**: jedinično testiranje C++ dijela
* **make**: automatizacija izgradnje (build)

## Struktura direktorija

```
MiniDB/
├── cpp/
│   ├── database.hpp        # Definicija Database klase
│   ├── database.cpp        # Implementacija metoda
│   └── main.cpp            # API‑kompatibilna C++ binarka
├── node/
│   └── server.js           # REST API sloj na hrvatskom
├── benchmarks/
│   ├── benchmark.cpp       # Benchmark mjerenje brzine umetanja
│   └── stress_test.cpp     # Paralelno testiranje s dretvama
├── tests/
│   └── test_database.cpp   # Jedinični testovi za C++ (Catch2)
├── Makefile                # Pravila za `make`, `make test`, `make benchmark`, `make stress`
└── README.md               # Ovaj dokument
```

## Instalacija i izgradnja

1. Klonirajte repozitorij:

   ```bash
   git clone https://github.com/korisnik/MiniDB.git
   cd MiniDB
   ```
2. Izgradite C++ binarke i testove:

   ```bash
   make
   make test
   ```
3. Instalirajte Node.js dependencije:

   ```bash
   cd node
   npm install
   ```

## Pokretanje

### C++ API binarka

U root direktoriju:

```bash
./main <command> <key> [value]
```

Primjeri:

```bash
./main insert ime Matej
./main get ime
./main update ime Ivan
./main delete ime
```

### REST API (Node.js)

1. U rootu provjerite da je `main` binarka prisutna.
2. Pokrenite server:

   ```bash
   cd node
   node server.js
   ```
3. API će slušati na `http://localhost:3000`.

### Primjeri `curl`

* **Insert**:

  ```bash
  curl -X POST http://localhost:3000/data \
    -H "Content-Type: application/json" \
    -d '{"key":"ime","value":"Matej"}'
  ```
* **Get**:

  ```bash
  curl http://localhost:3000/data/ime
  ```
* **Update**:

  ```bash
  curl -X PUT http://localhost:3000/data/ime \
    -H "Content-Type: application/json" \
    -d '{"value":"Ivan"}'
  ```
* **Delete**:

  ```bash
  curl -X DELETE http://localhost:3000/data/ime
  ```

## Testiranje

* **Jedinični testovi (Catch2)**:

  ```bash
  make test
  ```
* **Benchmark**:

  ```bash
  make benchmark
  ./benchmark [<N>]
  ```
* **Stress test**:

  ```bash
  make stress
  ./stress_test [<threads>] [<total>]
  ```

## Daljnji razvoj

* Dodavanje persistencije (fajl ili baza)
* Naprednije validacije ključeva/vrijednosti
* Autentikacija i autorizacija API‑ja
* Integracija s Dockerom i CI/CD pipeline

---

Matej Čiček | 2025.05.20
