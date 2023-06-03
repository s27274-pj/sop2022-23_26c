#!/usr/bin/env bash

# Przygotuj funkcję obliczającą rekurencyjnie ciąg Fibonacciego.
# Niech wynik zwraca za pomocą return. Czy są jakieś ograniczenia?

# Funkcja zwracająca n-ty wyraz ciągu Fibonacciego w statusie.
function fib {
  # Dla przypadków trywialnych zwracamy wartość stałą
  if [[ $1 == 1 ]]
  then
    return 0
  elif [[ $1 == 2 ]]
  then
    return 1
  fi

  # Dla wszystkich innych wyciągamy który wyraz chcemy obliczyć
  N=$1
  # Odejmujemy 1 żeby dostać poprzedni wyraz
  A=$((N - 1))
  # Wykonujemy naszą funkcję rekurencyjną i zapisujemy jej status w zmiennej
  A=$(fib $A; echo $?)
  # I to samo robimy dla jeszcze poprzedniego elementu
  B=$((N - 2))
  B=$(fib $B; echo $?)
  # Na koniec zwracamy ich sumę jako status funkcji
  return $((A + B))
}

# Jako przykład wybrałem wyraz 14. Dlaczego 14?
# Ponieważ jest to najwyższy wyraz tego ciągu,
# który może być poprawnie reprezentowany przez status.
fib 14
echo $? # 233

# Dlaczego wyraz 15 nie może być poprawnie zwrócony?
# Ponieważ Linux na status procesu przeznacza jeden bajt.
# Oznacza to, że nie ważne jaką wartość zwrócimy z funkcji,
# tak naprawdę to co zwracamy będzie N modulo 256.
#
# Czy można byłoby to obejść? Pewnie by można było,
# jeśli bylibyśmy gotowi zwracać wartość nie *tylko* w statusie, 
# ale także w zmiennej środowiskowej np. ile razy już doszliśmy do granicy 255.
# Ale jeśli już tak daleko chcemy zajść, to moim skromnym zdaniem nie ma sensu,
# już pomijając fakt, że status funkcji/procesu nie służy do zwracania danych,
# a jedynie komunikatów o błędach.
