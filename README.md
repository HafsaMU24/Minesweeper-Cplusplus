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

