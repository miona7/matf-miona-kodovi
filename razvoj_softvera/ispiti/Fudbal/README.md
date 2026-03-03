# Qt Simulator Takmičenja 🎯

---

## ⚠️ Napomena

Nemam originalnu kompletnu postavku zadatka. Implementacija predstavlja približno rešenje traženog zadatka.

---

## 📌 Opis zadatka

Aplikacija simulira takmičenje između više učesnika koji se učitavaju iz JSON fajla.

Svaki takmičar:

* Ima ime
* Ima opcioni klub (ako nije naveden postavlja se na `"amater"`)
* Ima preciznost (verovatnoću pogotka)
* Sakuplja bodove tokom jedne runde

---

## ⚙️ Logika rada

### Pokretanje meča

* Meč se može pokrenuti samo ako postoje najmanje dva takmičara
* Svaki takmičar se izvršava u posebnoj niti (`QThread`)
* Broj pokušaja u rundi definiše se pomoću `QSpinBox` komponente

  * Opseg: 1–10
  * Podrazumevana vrednost: 5

### Tok runde

* Svaka nit izvršava zadati broj pokušaja
* Pogodak se određuje na osnovu preciznosti takmičara
* Nakon svakog pokušaja, nit emituje signal ka glavnoj niti
* Glavna nit ažurira GUI i ispisuje pogodak ili promašaj

---

## 📊 Završetak runde

Kada se sve niti završe:

* Računa se medijana bodova
* Takmičari sa bodovima manjim od medijane se eliminišu
* Eliminisani se prikazuju u posebnoj listi
* Preostalim takmičarima se bodovi resetuju

Proces se ponavlja dok ne ostane samo jedan takmičar.

Kada ostane jedan učesnik, aplikacija prikazuje poruku sa pobednikom.

---

## 🛠 Tehničke karakteristike

* Qt GUI (`QListWidget`, `QPushButton`, `QSpinBox`)
* Rad sa `QThread` klasom
* Signal–slot komunikacija između niti i glavne niti
* Parsiranje JSON fajlova
* Osnovni principi konkurentnog programiranja

