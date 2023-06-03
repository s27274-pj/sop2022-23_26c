#!/usr/bin/env bash

# Napisz skrypt, który:
# sprawdzi, czy jego nazwa kończy się .sh .
# Jeśli nie, to niech zmieni swoją nazwę poprzez dopisanie tego rozszerzenia (rozszerzenie nazwy pliku).
# Sprawdzenie można zrobić na kilka sposobów, polecam przetestować 3 typowe:
# dopasowanie do wyrażenia regularnego (to jest bardziej uniwersalny sposób)
# porównanie ostatnich 3 liter nazwy skryptu
# użyć wbudowanego w basha mechanizmu do wyciągania części napisów ${%}, ${%%}, ${#}, ${##} 

# Przy użyciu wyrażenia regularnego sprawdzam czy argument zerowy kończy się na .sh
if [[ ! "$0" =~ \.sh$ ]]; then
  # Jeśli nie to przenoszę się w to samo miejsce, jedynie z dodaną końcówką .sh
  mv "$0" "${0}.sh"
fi
# Nie widziałem powodu aby używać wyciągania części napisów czy innych mechanizmów do manipulacji zmiennych