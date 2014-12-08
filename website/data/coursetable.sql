DROP TABLE IF EXISTS course;
CREATE TABLE course (
	id 				INTEGER PRIMARY KEY,
	course_number 	INT,
	course_name		VARCHAR(50),
	ects				INT,
	course_type		VARCHAR(50),
	affiliation		VARCHAR(50)
);