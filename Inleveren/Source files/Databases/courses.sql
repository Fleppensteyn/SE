DROP TABLE IF EXISTS affiliations;
CREATE TABLE affiliations (
  id      INTEGER PRIMARY KEY,
  name    VARCHAR(60),
  colour  CHAR(6)
);

DROP TABLE IF EXISTS course_types;
CREATE TABLE course_types (
  id      INTEGER PRIMARY KEY,
  name    VARCHAR(60),
  colour  CHAR(6)
);

DROP TABLE IF EXISTS courses;
CREATE TABLE courses (
  id      INTEGER PRIMARY KEY,
  name    VARCHAR(60),
  line    CHAR(2),
  number  CHAR(2),
  ects    INTEGER,
  affilid INTEGER REFERENCES affiliations(id),
  typeid  INTEGER REFERENCES course_types(id)
);

INSERT INTO affiliations (name, colour) VALUES ("Other","ffffff");
INSERT INTO affiliations (name, colour) VALUES ("Affiliated to CS","93cddd");
INSERT INTO affiliations (name, colour) VALUES ("Affiliated to Biology","c3d69b");
INSERT INTO affiliations (name, colour) VALUES ("Affiliated to Economics","b2a0c7");
INSERT INTO affiliations (name, colour) VALUES ("Programming Line","ff00ff");
INSERT INTO affiliations (name, colour) VALUES ("Algorithmics Line","00ff00");
INSERT INTO affiliations (name, colour) VALUES ("Foundations Line","3366ff");
INSERT INTO affiliations (name, colour) VALUES ("Computer Systems Line","ff0000");
INSERT INTO affiliations (name, colour) VALUES ("Software Engineering Line","ffff00");
INSERT INTO affiliations (name, colour) VALUES ("Computer Graphics Line","938953");

INSERT INTO course_types (name, colour) VALUES ("Academic Skills","fac090");
INSERT INTO course_types (name, colour) VALUES ("Mathematics","ffe599");
INSERT INTO course_types (name, colour) VALUES ("CS Essentials","d99593");
INSERT INTO course_types (name, colour) VALUES ("CS Mandatory","93cddd");
INSERT INTO course_types (name, colour) VALUES ("CS Elective","a9ecff");
INSERT INTO course_types (name, colour) VALUES ("Economics Essentials","b3a2c7");
INSERT INTO course_types (name, colour) VALUES ("Biology Essentials","c3d69b");

---Academic Skills
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Study Skills and Presenting","AS","1",3,1,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Orientation Computer Science & Economics","AS","2",3,4,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Orientation Computer Science","AS","2", 3,2,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Orientation Computer Science & Biology","AS","2", 3,3,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Trends and Literature Research","AS","3", 3,1,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Economics and Society","AS","4", 3,4,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Computer Science and Society","AS","4", 3,2,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Biology and Society","AS","4", 3,3,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Seminars","AS","5", 3,1,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Empirical Research","AS","6", 3,1,1);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Bachelor Project","AS","7", 15,1,1);
---Mathematics
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Statistics","M","5",6, 1, 2);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Logic","M","2",6, 2, 2);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Introduction Mathematics","M","1",6, 1, 2);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Advanced Mathematics 1","M","3",3, 1, 2);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Advanced Mathematics 2","M","4α",3, 2, 2);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Advanced Mathematics 2 ","M","4β",3, 3, 2);
---Computer Science Essentials
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Introduction to Programming","PR","1",6, 5, 3);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Foundations of Computer Science 1","FI","1",6, 7, 3);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Digital Techniques","CS","1",6, 8, 3);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Algorithmics & Data Structures 1","AL","1",6, 6, 3);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Databases","SE","1",6, 9, 3);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Programming 2","PR","2",6, 5, 3);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Data Mining ","AL","5",6, 6, 3);
---Computer Science Specific
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Algorithmics & Data Structures 2","AL","2",6, 6, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Concepts of Programming Languages","PR","3",6, 5, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Computer Architecture","CS","2",6, 8, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Computational Complexity","AL","4",6, 6, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Foundations of Computer Science 2","FI","2",6, 7, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Operating Systems","CS","3",6, 8, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Software Engineering","SE","2",6, 9, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Artificial Intelligence","AL","3",6, 6, 4);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("History of Computing ","C","1",3, 1, 4);
---Computer Science Electives
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Theory of Concurrency","FI","5",6, 7, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Programming and Correctness","FI","4",6, 7, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Foundations of Computer Science 3","FI","3",6, 7, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Natural Computing","AL","6",6, 6, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Compiler Construction","CS","4",6, 8, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Computer Graphics","CI","2",6, 10, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Computer Networks","CS","5",6, 8, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Security","SE","3",6, 9, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Human Computer Interaction β","CI","1",6, 10, 5);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Human Computer Interaction α ","SE","4",6, 9, 5);
---Economics Essentials
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Marketing","E","3",8, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Micro Economie","E","2",8, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Organisatie & strategie","E","4",8, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Integratie 1","E","5",5, 2, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Macro Economie","E","7",8, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Accounting","E","6",8, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Integratie 2 / Project Management","E","8",4, 2, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Finance","E","9",8, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Requirements Engineering","E","10",6, 9, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Business Information Systems","E","11",6, 1, 6);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Business Intelligence & Process Modeling ","E","12",6, 1, 6);
---Biology Essentials
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Biomedical Security","B","8",3, 2, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Moleculaire Biologie","B","9",6, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Molecular Design","B","14",12, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Natural Products","B","15",6, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Microbiologie","B","4",3, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Celfysiologie","B","3",3, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Celbiologie","B","2",3, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Moleculaire Genetica","B","1",5, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Basispracticum I&B","B","5",4, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Biochemie","B","6",6, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Bioethiek","B","7",3, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Moleculaire Genetica 2","B","10",6, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Celbiologie 2","B","11",6, 1, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Integratie: Informatica & Biologie","B","13",6, 2, 7);
INSERT INTO courses (name, line, number, ects, affilid, typeid) VALUES ("Integratie: Data Sharing","B","12",3, 2, 7);