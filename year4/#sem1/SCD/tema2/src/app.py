import datetime

from config import Config
from flask import Flask, request, jsonify, make_response
from models import db, Country, City, Temperature

app = Flask(__name__)
app.config.from_object(Config)
db.init_app(app)


@app.route('/api/countries', methods=['POST'])
def add_country():
    try:
        country = Country.query.filter_by(nume_tara=request.json['nume']).first()
        if country:
            return make_response(jsonify({'message': 'Country already exists'}), 409)

        new_country = Country(nume_tara=request.json['nume'],
                              latitudine=request.json['lat'],
                              longitudine=request.json['lon'])

        db.session.add(new_country)
        db.session.commit()

        return make_response(jsonify({'id': new_country.id}), 201)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/countries', methods=['GET'])
def get_countries():
    countries = Country.query.all()
    return make_response(jsonify([country.get_dict() for country in countries]), 200)


@app.route('/api/countries/<int:country_id>', methods=['PUT'])
def update_country(country_id):
    try:
        if country_id != request.json['id']:
            return make_response(jsonify({'message': 'Invalid data received'}), 400)

        country = Country.query.get(country_id)
        if not country:
            return make_response(jsonify({'message': 'Country not found'}), 404)

        new_country = Country.query.filter_by(nume_tara=request.json['nume']).first()

        if new_country and new_country.id != country_id:
            return make_response(jsonify({'message': 'Country already exists'}), 409)

        country.nume_tara = request.json['nume']
        country.latitudine = request.json['lat']
        country.longitudine = request.json['lon']

        db.session.commit()

        return make_response(jsonify({'message': 'Country updated'}), 200)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/countries/<int:country_id>', methods=['DELETE'])
def delete_country(country_id):
    try:
        country = Country.query.get(country_id)
        if not country:
            return make_response(jsonify({'message': 'Country not found'}), 404)

        db.session.delete(country)
        db.session.commit()

        return make_response(jsonify({'message': 'Country deleted'}), 200)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/countries/<country_id>', methods=['DELETE', 'PUT'])
def catch_all_countries(country_id):
    return make_response(jsonify({'message': f'Invalid id: {country_id}'}), 400)


@app.route('/api/cities', methods=['POST'])
def add_city():
    try:
        city = City.query.filter_by(id_tara=request.json['idTara'], nume_oras=request.json['nume']).first()
        if city:
            return make_response(jsonify({'message': 'City already exists'}), 409)

        country = Country.query.get(request.json['idTara'])
        if not country:
            return make_response(jsonify({'message': 'Country not found'}), 404)

        new_city = City(id_tara=request.json['idTara'],
                        nume_oras=request.json['nume'],
                        latitudine=request.json['lat'],
                        longitudine=request.json['lon'])

        db.session.add(new_city)
        db.session.commit()

        return make_response(jsonify({'id': new_city.id}), 201)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/cities', methods=['GET'])
def get_cities():
    cities = City.query.all()
    return make_response(jsonify([city.get_dict() for city in cities]), 200)


@app.route('/api/cities/country/<int:country_id>', methods=['GET'])
def get_cities_by_country(country_id):
    cities = City.query.filter_by(id_tara=country_id).all()
    return make_response(jsonify([city.get_dict() for city in cities]), 200)

@app.route('/api/cities/country/<country_id>', methods=['GET'])
def catch_all_cities_by_country(country_id):
    return make_response(jsonify({'message': f'Invalid id: {country_id}'}), 400)


@app.route('/api/cities/<int:city_id>', methods=['PUT'])
def update_city(city_id):
    try:
        if city_id != request.json['id']:
            return make_response(jsonify({'message': 'Invalid data received'}), 400)

        city = City.query.get(city_id)
        if not city:
            return make_response(jsonify({'message': 'City not found'}), 404)

        country = Country.query.get(request.json['idTara'])
        if not country:
            return make_response(jsonify({'message': 'Country not found'}), 404)

        new_city = City.query.filter_by(id_tara=request.json['idTara'], nume_oras=request.json['nume']).first()
        if new_city and new_city.id != city_id:
            return make_response(jsonify({'message': 'City already exists'}), 409)

        city.id_tara = request.json['idTara']
        city.nume_oras = request.json['nume']
        city.latitudine = request.json['lat']
        city.longitudine = request.json['lon']

        db.session.commit()

        return make_response(jsonify({'message': 'City updated'}), 200)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/cities/<int:city_id>', methods=['DELETE'])
def delete_city(city_id):
    try:
        city = City.query.get(city_id)
        if not city:
            return make_response(jsonify({'message': 'City not found'}), 404)

        db.session.delete(city)
        db.session.commit()

        return make_response(jsonify({'message': 'City deleted'}), 200)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/cities/<city_id>', methods=['DELETE', 'PUT'])
def catch_all_cities(city_id):
    return make_response(jsonify({'message': f'Invalid id: {city_id}'}), 400)


@app.route('/api/temperatures', methods=['POST'])
def add_temperature():
    time = datetime.datetime.now()

    try:
        city = City.query.get(request.json['idOras'])
        if not city:
            return make_response(jsonify({'message': 'City not found'}), 404)

        temperature = Temperature.query.filter_by(id_oras=request.json['idOras'], timestamp=time).first()
        if temperature:
            return make_response(jsonify({'message': 'Temperature already exists'}), 409)

        new_temperature = Temperature(valoare=request.json['valoare'],
                                      timestamp=time,
                                      id_oras=request.json['idOras'])

        db.session.add(new_temperature)
        db.session.commit()

        return make_response(jsonify({'id': new_temperature.id}), 201)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/temperatures/<int:temp_id>', methods=['PUT'])
def modify_temperature(temp_id):
    try:
        if temp_id != request.json['id']:
            return make_response(jsonify({'message': 'Invalid data received'}), 400)

        temperature = Temperature.query.filter_by(id=request.json['id']).first()
        if not temperature:
            return make_response(jsonify({'message': 'Temperature not found'}), 404)

        # check for timestamp and new city uniqueness
        new_temperature = (Temperature.query.filter_by(id_oras=request.json['idOras'],
                                                       timestamp=temperature.timestamp)
                           .first())
        if new_temperature and new_temperature.id != request.json['id']:
            return make_response(jsonify({'message': 'Temperature already exists'}), 409)

        temperature.valoare = request.json['valoare']
        temperature.id_oras = request.json['idOras']

        db.session.commit()

        return make_response(jsonify({'message': 'Temperature updated'}), 200)
    except Exception as e:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/temperatures/<int:temp_id>', methods=['DELETE'])
def delete_temperature(temp_id):
    try:
        temperature = Temperature.query.get(temp_id)
        if not temperature:
            return make_response(jsonify({'message': 'Temperature not found'}), 404)

        db.session.delete(temperature)
        db.session.commit()

        return make_response(jsonify({'message': 'Temperature deleted'}), 200)
    except Exception:
        return make_response(jsonify({'message': 'Invalid data received'}), 400)


@app.route('/api/temperatures/<temp_id>', methods=['DELETE', 'PUT'])
def catch_all_temperatures(temp_id):
    return make_response(jsonify({'message': f'Invalid id: {temp_id}'}), 400)


@app.route('/api/temperatures', methods=['GET'])
def get_temperatures():
    from_date = request.args.get('from')
    until_date = request.args.get('until')
    lat = request.args.get('lat')
    lon = request.args.get('lon')

    query = Temperature.query.join(City, City.id == Temperature.id_oras)

    try:
        if lat:
            lat = float(lat)
            query = query.filter(City.latitudine == lat)

        if lon:
            lon = float(lon)
            query = query.filter(City.longitudine == lon)
    except ValueError:
        return make_response(jsonify({'message': 'Invalid coordinates'}), 400)

    try:
        query = query_date_interval(from_date, query, until_date)
    except ValueError:
        return make_response(jsonify({'message': 'Invalid date format, use YYYY-MM-DD'}), 400)

    temperatures = query.all()

    return make_response(jsonify([temperature.get_dict() for temperature in temperatures]), 200)


def query_date_interval(from_date, query, until_date):
    if from_date:
        from_date = datetime.datetime.strptime(from_date, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp >= from_date)
    if until_date:
        until_date = datetime.datetime.strptime(until_date, '%Y-%m-%d')
        query = query.filter(Temperature.timestamp <= until_date)
    return query


@app.route('/api/temperatures/cities/<int:city_id>', methods=['GET'])
def get_temperatures_by_city(city_id):
    from_date = request.args.get('from')
    until_date = request.args.get('until')

    query = Temperature.query.filter_by(id_oras=city_id)

    try:
        query = query_date_interval(from_date, query, until_date)
    except ValueError:
        return make_response(jsonify({'message': 'Invalid date format, use YYYY-MM-DD'}), 400)

    temperatures = query.all()

    return make_response(jsonify([temperature.get_dict() for temperature in temperatures]), 200)


@app.route('/api/temperatures/cities/<city_id>', methods=['GET'])
def catch_all_temperatures_by_city(city_id):
    return make_response(jsonify({'message': f'Invalid id: {city_id}'}), 400)

@app.route('/api/temperatures/countries/<int:country_id>', methods=['GET'])
def get_temperatures_by_country(country_id):
    from_date = request.args.get('from')
    until_date = request.args.get('until')

    query = Temperature.query.join(City).filter(City.id_tara == country_id)

    try:
        query = query_date_interval(from_date, query, until_date)
    except ValueError:
        return make_response(jsonify({'message': 'Invalid date format, use YYYY-MM-DD'}), 400)

    temperatures = query.all()

    return make_response(jsonify([temperature.get_dict() for temperature in temperatures]), 200)


@app.route('/api/temperatures/countries/<country_id>', methods=['GET'])
def catch_all_temperatures_by_country(country_id):
    return make_response(jsonify({'message': f'Invalid id: {country_id}'}), 400)

@app.route('/api/clear_db', methods=['DELETE'])
def clear_db():
    db.drop_all()
    db.create_all()
    return make_response(jsonify({'message': 'Database cleared'}), 200)

if __name__ == "__main__":
    app.run(debug=True, host='0.0.0.0', port=5000)
