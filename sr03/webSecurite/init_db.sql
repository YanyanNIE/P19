CREATE TABLE users (
    id_user VARCHAR(20) NOT NULL,
    login_user VARCHAR(100) NOT NULL,
    mdp VARCHAR(40) NOT NULL,
    profil_user VARCHAR(10) NOT NULL,
    nom VARCHAR(30),
    prenom VARCHAR(30),
    numero_compte VARCHAR(12),
    solde_compte FLOAT,
    CHECK (profil_user="CLIENT" OR profil_user="CONSEILLER"),
    PRIMARY KEY(id_user,login_user)
);

CREATE TABLE messages(
    id_msg VARCHAR(30) NOT NULL,
    id_user_to VARCHAR(20),
    id_user_from VARCHAR(20),
    sujet_msg VARCHAR(100),
    corps_msg VARCHAR(2000)
);

INSERT INTO users
VALUES( "u001001", "bon.x@gmail.com","bobx","CLIENT","x","bob","00100101",123.2);

INSERT INTO users
VALUES( "u001002", "alice.y@gmail.com","alicey","CLIENT","y","alice","00100102",600);

INSERT INTO users
VALUES( "u001003", "alex.z@gmail.com","alexz","CONSEILLER","z","alex","00100103",100);

INSERT INTO messages
VALUES( "m001001", "alex.z@gmail.com", "alice.y@gmail.com","sujet1","hello ,this is ....");