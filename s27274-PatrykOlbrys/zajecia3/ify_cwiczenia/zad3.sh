#!/bin/bash

# Pierwszy sposób
# Porównanie trzech ostatnich liter nazwy skryptu

script_name=${0##*/}
script_name_len=${#script_name}
three_last_chrs_of_script_name=${script_name:$script_name_len-3}

if [[ $three_last_chrs_of_script_name == ".sh" ]]; then
  echo "Moja nazwa kończy się na .sh"
else
    new_script_name=$script_name.sh
    mv $script_name $new_script_name
fi

# Drugi sposób
# Dopasowanie do wyrażenia regularnego

script_name=${0##*/}
pattern="*.sh"

if [[ $script_name == $pattern ]]; then
  echo "Moja nazwa kończy się na .sh"
else
    new_script_name=$script_name.sh
    mv $script_name $new_script_name
fi

# Trzeci sposób
# Użycie wbudowanego mechanizmu do wyciągania części napisów w bashu

script_name=${0##*/}

if [[ ${script_name##*.} == "sh" ]]; then
  echo "Moja nazwa kończy się na .sh"
else
    new_script_name=$script_name.sh
    mv $script_name $new_script_name
fi
