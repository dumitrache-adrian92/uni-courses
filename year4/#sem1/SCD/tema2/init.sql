CREATE TABLE IF NOT EXISTS tari (
    id SERIAL PRIMARY KEY,
    nume_tara VARCHAR(255) NOT NULL UNIQUE,
    latitudine FLOAT NOT NULL,
    longitudine FLOAT NOT NULL
);

CREATE TABLE IF NOT EXISTS orase (
    id SERIAL PRIMARY KEY,
    id_tara INT NOT NULL,
    FOREIGN KEY (id_tara) REFERENCES tari(id) ON DELETE CASCADE,
    nume_oras VARCHAR(255) NOT NULL,
    latitudine DOUBLE PRECISION NOT NULL,
    longitudine DOUBLE PRECISION NOT NULL,
    UNIQUE (id_tara, nume_oras)
);

CREATE TABLE IF NOT EXISTS temperaturi (
    id SERIAL PRIMARY KEY,
    valoare DOUBLE PRECISION NOT NULL,
    timestamp TIMESTAMP NOT NULL,
    id_oras INT NOT NULL,
    FOREIGN KEY (id_oras) REFERENCES orase(id) ON DELETE CASCADE,
    UNIQUE (timestamp, id_oras)
);
