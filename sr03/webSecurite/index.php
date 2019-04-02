<?php
  session_start();

  require('controller/myController.php');

  if (isset($_GET['action'])) {
      if ($_GET['action'] == 'authenticate') {
          authenticate($_GET['login'],$_GET['mdp']);
      } else if ($_GET['action'] == 'home') {
          home();
      } else if ($_GET['action'] == 'messagerie') {
          messages();
      } else if ($_GET['action'] == 'sendmsg') {
          envoyerMessage($_GET['destinataire'],$_GET['sujet'],$_GET['corps']);
      } else if ($_GET['action'] == 'virement') {
          virements();
      } else if ($_GET['action'] == 'dovirement') {
          effectuerVirement($_GET['emetteur'],$_GET['beneficiaire'],$_GET['montant']);
      } else if ($_GET['action'] == 'clients') {
          clients();
      } else if ($_GET['action'] == 'disconnect') {
          disconnect();
      } else {
          badaction();
      }
  }  else {
      // aucune action => accueil
      home();
  }

?>
