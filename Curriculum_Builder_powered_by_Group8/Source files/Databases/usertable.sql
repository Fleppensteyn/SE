DROP TABLE IF EXISTS users;
CREATE TABLE users (
  id    INTEGER PRIMARY KEY,  --SQLite auto-increments INTEGER PRIMARY KEY
  name  VARCHAR(50) UNIQUE,   --Usernames are unique
  pass  CHAR(40),             --SHA-1 string length
  class TINYINT(1)            --Access level, 1 for users, 2 for admins, 0 for banned
);
--Basic users, password for all of them is test
INSERT INTO users (name, pass, class) VALUES ("admin", "098e54957c0f375705110b53d88a01862596050c", 2);
INSERT INTO users (name, pass, class) VALUES ("user",  "f7e7b8e28dbb1abd15992af61c8c453214313e62", 1);
INSERT INTO users (name, pass, class) VALUES ("banned","f98b7d081749d000d2b0bf1202440af91042aae8", 0);
