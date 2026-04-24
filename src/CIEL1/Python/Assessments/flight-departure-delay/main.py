class AirportDepartureDelay:
    def __init__(self, airport, from_year, from_month, flights, total_delay):
        self.airport = airport
        self.from_month = from_month
        self.from_year = from_year
        self.to_month = (self.from_month + 1) % 12
        if self.to_month < self.from_month :
            self.to_year = self.from_year + 1
        else:
            self.to_year = self.from_year

        # Question 1

    def mean_delay(self):
        # Question 1
        return 0
    
    def is_critical(self):
        return self.mean_delay() > 30
    
    def match(self, aiport, year, month):
        return self.airport == aiport and self.from_year == year and self.from_month == month
    
    def __repr__(self):
        # Question 1
        return f'En {self.from_month}/{self.from_year} {self.airport} a opéré {0} vols et cumulé {0} minutes de retard.'

    def __lt__(self, other):
        # Question 4
        return self.mean_delay() < other.mean_delay()

    def __gt__(self, other):
        # Question 4
        return self.mean_delay() > other.mean_delay()

    def __eq__(self, other):
        # Question 4
        return self.mean_delay() == other.mean_delay()

def find_delays_and_departures(delays_and_departures, year, month, airport):
    for dd in delays_and_departures:
        if dd.match(airport, year, month):
            return dd
    return None

def main():
    delays_and_departures = []
    
    # Question 1
     
    delays_and_departures.sort()
    
    # Question 3
    
    input_year = int(input("Saisissez l'année : "))
    input_month = int(input("Saisissez le mois : "))
    input_airport = input("Quel est le code de l'aéroport ? ")
    
    line = find_delays_and_departures(delays_and_departures, input_year, input_month, input_airport)
    
    if line is not None:
        print(line)
    else:
        print(f"Il n'existe aucune données pour {input_airport} en {input_month}/{input_year}")
    
if __name__ == "__main__":
    main()