import pytest

import requests

@pytest.fixture(scope='class')
def session():
    session = requests.Session()
    session.delete('http://localhost:5000/api/clear_db')
    yield session
    session.close()

@pytest.fixture(scope='class')
def session_with_countries(session):
    countries = [{'nume': 'Romania',
                  "lat": 123.45,
                  "lon": 1.0},
                 {'nume': 'France',
                  "lat": 123.45,
                  "lon": 1.0}]
    country_ids = [i + 1 for i in range(len(countries))]

    for country, country_id in zip(countries, country_ids):
        session.post('http://localhost:5000/api/countries', json=country)


    yield session, countries

@pytest.fixture(scope='class')
def session_with_cities(session_with_countries):
    session, countries = session_with_countries
    cities = [{'nume': 'Bucuresti',
               'lat': 123.45,
               'lon': 1.0,
               'idTara': 1},
              {'nume': 'Cluj',
               'lat': 123.45,
               'lon': 1.0,
               'idTara': 1},
              {'nume': 'Iasi',
               'lat': 123.45,
               'lon': 1.0,
               'idTara': 1},
              {'nume': 'Paris',
               'lat': 123.45,
               'lon': 1.0,
               'idTara': 2},
              {'nume': 'Lyon',
               'lat': 420.0,
               'lon': 2000.0,
               'idTara': 2}]

    for city in cities:
        session.post('http://localhost:5000/api/cities', json=city)

    yield session, countries, cities

@pytest.fixture(scope='class')
def session_with_temps(session_with_cities):
    session, countries, cities = session_with_cities
    temps = [{'idOras': 1,
              'valoare': 25.0},
             {'idOras': 1,
              'valoare': 26.0},
             {'idOras': 1,
              'valoare': 27.0},
             {'idOras': 4,
              'valoare': 25.0},
             {'idOras': 5,
              'valoare': 22.0}]

    for temp in temps:
        session.post('http://localhost:5000/api/temperatures', json=temp)


    yield session, countries, cities, temps
