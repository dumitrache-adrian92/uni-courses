from flask import jsonify

class MovieDatabase:
    def __init__(self):
        self.movies = {}
        self.next_id = 1

    def add_movie(self, title):
        self.movies[self.next_id] = title
        self.next_id += 1

    def get_movies(self):
        return list(self.movies.values())

    def get_movie(self, movie_id):
        return self.movies.get(movie_id)

    def reset(self):
        self.movies = {}
        self.next_id = 1

    def update_movie(self, movie_id, title):
        if movie_id not in self.movies:
            return False

        self.movies[movie_id] = title
        return True

    def delete_movie(self, movie_id):
        if movie_id not in self.movies:
            return False

        del self.movies[movie_id]

        return True
