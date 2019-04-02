<?php
define('DB_HOST','127.0.0.1');
define('DB_USER','sr03');
define('DB_PASSWD','sr03sr03');
define('DB_NAME','td3');

function findUserByLoginPwd($login, $pwd) {
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);

  if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
      $utilisateur = false;
  } else {
      $req="select nom,prenom,login_user,id_user,numero_compte,profil_user,solde_compte from users where login_user='$login' and mdp='$pwd'";
      if (!$result = $mysqli->query($req)) {
          echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
          $utilisateur = false;
      } else {
          if ($result->num_rows === 0) {
            $utilisateur = false;
          } else {
            $utilisateur = $result->fetch_assoc();
          }
          $result->free();
      }
      $mysqli->close();
  }

  return $utilisateur;
}


function findAllUsers() {
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);

  $listeUsers = array();

  if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
  } else {
      $req="select nom,prenom,login_user,id_user,numero_compte,profil_user,solde_compte from users";
      if (!$result = $mysqli->query($req)) {
          echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
      } else {
          while ($unUser = $result->fetch_assoc()) {
            $listeUsers[$unUser['login_user']] = $unUser;
          }
          $result->free();
      }
      $mysqli->close();
  }

  return $listeUsers;
}


function findMessagesInbox($userid) {
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);

  $listeMessages = array();

  if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
  } else {
      $req="select id_msg,sujet_msg,corps_msg,u.nom,u.prenom from messages m, users u where id_user_from=u.login_user and id_user_to='$userid'";
      if (!$result = $mysqli->query($req)) {
          echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
      } else {
          while ($unMessage = $result->fetch_assoc()) {
            $listeMessages[$unMessage['id_msg']] = $unMessage;
          }
          $result->free();
      }
      $mysqli->close();
  }

  return $listeMessages;
}

function findMessagesSentmails($userid) {
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);

  $listeMessages = array();

  if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
  } else {
      $req="select id_msg,sujet_msg,corps_msg,u.nom,u.prenom from messages m, users u where id_user_to=u.login_user and id_user_from='$userid'";
      if (!$result = $mysqli->query($req)) {
          echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
      } else {
          while ($unMessage = $result->fetch_assoc()) {
            $listeMessages[$unMessage['id_msg']] = $unMessage;
          }
          $result->free();
      }
      $mysqli->close();
  }

  return $listeMessages;
}

function dropMessage($msgid) {
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);

  if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
  } else {
      $req="delete from messages where id_msg=".$msgid;
      if (!$result = $mysqli->query($req)) {
          echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
      }
      $mysqli->close();
  }

}

function randomKey($length){
  $rand = '';
  for($i=0;$i<$length;$i++){
    $rand .= chr(mt_rand(65,119));
  }
  return $rand;
}

function addMessage($to,$from,$subject,$body) {
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);
  $id = randomKey(8);

  if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
  } else {
      $req="insert into messages(id_msg,id_user_to,id_user_from,sujet_msg,corps_msg) values('$id','$to','$from','$subject','$body')";
      if (!$result = $mysqli->query($req)) {
          echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
      }
      $mysqli->close();
  }
}

function transferMontant($emetteur,$beneficiaire,$montant){
  $mysqli = new mysqli(DB_HOST, DB_USER, DB_PASSWD, DB_NAME);
  $montant = (float) $montant;
  if ($mysqli->connect_error) {
    echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
  } else {
    $req="update users set solde_compte = solde_compte - $montant where numero_compte = '$emetteur';
          update users set solde_compte = solde_compte + $montant where numero_compte = '$beneficiaire';";
    if (!$result = $mysqli->multi_query($req)) {
      echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
    } 
    $mysqli->close();
  }  
}
?>
