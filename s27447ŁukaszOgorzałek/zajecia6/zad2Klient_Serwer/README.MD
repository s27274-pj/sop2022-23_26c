# Klient-Serwer Transfer Plików


## Serwer

Program serwera działa w następujący sposób:

1. Tworzy gniazdo i przypisuje je do określonego portu.
2. Rozpoczyna nasłuchiwanie przychodzących połączeń klientów.
3. Akceptuje połączenia klientów i obsługuje je w osobnych procesach.
4. Zapisuje logi dotyczące połączeń klientów do pliku, w tym adresu IP klienta i portu.
5. Odbiera od klienta żądaną nazwę pliku.
6. Wysyła klientowi rozmiar pliku. Jeśli plik nie istnieje, wysyła rozmiar pliku równy -1.
7. Wysyła dane pliku do klienta w paczkach.
8. Zamyka połączenie z klientem.

## Klient

Program klienta działa w następujący sposób:

1. Tworzy gniazdo i łączy się z adresem IP i portem serwera.
2. Prosi użytkownika o wpisanie nazwy pliku do pobrania.
3. Wysyła do serwera długość nazwy pliku i samą nazwę pliku.
4. Odbiera od serwera rozmiar pliku. Jeśli plik nie istnieje na serwerze, rozmiar pliku będzie równy -1.
5. Jeśli plik istnieje, pobiera dane pliku w paczkach i zapisuje je do lokalnego pliku.
6. Zamyka połączenie z serwerem.
