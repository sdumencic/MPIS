# MPIS

Projekt za kolegij Modeliranje procesnih informacijskih sustava - programska podrška za upravljanje postrojenjem trafostanice

## Sadržaj
- [MPIS](#mpis)
  - [Sadržaj](#sadržaj)
  - [Uvod](#uvod)
  - [Izgled programske podrške](#izgled-programske-podrške)
  - [UML dijagram](#uml-dijagram)
    - [Dalekovodno polje](#dalekovodno-polje)
    - [Prekidač](#prekidač)
    - [APU](#apu)
    - [Zaštita](#zaštita)
    - [Rastavljači](#rastavljači)
  - [Rad postrojenja](#rad-postrojenja)
    - [Uključenje](#uključenje)
    - [Isključenje](#isključenje)

## Uvod
Zadatak je izraditi programsku podršku prema uputama dobivenim u zadatku 4.
Za izradu ovog zadatka, odlučili smo se za programski jezik C++. IDE (Integrated Development Environment) koji
smo koristili je Qt Creator radi jednostavnog upravljanja grafičkim sučeljem.

## Izgled programske podrške
Programska podrška se sastoji od klasi koje predstavljaju plan prema kojem se rade elementi koje sadrži
dalekovodno polje. Elementi koji se nalaze u DV su objekti, dakle instance klasa te prema principu
nasljeđivanja, nasljeđuju varijable i metode koje se nalaze u njihovim klasama.

## UML dijagram
<img src="https://i.ibb.co/BjHRv8p/dijagram.png" alt="dijagram">

### Dalekovodno polje
Klasa dalekovodno polje služi za prikaz dalekovodnih polja koje smo dobili zadane još u prvom zadatku,
DV-B i DV-C.

### Prekidač
Klasa prekidač služi za uključivanje i isključivanje dalekovodnog polja. Prekidač utječe na elemente ostatka
polja. Da bi se uključilo prekidač, ostali elementi (sabirnički rastavljač, linijski rastavljač) u polju moraju
biti uključeni.

### APU
Klasa APU (automatski ponovni uklop) služi za ponovno uključenje postrojenja u slučaju da dođe do
prestanka rada. Ukoliko dođe do prestanka, zadatak APU-a je ponovno pokušati uključiti prekidač da bi
polje proradilo.

### Zaštita
Klasa zaštita služi za zaštitu postrojenje ili radnika u slučaju da dođe do izboja ili kvara postrojenja.
Prilikom prorade zaštite, prekidač se isključuje i polja prestaju s radom. S obzirom na dijagram slijeda koji
smo izradili u prošlom zadatku u kojem piše da za uključenje polja zaštita treba biti isključena, ako je
uključena, prekidač se neće moći uključiti.

###  Rastavljači
Klasa rastavljač je klasa iz koje vrste rastavljača nasljeđuju svoje atribute i metode. Postoje 3 vrste
rastavljača, a to su: sabirnički rastavljač, linijski rastavljač i rastavljač uzemljenja. Uloga rastavljača je
odvajanje dijela postrojenja pod naponom od onog koji nije pod naponom.

## Rad postrojenja
Rad postrojenja odvija se prema zadatku u kojem smo radili dijagram slijeda. Iz tog zadatka jasno je da na
početku treba provjeriti je li zaštita isključena kako bismo mogli uključiti dalekovodno polje. Tj. trebalo bi
sanirati razlog uključenja zaštite kako bi se nakon toga na siguran način moglo uključiti dalekovodno polje.
Isto tako, prema zadatku u kojem smo izradili dijagram slijeda, piše da je za upravljanje potrebno daljinsko
upravljanje. Ako je lokalno, elementima se može upravljati jedino fizički.

### Uključenje
Uključenje postrojenja se odvija u nekoliko koraka. Za početak se isključuje rastavljač uzemljenja da bi se
polje uzemljilo. Uključenje elemenata se odvija paralelno u prvom i drugom postrojenju, dakle, prvo se
uključuju sabirnički rastavljači u oba postrojenja. Zatim se uključuje linijski rastavljač oba postrojenja te
se na kraju može uključiti i prekidače oba postrojenja. APU možemo uključiti za automatsko ponovno
pokretanje.

### Isključenje
Isključenje dalekovodnog polja se odvija suprotnim redoslijedom od uključenja. Dakle, potrebno je prvo
isključiti prekidače, a zatim linijske rastavljače i sabirničke rastavljače. Na kraju se uključuje rastavljač
uzemljenja.



<img src="https://i.ibb.co/yNQytFc/mpis2.png" alt="mpis2">
<img src="https://i.ibb.co/nwvbNy7/Screenshot-2020-12-28-MPIS-1920-zadatak4-grupa2-pdf.png" alt="Screenshot-2020-12-28-MPIS-1920-zadatak4-grupa2-pdf">
