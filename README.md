##  Textbaserat Minröj (Minesweeper) i C++

# Syfte:
Denna uppgift syftar till att testa vår förståelse för Objektorienterad Programmering (OOP) i C++, särskilt principerna om Inkapsling och Komposition, samt modern Minneshantering med RAII (Resource Acquisition Is Initialization) och Smart Pointers.

# Programmets struktur och klassrelationner är uppbyggt av tre huvudklasser med tydliga ansvarsområden:
- Cell: Den minsta enheten. Kapslar in tillståndet för en enskild ruta (har mina, är avslöjad, är flaggad, antal angränsande minor).
- MinesweeperBoard: Hanterar spelplanens logik, placering av minor och uppdatering av rutor.
- Game: Styr spelets flöde, hanterar användarinmatning (avslöja/flagga/avsluta) och uppdaterar spelets status (Pågår, Vinst, Förlust, Avslutad).

# Istället för arv bygger programmet på Komposition:
- MinesweeperBoard består av (std::vector<std::vector<Cell>>) en samling av Cell-objekt.
- Game-objektet innehåller ett pekarreferens till ett MinesweeperBoard-objekt.

# Minneshantering (RAII)
Programmet använder moderna C++-metoder för att säkerställa att allokerat minne frigörs automatiskt (RAII).

MinesweeperBoar:
- Skapas på Heap-minnet inuti Game-konstruktorn.
- Game-klassen använder en std::unique_ptr<MinesweeperBoard> (board_ptr_) som unikt äger MinesweeperBoard-objektet.

Cell-objekt:
- Lagras inuti en std::vector i MinesweeperBoard-klassen.
- Vektorn skapas på Heapen, men dess destruktor hanterar automatiskt frigörandet av alla Cell-objekt som den innehåller.

När programmet avslutas tas Game-objektet bort. Dess destruktor anropas, vilket i sin tur utlöser destruktorn för std::unique_ptr, som automatiskt frigör minnet för MinesweeperBoard-objektet. Detta säkerställer att inget minne läcks.

