import pytest
import datetime

URL = 'http://127.0.0.1:5000'

@pytest.mark.incremental
class TestAddCountryRoute:
    def test_add_country(self, session):
        response = session.post(f'{URL}/api/countries',
                               json={'nume': 'Romania',
                                     "lat": 123.45,
                                     "lon": 1.0})
        assert response.status_code == 201
        assert response.json() == {'id': 1}

    def test_add_country_invalid(self, session):
        response = session.post(f'{URL}/api/countries',
                               json={'nume': 'Mongolia',
                                     "lat": 123.45})
        assert response.status_code == 400

    def test_add_country_invalid2(self, session):
        response = session.post(f'{URL}/api/countries',
                               json={"nume": "Mongolia",
                                     "lat": 123.45,
                                     "lon": "absolutely not a double"})
        assert response.status_code == 400

    def test_add_country_invalid3(self, session):
        response = session.post(f'{URL}/api/countries')
        assert response.status_code == 400

    def test_add_country_duplicate(self, session):
        response = session.post(f'{URL}/api/countries',
                               json={'nume': 'Romania',
                                     "lat": 1.0,
                                     "lon": 1.0})
        assert response.status_code == 409

    def test_add_second_country(self, session):
        response = session.post(f'{URL}/api/countries',
                               json={'nume': 'Mongolia',
                                     "lat": 1.0,
                                     "lon": 1.0})
        assert response.status_code == 201
        assert response.json() == {'id': 2}

@pytest.mark.incremental
class TestGetCountryRoute:
    def test_get_countries(self, session_with_countries):
        s, self.countries = session_with_countries

        response = s.get(f'{URL}/api/countries')
        assert response.status_code == 200

        for i in range(len(self.countries)):
            self.countries[i]['id'] = i + 1
            assert self.countries[i] in response.json()

class TestUpdateCountryRoute:
    NEW_ROMANIA = {'id': 1,
                   'nume': 'Romania',
                   'lat': 1.0,
                   'lon': 1.0}

    def test_update_country(self, session_with_countries):
        s, _ = session_with_countries
        response = s.put(f'{URL}/api/countries/1',
                               json=self.NEW_ROMANIA)
        assert response.status_code == 200

        response = s.get(f'{URL}/api/countries')
        assert response.status_code == 200
        print(response.json())
        assert self.NEW_ROMANIA in response.json()

    def test_update_country_invalid(self, session_with_countries):
        s, _ = session_with_countries
        response = s.put(f'{URL}/api/countries/1',
                              json={'nume': 'Romania',
                                    "lat": 1.0})
        assert response.status_code == 400

    def test_update_country_invalid2(self, session_with_countries):
        s, _ = session_with_countries
        response = s.put(f'{URL}/api/countries/1',
                              json={'id': 1234,
                                    'nume': 'Romania',
                                    'lat': 1.0,
                                    'lon': 'absolutely not a double'})
        assert response.status_code == 400

    def test_update_country_invalid3(self, session_with_countries):
        s, _ = session_with_countries
        response = s.put(f'{URL}/api/countries/1')
        assert response.status_code == 400

    def test_update_country_not_found(self, session_with_countries):
        s, _ = session_with_countries
        response = s.put(f'{URL}/api/countries/100',
                              json={'id':100,
                                    'nume': 'France',
                                    'lat': 1.0,
                                    'lon': 1.0})
        assert response.status_code == 404

class TestDeleteCountryRoute:
    def test_delete_country(self, session_with_countries):
        s, _ = session_with_countries
        response = s.delete(f'{URL}/api/countries/1')
        assert response.status_code == 200

        response = s.get(f'{URL}/api/countries')
        assert response.status_code == 200
        for country in response.json():
            assert country['nume'] != 'Romania'

    def test_delete_country_not_found(self, session_with_countries):
        s, _ = session_with_countries
        response = s.delete(f'{URL}/api/countries/100')
        assert response.status_code == 404

    def test_delete_country_invalid(self, session_with_countries):
        s, _ = session_with_countries
        response = s.delete(f'{URL}/api/countries/absolutely_not_an_int')
        assert response.status_code == 400

class TestAddCities:
    CITIES = [{'nume': 'Bucuresti',
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
               'lat': 123.45,
               'lon': 1.0,
               'idTara': 2}]

    def test_add_cities(self, session_with_countries):
        s, _ = session_with_countries
        for city in self.CITIES:
            response = s.post(f'{URL}/api/cities',
                                   json=city)
            assert response.status_code == 201

    def test_add_city_invalid(self, session_with_countries):
        s, _ = session_with_countries
        response = s.post(f'{URL}/api/cities',
                               json={'nume': 'Bucuresti',
                                     'lat': 123.45,
                                     'lon': 1.0})
        assert response.status_code == 400

    def test_add_city_invalid2(self, session_with_countries):
        s, _ = session_with_countries
        response = s.post(f'{URL}/api/cities',
                               json={'nume': 'Bucuresti',
                                     'lat': 123.45,
                                     'lon': 1.0,
                                     'idTara': 100})
        assert response.status_code == 404

    def test_add_city_invalid3(self, session_with_countries):
        s, _ = session_with_countries
        response = s.post(f'{URL}/api/cities',
                               json={'nume': 'Bucuresti',
                                     'lat': 123.45,
                                     'lon': 1.0,
                                     'idTara': 'absolutely not an int'})
        assert response.status_code == 400


    def test_add_city_invalid5(self, session_with_countries):
        s, _ = session_with_countries
        response = s.post(f'{URL}/api/cities',
                               json={'nume': 'Galati',
                                     'lat': 123.45,
                                     'lon': 1.0,
                                     'idTara': 'absolutely not an int'
                                     })
        assert response.status_code == 400

    def test_add_city_duplicate(self, session_with_countries):
        s, _ = session_with_countries
        response = s.post(f'{URL}/api/cities',
                               json={'nume': 'Bucuresti',
                                     'lat': 123.45,
                                     'lon': 1.0,
                                     'idTara': 1})
        assert response.status_code == 409

class TestGetCities:
    def test_get_cities(self, session_with_cities):
        s, _, cities = session_with_cities
        response = s.get(f'{URL}/api/cities')
        assert response.status_code == 200

        for i in range(len(cities)):
            cities[i]['id'] = i + 1
            assert cities[i] in response.json()

class TestUpdateCityRoute:
    NEW_BUCURESTI = {'id': 1,
                     'nume': 'Bucuresti',
                     'lat': 1.0,
                     'lon': 1.0,
                     'idTara': 1}

    def test_update_city(self, session_with_cities):
        s, countries, _ = session_with_cities
        response = s.put(f'{URL}/api/cities/1',
                              json=self.NEW_BUCURESTI)
        assert response.status_code == 200

        response = s.get(f'{URL}/api/cities')
        assert response.status_code == 200
        assert self.NEW_BUCURESTI in response.json()

    def test_update_city_invalid(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.put(f'{URL}/api/cities/1',
                              json={'nume': 'Bucuresti',
                                    'lat': 1.0})
        assert response.status_code == 400

    def test_update_city_invalid2(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.put(f'{URL}/api/cities/1',
                              json={'id': 1234,
                                    'nume': 'Bucuresti',
                                    'lat': 1.0,
                                    'lon': 'absolutely not a double'})
        assert response.status_code == 400

    def test_update_city_invalid3(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.put(f'{URL}/api/cities/1')
        assert response.status_code == 400

    def test_update_city_not_found(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.put(f'{URL}/api/cities/100',
                              json={'id': 100,
                                    'nume': 'Bucuresti',
                                    'lat': 1.0,
                                    'lon': 1.0,
                                    'idTara': 1})
        assert response.status_code == 404

    def test_update_city_to_already_existing(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.put(f'{URL}/api/cities/1',
                              json={'id': 1,
                                    'nume': 'Cluj',
                                    'lat': 1.0,
                                    'lon': 1.0,
                                    'idTara': 1})
        assert response.status_code == 409

class TestDeleteCityRoute:
    def test_delete_city(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.delete(f'{URL}/api/cities/1')
        assert response.status_code == 200

        response = s.get(f'{URL}/api/cities')
        assert response.status_code == 200
        for city in response.json():
            assert city['nume'] != 'Bucuresti'

    def test_delete_city_not_found(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.delete(f'{URL}/api/cities/100')
        assert response.status_code == 404

    def test_delete_city_invalid(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.delete(f'{URL}/api/cities/absolutely_not_an_int')
        assert response.status_code == 400

    def test_delete_city_invalid2(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.delete(f'{URL}/api/cities/1')
        assert response.status_code == 404

class TestAddTemperatureRoute:
    temps = [{'idOras': 1,
              'valoare': 25.0},
             {'idOras': 1,
              'valoare': 26.0},
             {'idOras': 1,
              'valoare': 27.0},
             {'idOras': 2,
              'valoare': 25.0},
             {'idOras': 2,
              'valoare': 22.0}]

    def test_add_temperatures(self, session_with_cities):
        s, _, cities = session_with_cities
        i = 1
        for temp in self.temps:
            response = s.post(f'{URL}/api/temperatures',
                               json=temp)
            assert response.status_code == 201
            assert response.json() == {'id': i}
            i += 1

    def test_add_temperature_invalid(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.post(f'{URL}/api/temperatures',
                           json={'idOras': 1,
                                 'temp': 'absolutely not a double'})
        assert response.status_code == 400

    def test_add_temperature_missing(self, session_with_cities):
        s, _, _ = session_with_cities
        response = s.post(f'{URL}/api/temperatures',
                           json={'idOras': 1000,
                                 'temp': 25.0})
        assert response.status_code == 404

class TestUpdateTemperatureRoute:
    new_temp = {'id': 1,
                'idOras': 1,
                'valoare': 30.0}

    def test_update_temperature(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.put(f'{URL}/api/temperatures/1',
                         json=self.new_temp)
        assert response.status_code == 200

        response = s.get(f'{URL}/api/temperatures')
        assert response.status_code == 200
        for temp in response.json():
            if temp['id'] == 1:
                assert temp['valoare'] == self.new_temp['valoare']

    def test_update_temperature_invalid(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.put(f'{URL}/api/temperatures/1',
                          json={'idOras': 1,
                                'valoare': 'absolutely not a double'})
        assert response.status_code == 400

    def test_update_temperature_invalid2(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.put(f'{URL}/api/temperatures/1',
                          json={'id': 1234,
                                'idOras': 1,
                                'valoare': 30.0})
        assert response.status_code == 400

    def test_update_temperature_not_found(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.put(f'{URL}/api/temperatures/100',
                          json={'id': 100,
                                'idOras': 1,
                                'valoare': 30.0})
        assert response.status_code == 404

class TestDeleteTemperatureRoute:
    def test_delete_temperature(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.delete(f'{URL}/api/temperatures/1')
        assert response.status_code == 200

        response = s.get(f'{URL}/api/temperatures')
        assert response.status_code == 200
        for temp in response.json():
            assert temp['id'] != 1

    def test_delete_temperature_not_found(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.delete(f'{URL}/api/temperatures/100')
        assert response.status_code == 404

    def test_delete_temperature_invalid(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.delete(f'{URL}/api/temperatures/absolutely_not_an_int')
        assert response.status_code == 400

    def test_delete_temperature_invalid2(self, session_with_temps):
        s, _, _, _ = session_with_temps
        response = s.delete(f'{URL}/api/temperatures/1')
        assert response.status_code == 404

class TestGetTemperatureRoute:
    def test_get_temperatures(self, session_with_temps):
        s, _, _, temps = session_with_temps
        response = s.get(f'{URL}/api/temperatures')
        assert response.status_code == 200

        response_temps = response.json()

        for temp in response_temps:
            temp.pop('timestamp')

        for i in range(len(temps)):
            temps[i]['id'] = i + 1
            del temps[i]['idOras']

            assert temps[i] in response_temps

    def test_get_temperatures_lon(self, session_with_temps):
        s, _, _, temps = session_with_temps
        response = s.get(f'{URL}/api/temperatures?lon=2000.0')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 1

    def test_get_temperatures_lat(self, session_with_temps):
        s, _, _, temps = session_with_temps
        response = s.get(f'{URL}/api/temperatures?lat=420.0')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 1

    def test_get_temperatures_lat_lon(self, session_with_temps):
        s, _, _, temps = session_with_temps
        response = s.get(f'{URL}/api/temperatures?lat=123.45&lon=1.0')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 4

    def test_get_temperatures_lat_lon_interval(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        two_days_ago = current_time - datetime.timedelta(days=2)
        tomorrow = current_time + datetime.timedelta(days=1)

        from_str = two_days_ago.strftime('%Y-%m-%d')
        until_str = tomorrow.strftime('%Y-%m-%d')


        response = s.get(f'{URL}/api/temperatures?lat=123.45&lon=1.0&from={from_str}&until={until_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 4

    def test_get_temperatures_lat_lon_interval_invalid(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.get(f'{URL}/api/temperatures?lat=123.45&lon=1.0&from=absolutely_not_a_date&until=absolutely_not_a_date')
        assert response.status_code == 400

    def test_get_temperatures_interval(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        two_days_ago = current_time - datetime.timedelta(days=2)
        tomorrow = current_time + datetime.timedelta(days=1)

        from_str = two_days_ago.strftime('%Y-%m-%d')
        until_str = tomorrow.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures?from={from_str}&until={until_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 5

    def test_get_temperatures_interval_empty(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.get(f'{URL}/api/temperatures?from=2021-01-01&until=2021-01-02')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 0

class TestGetTemperatureForCityRoute:
    def test_get_temperatures_for_city_interval(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        two_days_ago = current_time - datetime.timedelta(days=2)
        tomorrow = current_time + datetime.timedelta(days=1)

        from_str = two_days_ago.strftime('%Y-%m-%d')
        until_str = tomorrow.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures/cities/1?from={from_str}&until={until_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_city_from(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        two_days_ago = current_time - datetime.timedelta(days=2)

        from_str = two_days_ago.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures/cities/1?from={from_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_city_until(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        tomorrow = current_time + datetime.timedelta(days=1)

        until_str = tomorrow.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures/cities/1?until={until_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_city(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.get(f'{URL}/api/temperatures/cities/1')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_city_empty(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.get(f'{URL}/api/temperatures/cities/1?from=2021-01-01&until=2021-01-02')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 0

class TestGetTemperatureForCountryRoute:
    def test_get_temperatures_for_country_interval(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        two_days_ago = current_time - datetime.timedelta(days=2)
        tomorrow = current_time + datetime.timedelta(days=1)

        from_str = two_days_ago.strftime('%Y-%m-%d')
        until_str = tomorrow.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures/countries/1?from={from_str}&until={until_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_country_from(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        two_days_ago = current_time - datetime.timedelta(days=2)

        from_str = two_days_ago.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures/countries/1?from={from_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_country_until(self, session_with_temps):
        s, _, _, temps = session_with_temps

        current_time = datetime.datetime.now()
        tomorrow = current_time + datetime.timedelta(days=1)

        until_str = tomorrow.strftime('%Y-%m-%d')

        response = s.get(f'{URL}/api/temperatures/countries/1?until={until_str}')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_country(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.get(f'{URL}/api/temperatures/countries/1')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 3

    def test_get_temperatures_for_country_empty(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.get(f'{URL}/api/temperatures/countries/1?from=2021-01-01&until=2021-01-02')
        assert response.status_code == 200

        response_temps = response.json()

        assert len(response_temps) == 0

class TestGetCitiesAfterCountryDelete:
    def test_get_cities_after_country_delete(self, session_with_cities):
        s, _, cities = session_with_cities

        response = s.delete(f'{URL}/api/countries/1')
        assert response.status_code == 200

        response = s.get(f'{URL}/api/cities')
        assert response.status_code == 200

        for city in response.json():
            assert city['idTara'] != 1

class TestGetTemperaturesAfterCityDelete:
    def test_get_temperatures_after_city_delete(self, session_with_temps):
        s, _, _, temps = session_with_temps

        response = s.delete(f'{URL}/api/cities/1')
        assert response.status_code == 200

        response = s.get(f'{URL}/api/temperatures')
        assert response.status_code == 200
        assert len(response.json()) == 2
