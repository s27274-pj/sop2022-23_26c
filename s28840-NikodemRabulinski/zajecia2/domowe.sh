#!/bin/sh
# ^^^^^^^ Używam sh ponieważ nie ma w tym skrypcie żadnych bashyzmów, więc jest on bardziej przenośny

# Zadanie:
# Przygotuj skrypt, który odczyta plik (jego nazwa ma być argumentem skryptu) i wypisze go na terminalu tak,
# aby wszystkie wystąpienia Twojego imienia były podświetlone na czerwono.

# Rozwiązanie:

# Używam narzędzia sed, gdyż jest ono mi najbardziej znane i uznałem użycie go do tego celu za najprostsze
sed \
  's,\(nikodem\),\x1b[31m\1\x1b[0m,gi' \
  $1 # I na koniec podajemy ścieżkę do pliku jako argument, tak jak to mówiła treść polecenia.

# Wyjaśnienie skryptu sed:
# Najpierw mamy komendę, którą sed ma wykonać. Tutaj używam 's' od substitute, czyli podmień.
# Następnie separator. Najczęściej jest to '/', lecz może być to praktycznie dowolny znak.
# Ja dla czytelności używam w tym wypadku ','.
# Później mamy regex zaznaczający fragment do zastąpienia. Ja chcę podmienić wszystkie wystąpienia mojego imienia,
# ale też zaznaczyć je w grupę, więc użyłem \(nikodem\)
# Następnie jest na co ma zostać ten tekst podmieniony.
# Jako iż chcemy zaznaczyć każde wystąpienie mojego imienia na czerwono,
# zamieniam te fragmenty na:
#     '\x1b[31m' - w ten sposób rozpoczynamy kolorowanie tekstu na czerwono.
#     GNU sed używa \x do znaków w formie heksadecymalnej
#     '\1' - Wstawiamy moje imię, o tym za chwilę
#     '\x1b[0m' - Resetujemy formatowanie tesktu.
# Na koniec podajemy flagi, które wyjaśniają dlaczego użyłem grupowania i \1 do pokolorowania swojego imienia.
# Są to:
# 'g' - global, czyli że podmienianie ma się wykonywać wiele razy w jednej linii, a nie maksymalnie raz
# 'i' - case-'i'nsensitive - wielkość liter nie ma znaczenia. Dlatego użyłem grupowania i referencji do grupy,
# żeby przypadki jak NiKoDeM, albo Nikodem, albo niKOdem też zostały pokolorowane BEZ zmiany wielkości liter.
