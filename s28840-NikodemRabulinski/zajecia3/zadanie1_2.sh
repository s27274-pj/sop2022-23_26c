#!/usr/bin/env bash

# Napisz skrypt, który:
# - sprawdzi, czy istnieje plik config.cfg w bieżącym katalogu.
# - Jeśli taki plik istnieje, to niech go wykona.
# - Jeśli nie istnieje, to niech sprawdzi, czy podano argument i wykona plik o nazwie takiej jak wartość argumentu (parametru) skryptu.
# - Jeśli żadne z powyższych nie nastąpiło, to niech wyświetli komunikat o błędzie.

# UWAGA: We wszystkich zadaniach zakładam, że przez "bieżący katalog" mamy na myśli katalog z którego jest wykonywany skrypt,
# a nie katalog, w którym skrypt się znajduje.

# Najpierw sprawdzam czy taki plik istnieje w bieżącym katalogu
if [[ -a config.cfg ]]; then
  # I jeśli tak to próbuję go wykonać
  ./config.cfg
# W przeciwnym razie wykorzystuję polecenie `which`, które wykona się poprawnie *jedynie* kiedy podany argument istnieje i jest wykonywalny
# tj. jeśli jest to ścieżka to sprawdzi czy dany plik jest wykonywalny, a jeśli to nazwa programu to sprawdzi czy jest on w PATH
elif which "$1" >/dev/null 2>&1; then
  "$1"
# I oczywiście jeśli żadna z tych opcji nie zadziała, wyświetlam komunikat o błędzie
else
  echo "config.cfg nie istnieje ani podany argument nie jest wykonywalny"
  exit 1
fi
