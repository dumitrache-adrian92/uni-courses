from flask import Flask, jsonify, request, Response
from database import MovieDatabase

app = Flask(__name__)
db = MovieDatabase()

@app.route('/movies', methods=['GET'])
def get_movies():
        return jsonify([{'nume': v} for v in db.get_movies()])

@app.route('/movies', methods=['POST'])
def add_movie():
    data = request.get_json(silent=True)
    if not data or 'nume' not in data:
        return Response(status=400)

    db.add_movie(data['nume'])
    return Response(status=201)


@app.route('/movie/<int:movie_id>', methods=['PUT'])
def update_movie(movie_id):
    data = request.get_json(silent=True)
    if not data or 'nume' not in data:
        return Response(status=400)

    if not db.update_movie(movie_id, data['nume']):
        return Response(status=404)

    return jsonify(status=200)

@app.route('/movie/<int:movie_id>', methods=['GET'])
def get_movie(movie_id):
    movie = db.get_movie(movie_id)
    if movie is None:
        return Response(status=404)

    print(movie)

    return jsonify(movie), 200

@app.route('/movie/<int:movie_id>', methods=['DELETE'])
def delete_movie(movie_id):
    if not db.delete_movie(movie_id):
        return Response(status=404)

    return jsonify(status=200)

@app.route('/reset', methods=['DELETE'])
def reset_movies():
    db.reset()
    return jsonify(status=200)

if __name__ == '__main__':
    app.run('0.0.0.0', debug=True)
