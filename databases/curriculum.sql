DROP TABLE IF EXISTS curriculum;
CREATE TABLE curriculum (
  id INTEGER PRIMARY KEY,
  name VARCHAR(60)
);

DROP TABLE IF EXISTS years;
CREATE TABLE years (
  id INTEGER PRIMARY KEY,
  cid INTEGER REFERENCES curriculum(id),
  ind INTEGER,
  name VARCHAR(60)
);

DROP TABLE IF EXISTS columns;
CREATE TABLE columns (
  yid INTEGER REFERENCES years(id),
  ind INTEGER,
  lid INTEGER REFERENCES lines(id)
);

DROP TABLE IF EXISTS lines;
CREATE TABLE lines (
  id INTEGER,
  ind INTEGER,
  type TINYINT, --1 = course, 2 = split, 3 = choice
  fid INTEGER
);

DROP TABLE IF EXISTS splits;
CREATE TABLE splits (
  id INTEGER PRIMARY KEY,
  left INTEGER REFERENCES lines(id),
  right INTEGER REFERENCES lines(id)
);

DROP TABLE IF EXISTS choices;
CREATE TABLE choices (
  id INTEGER PRIMARY KEY,
  count INTEGER,
  pick INTEGER
);

DROP TABLE IF EXISTS options;
CREATE TABLE options (
  cid INTEGER REFERENCES choices(id),
  course INTEGER REFERENCES courses(id),
  ind INTEGER
);

INSERT INTO curriculum (name) VALUES ("Informatica");
INSERT INTO curriculum (name) VALUES ("I&E");
INSERT INTO curriculum (name) VALUES ("I&B");

INSERT INTO years (cid, ind, name) VALUES (1, 1, "Year 1");
INSERT INTO years (cid, ind, name) VALUES (1, 2, "Year 2");
INSERT INTO years (cid, ind, name) VALUES (1, 3, "Year 3");
INSERT INTO years (cid, ind, name) VALUES (2, 1, "Year 1");
INSERT INTO years (cid, ind, name) VALUES (2, 2, "Year 2");
INSERT INTO years (cid, ind, name) VALUES (2, 3, "Year 3");
INSERT INTO years (cid, ind, name) VALUES (3, 1, "Year 1");
INSERT INTO years (cid, ind, name) VALUES (3, 2, "Year 2");
INSERT INTO years (cid, ind, name) VALUES (3, 3, "Year 3");

INSERT INTO columns(yid, ind, lid) VALUES (1, 1, 1);
INSERT INTO columns(yid, ind, lid) VALUES (1, 2, 2);
INSERT INTO lines(id, ind, type, fid) VALUES (1, 1, 1, 18);
INSERT INTO lines(id, ind, type, fid) VALUES (1, 2, 1, 20);
INSERT INTO lines(id, ind, type, fid) VALUES (1, 3, 1, 19);
INSERT INTO lines(id, ind, type, fid) VALUES (1, 4, 1, 14);
INSERT INTO lines(id, ind, type, fid) VALUES (1, 5, 1, 1);
INSERT INTO lines(id, ind, type, fid) VALUES (1, 6, 1, 3);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 1, 1, 21);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 2, 1, 23);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 3, 1, 13);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 4, 1, 15);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 5, 1, 16);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 6, 1, 5);
INSERT INTO lines(id, ind, type, fid) VALUES (2, 7, 1, 7);

INSERT INTO columns(yid, ind, lid) VALUES (2, 1, 3);
INSERT INTO columns(yid, ind, lid) VALUES (2, 2, 4);
INSERT INTO lines(id, ind, type, fid) VALUES (3, 1, 1, 26);
INSERT INTO lines(id, ind, type, fid) VALUES (3, 2, 1, 25);
INSERT INTO lines(id, ind, type, fid) VALUES (3, 3, 1, 27);
INSERT INTO lines(id, ind, type, fid) VALUES (3, 4, 1, 29);
INSERT INTO lines(id, ind, type, fid) VALUES (3, 5, 1, 12);
INSERT INTO lines(id, ind, type, fid) VALUES (4, 1, 1, 22);
INSERT INTO lines(id, ind, type, fid) VALUES (4, 2, 1, 32);
INSERT INTO lines(id, ind, type, fid) VALUES (4, 3, 1, 28);
INSERT INTO lines(id, ind, type, fid) VALUES (4, 4, 1, 30);
INSERT INTO lines(id, ind, type, fid) VALUES (4, 5, 1, 9);
INSERT INTO lines(id, ind, type, fid) VALUES (4, 6, 1, 10);

INSERT INTO splits(left, right) VALUES (6, 7);
INSERT INTO splits(left, right) VALUES (9, 10);
INSERT INTO columns(yid, ind, lid) VALUES (3, 1, 5);
INSERT INTO columns(yid, ind, lid) VALUES (3, 2, 8);
INSERT INTO columns(yid, ind, lid) VALUES (3, -1, 6);
INSERT INTO columns(yid, ind, lid) VALUES (3, -1, 7);
INSERT INTO columns(yid, ind, lid) VALUES (3, -1, 9);
INSERT INTO columns(yid, ind, lid) VALUES (3, -1, 10);
INSERT INTO lines(id, ind, type, fid) VALUES (5, 1, 1, 24);
INSERT INTO lines(id, ind, type, fid) VALUES (5, 2, 1, 31);
INSERT INTO lines(id, ind, type, fid) VALUES (5, 3, 1, 41);
INSERT INTO lines(id, ind, type, fid) VALUES (5, 4, 2, 1);
INSERT INTO lines(id, ind, type, fid) VALUES (6, 1, 1, 34);
INSERT INTO lines(id, ind, type, fid) VALUES (6, 2, 1, 37);
INSERT INTO lines(id, ind, type, fid) VALUES (7, 1, 1, 40);
INSERT INTO lines(id, ind, type, fid) VALUES (7, 2, 1, 42);
INSERT INTO lines(id, ind, type, fid) VALUES (7, 3, 1, 43);
INSERT INTO lines(id, ind, type, fid) VALUES (8, 1, 1, 33);
INSERT INTO lines(id, ind, type, fid) VALUES (8, 2, 2, 2);
INSERT INTO lines(id, ind, type, fid) VALUES (9, 1, 1, 38);
INSERT INTO lines(id, ind, type, fid) VALUES (9, 2, 1, 36);
INSERT INTO lines(id, ind, type, fid) VALUES (9, 3, 1, 11);
INSERT INTO lines(id, ind, type, fid) VALUES (10, 1, 1, 39);
INSERT INTO lines(id, ind, type, fid) VALUES (10, 2, 1, 35);

INSERT INTO columns(yid, ind, lid) VALUES (4, 1, 11);
INSERT INTO columns(yid, ind, lid) VALUES (4, 2, 12);
INSERT INTO lines(id, ind, type, fid) VALUES (11, 1, 1, 18);
INSERT INTO lines(id, ind, type, fid) VALUES (11, 2, 1, 19);
INSERT INTO lines(id, ind, type, fid) VALUES (11, 3, 1, 14);
INSERT INTO lines(id, ind, type, fid) VALUES (11, 4, 1, 45);
INSERT INTO lines(id, ind, type, fid) VALUES (11, 5, 1, 1);
INSERT INTO lines(id, ind, type, fid) VALUES (11, 6, 1, 2);
INSERT INTO lines(id, ind, type, fid) VALUES (12, 1, 1, 21);
INSERT INTO lines(id, ind, type, fid) VALUES (12, 2, 1, 44);
INSERT INTO lines(id, ind, type, fid) VALUES (12, 3, 1, 46);
INSERT INTO lines(id, ind, type, fid) VALUES (12, 4, 1, 5);
INSERT INTO lines(id, ind, type, fid) VALUES (12, 5, 1, 6);

INSERT INTO columns(yid, ind, lid) VALUES (5, 1, 13);
INSERT INTO columns(yid, ind, lid) VALUES (5, 2, 14);
INSERT INTO lines(id, ind, type, fid) VALUES (13, 1, 1, 20);
INSERT INTO lines(id, ind, type, fid) VALUES (13, 2, 1, 47);
INSERT INTO lines(id, ind, type, fid) VALUES (13, 3, 1, 49);
INSERT INTO lines(id, ind, type, fid) VALUES (13, 4, 1, 13);
INSERT INTO lines(id, ind, type, fid) VALUES (13, 5, 1, 12);
INSERT INTO lines(id, ind, type, fid) VALUES (14, 1, 1, 22);
INSERT INTO lines(id, ind, type, fid) VALUES (14, 2, 1, 23);
INSERT INTO lines(id, ind, type, fid) VALUES (14, 3, 1, 48);
INSERT INTO lines(id, ind, type, fid) VALUES (14, 4, 1, 50);
INSERT INTO lines(id, ind, type, fid) VALUES (14, 5, 1, 9);
INSERT INTO lines(id, ind, type, fid) VALUES (14, 6, 1, 10);

INSERT INTO splits(left, right) VALUES (17, 18);
INSERT INTO splits(left, right) VALUES (19, 20);
INSERT INTO columns(yid, ind, lid) VALUES (6, 1, 15);
INSERT INTO columns(yid, ind, lid) VALUES (6, 2, 16);
INSERT INTO columns(yid, ind, lid) VALUES (6, -1, 17);
INSERT INTO columns(yid, ind, lid) VALUES (6, -1, 18);
INSERT INTO columns(yid, ind, lid) VALUES (6, -1, 19);
INSERT INTO columns(yid, ind, lid) VALUES (6, -1, 20);
INSERT INTO lines(id, ind, type, fid) VALUES (15, 1, 1, 24);
INSERT INTO lines(id, ind, type, fid) VALUES (15, 2, 1, 31);
INSERT INTO lines(id, ind, type, fid) VALUES (15, 3, 1, 51);
INSERT INTO lines(id, ind, type, fid) VALUES (15, 4, 2, 3);
INSERT INTO lines(id, ind, type, fid) VALUES (17, 1, 1, 52);
INSERT INTO lines(id, ind, type, fid) VALUES (17, 2, 1, 53);
INSERT INTO lines(id, ind, type, fid) VALUES (18, 1, 1, 41);
INSERT INTO lines(id, ind, type, fid) VALUES (18, 2, 1, 42);
INSERT INTO lines(id, ind, type, fid) VALUES (16, 1, 1, 32);
INSERT INTO lines(id, ind, type, fid) VALUES (16, 2, 2, 4);
INSERT INTO lines(id, ind, type, fid) VALUES (19, 1, 1, 54);
INSERT INTO lines(id, ind, type, fid) VALUES (19, 2, 1, 11);
INSERT INTO lines(id, ind, type, fid) VALUES (20, 1, 1, 15);
INSERT INTO lines(id, ind, type, fid) VALUES (20, 2, 1, 16);

INSERT INTO splits(left, right) VALUES (23, 24);
INSERT INTO columns(yid, ind, lid) VALUES (7, 1, 21);
INSERT INTO columns(yid, ind, lid) VALUES (7, 2, 22);
INSERT INTO columns(yid, ind, lid) VALUES (7, -1, 23);
INSERT INTO columns(yid, ind, lid) VALUES (7, -1, 24);
INSERT INTO lines(id, ind, type, fid) VALUES (21, 1, 2, 5);
INSERT INTO lines(id, ind, type, fid) VALUES (23, 1, 1, 18);
INSERT INTO lines(id, ind, type, fid) VALUES (23, 2, 1, 19);
INSERT INTO lines(id, ind, type, fid) VALUES (23, 3, 1, 62);
INSERT INTO lines(id, ind, type, fid) VALUES (23, 4, 1, 61);
INSERT INTO lines(id, ind, type, fid) VALUES (24, 1, 1, 60);
INSERT INTO lines(id, ind, type, fid) VALUES (24, 2, 1, 59);
INSERT INTO lines(id, ind, type, fid) VALUES (24, 3, 1, 1);
INSERT INTO lines(id, ind, type, fid) VALUES (24, 4, 1, 4);
INSERT INTO lines(id, ind, type, fid) VALUES (22, 1, 1, 21);
INSERT INTO lines(id, ind, type, fid) VALUES (22, 2, 1, 13);
INSERT INTO lines(id, ind, type, fid) VALUES (22, 3, 1, 63);
INSERT INTO lines(id, ind, type, fid) VALUES (22, 4, 1, 64);
INSERT INTO lines(id, ind, type, fid) VALUES (22, 5, 1, 5);
INSERT INTO lines(id, ind, type, fid) VALUES (22, 6, 1, 8);

INSERT INTO columns(yid, ind, lid) VALUES (8, 1, 25);
INSERT INTO columns(yid, ind, lid) VALUES (8, 2, 26);
INSERT INTO lines(id, ind, type, fid) VALUES (25, 1, 1, 20);
INSERT INTO lines(id, ind, type, fid) VALUES (25, 2, 1, 65);
INSERT INTO lines(id, ind, type, fid) VALUES (25, 3, 1, 55);
INSERT INTO lines(id, ind, type, fid) VALUES (25, 4, 1, 56);
INSERT INTO lines(id, ind, type, fid) VALUES (25, 5, 1, 14);
INSERT INTO lines(id, ind, type, fid) VALUES (25, 6, 1, 12);
INSERT INTO lines(id, ind, type, fid) VALUES (26, 1, 1, 22);
INSERT INTO lines(id, ind, type, fid) VALUES (26, 2, 1, 23);
INSERT INTO lines(id, ind, type, fid) VALUES (26, 3, 1, 66);
INSERT INTO lines(id, ind, type, fid) VALUES (26, 4, 1, 67);
INSERT INTO lines(id, ind, type, fid) VALUES (26, 5, 1, 9);
INSERT INTO lines(id, ind, type, fid) VALUES (26, 6, 1, 10);

INSERT INTO splits(left, right) VALUES (29, 30);
INSERT INTO columns(yid, ind, lid) VALUES (9, 1, 27);
INSERT INTO columns(yid, ind, lid) VALUES (9, 2, 28);
INSERT INTO columns(yid, ind, lid) VALUES (9, -1, 29);
INSERT INTO columns(yid, ind, lid) VALUES (9, -1, 30);
INSERT INTO lines(id, ind, type, fid) VALUES (27, 1, 1, 24);
INSERT INTO lines(id, ind, type, fid) VALUES (27, 2, 1, 37);
INSERT INTO lines(id, ind, type, fid) VALUES (27, 3, 2, 6);
INSERT INTO lines(id, ind, type, fid) VALUES (29, 1, 1, 42);
INSERT INTO lines(id, ind, type, fid) VALUES (29, 2, 1, 25);
INSERT INTO lines(id, ind, type, fid) VALUES (29, 3, 1, 32);
INSERT INTO lines(id, ind, type, fid) VALUES (30, 1, 1, 57);
INSERT INTO lines(id, ind, type, fid) VALUES (30, 2, 1, 58);
INSERT INTO lines(id, ind, type, fid) VALUES (28, 1, 1, 69);
INSERT INTO lines(id, ind, type, fid) VALUES (28, 2, 1, 68);
INSERT INTO lines(id, ind, type, fid) VALUES (28, 3, 1, 15);
INSERT INTO lines(id, ind, type, fid) VALUES (28, 4, 1, 16);
INSERT INTO lines(id, ind, type, fid) VALUES (28, 5, 1, 11);
