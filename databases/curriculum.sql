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
  type TINYINT,
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

INSERT INTO curriculum (name) VALUES ("Test");
INSERT INTO curriculum (name) VALUES ("Toast");

INSERT INTO years (cid, ind, name) VALUES (1, 1, "Sub 1");
INSERT INTO years (cid, ind, name) VALUES (1, 2, "Sub 2");
INSERT INTO years (cid, ind, name) VALUES (2, 1, "Pls 1");
INSERT INTO years (cid, ind, name) VALUES (2, 2, "Pls 2");

INSERT INTO columns (yid, ind, lid) VALUES (1,1,1);
INSERT INTO columns (yid, ind, lid) VALUES (1,2,2);
INSERT INTO columns (yid, ind, lid) VALUES (2,1,3);
INSERT INTO columns (yid, ind, lid) VALUES (3,1,4);
INSERT INTO columns (yid, ind, lid) VALUES (3,2,5);
INSERT INTO columns (yid, ind, lid) VALUES (3,3,6);
INSERT INTO columns (yid, ind, lid) VALUES (4,1,7);
INSERT INTO columns (yid, ind, lid) VALUES (4,-1,8);
INSERT INTO columns (yid, ind, lid) VALUES (4,-1,9);

INSERT INTO lines (id, ind, type, fid) VALUES (1,1,1,1);
INSERT INTO lines (id, ind, type, fid) VALUES (1,2,1,2);
INSERT INTO lines (id, ind, type, fid) VALUES (1,3,1,3);
INSERT INTO lines (id, ind, type, fid) VALUES (1,4,1,4);
INSERT INTO lines (id, ind, type, fid) VALUES (2,1,1,5);
INSERT INTO lines (id, ind, type, fid) VALUES (2,2,1,6);
INSERT INTO lines (id, ind, type, fid) VALUES (2,3,1,7);
INSERT INTO lines (id, ind, type, fid) VALUES (2,4,1,8);
INSERT INTO lines (id, ind, type, fid) VALUES (3,1,1,9);
INSERT INTO lines (id, ind, type, fid) VALUES (3,2,1,10);
INSERT INTO lines (id, ind, type, fid) VALUES (4,1,1,11);
INSERT INTO lines (id, ind, type, fid) VALUES (4,2,1,12);
INSERT INTO lines (id, ind, type, fid) VALUES (5,1,1,13);
INSERT INTO lines (id, ind, type, fid) VALUES (5,2,1,14);
INSERT INTO lines (id, ind, type, fid) VALUES (6,1,1,15);
INSERT INTO lines (id, ind, type, fid) VALUES (6,2,1,16);
INSERT INTO lines (id, ind, type, fid) VALUES (7,1,1,17);
INSERT INTO lines (id, ind, type, fid) VALUES (7,2,2,1);
INSERT INTO lines (id, ind, type, fid) VALUES (8,1,1,18);
INSERT INTO lines (id, ind, type, fid) VALUES (8,2,1,19);
INSERT INTO lines (id, ind, type, fid) VALUES (9,1,1,20);

INSERT INTO splits (left, right) VALUES (8,9);

INSERT INTO choices (count, pick) VALUES (4,2);

INSERT INTO options (cid, course, ind) VALUES (1,21,1);
INSERT INTO options (cid, course, ind) VALUES (1,22,2);
INSERT INTO options (cid, course, ind) VALUES (1,23,3);
INSERT INTO options (cid, course, ind) VALUES (1,24,4);
