#!/bin/bash
function coto {
    imie="^[A-Z][a-zęóąśłć]*$"
    kodpocztowy="^[0-9]{2}-[0-9]{3}$"
    mail="^[a-zA-Z0-9._-]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,}$"
    if [[ $1 =~ $imie ]]
        then echo "Jest to imie"
    elif [[ $1 =~ $kodpocztowy ]]
        then echo "Jest to kod pocztowy"
    elif [[ $1 =~ $mail ]]
        then echo "Jest to mail"
    else
        echo "Podany ciag nie jest Imieniem/KodemPocztowym/Mailem"
    fi          
}

coto polskagurom@gmail.com