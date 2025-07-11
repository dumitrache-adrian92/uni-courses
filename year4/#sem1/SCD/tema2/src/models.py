from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class Country(db.Model):
    __tablename__ = 'tari'
    id = db.Column(db.Integer, primary_key=True)
    nume_tara = db.Column(db.String(255), unique=True, nullable=False)
    latitudine = db.Column(db.Double, nullable=False)
    longitudine = db.Column(db.Double, nullable=False)

    def get_dict(self):
        return {'id': self.id, 'nume': self.nume_tara,
                'lat': self.latitudine, 'lon': self.longitudine}

class City(db.Model):
    __tablename__ = 'orase'
    id = db.Column(db.Integer, primary_key=True)
    id_tara = db.Column(db.Integer, db.ForeignKey('tari.id', ondelete='CASCADE'), nullable=False)
    parent = db.relationship('Country', backref=db.backref('orase', passive_deletes=True))
    nume_oras = db.Column(db.String(255), nullable=False)
    latitudine = db.Column(db.Double, nullable=False)
    longitudine = db.Column(db.Double, nullable=False)
    __table_args__ = (db.UniqueConstraint('id_tara', 'nume_oras', name='tara_oras_uq'),)

    def get_dict(self):
        return {'id': self.id, 'idTara': self.id_tara, 'nume': self.nume_oras,
                'lat': self.latitudine, 'lon': self.longitudine}

class Temperature(db.Model):
    __tablename__ = 'temperaturi'
    id = db.Column(db.Integer, primary_key=True)
    valoare = db.Column(db.Double, nullable=False)
    timestamp = db.Column(db.DateTime, nullable=False)
    id_oras = db.Column(db.Integer, db.ForeignKey('orase.id', ondelete='CASCADE'), nullable=False)
    parent = db.relationship('City', backref=db.backref('temperaturi', passive_deletes=True))
    __table_args__ = (db.UniqueConstraint('timestamp', 'id_oras', name='oras_ts_uq'),)

    def get_dict(self):
        return {'id': self.id, 'valoare': self.valoare, 'timestamp': self.timestamp}
