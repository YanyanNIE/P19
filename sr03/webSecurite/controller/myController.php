<?php
  require ('model/myModel.php');

  function isLoggedOn() {
      if(!isset($_SESSION["connected_user"]) || $_SESSION["connected_user"] == "") {
          // utilisateur non connecté
          require('view/login.php');
          return false;
      }
      return true;
  }

  function badaction() {
    require('view/erraction.php');
  }

  function authenticate($login, $mdp) {
      if ($login == "" || $mdp == "") {
          // manque login ou mot de passe
          $errmsg = "nullvalue";
          require('view/login.php');
      } else {
          $utilisateur = findUserByLoginPwd($login, $mdp);
          if ($utilisateur == false) {
            // echec authentification
            require('view/errauthent.php');
          } else {
            $_SESSION["connected_user"] = $utilisateur;
            require('view/accueil.php');
          }
      }
  }

  function home() {
      if (isLoggedOn()) {
        require('view/accueil.php');
      }
  }

  function clients() {
      if (isLoggedOn()) {
          $listeUsers = findAllUsers();
          require('view/ficheClient.php');
      }
  }

  function messages() {
      if (isLoggedOn()) {
          $listeUsers = findAllUsers();
          $messagesRecus = findMessagesInbox($_SESSION["connected_user"]["login_user"]);
          $messagesEnvoyes = findMessagesSentmails($_SESSION["connected_user"]["login_user"]);
          require('view/messagerie.php');
      }
  }

  function envoyerMessage($destinataire,$sujet,$corps) {
      if (isLoggedOn()) {
          addMessage($destinataire,$_SESSION["connected_user"]["login_user"],$sujet,$corps);
          $listeUsers = findAllUsers();
          $messagesRecus = findMessagesInbox($_SESSION["connected_user"]["login_user"]);
          $messagesEnvoyes = findMessagesSentmails($_SESSION["connected_user"]["login_user"]);
          require('view/messagerie.php');
      }
  }

  function virements() {
      if (isLoggedOn()) {
          $listeUsers = findAllUsers();
          require('view/virement.php');
      }
  }

  function effectuerVirement($emetteur,$beneficiaire,$montant) {
      if (isLoggedOn()) {
          // ici, il faut appeler une fonction du modèle qui enregistrera le virement
          transferMontant($emetteur,$beneficiaire,$montant);
          $virement_ok = true;
          require('view/virement.php');
      }
  }

  function disconnect() {
    unset($_SESSION["connected_user"]);
    require('view/login.php');
  }

?>
